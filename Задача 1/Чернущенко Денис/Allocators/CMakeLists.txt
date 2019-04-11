cmake_minimum_required(VERSION 3.13)
project(Allocators)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/googletest-release-1.8.1)

include_directories(lib/googletest-release-1.8.1/googletest/include)
include_directories(lib/googletest-release-1.8.1/googlemock/include)

include_directories(AllocatorsLib)
add_subdirectory(AllocatorsLib)

add_executable(Allocators main.cpp AllocatorsLibTests/AllocatorsTests.cpp
        AllocatorsLib/Array.h AllocatorsLib/LinearAllocator.cpp AllocatorsLib/LinearAllocator.h
        AllocatorsLib/StackAllocator.cpp AllocatorsLib/StackAllocator.h AllocatorsLib/LinkedListAllocator.cpp
        AllocatorsLib/LinkedListAllocator.h AllocatorsLib/MemoryBlocksContainer.h AllocatorsLib/Allocator.h
        AllocatorsLib/MemoryBlock.cpp AllocatorsLib/MemoryBlock.h)

target_link_libraries(Allocators gtest gtest_main)
