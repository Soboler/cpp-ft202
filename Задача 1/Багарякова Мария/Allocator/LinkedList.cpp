#include<iostream>
using namespace std;

struct ListItem {
	int value;
	ListItem* next;
};

class LinkedList {
	ListItem* first;
	size_t length;
public:
	LinkedList() {
		first = (ListItem*)malloc(sizeof(ListItem));
		first->next = NULL;
		length = 1;
	}

	void set(int index, int value) {
		ListItem* current = first;
		for (int i = 0; i < index; i++) {
			if (current->next == NULL) {
				current->next = (ListItem*)malloc(sizeof(ListItem));
			}
			current = current->next;
		}
		current->value = value;
	}

	int get(int index) {
		if (index < length && index >= 0) {
			ListItem* current = first;
			for (int i = 0; i < index; i++) {
				current = current->next;
			}
			return current->value;
		}
	}

	void push_back(int value) {
		ListItem *current = first;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = (ListItem*)malloc(sizeof(ListItem));
		length++;
		current->next->value = value;
		current->next->next = NULL;
	}

	int pop_back() {
		if (length > 1) {
			ListItem* current = first;
			while (true) {
				ListItem* current = current->next;
				if (current->next == NULL)
					break;
			}
			int value = current->value;
			length--;
			delete current;
			return value;
		}
	}

	void remove_all() {
		ListItem* current = first;
		while (current != NULL) {
			ListItem* next = current->next;
			delete current;
			current = next;
		}
		first = (ListItem*)malloc(sizeof(ListItem));
		first->next = NULL;
		length = 1;
	}

	~LinkedList() {
		ListItem* current = first;
		while (current != NULL) {
			ListItem* next = current->next;
			delete current;
			current = next;
		}
	}
};