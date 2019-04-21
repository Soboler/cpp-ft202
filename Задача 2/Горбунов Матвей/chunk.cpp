#include "chunk.h"
#include "malloc.h"

chunk::chunk(size_t size, chunk* parent)
{
	this->size = size;
	ptr = (int*)malloc(size);
	is_free = true;
	this->parent = parent;
	prev = nullptr;
	next = nullptr;
	left = nullptr;
	right = nullptr;
}

void chunk::split()
{
	left = new chunk(size / 2, this);
	right = new chunk(size / 2, this);
	right->next = next;
	if (prev != nullptr)
		prev->next = left;
	if (next != nullptr)
		left->prev = prev;
	left->next = right;
	right->prev = left;
	is_free = false;
}

void chunk::unite()
{
	prev = left->prev;
	next = right->next;
	left = right->next;
	left->~chunk();
	right->~chunk();
}


chunk::~chunk()
{
	free(ptr);
	is_free = true;
}
