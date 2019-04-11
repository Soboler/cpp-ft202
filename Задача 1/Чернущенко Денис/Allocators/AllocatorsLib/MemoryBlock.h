#ifndef ALLOCATORS_MEMORYBLOCK_H
#define ALLOCATORS_MEMORYBLOCK_H

#include "MemoryBlocksContainer.h"

class MemoryBlock : MemoryBlocksContainer
{
public:
    int* memoryBlock;
    MemoryBlock* previous;

    MemoryBlock();
    ~MemoryBlock() override;

    int getMemoryBlockSize() override;
    int getMemoryBlockCapacity() override;
};

#endif //ALLOCATORS_MEMORYBLOCK_H
