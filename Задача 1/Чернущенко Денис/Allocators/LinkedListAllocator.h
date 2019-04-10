#ifndef ALLOCATORS_LINKEDLISTALLOCATOR_H
#define ALLOCATORS_LINKEDLISTALLOCATOR_H

#include <iostream>
#include "Allocator.h"
#include "MemoryBlock.h"

class LinkedListAllocator : public Allocator
{
public:
    int getLength() override;
    int& operator[] (int index) override;
    void push(int item) override;
    int pop() override;
    int get(int index) override;
    void set(int item, int index) override;
    void removeAll() override;

    int getMemoryBlockSize() override;
    int getMemoryBlockCapacity() override;

protected:
    int length = 0;
    int memoryBlockCount = 1;
    MemoryBlock* lastMemoryBlock = new MemoryBlock();

    MemoryBlock* getMemoryBlock(int index);
    void deleteLastBlock();
};

#endif //ALLOCATORS_LINKEDLISTALLOCATOR_H
