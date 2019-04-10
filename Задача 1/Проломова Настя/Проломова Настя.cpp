#include<iostream>
using namespace std;

class LinearArr {
private:

	int *startPtr;
	int offset;
	size_t const int_size = sizeof(int);
	size_t SIZE;

	void resize() {
		SIZE *= 2;
		int *ptr = (int*)malloc(SIZE);
		for (int i = 0; i < offset; i ++) {
			*(ptr + i * int_size) = *(startPtr + i * int_size);
		}
		free(startPtr);
		startPtr = ptr;
	}


public:
	LinearArr() {
		SIZE = 1024;
		startPtr = (int*)malloc(SIZE);
		offset = 0;
	}

	void set(size_t index, int value) {
		if (offset * int_size > SIZE * 0.75)
			resize();
		startPtr[index] = value;
		offset++;
	}

	int get(size_t index) {
		if (index >= SIZE)
		{
			throw range_error("Index is out of range");
		}
		return startPtr[index];
	}

	void remove_all() {
		for (int i = 0; i < offset; i++)
			startPtr[i] = INT_MIN;
		free(startPtr);
		offset = 0;
		SIZE = 1024;
		startPtr = (int*)malloc(SIZE);
	}
};


class Stack {
private:

	int *startPtr;
	size_t const int_size = sizeof(int);
	size_t SIZE;
	int offset;

	void resize() {
		SIZE *= 2;
		int *ptr = (int*)malloc(SIZE);
		for (int i = 0; i < offset; i++) {
			*(ptr + i * int_size) = *(startPtr + i * int_size);
		}
		free(startPtr);
		startPtr = ptr;
	}

public:
	Stack() {
		SIZE = 1024;
		startPtr = (int*)malloc(SIZE);
		offset = 0;
	}

	void push_back(int value) {
		if (offset *int_size > SIZE * 0.75)
			resize();
		startPtr[offset] = value;
		offset++;
	}

	int pop_back() {
		if (offset == 0)
			throw range_error("Empty stack");
		offset--;
		int value = startPtr[offset];
		startPtr[offset] = INT_MIN;
		return value;
	}

	void remove_all() {
		for (int i = 0; i < offset; i++)
			startPtr[i] = INT_MIN;
		free(startPtr);
		startPtr = (int*)malloc(SIZE);
		offset = 0;
		SIZE = 1024;
	}
};



struct Node {
	int value;
	Node *child;
	Node *parent;
};

class LinkedList {
private:

	Node *startPtr;
	Node *endPtr;
	int offset;
	size_t const int_size = sizeof(int);

public:
	LinkedList() {
		startPtr = NULL;
		endPtr = NULL;
		offset = 0;
	}

	void push_back(int value) {
		Node *ptr = (Node*)malloc(int_size);
		if (offset == 0)
			startPtr = ptr;
		if (endPtr != NULL)
			endPtr->child = ptr;
		ptr->value = value;
		ptr->child = NULL;
		ptr->parent = endPtr;
		endPtr = ptr;
		offset++;
	}

	int pop_back() {
		int value = endPtr->value;
		Node* toPop = endPtr;
		endPtr = endPtr->parent;
		endPtr->child = NULL;
		offset--;
		return value;
	}

	void set(int index, int value) {
		if (index >= offset)
			throw range_error("Index out of range");
		Node *curr_node = startPtr;
		int i = 0;
		while (i != index) {
			curr_node = curr_node->child;
			i++;
		}
		curr_node->value = value;
	}

	int get(int index) {
		if (index >= offset)
			throw range_error("Index out of range");
		Node *curr_node = startPtr;
		int i = 0;
		while (i != index) {
			curr_node = curr_node->child;
			i++;
		}
		return curr_node->value;
	}

	void remove_all() {
		offset = 0;
		Node *curr_node = startPtr;
		while (curr_node != NULL) {
			Node *child = curr_node->child;
			curr_node = child;
		}
		startPtr = NULL;
		endPtr = NULL;
	}
};


int main() {
	LinearArr arr;
	arr.set(0, 0);
	arr.set(1, 1);
	arr.set(2, 2);
	cout << arr.get(0) << endl;
	arr.set(2, 3);
	cout << arr.get(1) << endl;
	cout << arr.get(2) << endl;
	arr.remove_all();
	cout << arr.get(0) << endl;

	Stack stack;
	stack.push_back(0);
	stack.push_back(1);
	stack.push_back(2);
	cout << stack.pop_back() << endl;
	stack.push_back(3);
	cout << stack.pop_back() << endl;
	cout << stack.pop_back() << endl;
	cout << stack.pop_back() << endl;
	stack.remove_all();

	LinkedList list;
	list.push_back(0);
	list.push_back(1);
	list.push_back(2);
	cout << list.pop_back() << endl;
	cout << list.get(0) << endl;
	cout << list.get(1) << endl;
	list.set(1, 4);
	cout << list.get(1) << endl;
	list.remove_all();
}
