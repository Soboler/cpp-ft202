#pragma once
#include "node.h"

const int min_level_size = 32;

class buddy_allocator
{
	node* tree;
	int min_level;
	void* memory;
	size_t memory_size;

	static int get_power_of_two(int number);

	int get_level(size_t size) const;

public:
	buddy_allocator(size_t size);

	void* alloc(size_t size) const;
	void free(void* ptr) const;

	~buddy_allocator();

	void print_memory_tree() const;
	void dump() const;
};
