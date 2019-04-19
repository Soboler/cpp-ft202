#include "pch.h"
#include <iostream>

using namespace std;

class Allocator
{
private:
	size_t* start;
	size_t length;
	size_t value;
	Allocator* left;
	Allocator* right;
	bool is_filled;

public:
	Allocator(size_t size)
	{
		start = &size;
		length = size;
		is_filled = false;
	}

	Allocator(size_t* start, size_t length)
	{
		this->start = start;
		this->length = length;
	}

	void* Alloc(size_t size)
	{
		if (left == nullptr)
			left = new Allocator(start, length / 2);
		if (right == nullptr)
			right = new Allocator(start + length / 2, length / 2);

		if (size > length / 2)
		{
			is_filled = true;
			value = size;
			return start;
		}

		if (!left->is_filled)
			return left->Alloc(size);
		if (!right->is_filled)
			return right->Alloc(size);
	}

	void Free(void *ptr)
	{
		if (left != nullptr)
		{
			if (left->start == ptr)
			{
				left = nullptr;
				return;
			}
			left->Free(ptr);
		}
		if (start == ptr)
			is_filled = false;
		if (right != nullptr)
		{
			if (right->start == ptr)
			{
				right = nullptr;
				return;
			}
			right->Free(ptr);
		}
	}

	void Dump()
	{
		if (left != nullptr)
			left->Dump();
		if (is_filled)
			cout << start << " " << value << endl;
		if (right != nullptr)
			right->Dump();
	}
};

int main()
{
	auto a = Allocator(1024);
	a.Alloc(256);
	a.Alloc(128);
	a.Alloc(32);
	a.Alloc(32);
	a.Alloc(64);
	a.Alloc(60);
	a.Dump();
}