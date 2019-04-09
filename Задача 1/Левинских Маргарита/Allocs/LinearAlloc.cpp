#include "pch.h"
#include <iostream>
using namespace std;


class Arr
{
	int *arr;
	size_t capacity;
	size_t size;
	size_t last;

public:
	Arr()
	{
		initialize();
	}

	void initialize()
	{
		capacity = pow(2, 22); // 1 Гб памяти
		size = capacity / sizeof(int); // кол-во элементов
		last = 0; // последний заполненный элемент
		arr = (int*)malloc(capacity);
	}

	int get(int index)
	{
		if (check_boundaries(index))
		{
			return arr[index];
		}
	}

	void set(int index, int value)
	{
		while (!check_boundaries(index))
		{
			extend();
		}
		while (last <= index)
		{
			last++;
			arr[last] = INT32_MIN;
		}
		arr[index] = value;
	}

	int operator[](int index)
	{
		return get(index);
	}

	int pop_back()
	{
		if (last == 0)
		{
			throw out_of_range("No items");
		}
		int elem = arr[last - 1];
		arr[last - 1] = INT32_MIN;
		while (arr[last - 1] == INT32_MIN)
		{
			last -= 1;
			if (last == 0)
			{
				break;
			}
		}
		return elem;
	}

	void push_back(int value)
	{
		if (last == size)
		{
			extend();
		}
		last += 1;
		arr[last - 1] = value;
	}

	void remove_all()
	{
		delete[] arr;
		initialize();
	}

	~Arr()
	{
		delete[] arr;
	}

private:

	void extend()
	{
		capacity = 2 * capacity;
		int *newarr = (int*)malloc(capacity);
		memcpy(newarr, arr, size);
		size = capacity / sizeof(int);
		delete[] arr;
		arr = newarr;
	}

	bool check_boundaries(int index)
	{
		if (index > size - 1 || index < 0)
		{
			throw out_of_range("Index was out of range");
		}
		return true;
	}
};

int main()
{
	Arr* a = new Arr();
	a->push_back(100);
	a->set(5, 111);
}