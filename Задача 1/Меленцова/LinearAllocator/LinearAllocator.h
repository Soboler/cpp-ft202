#pragma once

#include <cassert>
#include "PointerMath.h"

// using namespace pointer_math;

class LinearAllocator
{
public:

	LinearAllocator(size_t size, void* start);
	~LinearAllocator();

	void* allocate(size_t size, u8 alignment);
	void deallocate(void* p);
	void clear();

protected:

	void* _start;
	size_t _size;
	size_t _used_memory;
	size_t _num_allocations;

private:

	LinearAllocator(const LinearAllocator&);

	//Prevent copies because it might cause errors 
	LinearAllocator& operator=(const LinearAllocator&);
	void* _current_pos;
};
