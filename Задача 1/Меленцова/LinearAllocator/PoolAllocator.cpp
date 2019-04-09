#include "PoolAllocator.h" 

PoolAllocator::PoolAllocator(size_t objectSize, u8 objectAlignment, size_t size, void* mem)
{
	assert(objectSize >= sizeof(void*));
	_objectAlignment = objectAlignment;
	_objectSize = objectSize;
	_size = size;
	_used_memory = 0;
	_num_allocations = 0;

	//Calculate adjustment needed to keep object correctly aligned 
	u8 adjustment = pointer_math::alignForwardAdjustment(mem, objectAlignment);
	_free_list = (void**)pointer_math::add(mem, adjustment);
	size_t numObjects = (size - adjustment) / objectSize;
	void** p = _free_list;

	//Initialize free blocks list 
	for (size_t i = 0; i < numObjects - 1; i++)
	{
		*p = pointer_math::add(p, objectSize);
		p = (void**)*p;
	}

	*p = nullptr;
}

PoolAllocator::~PoolAllocator()
{
	_free_list = nullptr;
}

void* PoolAllocator::allocate(size_t size, u8 alignment)
{
	assert(size == _objectSize && alignment == _objectAlignment);
	if (_free_list == nullptr) return nullptr;
	void* p = _free_list;
	_free_list = (void**)(*_free_list);
	_used_memory += size;
	_num_allocations++;
	return p;
}

void PoolAllocator::deallocate(void* p)
{
	*((void**)p) = _free_list;
	_free_list = (void**)p;
	_used_memory -= _objectSize;
	_num_allocations--;
}