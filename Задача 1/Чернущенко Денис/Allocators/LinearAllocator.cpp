#include "LinearAllocator.h"

using namespace std;

LinearAllocator::~LinearAllocator()
{
    free(memoryBlock);
}

int& LinearAllocator::operator[] (const int index)
{
    if (index < 0) throw out_of_range("Negative index is not valid.");

    while (index >= capacity)
        enlargeBlock();

    if(index >= length) length = index + 1;

    return memoryBlock[index];
}

void LinearAllocator::push(const int item)
{
    set(item, length);
}

int LinearAllocator::pop()
{
    if (length-- == 0) throw out_of_range("Array instance is empty.");

    return memoryBlock[length];
}

int LinearAllocator::get(const int index)
{
    return (*this)[index];
}

void LinearAllocator::set(const int item, const int index)
{
    (*this)[index] = item;
}

void LinearAllocator::removeAll()
{
    length = 0;
}

int LinearAllocator::getLength()
{
    return length;
}

int LinearAllocator::getMemoryBlockSize()
{
    return memoryBlockSize;
}

int LinearAllocator::getMemoryBlockCapacity()
{
    return memoryBlockSize / sizeof(int);
}

void LinearAllocator::enlargeBlock()
{
    resizeBlock(true, PULL_SIZE);
}

void LinearAllocator::resizeBlock(const bool enlarge, const int addingBytesCount, const bool saveValues)
{
    memoryBlockSize += enlarge ? addingBytesCount : -addingBytesCount;
    int* newMemoryBlock = (int*)malloc(memoryBlockSize);

    if (saveValues)
        for (int i = 0; i < length; ++i)
            newMemoryBlock[i] = memoryBlock[i];

    free(memoryBlock);

    memoryBlock = newMemoryBlock;
    capacity = getMemoryBlockCapacity();
}
