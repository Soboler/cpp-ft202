
#include "pch.h"
#include <iostream>

class LinearArray {
	const int defaultSize = 1024;
	int size;
	int *firstElemPtr;
	int count;

	void resize(int newSize) {
		int oldSize = size;
		int *oldFirstElem = firstElemPtr;
		size = newSize;
		firstElemPtr = (int*)malloc(size);
		if (firstElemPtr == NULL)
			throw new std::bad_alloc;
		for (int i = 0; i < oldSize; i++)
			*(firstElemPtr + i) = *(oldFirstElem + i);
	}

public:
	LinearArray() {
		size = defaultSize;
		firstElemPtr = (int*)malloc(size);
	}
	~LinearArray() {
		free(firstElemPtr);
	}

	int get(int index) {
		if (index >= count)
			throw new std::out_of_range("");
		return *(firstElemPtr + index);
	}

	void set(int index, int value) {
		if (index > count)
			throw new std::out_of_range("");
		if (index == count)
			push_back(value);
		*(firstElemPtr + index) = value;
	}

	void push_back(int value) {
		if (count == size)
			resize(size * 2);
		*(firstElemPtr + count) = value;
		count++;
	}

	int pop_back() {
		if (count <= 0)
			throw new std::out_of_range("");
		count--;
		return *(firstElemPtr + count);
	}

	void remove_all() {
		count = 0;
		resize(defaultSize);
	}
};

class Stack {
	const int defaultSize = 1024;
	int size;
	int *firstElemPtr;
	int count;

	void resize(int newSize) {
		int oldSize = size;
		int *oldFirstElem = firstElemPtr;
		size = newSize;
		firstElemPtr = (int*)malloc(size);
		if (firstElemPtr == NULL)
			throw new std::bad_alloc;
		for (int i = 0; i < oldSize; i++)
			*(firstElemPtr + i) = *(oldFirstElem + i);
	}

public:
	Stack() {
		size = defaultSize;
		firstElemPtr = (int*)malloc(size);
	}
	~Stack() {
		free(firstElemPtr);
	}

	void push_back(int value) {
		if (count == size)
			resize(size * 2);
		*(firstElemPtr + count) = value;
		count++;
	}

	int pop_back() {
		if (count <= 0)
			throw new std::out_of_range("");
		count--;
		return *(firstElemPtr + count);
	}

	void remove_all() {
		count = 0;
		resize(defaultSize);
	}
};

class LinkedArray {
	struct LinkedNode {
		int value;
		LinkedNode *prevElemPtr;
		LinkedNode *nextElemPtr;
	};

	LinkedNode *firstElemPtr;
	LinkedNode *lastElemPtr;
	int count;

	LinkedNode getNode(int index) {
		if (index >= count)
			throw new std::out_of_range("");
		LinkedNode *current = firstElemPtr;
		while (index > 0) {
			current = current->nextElemPtr;
			index--;
		}
		return *current;
	}

public:
	LinkedArray() {
		firstElemPtr = NULL;
		lastElemPtr = NULL;
	}

	int get(int index) {
		return getNode(index).value;
	}

	void set(int index, int value) {
		if (index > count)
			throw new std::out_of_range("");
		if (index == count) {
			push_back(value);
		}
		else {
			LinkedNode *current = firstElemPtr;
			while (index > 0) {
				current = current->nextElemPtr;
				index--;
			}
			current->value = value;
		}
	}

	void push_back(int value) {
		LinkedNode *newNode = (LinkedNode*)malloc(sizeof(int));
		if (count == 0) {
			firstElemPtr = newNode;
		}
		if (lastElemPtr != NULL)
			lastElemPtr->nextElemPtr = newNode;
		newNode->value = value;
		newNode->prevElemPtr = lastElemPtr;
		lastElemPtr = newNode;
		count++;
	}

	int pop_back() {
		if (count <= 0)
			throw new std::out_of_range("");
		count--;
		LinkedNode elem = *lastElemPtr;
		lastElemPtr = elem.prevElemPtr;
		return elem.value;
	}

	void remove_all() {
		count = 0;
		LinkedNode *current = lastElemPtr;
		while (current != NULL) {
			LinkedNode *nextCurrent = current->prevElemPtr;
			current->prevElemPtr = NULL;
			current->nextElemPtr = NULL;
		}
		firstElemPtr = NULL;
		lastElemPtr = NULL;
	}
};

int main()
{
	LinearArray linear = LinearArray();
	for (int i = 0; i < 10; i++)
		linear.push_back(i);
	std::cout << "at index 7: " << linear.get(7) << std::endl;
	linear.set(6, 66);
	std::cout << "at index 6 after set: " << linear.get(6) << std::endl;
	for (int i = 0; i < 10; i++) {
		int current = linear.pop_back();
		std::cout << "linear pop: " << current << std::endl;
	}
	std::getchar();
	//----------------------
	Stack stack = Stack();
	for (int i = 0; i < 10; i++)
		stack.push_back(i);
	for (int i = 0; i < 10; i++) {
		int current = stack.pop_back();
		std::cout << "stack pop: " << current << std::endl;
	}
	std::getchar();
	//-----------------------
	LinkedArray linked = LinkedArray();
	for (int i = 0; i < 10; i++)
		linked.push_back(i);
	std::cout << "at index 7: " << linked.get(7) << std::endl;
	linked.set(6, 66);
	std::cout << "at index 6 after set: " << linked.get(6) << std::endl;
	for (int i = 0; i < 10; i++) {
		int current = linked.pop_back();
		std::cout << "linked pop: " << current << std::endl;
	}
	std::getchar();
}