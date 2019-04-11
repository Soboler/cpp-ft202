#include <iostream>
#include "LinkedListAllocator.h"

int LinkedListAllocator::getLength()
{
    return length;
}

int& LinkedListAllocator::operator[](const int index)
{
    if (index < 0) throw std::out_of_range("Negative index is not valid.");
    if(index >= length) length = index + 1;

    MemoryBlock* memoryBlockWithSpecifiedIndex = getMemoryBlock(index);
    const int modOfCapacity = index % memoryBlockWithSpecifiedIndex -> getMemoryBlockCapacity();

    return memoryBlockWithSpecifiedIndex -> memoryBlock[modOfCapacity];
}

void LinkedListAllocator::push(const int item)
{
    set(item, length);
}

int LinkedListAllocator::pop()
{
    if (length-- == 0) throw std::out_of_range("Array instance is empty.");

    int poppedItem = (*this)[length];
    length--;

    if (memoryBlockCount > 1 && getMemoryBlockCapacity() - length >= PULL_SIZE / sizeof(int))
        deleteLastBlock();

    return poppedItem;
}

int LinkedListAllocator::get(const int index)
{
    return (*this)[index];
}

void LinkedListAllocator::set(const int item, const int index)
{
    (*this)[index] = item;
}

void LinkedListAllocator::removeAll() // TODO: Maybe delete[] and recreate start block.?
{
    while (memoryBlockCount > 1 && getMemoryBlockCapacity() - length >= PULL_SIZE / sizeof(int))
        deleteLastBlock();

    length = 0;
}

int LinkedListAllocator::getMemoryBlockSize()
{
    return getMemoryBlockCapacity() * sizeof(int);
}

int LinkedListAllocator::getMemoryBlockCapacity()
{
    return memoryBlockCount * lastMemoryBlock -> getMemoryBlockCapacity();
}

MemoryBlock *LinkedListAllocator::getMemoryBlock(const int index)
{
    int currentBlockNumber = memoryBlockCount;

    while (memoryBlockCount * lastMemoryBlock -> getMemoryBlockCapacity() - 1 < index)
    {
        auto newMemoryBlock  = new MemoryBlock();
        newMemoryBlock -> previous = lastMemoryBlock;
        lastMemoryBlock = newMemoryBlock;

        memoryBlockCount++;
    }

    MemoryBlock* memoryBlock = lastMemoryBlock;

    while (memoryBlock -> previous != nullptr &&
           memoryBlock -> getMemoryBlockCapacity() * (currentBlockNumber - 1) > index)
        memoryBlock = memoryBlock -> previous;

    return memoryBlock;
}

void LinkedListAllocator::deleteLastBlock()
{
    memoryBlockCount--;

    MemoryBlock* previous = lastMemoryBlock -> previous;
    delete(lastMemoryBlock);
    lastMemoryBlock = previous;
}
