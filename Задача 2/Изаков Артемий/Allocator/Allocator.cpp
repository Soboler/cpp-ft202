#include <iostream>
#include "buddy_allocator.h"

int main()
{
	auto allocator = new buddy_allocator(1000);
	allocator->dump();

	auto a = allocator->alloc(50);
	allocator->dump();

	auto b = allocator->alloc(100);
	allocator->dump();

	allocator->free(a);
	allocator->dump();

	allocator->free(b);
	allocator->dump();

	//allocator->print_memory_tree();

	delete allocator;
}
