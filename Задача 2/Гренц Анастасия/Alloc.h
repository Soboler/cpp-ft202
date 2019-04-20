#include "Block.h"
class Allocator
{
private:
	Block *pointer;
	int size;
	int blocksAmount;



	Block* SplitBlocks(Block* block);

	void splitBlocksUsing(Block* left, Block* block, Block* right, Block* prev, Block* next);



public:
	Allocator(int size_t);

	void* Alloc(int size);

	void Free(void *ptr);

	void Dump();

	~Allocator();

};
