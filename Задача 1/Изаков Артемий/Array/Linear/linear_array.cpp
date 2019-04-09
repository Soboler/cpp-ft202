#include "pch.h"
#include "linear_array.h"
#include <stdexcept>

using namespace std;

void linear_array::enlarge()
{
	capacity *= 2;
	const auto new_inner = (int*)realloc(inner, capacity * sizeof(int));
	inner = new_inner;
}

void linear_array::check_index(const int index) const
{
	if (index < 0 || index >= length)
		throw out_of_range("index out of range");
}

linear_array::linear_array()
{
	length = 0;
	capacity = 2;
	inner = (int*)malloc(capacity * sizeof(int));
}

int linear_array::get(const int index) const
{
	if (index >= capacity)
		throw out_of_range("index out of range");
	return inner[index];
}

void linear_array::set(const int index, const int value) const
{
	check_index(index);
	inner[index] = value;
}

void linear_array::push_back(const int value)
{
	length++;
	while (length > capacity)
		enlarge();
	inner[length - 1] = value;
}

int linear_array::pop_back()
{
	if (length == 0)
		throw out_of_range("no elements left");
	length--;
	return get(length);
}

void linear_array::remove_all()
{
	length = 0;
	capacity = 1;
	enlarge();
}

linear_array::~linear_array()
{
	free(inner);
}
