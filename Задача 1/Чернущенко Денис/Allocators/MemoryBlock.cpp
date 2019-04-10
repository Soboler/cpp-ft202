#include "MemoryBlock.h"

MemoryBlock::~MemoryBlock()
{
    free(memoryBlock);
}

int MemoryBlock::getMemoryBlockSize()
{
    return PULL_SIZE;
}

int MemoryBlock::getMemoryBlockCapacity()
{
    return getMemoryBlockSize() / sizeof(int);
}
