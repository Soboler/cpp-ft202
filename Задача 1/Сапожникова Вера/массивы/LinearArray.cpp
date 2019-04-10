#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

class LinearArr {
private:
	const size_t BASE_SIZE = 10;
	int *array;
	int cnt;
	int lastIndex;
	size_t const int_size = sizeof(int);
	size_t SIZE;

	void resize()
	{
		SIZE *= 2;
		int *newArr = (int*)malloc(2 * SIZE * sizeof(int));
		memcpy(newArr, array, SIZE);
		delete[] array;
		array = newArr;
	}


public:
	LinearArr()
	{
		SIZE = BASE_SIZE;
		array = (int*)malloc(SIZE);
		cnt = 0;
		lastIndex = 0;
	}

	void set(size_t index, int value)
	{
		if (index > lastIndex)
		{
			lastIndex = index;
		}

		size_t required_size = sizeof(value) *(index + 1);
		if (required_size > SIZE)
		{
			resize();
		}
		array[index] = value;
		cnt++;
	}

	
	int get(size_t index)
	{
		if (index < 0 || index >= SIZE)
		{
			exit(-1);
		}
		return array[index];
	}

	
	void removeAll()
	{

		for (int i = 0; i < cnt; i++)
		{
			array[i] = INT_MIN;
		}
		free(array);
		cnt = 0;
		lastIndex = 0;
		array = (int*)malloc(BASE_SIZE);
	}

	size_t size(void) const { return cnt; }

	void print() {
		for (int i = 0; i < cnt; i++)
		{
			printf("%d ", array[i]);
		}
	}
};

/*int main() {
	LinearArr lc;
	for (int i = 0; i < 5; ++i) {
		lc.set(i, i + 1);
	}
	lc.print();
	printf("size: %d\n ", lc.size());
	printf("get(2): %d\n ", lc.get(2));
	printf("get(3): %d\n ", lc.get(3));
	lc.print();


	lc.removeAll();
	return 0;
}*/