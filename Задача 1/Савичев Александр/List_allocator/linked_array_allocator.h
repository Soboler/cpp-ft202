#pragma once
#include "allocator_interface.h"
#include <vector>
#include <memory>

template<class T>
struct block
{
	int size = 0;
	T* elements = nullptr;
	block<T>* next = nullptr;

	block()
	{
	}

	explicit block(const int size)
	{
		elements = (T*)malloc(size * sizeof(T));
		this->size = size;
	}

	~block()
	{
		free(elements);
		if (next)
			delete next;
		next = nullptr;
	}
};

template<class T>
class linked_array_allocator : public allocator_interface<T>
{
	block<T>* first;
	block<T>* last;
	int capacity;
	int length;

	void enlarge()
	{
		auto new_block = new block<T>(capacity);
		last->next = new_block;
		last = new_block;
		capacity *= 2;
	}

	T* get_ptr_to_elem(int index)
	{
		auto current_block = first;
		auto counter = current_block->size;
		while (counter <= index)
		{
			current_block = current_block->next;
			counter += current_block->size;
		}

		auto pos = index - counter + current_block->size;
		return current_block->elements + pos;
	}

public:
	linked_array_allocator()
	{
		length = 0;
		capacity = 2;
		first = new block<T>(capacity);
		last = first;
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
		return *get_ptr_to_elem(index);
	}

	void set(const int index, const T value) override
	{
		while (index >= capacity)
			enlarge();
		auto ptr = get_ptr_to_elem(index);
		(*ptr) = value;
		length = index + 1;
	}

	void remove_all()
	{
		length = 0;
	}

	~linked_array_allocator()
	{
		delete first;
	}

	int size() override
	{
		return length;
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
		auto copy = new T[capacity];
		auto ptr = copy;
		auto current_block = first;
		while (current_block)
		{
			ptr = (T*)memcpy(ptr, current_block->elements, current_block->size * sizeof(T));
			ptr += current_block->size;
			current_block = current_block->next;
		}
		return copy;
	}

	std::string class_name() override
	{
		return "linked_array_allocator";
	}
};
