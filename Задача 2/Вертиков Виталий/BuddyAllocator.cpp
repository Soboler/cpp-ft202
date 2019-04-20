#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;


struct BuddyItem {
	int level;
	bool free;
	BuddyItem* next;
	BuddyItem* prev;
	char* data;
};


class BuddyAllocator {

	vector<vector<BuddyItem*>> blocks;
	int maxLevel;

public:

	BuddyAllocator(size_t size) {
		maxLevel = getPower(size);
		for (int i = 0; i <= maxLevel; i++) {
			blocks.push_back(vector<BuddyItem*>());
		}
		BuddyItem* block = new BuddyItem{ maxLevel, true, NULL, NULL, (char*)malloc(1 << maxLevel) };
		block->next = block;
		block->prev = block;
		blocks[maxLevel].push_back(block);
	}

	void* Alloc(size_t size) {
		int level = getPower(size);

		int index = findFreeBlock(level);
		if (index != -1) {
			BuddyItem* block =  blocks[level][index];
			block->free = false;
			return block->data;
		}
		else {
			for (int i = level; i++; i <= maxLevel) {
				index = findFreeBlock(i);
				if (index != -1) {
					BuddyItem* neededBlock = SplitToNeededBlock(blocks[i][index], level, index);
					neededBlock->free = false;
					return neededBlock->data;
				}
			}
		}
	}

	void Free(void *ptr) {
		pair<BuddyItem*, int> pair = findBlock(ptr);
		BuddyItem* block = pair.first;
		int index = pair.second;
		block->free = true;
		BuddyItem* neighbour = index % 2 == 0 ? block->next : block->prev;
		if (neighbour->free && neighbour->level == block->level) {
			if (index % 2 == 0) {
				mergeBlocks(block, neighbour);
			}
			else {
				mergeBlocks(neighbour, block);
			}
		}
	}

	void Dump() {
		for (int i = 0; i <= maxLevel; i++) {
			for (int j = 0; j < blocks[i].size(); j++) {
				BuddyItem* block = blocks[i][j];
				printf("Level:%d Size:%d ", block->level, 1 << block->level);
				printf("Free:%s\n", block->free ? "true" : "false");
			}
		}
	}

private:

	void mergeBlocks(BuddyItem* left, BuddyItem* right) {
		BuddyItem* newBlock = new BuddyItem{ left->level + 1, true, right->next, left->prev, left->data };
		newBlock->prev->next = newBlock;
		newBlock->next->prev = newBlock;
		blocks[newBlock->level].push_back(newBlock);
		blocks[left->level].erase(blocks[left->level].begin() + getIndex(left));
		blocks[right->level].erase(blocks[right->level].begin() + getIndex(right));
		delete left;
		delete right;
		int index = getIndex(newBlock);
		BuddyItem* neighbour = index % 2 == 0 ? newBlock->next : newBlock->prev;

		if (neighbour->free && neighbour->level == newBlock->level && neighbour->level != maxLevel) {
			if (index % 2 == 0) {
				mergeBlocks(newBlock, neighbour);
			}
			else {
				mergeBlocks(neighbour, newBlock);
			}
		}
	}

	int getIndex(BuddyItem* block) {
		for (int i = 0; i < blocks[block->level].size(); i++) {
			if (blocks[block->level][i] == block) {
				return i;
			}
		}
	}
	 
	int getPower(size_t size) {
		long unsigned int level;
		_BitScanReverse(&level, (long unsigned int)size);
		level++;
		return (int)level;
	}

	BuddyItem* SplitToNeededBlock(BuddyItem* block, int neededLevel, int index) {
		BuddyItem* res = NULL;
		for (int i = block->level; i > neededLevel;  i--) {
			BuddyItem* leftBlock = new BuddyItem { block->level - 1, true, NULL, block->prev, block->data};
			BuddyItem* rightBlock = new BuddyItem { block->level - 1, true, block->next, NULL, block->data + (1 << (block->level - 1)) };
			leftBlock->next = rightBlock;
			rightBlock->prev = leftBlock;
			block->prev->next = leftBlock;
			block->next->prev = rightBlock;
			blocks[block->level - 1].push_back(leftBlock);
			blocks[block->level - 1].push_back(rightBlock);
			blocks[block->level].erase(blocks[block->level].begin() + index);
			delete res;
			block = leftBlock;
			index = blocks[block->level].size() - 1;
			res = leftBlock;
		}
		return res;
	}

	pair<BuddyItem*, int> findBlock(void* ptr) {
		for (int i = 0; i <= maxLevel; i++) {
			for (int j = 0; j < blocks[i].size(); j++) {
				if (blocks[i][j]->data == ptr) {
					return make_pair(blocks[i][j], j);
				}
			}
		}
	}

	int findFreeBlock(int level) {
		for (int j = 0; j < blocks[level].size(); j++) {
			if (blocks[level][j]->free) {
				return j;
			}
		}
		return -1;
	}
};


int main() {
	BuddyAllocator alloc = BuddyAllocator(100);
	void* ptr1 = alloc.Alloc(53);
	void* ptr2 = alloc.Alloc(20);
	void* ptr3 = alloc.Alloc(10);
	alloc.Dump();
	printf("\n\n");
	alloc.Free(ptr1);
	alloc.Free(ptr2);
	alloc.Free(ptr3);
	alloc.Dump();
}
