#include "buddy_allocator.h"
#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;

int buddy_allocator::get_power_of_two(const int number)
{
	auto result = 1;
	while (result < number)
		result *= 2;
	return result;
}

int buddy_allocator::get_level(const size_t size) const
{
	return (int)log2((double)memory_size / size);
}

buddy_allocator::buddy_allocator(const size_t size)
{
	memory_size = get_power_of_two(size);
	memory = malloc(memory_size);
	tree = new node(memory, 0, memory_size, min_level_size);
	min_level = get_level(min_level_size);
}

void* buddy_allocator::alloc(const size_t size) const
{
	if (size > memory_size)
		throw invalid_argument("size");

	const auto real_size = get_power_of_two(size);
	const auto level = get_level(real_size);

	const auto result = tree->allocate(level);
	if (result == nullptr)
		throw out_of_range("all memory is occupied");
	return result;
}

void buddy_allocator::free(void* ptr) const
{
	tree->get(ptr)->free();
}

buddy_allocator::~buddy_allocator()
{
	delete tree;
	::free(memory);
}

void buddy_allocator::print_memory_tree() const
{
	tree->print();
}

void buddy_allocator::dump() const
{
	cout << "[";
	tree->print_memory(tree->is_free);
	cout << "]\n";
}
