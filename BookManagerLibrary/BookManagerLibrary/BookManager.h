#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book
{
private:
	string title;
	string author;

public:
	Book(const string& title, const string& author) : title(title), author(author)
	{
	}

	string GetTitle() const { return title; }
	string GetAuthor() const { return author; }
};

class BookManager
{

public:
	// 책 추가
	void addBook(const string& title, const string& author)
	{
		if (title.empty() || author.empty())
		{
			cout << "[오류] 올바른 책 제목과 저자명을 입력하세요." << endl;
			return;
		}
		
		books.push_back(Book(title, author));
		cout << "[알림]" << "작가 : " << author << " 책 제목 : " << title << " 책이 추가되었습니다." << endl;
	}

	// 모든 책 출력
	void displayAllBooks() const
	{
		if (books.empty())
		{
			cout << "[알림] 현재 등록된 책이 없습니다." << endl;
			return;
		}

		cout << "=== 현재 도서 목록 ===" << endl;
		for (size_t i = 0; i < books.size(); i++)
		{
			cout << i + 1 << ". " << books[i].GetTitle() << " by " << books[i].GetAuthor() << endl;
		}
	}

	// 책 제목으로 검색
	void searchByTitle(const string& title) const 
	{
		if (title.empty()) 
		{
			cout << "[오류] 검색할 책 제목을 정확히 입력하세요." << endl;
			return;
		}

		for (size_t i = 0; i < books.size(); ++i) 
		{
			if (books[i].GetTitle() == title) 
			{
				cout << "[검색 결과] " << books[i].GetTitle() << " by " << books[i].GetAuthor() << endl;
				return; 
			}
		}
		cout << "[알림] 해당 제목의 책을 찾을 수 없습니다: " << title << endl;
	}

	// 작가로 검색
	void searchByAuthor(const string& author) const 
	{
		if (author.empty()) 
		{
			cout << "[오류] 검색할 작가명을 정확히 입력하세요." << endl;
			return;
		}

		bool found = false;
		for (size_t i = 0; i < books.size(); ++i) 
		{
			if (books[i].GetAuthor() == author) 
			{
				if (!found) 
				{
					cout << "[검색 결과] '" << author << "' 작가의 책 목록:" << endl;
				}
				cout << " - " << books[i].GetTitle() << endl;
				found = true;
			}
		}
		if (!found) 
		{
			cout << "[알림] '" << author << "' 작가의 책을 찾을 수 없습니다." << endl;
		}
	}
private:
	vector<Book> books; // Book 객체를 담는 벡터

};

void printMenu()
{
	cout << "\n=== 도서관 관리 프로그램 ===" << endl;
	cout << "1. 책 추가" << endl;
	cout << "2. 모든 책 출력" << endl;
	cout << "3. 책 제목으로 검색" << endl;
	cout << "4. 작가로 검색" << endl;
	cout << "5. 종료" << endl;
	cout << "선택: ";
}

int main() {
	BookManager manager;

	while (true)
	{
		printMenu();

		int choice;
		cin >> choice;

		if (cin.fail())
		{
			// 숫자 이외의 값 처리
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "[오류] 숫자로 입력해 주세요." << endl;
			continue;
		}

		if (choice == 1)
		{
			// 책 추가
			cin.ignore(); // 버퍼 정리
			cout << "책 제목: ";
			string title;
			getline(cin, title);

			cout << "책 저자: ";
			string author;
			getline(cin, author);

			manager.addBook(title, author);

		}
		else if (choice == 2)
		{
			// 모든 책 출력
			manager.displayAllBooks();

		}
		else if (choice == 3)
		{
			// 책 제목으로 검색
			cin.ignore();
			cout << "검색할 책 제목: ";
			string searchTitle;
			getline(cin, searchTitle);

			manager.searchByTitle(searchTitle);

		}
		else if (choice == 4)
		{
			// 작가로 검색
			cin.ignore();
			cout << "검색할 작가명: ";
			string searchAuthor;
			getline(cin, searchAuthor);

			manager.searchByAuthor(searchAuthor);

		}
		else if (choice == 5)
		{
			// 종료
			cout << "프로그램을 종료합니다." << endl;
			break;
		}
		else
		{
			cout << "[오류] 메뉴에 없는 번호입니다. 다시 시도하세요." << endl;
		}
	}

	return 0;
}
