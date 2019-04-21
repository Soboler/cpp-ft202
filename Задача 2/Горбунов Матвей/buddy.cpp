#include "buddy.h"
#include <iostream>
#include <cmath>

using namespace std;

void buddy::print(chunk * chunk)
{
	cout << "Allocated " << chunk->size;
	if (chunk->is_free)
		cout << " of free memory";
	else
		cout << " of taken memory";
	cout << " at pointer " << chunk->ptr << endl;
}

buddy::buddy(size_t size)
{
	this->size = size;
	size_t pointer = pow(2, ceil(log(size) / log(2)));
	first = new chunk(size, nullptr);
}

void * buddy::Alloc(size_t size)
{
	chunk *current = first;
	size_t safe_size = pow(2, ceil(log(size) / log(2)));
	int *pointer = current->ptr;

	while (!(current->size == safe_size && current->is_free))
	{
		if (!current->is_free || (log2(current->size) < ceil(log2(size))))
		{
			current = current->next;
			pointer = current->ptr;
		}
		else
		{
			current->split();
			if (current == first)
				first = current->left;
			current = current->left;
			pointer = current->ptr;
		}
		if (current == nullptr)
			throw new exception("Reached memory limit!");
	}

	current->is_free = false;
	return pointer;
}

void buddy::Free(void * ptr)
{
	chunk* current = first;
	while (current->ptr != ptr)
		current = current->next;
	while (true)
	{
		current->is_free = true;
		current = current->parent;
		chunk* left = current->left;
		chunk* right = current->right;
		if (left->is_free && right->is_free)
		{
			if (current->left == first)
				first = current;
			current->unite();
		}
		else
			break;
	}
}

void buddy::Dump()
{
	chunk* current = first;
	while (current != nullptr)
	{
		print(current);
		current = current->next;
	}
}

buddy::~buddy()
{
	free(first);
}
