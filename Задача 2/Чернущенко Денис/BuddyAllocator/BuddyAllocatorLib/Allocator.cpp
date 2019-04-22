#include "Allocator.h"
#include "BlockStatus.h"
#include <cmath>
#include <iostream>
#include <iomanip>

Allocator::Allocator(size_t pullSize)
{
    levelsCount = getNecessaryLevel(pullSize) + 1;

    descriptorsList = new BorderDescriptor*[levelsCount];
    countOfDescriptorsOnLevel = new short[levelsCount];
    countOfFreeBlocksOnLevel = new short[levelsCount];

    memoryPool = malloc(getBlockSize(levelsCount - 1));

    descriptorsList[levelsCount - 1] = new BorderDescriptor(memoryPool, levelsCount - 1, 0);
    countOfDescriptorsOnLevel[levelsCount - 1] = 1;
    countOfFreeBlocksOnLevel[levelsCount - 1] = 1;

    for (short i = 0; i < levelsCount - 1; ++i)
    {
        descriptorsList[i] = nullptr;
        countOfFreeBlocksOnLevel[i] = 0;
        countOfDescriptorsOnLevel[i] = 0;
    }

    memoryDescriptorMap = { { memoryPool, descriptorsList[levelsCount - 1] } };
}

Allocator::~Allocator()
{
    free(memoryPool);
    delete[](descriptorsList);
    delete[](countOfDescriptorsOnLevel);
    delete[](countOfFreeBlocksOnLevel);
}

void* Allocator::Allocate(size_t size)
{
    short levelOfDesiredBlock = getNecessaryLevel(size);
    BorderDescriptor* desiredDescriptor = findFreeBlockForCustomLevel(levelOfDesiredBlock);
    while (desiredDescriptor->level > fmax(levelOfDesiredBlock, 0))
        desiredDescriptor = splitOnBuddies(desiredDescriptor);

    desiredDescriptor->status = BlockStatus::Reserved;
    countOfFreeBlocksOnLevel[desiredDescriptor->level]--;

    return desiredDescriptor->memoryBlock;
}

void Allocator::Free(void* blockPointer)
{
    BorderDescriptor* exemptedBlock = memoryDescriptorMap[blockPointer];
    exemptedBlock->status = BlockStatus::Free;
    countOfFreeBlocksOnLevel[exemptedBlock->level]++;

    while (findAccessibleBuddyDescriptor(exemptedBlock) != nullptr)
        exemptedBlock = tryToCombineWithBuddy(exemptedBlock);
}

void Allocator::Dump()
{
    using namespace std;

    map<BlockStatus, string> statusStringMap = {
            { BlockStatus::Free, "F" },
            { BlockStatus::Reserved, "R" },
            { BlockStatus::Split, "S" },
            { BlockStatus::Unallocated, "U" }
    };

    auto blockLength = [](size_t level) -> size_t { return (getBlockSize(level) / getBlockSize(0)) * 2 + 1; };

    for (int level = levelsCount - 1; level >= 0; --level)
    {
        if (countOfDescriptorsOnLevel[level] == 0) continue;

        BorderDescriptor* descriptor = descriptorsList[level];

        if (descriptor != nullptr)
            cout << setfill('-') << setw(blockLength(levelsCount - 1)) << "-" << endl << setfill(' ');

        while (descriptor != nullptr)
        {
            cout << '|' << setw(blockLength(descriptor->level) / 2) << statusStringMap[descriptor->status];
            size_t width = blockLength(descriptor->level) / 2 - statusStringMap[descriptor->status].length();
            cout << setw(width) << (width > 0 ? " " : "");

            descriptor = descriptor->next;
        }
        cout << '|';
        size_t width = blockLength(levelsCount - 1) - blockLength(level) * countOfDescriptorsOnLevel[level] + 1;
        if (width > 1) cout << setw(width) << '|';
        cout << " Level: " << level << ", size of one block: " << getBlockSize(level) << " bytes" << endl;
    }

    cout << setfill('-') << setw(blockLength(levelsCount - 1)) << "-" << endl << setfill(' ');
}

short Allocator::getNecessaryLevel(size_t memorySize)
{
    if (memorySize == 0) std::__throw_out_of_range("Can not allocate zero bytes.");
    return fmax(ceil(log2(memorySize)) - MIN_POWER, 0);
}

