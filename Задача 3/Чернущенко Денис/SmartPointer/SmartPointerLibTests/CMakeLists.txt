project(SmartPointerLibTests)

add_subdirectory(lib/googletest-release-1.8.1)

include_directories(lib/googletest-release-1.8.1/googletest/include)
include_directories(lib/googletest-release-1.8.1/googlemock/include)

add_library(SmartPointerLibTests TestsRunner.h TestsRunner.cpp SmartPointerTests.cpp)

target_link_libraries(SmartPointerLibTests SmartPointerLib gtest gtest_main)
