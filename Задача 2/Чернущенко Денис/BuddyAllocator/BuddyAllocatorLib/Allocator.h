#ifndef BUDDYALLOCATOR_ALLOCATOR_H
#define BUDDYALLOCATOR_ALLOCATOR_H
#define MIN_POWER 5

#include "BorderDescriptor.h"
#include <cstddef>
#include <map>

class Allocator
{
public:
    ~Allocator();

    explicit Allocator(size_t pullSize);
    void* Allocate(size_t size);
    void Free(void* blockPointer);

    void Dump();

private:
    void* memoryPool;
    short levelsCount;
    BorderDescriptor** descriptorsList;
    short* countOfDescriptorsOnLevel;
    short* countOfFreeBlocksOnLevel;
    std::map<void*, BorderDescriptor*> memoryDescriptorMap;

    static short getNecessaryLevel(size_t memorySize);
    static size_t getBlockSize(short level);
    BorderDescriptor* findFreeBlockForCustomLevel(short level);
    BorderDescriptor* splitOnBuddies(BorderDescriptor* splitDescriptor);
    BorderDescriptor* getNeighbourDescriptor(BorderDescriptor* startDescriptor, BorderDescriptor* descriptor);
    static BorderDescriptor* findAccessibleBuddyDescriptor(BorderDescriptor* descriptor);
    BorderDescriptor* tryToCombineWithBuddy(BorderDescriptor* descriptor);
};


#endif //BUDDYALLOCATOR_ALLOCATOR_H
