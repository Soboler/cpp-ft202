#include "BuddyAlloc.h"
#include "string.h"
#include "stdio.h"

void print(unsigned char* tmp)
{
	for (size_t i = 0; i < 500; i++)
	{
		printf("%02hhx", tmp[i]);
	}
}

int dump()
{
	int size = 500;

	buddy_allocator_t * buddyT = constructor(size);
	if (buddyT)
	{
		uint8_t order = 0;
		uint8_t oldOrder = 0;
		void * ptr = alloc(buddyT, 30, &order);
		void * oldPtr = NULL;
		if (ptr)
		{
			memcpy(ptr, "Test Case 1", 11);
			unsigned char* tmp = (unsigned char*)buddyT->memStart;
			print(tmp);
			printf("\n");
		}
		else
		{
			printf("Cannot allocate memory from buddy allocator\n");
		}

		ptr = alloc(buddyT, 14, &order);
		if (ptr)
		{
			memcpy(ptr, "Test Case 2", 11);
			unsigned char* tmp = (unsigned char*)buddyT->memStart;
			print(tmp);
			buddy_allocator_free(buddyT, ptr, order);
			printf("\n");
		}
		else
		{
			printf("Cannot allocate memory from buddy allocator\n");
		}


		ptr = alloc(buddyT, 15, &order);
		if (ptr)
		{
			memcpy(ptr, "Test Case 3", 11);
			unsigned char* tmp = (unsigned char*)buddyT->memStart;
			print(tmp);
		}
		else
		{
			printf("Cannot allocate memory from buddy allocator\n");
		}

		return 0;
	}
}

int main()
{
	dump();
}
