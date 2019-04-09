#include "pch.h"
#include "LinearArray.h"
using namespace std;


LinearArr::LinearArr(int n)
{
	last = 0;
	size = n;
	arr = (int*)malloc(n * sizeof(int));
}

int LinearArr::get(int index)
{
	if (check_boundaries(index))
	{
		return arr[index];
	}
}

void LinearArr::set(int index, int value)
{
	while (!check_boundaries(index))
	{
		extend();
	}
	while (index + 1 > last)
	{
		last += 1;
		arr[last] = INT32_MIN;
	}
	arr[index] = value;
}

int LinearArr::pop_back()
{
	if (last == 0)
	{
		throw out_of_range("No items");
	}
	int elem = arr[last - 1];
	arr[last - 1] = INT32_MIN;
	while (arr[last - 1] == INT32_MIN && last != 0)
	{
		last -= 1;
	}
	return elem;
}

int LinearArr::operator[](int index)
{
	return get(index);
}

void LinearArr::push_back(int value)
{
	if (last == size)
	{
		extend();
	}
	last += 1;
	arr[last - 1] = value;
}

void LinearArr::remove_all()
{
	delete[] arr;
	arr = (int*)malloc(size * sizeof(int));
}

void LinearArr::extend()
{
	int *newarr = (int*)malloc(2 * size * sizeof(int));
	memcpy(newarr, arr, size);
	size *= 2;
	delete[] arr;
	arr = newarr;
}

bool LinearArr::check_boundaries(int index)
{
	if (index > size - 1 || index < 0)
	{
		return false;
	}
	return true;
}