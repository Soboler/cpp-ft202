#ifndef BUDDYALLOCATOR_BLOCKSTATUS_H
#define BUDDYALLOCATOR_BLOCKSTATUS_H


enum BlockStatus : char
{
    Free = 'F',
    Reserved = 'R',
    Split = 'S',
    Unallocated = 'U',
};


#endif //BUDDYALLOCATOR_BLOCKSTATUS_H
