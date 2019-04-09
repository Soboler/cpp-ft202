#include "LinearAllocator.h"

LinearAllocator::LinearAllocator(size_t size, void* start) {
	assert(size > 0);
	_start = start;
	_size = size;
	_used_memory = 0;
	_num_allocations = 0;
	_current_pos = start;
}

LinearAllocator::~LinearAllocator() {
	assert(_num_allocations == 0 && _used_memory == 0);
	_start = nullptr; _size = 0;
	_current_pos = nullptr;
}

void* LinearAllocator::allocate(size_t size, u8 alignment)
{
	assert(size != 0);
	u8 adjustment = pointer_math::alignForwardAdjustment(_current_pos, alignment);

	if (_used_memory + adjustment + size > _size) return nullptr;

	uptr aligned_address = (uptr)_current_pos + adjustment;
	_current_pos = (void*)(aligned_address + size);
	_used_memory += size + adjustment;
	_num_allocations++;

	return (void*)aligned_address;
}

void LinearAllocator::deallocate(void* p)
{
	assert(false && "Use clear() instead");
}

void LinearAllocator::clear()
{
	_num_allocations = 0;
	_used_memory = 0;
	_current_pos = _start;
}

LinearAllocator & LinearAllocator::operator=(const LinearAllocator &)
{
	return *this;
}
