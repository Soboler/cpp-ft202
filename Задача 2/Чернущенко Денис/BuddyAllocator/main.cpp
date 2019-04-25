#include "BuddyAllocatorLibTests/TestsRunner.h"

#define TESTING

int main(int argc, char* argv[])
{
#ifdef TESTING
    return TestsRunner::run_tests(argc, argv);
#endif

    return 0;
}