size_t Allocator::getBlockSize(short level)
{
    return pow(2, level + MIN_POWER);
}

BorderDescriptor* Allocator::findFreeBlockForCustomLevel(short level)
{
    while (level <= levelsCount && countOfFreeBlocksOnLevel[level] == 0) level++;

    if (level >= levelsCount) std::__throw_out_of_range("Out of allocator memory resource.");

    BorderDescriptor* foundDescriptor = descriptorsList[level];
    while (foundDescriptor->status != BlockStatus::Free)
        foundDescriptor = foundDescriptor->next;

    return foundDescriptor;
}

BorderDescriptor* Allocator::splitOnBuddies(BorderDescriptor* splitDescriptor)
{
    short newLevel = splitDescriptor->level - 1;
    short firstBuddyIndex = splitDescriptor->indexOnLevel * 2;

    BorderDescriptor* firstBuddy;
    BorderDescriptor* secondBuddy;

    if (countOfDescriptorsOnLevel[newLevel] <= firstBuddyIndex)
    {
        firstBuddy = new BorderDescriptor(splitDescriptor->memoryBlock, newLevel, firstBuddyIndex);
        auto pointerOnSecondHalfOfMemoryBlock = (void*)((size_t)splitDescriptor->memoryBlock + getBlockSize(newLevel));
        secondBuddy = new BorderDescriptor(pointerOnSecondHalfOfMemoryBlock, newLevel, firstBuddyIndex + 1);

        firstBuddy->next = secondBuddy;
        secondBuddy->previous = firstBuddy;

        BorderDescriptor* lastDescriptorOnLevel = descriptorsList[newLevel];
        while (lastDescriptorOnLevel != nullptr && lastDescriptorOnLevel->next != nullptr)
            lastDescriptorOnLevel = lastDescriptorOnLevel->next;

        firstBuddy->previous = lastDescriptorOnLevel;
        if (lastDescriptorOnLevel != nullptr)
            lastDescriptorOnLevel->next = firstBuddy;
        else
            descriptorsList[newLevel] = firstBuddy;

        countOfDescriptorsOnLevel[newLevel] += 2;
    }
    else
    {
        firstBuddy = descriptorsList[newLevel];
        while (firstBuddy->indexOnLevel != firstBuddyIndex)
            firstBuddy = firstBuddy->next;
        secondBuddy = firstBuddy->next;

        firstBuddy->status = BlockStatus::Free;
        secondBuddy->status = BlockStatus::Free;
    }

    countOfFreeBlocksOnLevel[newLevel] += 2;
    memoryDescriptorMap.insert_or_assign(firstBuddy->memoryBlock, firstBuddy);
    memoryDescriptorMap.insert_or_assign(secondBuddy->memoryBlock, secondBuddy);

    splitDescriptor->status = BlockStatus::Split;
    countOfFreeBlocksOnLevel[splitDescriptor->level]--;

    return firstBuddy;
}

BorderDescriptor* Allocator::findAccessibleBuddyDescriptor(BorderDescriptor* descriptor)
{
    BorderDescriptor* buddyDescriptor = descriptor->indexOnLevel % 2 == 0 ? descriptor->next : descriptor->previous;

    if (buddyDescriptor == nullptr || buddyDescriptor->status != BlockStatus::Free) return nullptr;

    return buddyDescriptor;
}

BorderDescriptor* Allocator::tryToCombineWithBuddy(BorderDescriptor* descriptor)
{
    BorderDescriptor* buddyDescriptor = findAccessibleBuddyDescriptor(descriptor);

    if (descriptor->status != BlockStatus::Free || buddyDescriptor == nullptr) return nullptr;

    short parentBlockLevel = descriptor->level + 1;
    BorderDescriptor* parentDescriptor = descriptorsList[parentBlockLevel];
    while (parentDescriptor->indexOnLevel != descriptor->indexOnLevel / 2)
        parentDescriptor = parentDescriptor->next;

    descriptor->status = BlockStatus::Unallocated;
    buddyDescriptor->status = BlockStatus::Unallocated;
    parentDescriptor->status = BlockStatus::Free;

    memoryDescriptorMap.insert_or_assign(parentDescriptor->memoryBlock, parentDescriptor);

    return parentDescriptor;
}
