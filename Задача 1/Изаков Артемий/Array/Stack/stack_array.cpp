#include "pch.h"
#include "stack_array.h"

#include <stdexcept>

using namespace std;

void stack_array::enlarge()
{
	capacity *= 2;
	const auto new_inner = (int*)realloc(inner, capacity * sizeof(int));
	inner = new_inner;
}

void stack_array::check_index(const int index) const
{
	if (index < 0 || index >= length)
		throw out_of_range("index out of range");
}

stack_array::stack_array()
{
	length = 0;
	capacity = 2;
	inner = (int*)malloc(capacity * sizeof(int));
}

void stack_array::push_back(const int value)
{
	length++;
	while (length > capacity)
		enlarge();
	inner[length - 1] = value;
}

int stack_array::pop_back()
{
	if (length == 0)
		throw out_of_range("no elements left");
	length--;
	return inner[length];
}

void stack_array::remove_all()
{
	length = 0;
	capacity = 1;
	enlarge();
}

stack_array::~stack_array()
{
	free(inner);
}
