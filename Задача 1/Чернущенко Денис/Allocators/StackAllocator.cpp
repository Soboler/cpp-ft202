#include "StackAllocator.h"

int StackAllocator::pop()
{
    int poppedItem = LinearAllocator::pop();

    if (length > 0 && capacity - length >= PULL_SIZE / sizeof(int))
        reduceBlock();

    return poppedItem;
}

void StackAllocator::removeAll()
{
    if (memoryBlockSize > PULL_SIZE)
        resizeBlock(false, memoryBlockSize - PULL_SIZE, false);

    LinearAllocator::removeAll();
}

void StackAllocator::reduceBlock()
{
    resizeBlock(false, PULL_SIZE);
}
