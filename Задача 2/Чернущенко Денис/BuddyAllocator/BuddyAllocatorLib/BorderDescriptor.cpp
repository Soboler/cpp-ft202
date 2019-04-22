#include "BorderDescriptor.h"

BorderDescriptor::BorderDescriptor(void* memoryBlock, short level, int indexOnLevel)
{
    this->memoryBlock = memoryBlock;
    this->level = level;
    this->indexOnLevel = indexOnLevel;
    status = BlockStatus::Free;
}
