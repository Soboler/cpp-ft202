#include "pch.h"
#include <iostream>

using namespace std;

class Allocator
{
	struct Block
	{
		size_t size = 0;
		bool is_taken = false;
		Block* last_block;
		Block* body;
		Block* nextL_block;
		Block* nextR_block;
	};

	Block* start;

	void block_initialise(Block* block, size_t block_size, Block* previous, Block* buddy)
	{
		block->size = block_size;
		block->last_block = previous;
		block->body = buddy;
		block->nextL_block = NULL;
		block->nextR_block = NULL;
	}

	void print_dumps(Block* block)
	{
		if (block != nullptr)
		{
			print_dumps(block->nextL_block);
			if (block->nextL_block == NULL && block->nextR_block == NULL)
			{
				printf("%s %d:\n", "Bloack size: ", block->size);
				printf("%s %d:\n", "Taken: ", block->is_taken);
			}
			print_dumps(block->nextR_block);
		}
	}

public:
	Allocator(size_t allocator_size)
	{
		start = new Block();
		block_initialise(start, allocator_size, NULL, NULL);
	}

	void Dump()
	{
		print_dumps(start);
	}

	void Free(void *ptr)
	{
		Block* block = (Block*)ptr;
		if (block == start)
		{
			start->is_taken = false;
			start->nextL_block = NULL;
			start->nextR_block = NULL;
			return;
		}
		if (block->body->is_taken)
		{
			block->is_taken = false;
		}
		else
		{
			Block* current_block = block;
			while (!current_block->body->is_taken)
			{
				delete current_block->body;
				Block* previous = current_block->last_block;
				delete current_block;
				current_block = previous;
				current_block->nextL_block = NULL;
				current_block->nextR_block = NULL;
				previous->is_taken = false;
				if (current_block == start || current_block->is_taken) break;
			}
		}
	}

	void* Alloc(size_t alloc_size)
	{
		Block* current_block = start;
		size_t current_size = current_block->size;
		void* result = nullptr;
		while (true)
		{
			if (current_size / 2 < 1) throw exception("Allocator is overflowed");
			if (alloc_size > current_size) throw exception("Allocator is overflowed");
			else
			{
				if (alloc_size > current_size / 2)
				{
					current_block->is_taken = true;
					if (current_block->body->is_taken)
					{
						current_block->last_block->is_taken = true;
						current_block->body->last_block->is_taken = true;
					}
					result = current_block;
					break;
				}
				if (current_block->nextL_block == NULL && current_block->nextR_block == NULL)
				{
					Block* left_block = new Block();
					Block* right_block = new Block();
					block_initialise(left_block, current_size / 2, current_block, right_block);
					current_block->nextL_block = left_block;

					block_initialise(right_block, current_size / 2, current_block, left_block);
					current_block->nextR_block = right_block;
				}
				current_size = current_size / 2;
				if (!current_block->nextL_block->is_taken) current_block = current_block->nextL_block;
				else if (!current_block->nextR_block->is_taken) current_block = current_block->nextR_block;
				else throw exception("Allocator is overflowed");
			}
		}
		return result;
	}
};

int main()
{
	Allocator* alloc = new Allocator(64);
	void* result1 = alloc->Alloc(8);
	void* result2 = alloc->Alloc(8);
	void* result3 = alloc->Alloc(16);
	alloc->Free(result2);
	alloc->Free(result3);
	alloc->Free(result1);
	alloc->Dump();
	return 0;
}