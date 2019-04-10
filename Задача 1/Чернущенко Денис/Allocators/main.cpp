#include <iostream>
#include "Allocator.h"
#include "LinearAllocator.h"
#include "StackAllocator.h"
#include "LinkedListAllocator.h"

using namespace std;

void testAllocator(Allocator& allocator)
{
    cout << "arr.getMemoryBlockSize(): " << allocator.getMemoryBlockSize() << endl;
    cout << "arr.getMemoryBlockCapacity(): " << allocator.getMemoryBlockCapacity() << endl;
    cout << endl;

    allocator[allocator.getMemoryBlockCapacity()] = 10;
    cout << "allocator[allocator.getMemoryBlockCapacity()] = 10;" << endl;
    cout << "Length: " << allocator.getLength() << endl;
    cout << "arr.getMemoryBlockSize(): " << allocator.getMemoryBlockSize() << endl;
    cout << "arr.getMemoryBlockCapacity(): " << allocator.getMemoryBlockCapacity() << endl;
    cout << endl;

    allocator.pop();
    cout << "allocator.pop();" << endl;
    cout << "Length: " << allocator.getLength() << endl;
    cout << "arr.getMemoryBlockSize(): " << allocator.getMemoryBlockSize() << endl;
    cout << "arr.getMemoryBlockCapacity(): " << allocator.getMemoryBlockCapacity() << endl;

    cout << endl;
    allocator.set(789, 3);
    cout << "allocator.set(789, 3);" << endl;

    for (int i = 0; i < 100; ++i)
        cout << allocator[i] << ' ';

    cout << endl << endl;

    allocator.removeAll();
    cout << "allocator.removeAll();" << endl;

    cout << endl;

    cout << "Length: " << allocator.getLength() << endl;
    cout << "arr.getMemoryBlockSize(): " << allocator.getMemoryBlockSize() << endl;
    cout << "arr.getMemoryBlockCapacity(): " << allocator.getMemoryBlockCapacity() << endl;
}

int main()
{
    LinearAllocator linearAllocator;
    StackAllocator stackAllocator;
    LinkedListAllocator linkedListAllocator;

    Allocator* allocators[] = {&linearAllocator, &stackAllocator, &linkedListAllocator};

    for (auto & allocator : allocators)
    {
        testAllocator(*allocator);

        cout << endl << "--------------------------------------" << endl;
    }

    return 0;
}
