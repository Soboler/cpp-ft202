#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include "../BuddyAllocatorLib/Allocator.h"

#define MB 1024
#define TWO_MB 2048
#define TEN_MB 40960

#define DUMP_OUTPUT
// BlockStatus::Free :          'F'
// BlockStatus::Reserved :      'R'
// BlockStatus::Split :         'S'
// BlockStatus::Unallocated :   'U'

TEST(AllocatorTest, AllocateMinBlock) {
    Allocator allocator(MB);

    auto intPointer = (int*)allocator.Allocate(1);
    ASSERT_TRUE(intPointer != nullptr);

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif

    *intPointer = 15;
    ASSERT_EQ(*intPointer, 15);
}

TEST(AllocatorTest, AllocateMaxBlock) {
    Allocator allocator(MB);

    void* memoryPointer = allocator.Allocate(MB);
    ASSERT_TRUE(memoryPointer != nullptr);

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif
}

TEST(AllocatorTest, ThrowOnZeroAllocationRequest) {
    ASSERT_THROW(Allocator(0), std::out_of_range);

    Allocator allocator(MB);

    ASSERT_THROW(allocator.Allocate(0), std::out_of_range);

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif
}

TEST(AllocatorTest, AllocateTwoDifferentlyBlocks) {
    Allocator allocator(TWO_MB);

    void* firstBlock = allocator.Allocate(40);
    ASSERT_TRUE(firstBlock != nullptr);

    void* secondBlock = allocator.Allocate(260);
    ASSERT_TRUE(secondBlock != nullptr);

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif
}

TEST(AllocatorTest, ThrowOnTooBigAllocationRequest) {
    Allocator allocator(MB);

    ASSERT_THROW(allocator.Allocate(MB + 1), std::out_of_range);

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif
}

TEST(AllocatorTest, AllocateMaxSmallBlocksCount) {
    Allocator allocator(MB);

    size_t maxSmallBlocksCount = MB / (size_t)pow(2, MIN_POWER);

    for (int i = 0; i < maxSmallBlocksCount; ++i)
        ASSERT_NO_THROW(allocator.Allocate(sizeof(int)));

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif
}

TEST(AllocatorTest, AllocateMaxSmallBlocksCountThenFreeHalfAndAllocateAgain) {
    Allocator allocator(MB);

    size_t maxSmallBlocksCount = MB / (size_t)pow(2, MIN_POWER);
    void** memoryPointers = new void*[maxSmallBlocksCount];

    for (int i = 0; i < maxSmallBlocksCount; ++i)
        ASSERT_NO_THROW(memoryPointers[i] = allocator.Allocate(sizeof(int)));

    for (int i = 0; i < maxSmallBlocksCount; i += 2)
        ASSERT_NO_THROW(allocator.Free(memoryPointers[i]));

    for (int i = 0; i < maxSmallBlocksCount; i += 2)
        ASSERT_NO_THROW(allocator.Allocate(sizeof(int)));

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif
}

TEST(AllocatorTest, AllocateTooMuchBlocks) {
    Allocator allocator(MB);

    size_t maxSmallBlocksCount = MB / (size_t)pow(2, MIN_POWER);

    for (int i = 0; i < maxSmallBlocksCount; ++i)
        ASSERT_NO_THROW(allocator.Allocate(sizeof(int)));

    ASSERT_THROW(allocator.Allocate(1), std::out_of_range);
}

TEST(AllocatorTest, AllocateBlockSizeMoreThanOneStandardPage) {
    Allocator allocator(TEN_MB);

    ASSERT_TRUE(allocator.Allocate(TEN_MB) != nullptr);

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif
}
