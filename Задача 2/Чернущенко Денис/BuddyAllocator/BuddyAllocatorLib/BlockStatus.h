#ifndef BUDDYALLOCATOR_BLOCKSTATUS_H
#define BUDDYALLOCATOR_BLOCKSTATUS_H

enum BlockStatus
{
    Free,
    Reserved,
    Split,
    Unallocated,
};

#endif //BUDDYALLOCATOR_BLOCKSTATUS_H
