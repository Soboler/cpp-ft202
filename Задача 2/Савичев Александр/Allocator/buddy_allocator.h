#pragma once
#include "node.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

const int min_memory_size = 32;

class buddy_allocator
{
	node* tree_;
	int tree_height_;
	void* memory_;
	size_t memory_size_;

	static int get_power_of_2(int v)
	{
		v--;
		v |= v >> 1;
		v |= v >> 2;
		v |= v >> 4;
		v |= v >> 8;
		v |= v >> 16;
		return ++v;
	}

	int get_level(const size_t size) const
	{
		auto start_order = 1;
		const auto memory_count = memory_size_ / size;
		auto order = 0;
		while (start_order < memory_count)
		{
			start_order <<= 1;
			order++;
		}
		return order;
	}

public:
	explicit buddy_allocator(const size_t size)
	{
		memory_size_ = get_power_of_2(size);
		memory_ = malloc(memory_size_);
		tree_ = new node(memory_, 0, memory_size_, min_memory_size);
		tree_height_ = get_level(min_memory_size);
	}

	void* alloc(const size_t size) const
	{
		if (size > memory_size_)
			throw std::invalid_argument("size");

		const auto real_size = get_power_of_2(size);
		const auto level = get_level(real_size);

		const auto result = tree_->allocate(level);
		if (result == nullptr)
			throw std::out_of_range("all memory is used");
		return result;
	}

	void free(void* ptr) const
	{
		tree_->get(ptr)->free();
	}

	~buddy_allocator()
	{
		delete tree_;
		::free(memory_);
	}

	void print_memory_tree() const
	{
		tree_->print();
	}

	void dump() const
	{
		std::cout << "[";
		tree_->print_memory(tree_->is_free);
		std::cout << "]\n";
	}
};