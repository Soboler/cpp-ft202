project(BuddyAllocatorLib)

set(HEADER_FILES
        Allocator.h
        BlockStatus.h
        BorderDescriptor.h)

set(SOURCE_FILES
        Allocator.cpp
        BorderDescriptor.cpp)

add_library(BuddyAllocatorLib STATIC ${SOURCE_FILES} ${HEADER_FILES})
