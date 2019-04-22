cmake_minimum_required(VERSION 3.14)
project(BuddyAllocator)

set(CMAKE_CXX_STANDARD 17)

include_directories ("${PROJECT_SOURCE_DIR}/BuddyAllocatorLib")
include_directories ("${PROJECT_SOURCE_DIR}/BuddyAllocatorLibTests")
include_directories(BuddyAllocatorLibTests/lib/googletest-release-1.8.1/googletest/include)
include_directories(BuddyAllocatorLibTests/lib/googletest-release-1.8.1/googlemock/include)

add_subdirectory (BuddyAllocatorLib)
add_subdirectory(BuddyAllocatorLibTests)

add_executable(BuddyAllocator main.cpp BuddyAllocatorLibTests/AllocatorTests.cpp)
target_link_libraries (BuddyAllocator BuddyAllocatorLib BuddyAllocatorLibTests)
