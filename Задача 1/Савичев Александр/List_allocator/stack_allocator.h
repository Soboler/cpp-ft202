#pragma once
#include "allocator_interface.h"
#include <cstdlib>
#include <vector>

template<class T>
class stack_allocator : public allocator_interface<T>
{
	T* inner;
	int capacity;
	int length;

	void enlarge()
	{
		capacity *= 2;
		auto new_inner = (T*)realloc(inner, capacity * sizeof(T));
		inner = new_inner;
	}

protected:
	T get(const int index) override
	{
		if (index >= length || index < 0)
			throw std::out_of_range("out of range");
		return inner[index];
	}

	void set(const int index, const T value) override
	{
		while (index >= capacity)
			enlarge();
		inner[index] = value;
	}

public:
	stack_allocator()
	{
		length = 0;
		capacity = 2;
		inner = (T*)malloc(capacity * sizeof(T));
	}

	void push_back(const T value) override
	{
		set(length, value);
		length++;
	}

	T pop_back() override
	{
		auto ret = get(length - 1);
		length--;
		return ret;
	}

	void remove_all()
	{
		length = 0;
	}

	~stack_allocator()
	{
		free(inner);
	}

	int size() override
	{
		return length;
	}

	T* all_elements() override
	{
		auto copy = new T[length];
		memcpy(copy, inner, length * sizeof(T));
		return copy;
	}

	std::string class_name() override
	{
		return "stack_allocator";
	}
};
