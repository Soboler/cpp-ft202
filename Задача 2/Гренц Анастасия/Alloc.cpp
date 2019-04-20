#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "Block.h"
#include "pch.h"
#include "Alloc.h"
#include "Block.h"

	Block* Allocator::SplitBlocks(Block* block) {
		int buddy_sizes = block->size / 2;
		auto prev_b = block->left;
		auto next_b = block->right;
		auto left_b = new Block(buddy_sizes);
		auto right_b = new Block(buddy_sizes);
		splitBlocksUsing(left_b, block, right_b, prev_b, next_b);
		delete block;
		this->blocksAmount += 1;
		return left_b;
	}

	void Allocator::splitBlocksUsing(Block* left, Block* block, Block* right, Block* prev, Block* next) {
		prev->right = left;
		next->left = right;
		left->right = right;
		left->left = prev;
		right->right = next;
		right->left = left;
		left->start = block->start;
		right->start = block->start + (block->size / 2);
	}


	Allocator::Allocator(int size_t) {
		this->size = (int)1 << (int)(ceil(log2(size_t)));
		this->pointer = new Block(1);
		auto block = new Block(this->size);
		this->pointer->left = pointer;
		this->pointer->right = block;
		block->left = pointer;
		block->right = block;
		this->blocksAmount = 1;
	}

	void* Allocator::Alloc(int size) {
		int default_size = this->size;
		int required_size = this->size + 1;
		while (size <= default_size) {
			required_size = default_size;
			default_size /= 2;
		}
		auto block = pointer;
		Block* suitable_node = NULL;
		int min_suitable_node_size = size + 1;
		for (int i = 0; i < blocksAmount; i++) {
			block = block->right;
			int block_size = block->size;
			if (block->isFree) {
				if (required_size <= block_size && block_size < min_suitable_node_size) {
					min_suitable_node_size = block_size;
					suitable_node = block;
				}
			}
		};
		Block* required_block = suitable_node;
		if (required_block == NULL) {
			exit(1);
		}

		int chunk_size = required_block->size;
		while (chunk_size != required_size) {
			required_block = SplitBlocks(required_block);
			chunk_size = required_block->size;
		}
		required_block->isFree = false;
		return required_block->ptr;
	}

	void Allocator::Free(void *ptr) {
		Block* block = pointer;
		for (int i = 0; i < blocksAmount; i++) {
			block = block->right;
			if (block->ptr == ptr) {
				block->isFree = true;
				break;
			}
		}
	}

	void Allocator::Dump() {
		auto block = pointer;
		for (int i = 0; i < blocksAmount; i++) {
			block = block->right;
			if (block->isFree) {
				std::cout << "empty: ";
			}
			else {
				std::cout << "full: ";
			}
			std::cout << block->start << " - " << block->start + block->size - 1 << endl;
		};

	}

	Allocator::~Allocator()
	{
		free(pointer);
	}




int main(int argc, const char * argv[]) {

	auto a = Allocator((int)1 << 10);
	auto aPrt = a.Alloc(8);
	a.Alloc(256);
	a.Alloc(128);
	a.Alloc(32);
	a.Alloc(32);
	a.Alloc(64);
	a.Alloc(60);
	a.Dump();
	a.Free(aPrt);
	a.Dump();
	return 0;
}



