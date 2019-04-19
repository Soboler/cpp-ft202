#pragma once

struct node
{
	node* parent = nullptr;
	node* left = nullptr;
	node* right = nullptr;

	void* mem_ptr;
	int level;

	bool is_free = true;
	bool is_splitted = false;

	node(void* mem_ptr, int level, size_t size, size_t min_size);

	void* allocate(int level);
	node* get(void* ptr);
	void free();

	void print();
	void print_memory(bool is_free) const;

	~node();
};
