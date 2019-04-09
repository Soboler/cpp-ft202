// LinearAllocator.cpp: определяет точку входа для консольного приложения.
//

#include "LinearAllocator.h"
#include "StackAllocator.h"
#include "PoolAllocator.h"
#include <iostream>
using namespace std;

using byte = uint8_t;

class TestClass {
	public:
	char val1;
	int val0;
	double val2;
};


namespace LinearTest {
	template <class T> T* allocateNew(LinearAllocator& allocator)
	{
		return new (allocator.allocate(sizeof(T), __alignof(T))) T;
	}

	void main()
	{
		byte buffer[100];
		LinearAllocator* alloc = new LinearAllocator(100, &buffer);
		TestClass* test = allocateNew<TestClass>(*alloc);
		test->val1 = 'a';
		test->val0 = 'a';
		TestClass* test1 = allocateNew<TestClass>(*alloc);
		test1->val1 = 'b';
		test1->val0 = 'b';
		cout << "Hello " << test->val1 << test->val0 << endl;
		cout << "Hello " << test1->val1 << test1->val0 << endl;
		alloc->clear();
		test1 = allocateNew<TestClass>(*alloc);
		test1->val1 = 'b';
		test1->val0 = 'b';
		cout << "Object  " << test << " has same adress with " << test1 << endl;
		cout << "Hello " << test->val1 << test->val0 << endl;
	}
}

namespace StackTest {

	template <class T> T* allocateNew(StackAllocator& allocator)
	{
		return new (allocator.allocate(sizeof(T), __alignof(T))) T;
	}

	template <class T> void deallocateDelete(StackAllocator& allocator, T& object)
	{
		object.~T();
		allocator.deallocate(&object);
	}

	void main()
	{
		byte buffer[100];
		StackAllocator* alloc = new StackAllocator(100, &buffer);
		TestClass* test = allocateNew<TestClass>(*alloc);
		test->val1 = 'a';
		test->val0 = 'a';
		TestClass* test1 = allocateNew<TestClass>(*alloc);
		test1->val1 = 'b';
		test1->val0 = 'b';
		cout << "Hello " << test->val1 << test->val0 << endl;
		cout << "Hello " << test1->val1 << test1->val0 << endl;
		int diff = (reinterpret_cast<uptr>(test1) - reinterpret_cast<uptr>(test));
		cout << diff << " if it equals 24 then objects follow by each other (16 obj + 8 header)" << endl;
		deallocateDelete<TestClass>(*alloc, *test1);
		TestClass* test2 = allocateNew<TestClass>(*alloc);
		cout << test1 << " test and test2 have the same address now, as we deleted test1 and test2 took its place" << test2 << endl;
	}
}

namespace PoolTest {

	template <class T> T* allocateNew(PoolAllocator& allocator)
	{
		return new (allocator.allocate(sizeof(T), __alignof(T))) T;
	}

	template <class T> void deallocateDelete(PoolAllocator& allocator, T& object)
	{
		object.~T();
		allocator.deallocate(&object);
	}

	void main()
	{
		byte buffer[102];
		PoolAllocator* alloc = new PoolAllocator(sizeof(TestClass), __alignof(TestClass), 102, &buffer);
		TestClass* test = allocateNew<TestClass>(*alloc);
		TestClass* test1 = allocateNew<TestClass>(*alloc);
		int diff = (reinterpret_cast<uptr>(test1) - reinterpret_cast<uptr>(test));
		cout << diff << "if diff is 16, objects go each one by one, " << endl;
		deallocateDelete<TestClass>(*alloc, *test);
		TestClass* test2 = allocateNew<TestClass>(*alloc);
		int diff1 = (reinterpret_cast<uptr>(test2) - reinterpret_cast<uptr>(test1));
		cout << diff1 << "test2 goes before test1, as we deleted test, test2 took its place " << endl;
	}
}


int main(void)
{
	LinearTest::main();
	StackTest::main();
	PoolTest::main();
	return 0;
}


