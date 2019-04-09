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
		last = 0; // верхушка стека
		arr = (int*)malloc(capacity);
	}

	int pop_back()
	{
		if (last == 0)
		{
			throw out_of_range("No items");
		}
		int elem = arr[last - 1];
		last--;
		return elem;
	}

	void push_back(int value)
	{
		if (last == size)
		{
			extend();
		}
		last++;
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
};