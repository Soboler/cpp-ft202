#include "pch.h"
#include "StackArray.h""
using namespace std;

StackArr::StackArr(int n)
{
	last = 0;
	size = n;
	arr = (int*)malloc(n * sizeof(int));
}

int StackArr::pop_back()
{
	if (last == 0)
	{
		throw out_of_range("No items");
	}
	int elem = arr[last - 1];
	last -= 1;
	return elem;
}

void StackArr::push_back(int value)
{
	if (last == size)
	{
		extend();
	}
	last += 1;
	arr[last - 1] = value;
}

void StackArr::remove_all()
{
	delete[] arr;
	last = 0;
	arr = (int*)malloc(size * sizeof(int));
}

void StackArr::extend()
{
	int *newarr = (int*)malloc(2 * size * sizeof(int));
	memcpy(newarr, arr, size);
	size *= 2;
	delete[] arr;
	arr = newarr;
}