/*
Связный список
*/


#include <iostream>
#include <cstddef>

template <typename T>

class Node {
public:
	Node(){}
	explicit Node(T data) {
		item = data;
	}

	void setData(T data) {
		item = data;
	}

	T getData() {
		return item;
	}

	T item;
	Node<T>* next;
};

template <typename T>

class LinkedList {
public:
	LinkedList() {
		_size = 0;
	}

	void add(T item) {
		Node<T>* node = new Node<T>(item);
		if (_size == 0) {
			last = *node;
			first = *node;
		}
		else {
			last.next = node;
			last = *node;
		}
		_size++;
	}

	T& operator [](int i) {
		if (i < 0 || i > _size) {
			throw "out of range";
		}
		int count = 0;
		Node<T>* node = &first;
		while (node != NULL) {
			if (count == i)
				return node->item;
			else
				node = node->next;
			count++;
		}
	}

	int size() {
		return _size;
	}

private:
	int _size = 0;
	Node<T> first;
	Node<T> last;
};
