#include "pch.h"
#include <iostream>
#include <math.h>


struct Block {
public:
	int order;
	bool free;
	Block *left;
	Block *right;
	Block *child1;
	Block *child2;
	Block *parent;
	size_t size;

	Block(int order, size_t size, Block *parent) {
		this->order = order;
		this->size = size;
		left = NULL;
		right = NULL;
		child1 = NULL;
		child2 = NULL;
		this->parent = parent;
		free = true;
	}

	Block(){
		left = NULL;
		right = NULL;
		child1 = NULL;
		child2 = NULL;
		parent = NULL;
	}

	void del() {
		left = NULL;
		right = NULL;
		child1 = NULL;
		child2 = NULL;
		parent = NULL;
	}
};

class Alloc {
	Block *start;

public:
	Alloc(size_t size) {

		start = new Block(floor(log2(size)), size, NULL);
	}

	void* add(size_t size) {
		int order = ceil(log2(size));
		Block *cur_block = start;
		while (!(cur_block->order == order && cur_block->free))
		{
			if (cur_block == NULL) {
				throw std::exception("no free space");
			}
			else if (cur_block->order > order && cur_block->free) {
				cur_block->free = false;
				cur_block->child1 = new Block(cur_block->order - 1, cur_block->size / 2, cur_block);
				cur_block->child2 = new Block(cur_block->order - 1, cur_block->size / 2, cur_block);
				cur_block->child1->left = cur_block->left;
				if (cur_block->left) {
					cur_block->left->right = cur_block->child1;
				}
				cur_block->child1->right = cur_block->child2;
				cur_block->child2->left = cur_block->child1;
				cur_block->child2->right = cur_block->right;
				cur_block->right = NULL;
				cur_block->left = NULL;
				if (cur_block == start)
					start = cur_block->child1;
				cur_block = cur_block->child1;
			}
			else
			{
				cur_block = cur_block->right;
			}
		}
		cur_block->free = false;
		return cur_block;
	}

	void free(void* ptr) {
		Block *cur_block = start;
		while (cur_block != ptr) {
			cur_block = cur_block->right;
		}
		while (true)
		{
			cur_block->free = true;
			cur_block = cur_block->parent;
			if (cur_block != NULL && cur_block->child1->free && cur_block->child2->free) {
				if (start == cur_block->child1){
					start = cur_block;
				}
				cur_block->left = cur_block->child1->left;
				cur_block->right = cur_block->child2->right;
				cur_block->child1->del();
				cur_block->child2->del();
				delete cur_block->child1;
				delete cur_block->child2;
				cur_block->child1 = NULL;
				cur_block->child2 = NULL;
			}
			else
			{
				break;
			}
		}
	}

	void dump() {
		Block *cur_block = start;
		while (cur_block != NULL)
		{
			std::cout << "address: ";
			std::cout << cur_block;
			std::cout << " size: ";
			std::cout << cur_block->size;
			if (cur_block->free) {
				std::cout << " free space" << std::endl;
			}
			else{
				std::cout << " not free space" << std::endl;
			}
			cur_block = cur_block->right;
		}
	}
};


int main()
{
	Alloc alloc = Alloc(1024);
	void *ref1 = alloc.add(32);
	void *ref2 = alloc.add(200);
	void *ref3 = alloc.add(16);
	void *ref4 = alloc.add(100);
	alloc.dump();
	std::cout << " end" << std::endl;
	alloc.free(ref1);
	alloc.free(ref3);
	alloc.dump();
	std::cout << " end" << std::endl;
	alloc.free(ref2);
	alloc.free(ref4);
	alloc.dump();
}

