#include <iostream>
#include "buddy.h"

using namespace std;

int main()
{
	auto allocator = new buddy(128);
	auto first = allocator->Alloc(64);
	auto second = allocator->Alloc(32);
	auto third = allocator->Alloc(16);
	auto fourth = allocator->Alloc(8);
	auto fifth = allocator->Alloc(8);
	allocator->Dump();
	cout << "" << endl;

	allocator->Free(first);
	allocator->Free(third);
	allocator->Dump();
	cout << "" << endl;

	auto newest = allocator->Alloc(10);
	allocator->Dump();
	cout << "" << endl;

	allocator->Free(newest);
	allocator->Dump();
}
