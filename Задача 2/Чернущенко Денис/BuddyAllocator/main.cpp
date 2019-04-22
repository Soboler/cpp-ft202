#include "BuddyAllocatorLibTests/TestsRunner.h"
#include "BuddyAllocatorLib/Allocator.h"

#define TESTING

int main(int argc, char* argv[])
{
#ifdef TESTING
    return TestsRunner::run_tests(argc, argv);
#endif

    Allocator allocator(1024);
    auto intPointer = (int*)allocator.Allocate(1);
    allocator.Dump();

/* Output:
-----------------------------------------------------------------
|                               S                               | Level: 5, size of one block: 1024 bytes
-----------------------------------------------------------------
|               S               |               F               | Level: 4, size of one block: 512 bytes
-----------------------------------------------------------------
|       S       |       F       |                               | Level: 3, size of one block: 256 bytes
-----------------------------------------------------------------
|   S   |   F   |                                               | Level: 2, size of one block: 128 bytes
-----------------------------------------------------------------
| S | F |                                                       | Level: 1, size of one block: 64 bytes
-----------------------------------------------------------------
|R|F|                                                           | Level: 0, size of one block: 32 bytes
-----------------------------------------------------------------
*/

    return 0;
}
