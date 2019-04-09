#include<iostream>
using namespace std;

class Stack {
	int* pointer;
	size_t memorySize = pow(2, 30);
	size_t length = memorySize / sizeof(int);
	size_t lastElemIndex = -1;
public:
	Stack() {
		pointer = (int*)malloc(memorySize);
	}

	void push(int value) {
		if (lastElemIndex + 1 >= length) {
			memorySize*=2;
			int *newPointer = (int*)malloc(memorySize);
			memcpy(newPointer, pointer, length);
			length = memorySize / sizeof(int);
			delete[] pointer;
			pointer = newPointer;
		}
		lastElemIndex++;
		pointer[lastElemIndex] = value;
	}

	int pop() {
		if (lastElemIndex != -1) {
			int result = pointer[lastElemIndex];
			lastElemIndex--;
			return result;
		}
	}

	void remove_all() {
		delete[] pointer;
		memorySize = pow(2, 30);
		length = memorySize / sizeof(int);
		pointer = (int*)malloc(memorySize);
	}

	~Stack() {
		delete[] pointer;
	}
};