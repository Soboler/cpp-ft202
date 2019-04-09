#pragma once
#include "allocator_interface.h"

template<class T>
class array_tight_allocator : public allocator_interface<T>
{
	T* elements;

public:
	array_tight_allocator()
	{
		
	}

	T pop_back() override
	{

	}


	T get(int index) override
	{
	}

	void set(int index, T value) override
	{
	}

	void push_back(T value) override
	{
	}
};
