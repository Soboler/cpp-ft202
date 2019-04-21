#pragma once
#include <iostream>

class node
{
	node* parent_ = nullptr;
	node* left_ = nullptr;
	node* right_ = nullptr;

	void* ptr_;
	int level_;

	bool is_splitted_ = false;

public:
	bool is_free = true;

	node(void* ptr, const int level, const size_t size, const size_t min_size, node* parent = nullptr)
	{
		if (size <= min_size)
			return;
		const auto next_size = size >> 1;
		left_ = new node(ptr, level + 1, next_size, min_size,this);
		right_ = new node((char*)ptr + next_size, level + 1, next_size, min_size, this);
		parent_ = parent;
		ptr_ = ptr;
		level_ = level;
	}

	void* allocate(const int level)
	{
		if(!is_free || level < level_)
			return nullptr;

		if (level == this->level_ && !is_splitted_)
		{
			is_free = false;
			return ptr_;
		}

		is_splitted_ = true;

		const auto left_ptr = left_->allocate(level);
		return left_ptr != nullptr ? left_ptr : right_->allocate(level);
	}

	node* get(void* ptr)
	{
		if (ptr == ptr_ && !is_free)
			return this;
		if (left_ == nullptr)
			return nullptr;

		const auto result = left_->get(ptr);
		return result == nullptr ? right_->get(ptr) : result;
	}

	void free()
	{
		is_free = true;
		is_splitted_ = false;

		if (parent_ == nullptr)
			return;

		const auto other_node = parent_->left_ == this ? parent_->right_ : parent_->left_;
		if (other_node->is_free)
			parent_->free();
	}

	void print() const
	{
		std::cout << "left:" << left_ << "\n";
		std::cout << "right:" << right_ << "\n";
		std::cout << "\n";

		std::cout << "ptr: " << ptr_ << "\n";
		std::cout << "level: " << level_ << "\n";
		std::cout << "\n";

		std::cout << "is_free:" << is_free << "\n";
		std::cout << "is_splitted:" << is_splitted_ << "\n";

		std::cout << "---------------------------------\n";

		if (left_ == nullptr) return;
		left_->print();
		right_->print();
	}

	static void print_divider(const node* node)
	{
		if (node->is_splitted_)
			std::cout << "|";
		else
			std::cout << " ";
	}

	void print_memory(bool is_free) const
	{
		is_free = is_free && this->is_free;
		if (left_ != nullptr)
		{
			left_->print_memory(is_free);
			print_divider(this);
			right_->print_memory(is_free);
		}
		else
			std::cout << (is_free ? "_" : "X");
	}

	~node()
	{
		delete left_;
		delete right_;
	}
};
