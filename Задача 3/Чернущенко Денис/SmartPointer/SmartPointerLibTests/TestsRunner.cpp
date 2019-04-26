#include "TestsRunner.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>

int TestsRunner::run_tests(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
