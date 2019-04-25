#ifndef BUDDYALLOCATOR_BORDERDESCRIPTOR_H
#define BUDDYALLOCATOR_BORDERDESCRIPTOR_H

#include "BlockStatus.h"

struct BorderDescriptor
{
    BorderDescriptor(void* memoryBlock, short level, int indexOnLevel);

    void* memoryBlock;
    short level;
    BlockStatus status;
    int indexOnLevel;
    BorderDescriptor* next = nullptr;
    BorderDescriptor* previous = nullptr;
};


#endif //BUDDYALLOCATOR_BORDERDESCRIPTOR_H
