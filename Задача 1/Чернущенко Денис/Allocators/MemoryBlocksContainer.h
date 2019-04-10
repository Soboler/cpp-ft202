#ifndef ALLOCATORS_MEMORYBLOCKSCONTAINER_H
#define ALLOCATORS_MEMORYBLOCKSCONTAINER_H

class MemoryBlocksContainer
{
public:
    const int PULL_SIZE = 1024;

    MemoryBlocksContainer() = default;
    virtual ~MemoryBlocksContainer() = default;
    MemoryBlocksContainer(const MemoryBlocksContainer&) = delete;
    MemoryBlocksContainer& operator= (const MemoryBlocksContainer&) = delete;

    virtual int getMemoryBlockSize() = 0;
    virtual int getMemoryBlockCapacity() = 0;
};

#endif //ALLOCATORS_MEMORYBLOCKSCONTAINER_H
