#include "StackAllocator.h" 

StackAllocator::StackAllocator(size_t size, void* start) 
{
	assert(size > 0);
	_start = start;
	_size = size;
	_used_memory = 0;
	_num_allocations = 0;
	_current_pos = start;
	_prev_position = nullptr;

}

StackAllocator::~StackAllocator()
{
	_prev_position = nullptr;
	_current_pos = nullptr;
}

void* StackAllocator::allocate(size_t size, u8 alignment)
{
	assert(size != 0);
	//вычисляем корректировку с вершиной стека, размер + хэдер(выравнивание + заголовок),
	//в заголовке размер корректировки и адрес предыдущее распределение
	u8 adjustment = pointer_math::alignForwardAdjustmentWithHeader(_current_pos, alignment, sizeof(AllocationHeader));

	if (_used_memory + adjustment + size > _size) return nullptr;

	void* aligned_address = pointer_math::add(_current_pos, adjustment);
	//Add Allocation Header 
	AllocationHeader* header = (AllocationHeader*)(pointer_math::subtract(aligned_address, sizeof(AllocationHeader)));
	header->adjustment = adjustment;

	header->prev_address = _prev_position;
	_prev_position = aligned_address;

	_current_pos = pointer_math::add(aligned_address, size);
	_used_memory += size + adjustment;
	_num_allocations++;

	return aligned_address;
};

void StackAllocator::deallocate(void* p)
{
	assert(p == _prev_position);

	//Access the AllocationHeader in the bytes before p 
	AllocationHeader* header = (AllocationHeader*)(pointer_math::subtract(p, sizeof(AllocationHeader)));
	_used_memory -= (uptr)_current_pos - (uptr)p + header->adjustment;
	_current_pos = pointer_math::subtract(p, header->adjustment);
	_prev_position = header->prev_address;
	_num_allocations--;
}

StackAllocator & StackAllocator::operator=(const StackAllocator &)
{
	return *this;
}