#include <iostream>

template <typename T>
class SimpleVector
{
public:
	SimpleVector()
	{
		data = new T[10];
	}
	SimpleVector(int capacity = 10) : currentSize(0), currentCapacity(capacity)
	{
		data = new T[currentCapacity];
	}

	~SimpleVector()
	{
		delete[] data;
	}

	void push_back(const T& value)
	{
		if (currentSize < currentCapacity)
		{
			data[currentSize] = value;
			currentSize++;
		}
	}

	void pop_back()
	{
		if (currentSize > 0)
		{
			currentSize--;
		}
	}

	int size() const
	{
		return currentSize;
	}

	void resize(int newCapacity)
	{
		if (newCapacity <= currentSize)
		{
			return;
		}

		T* newData = new T[newCapacity];

		// 기존 원소들을 새 배열에 복사
		for (int i = 0; i < currentSize; ++i)
		{
			newData[i] = data[i];
		}

		delete[] data;

		data = newData;
		currentCapacity = newCapacity;
	}

	int capacity() const
	{
		return currentCapacity;
	}

private:
	T* data;
	int currentSize;
	int currentCapacity;
};
