#ifndef ALLOCATORS_ALLOCATOR_H
#define ALLOCATORS_ALLOCATOR_H

#include "Array.h"
#include "MemoryBlocksContainer.h"

class Allocator : public Array, public MemoryBlocksContainer { };

#endif //ALLOCATORS_ALLOCATOR_H
