#include<iostream>
using namespace std;

class LinearArray {
	int* pointer;
	size_t memorySize = pow(2, 30);
	size_t length = memorySize / sizeof(int);
public:
	LinearArray() {
		pointer = (int*)malloc(memorySize);
	}

	void set(int index, int value) {
		if (index >= length) {
			while (index >= length) {
				memorySize*=2;
				int *newPointer = (int*)malloc(memorySize);
				memcpy(newPointer, pointer, length);
				length = memorySize / sizeof(int);
				delete[] pointer;
				pointer = newPointer;
			}
		}
		pointer[index] = value;
	}

	int get(int index) {
		if (index < length && index >= 0) {
			return pointer[index];
		}
	}

	void remove_all() {
		delete[] pointer;
		memorySize = pow(2, 30);
		length = memorySize / sizeof(int);
		pointer = (int*)malloc(memorySize);
	}

	~LinearArray() {
		delete[] pointer;
	}
};

int main() {

}