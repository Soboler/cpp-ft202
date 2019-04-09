#pragma once

#include <cassert>
#include "PointerMath.h"

class StackAllocator
{
public:

	StackAllocator(size_t size, void* start);
	~StackAllocator();

	void* allocate(size_t size, u8 alignment);
	void deallocate(void* p);

protected:

	void* _start;
	size_t _size;
	size_t _used_memory;
	size_t _num_allocations;

private:

	StackAllocator(const StackAllocator&);

	//Prevent copies because it might cause errors 
	StackAllocator& operator=(const StackAllocator&);

	struct AllocationHeader
	{
		void* prev_address;
		u8 adjustment;
	};

	void* _prev_position;
	void* _current_pos;

};