#include "node.h"
#include <iostream>

using namespace std;

node::node(void* mem_ptr, const int level, const size_t size, const size_t min_size) : mem_ptr(mem_ptr), level(level)
{
	if (size > min_size)
	{
		const auto next_size = size / 2;
		left = new node(mem_ptr, level + 1, next_size, min_size);
		right = new node((int*)mem_ptr + next_size, level + 1, next_size, min_size);
		left->parent = this;
		right->parent = this;
	}
}

void* node::allocate(const int level)
{
	if (!is_free || level < this->level)
		return nullptr;

	if (level == this->level && !is_splitted)
	{
		is_free = false;
		return mem_ptr;
	}

	is_splitted = true;

	const auto left_ptr = left->allocate(level);
	return left_ptr != nullptr ? left_ptr : right->allocate(level);
}

node* node::get(void* ptr)
{
	if (ptr == mem_ptr && !is_free)
		return this;
	if (left == nullptr)
		return nullptr;

	const auto result = left->get(ptr);
	return result != nullptr ? result : right->get(ptr);
}

void node::free()
{
	is_free = true;
	is_splitted = false;

	if (parent == nullptr)
		return;

	const auto other_node = parent->left == this ? parent->right : parent->left;
	if (other_node->is_free)
		parent->free();
}

void node::print()
{
	cout << "\n------=== " << this << " ===------\n";

	cout << "parent:" << parent << endl;
	cout << "left:" << left << endl;
	cout << "parent:" << right << endl;
	cout << endl;

	cout << "mem_ptr: " << mem_ptr << endl;
	cout << "level: " << level << endl;
	cout << endl;

	cout << "is_free:" << is_free << endl;
	cout << "is_splitted:" << is_splitted << endl;

	cout << "------------------------------------\n";

	if (left != nullptr)
	{
		left->print();
		right->print();
	}
}

void print_divider(const node* node)
{
	if (node->is_splitted)
		cout << "|";
	else
		cout << " ";
}

void node::print_memory(bool is_free) const
{
	is_free = is_free && this->is_free;
	if (left != nullptr)
	{
		left->print_memory(is_free);
		print_divider(this);
		right->print_memory(is_free);
	}
	else
	{
		cout << (is_free ? "_" : "X");
	}
}

node::~node()
{
	delete left;
	delete right;
}
