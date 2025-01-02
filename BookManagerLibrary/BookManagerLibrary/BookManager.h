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
	// å �߰�
	void addBook(const string& title, const string& author)
	{
		if (title.empty() || author.empty())
		{
			cout << "[����] �ùٸ� å ����� ���ڸ��� �Է��ϼ���." << endl;
			return;
		}
		
		books.push_back(Book(title, author));
		cout << "[�˸�]" << "�۰� : " << author << " å ���� : " << title << " å�� �߰��Ǿ����ϴ�." << endl;
	}

	// ��� å ���
	void displayAllBooks() const
	{
		if (books.empty())
		{
			cout << "[�˸�] ���� ��ϵ� å�� �����ϴ�." << endl;
			return;
		}

		cout << "=== ���� ���� ��� ===" << endl;
		for (size_t i = 0; i < books.size(); i++)
		{
			cout << i + 1 << ". " << books[i].GetTitle() << " by " << books[i].GetAuthor() << endl;
		}
	}

	// å �������� �˻�
	void searchByTitle(const string& title) const 
	{
		if (title.empty()) 
		{
			cout << "[����] �˻��� å ������ ��Ȯ�� �Է��ϼ���." << endl;
			return;
		}

		for (size_t i = 0; i < books.size(); ++i) 
		{
			if (books[i].GetTitle() == title) 
			{
				cout << "[�˻� ���] " << books[i].GetTitle() << " by " << books[i].GetAuthor() << endl;
				return; 
			}
		}
		cout << "[�˸�] �ش� ������ å�� ã�� �� �����ϴ�: " << title << endl;
	}

	// �۰��� �˻�
	void searchByAuthor(const string& author) const 
	{
		if (author.empty()) 
		{
			cout << "[����] �˻��� �۰����� ��Ȯ�� �Է��ϼ���." << endl;
			return;
		}

		bool found = false;
		for (size_t i = 0; i < books.size(); ++i) 
		{
			if (books[i].GetAuthor() == author) 
			{
				if (!found) 
				{
					cout << "[�˻� ���] '" << author << "' �۰��� å ���:" << endl;
				}
				cout << " - " << books[i].GetTitle() << endl;
				found = true;
			}
		}
		if (!found) 
		{
			cout << "[�˸�] '" << author << "' �۰��� å�� ã�� �� �����ϴ�." << endl;
		}
	}
private:
	vector<Book> books; // Book ��ü�� ��� ����

};

void printMenu()
{
	cout << "\n=== ������ ���� ���α׷� ===" << endl;
	cout << "1. å �߰�" << endl;
	cout << "2. ��� å ���" << endl;
	cout << "3. å �������� �˻�" << endl;
	cout << "4. �۰��� �˻�" << endl;
	cout << "5. ����" << endl;
	cout << "����: ";
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
			// ���� �̿��� �� ó��
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "[����] ���ڷ� �Է��� �ּ���." << endl;
			continue;
		}

		if (choice == 1)
		{
			// å �߰�
			cin.ignore(); // ���� ����
			cout << "å ����: ";
			string title;
			getline(cin, title);

			cout << "å ����: ";
			string author;
			getline(cin, author);

			manager.addBook(title, author);

		}
		else if (choice == 2)
		{
			// ��� å ���
			manager.displayAllBooks();

		}
		else if (choice == 3)
		{
			// å �������� �˻�
			cin.ignore();
			cout << "�˻��� å ����: ";
			string searchTitle;
			getline(cin, searchTitle);

			manager.searchByTitle(searchTitle);

		}
		else if (choice == 4)
		{
			// �۰��� �˻�
			cin.ignore();
			cout << "�˻��� �۰���: ";
			string searchAuthor;
			getline(cin, searchAuthor);

			manager.searchByAuthor(searchAuthor);

		}
		else if (choice == 5)
		{
			// ����
			cout << "���α׷��� �����մϴ�." << endl;
			break;
		}
		else
		{
			cout << "[����] �޴��� ���� ��ȣ�Դϴ�. �ٽ� �õ��ϼ���." << endl;
		}
	}

	return 0;
}
