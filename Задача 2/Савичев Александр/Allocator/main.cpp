#include "pch.h"
#include <iostream>
#include "buddy_allocator.h"

int main()
{
	const auto allocator = new buddy_allocator(500);
	allocator->dump();

	const auto first = allocator->alloc(64);
	allocator->dump();

	const auto second = allocator->alloc(150);
	allocator->dump();

	allocator->free(first);
	allocator->dump();

	allocator->free(second);
	allocator->dump();

	delete allocator;
	return 0;
}
