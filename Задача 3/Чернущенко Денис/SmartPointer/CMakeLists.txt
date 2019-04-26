cmake_minimum_required(VERSION 3.14)
project(SmartPointer)

set(CMAKE_CXX_STANDARD 17)

include_directories ("${PROJECT_SOURCE_DIR}/SmartPointerLib")
include_directories ("${PROJECT_SOURCE_DIR}/SmartPointerLibTests")
include_directories(SmartPointerLibTests/lib/googletest-release-1.8.1/googletest/include)
include_directories(SmartPointerLibTests/lib/googletest-release-1.8.1/googlemock/include)

add_subdirectory (SmartPointerLib)
add_subdirectory(SmartPointerLibTests)

add_executable(SmartPointer main.cpp SmartPointerLibTests/SmartPointerTests.cpp)
target_link_libraries (SmartPointer SmartPointerLib SmartPointerLibTests)
