#pragma once
#include <stdexcept>
#include "allocator_interface.h"
#include <cstdlib>

template<class T>
class linear_allocator : public allocator_interface<T>
{
	T* inner;
	int capacity;
	int length;

	void enlarge()
	{
		const auto new_capacity = capacity * 2;
		auto new_inner = (T*)malloc(new_capacity * sizeof(T));
		for (auto i = 0; i < capacity; i++)
			new_inner[i] = inner[i];
		free(inner);
		capacity = new_capacity;
		inner = new_inner;
	}

public:
	linear_allocator()
	{
		length = 0;
		capacity = 2;
		inner = (T*)malloc(capacity * sizeof(T));
	}

	T& operator [] (const int index)
	{
		T res = get(index);
		return res;
	}

	T get(const int index) override
	{
		if (index >= length)
			throw std::out_of_range("out of range");
		return inner[index];
	}

	void set(const int index, const T value) override
	{
		while (index >= capacity)
			enlarge();
		length = index + 1;
		inner[index] = value;
	}

	int size() override
	{
		return length;
	}

	void remove_all()
	{
		length = 0;
	}

	~linear_allocator()
	{
		free(inner);
	}

	void push_back(T value) override
	{
		set(length, value);
	}

	T pop_back() override
	{
		auto value = get(length - 1);
		length--;
		return value;
	}

	T* all_elements() override
	{
		auto copy = new T[length];
		memcpy(copy, inner, length * sizeof(T));
		return copy;
	}

	std::string class_name() override
	{
		return "linear_allocator";
	}
};
