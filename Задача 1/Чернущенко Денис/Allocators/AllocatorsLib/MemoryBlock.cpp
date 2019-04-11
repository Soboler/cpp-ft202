#include <iostream>
#include "MemoryBlock.h"

MemoryBlock::MemoryBlock()
{
    memoryBlock = (int*)malloc(PULL_SIZE);
    previous = nullptr;
}

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
