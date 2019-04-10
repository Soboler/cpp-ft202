#ifndef ALLOCATOR_LINEARALLOCATOR_H
#define ALLOCATOR_LINEARALLOCATOR_H

#include <iostream>
#include "Allocator.h"

class LinearAllocator : public Allocator
{
public:
    ~LinearAllocator() override;

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
    int* memoryBlock = (int*)malloc(PULL_SIZE);
    int memoryBlockSize = PULL_SIZE;
    int length = 0;
    int capacity = getMemoryBlockCapacity();

    void enlargeBlock();
    void resizeBlock(bool enlarge, int addingBytesCount, bool saveValues = true);
};

#endif //ALLOCATOR_LINEARALLOCATOR_H
