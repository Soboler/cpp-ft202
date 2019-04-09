#pragma once

#include <cassert>
#include "PointerMath.h"

class PoolAllocator
{
public:
	PoolAllocator(size_t objectSize, u8 objectAlignment, size_t size, void* mem);
	~PoolAllocator();
	void* allocate(size_t size, u8 alignment);
	void deallocate(void* p);

protected:
	size_t _size;
	size_t _used_memory;
	size_t _num_allocations;

private:

	PoolAllocator(const PoolAllocator&);

	//Prevent copies because it might cause errors 
	PoolAllocator& operator=(const PoolAllocator&); size_t _objectSize;

	u8 _objectAlignment;
	void** _free_list;

};