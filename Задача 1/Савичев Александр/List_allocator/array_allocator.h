#pragma once
#include <stdexcept>
#include <vector>
#include "allocator_interface.h"
#include <cstdlib>

template<class T>
class array_allocator : allocator_interface<T>
{
	T* inner;
	int capacity;
	std::vector<int> used_indexes;

	void enlarge()
	{
		const auto new_capacity = capacity * 2;
		//const auto new_inner = new T[new_capacity];
		auto new_inner = (T*)malloc(new_capacity * sizeof(T));
		for (auto i = 0; i < capacity; i++)
			new_inner[i] = inner[i];
		free(inner);
		capacity = new_capacity;
		inner = new_inner;
	}

	/*struct indexer
	{
		array_allocator& a;
		int index;
		indexer(array_allocator& a, const int index) : a(a), index(index) {}

		explicit operator int() const
		{
			return a.get(index);
		}
	
		T & operator=(const T& value) const
		{
			a.set(index, value);
			return a.inner[index];
		}
	};*/

public:
	int length;

	array_allocator()
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
		used_indexes.push_back(index);
	}

	void push_back(const T value) override
	{
		//used_indexes.push_back(length);
		set(length, value);
	}

	T pop_back() override
	{
		if (used_indexes.empty())
			throw std::out_of_range("out of range");
		const auto index = used_indexes[used_indexes.size() - 1];
		const auto value = get(index);
		used_indexes.pop_back();
		if (used_indexes.empty())
			length = 0;
		else
			length = used_indexes[used_indexes.size() - 1] + 1;
		return value;
	}

	void remove_all()
	{
		length = 0;
	}

	~array_allocator()
	{
		free(inner);
	}
};
