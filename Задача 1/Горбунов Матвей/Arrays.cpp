#include <iostream>
#include <malloc.h>
using namespace std;

class Arr
{
private:
	int* inner;
	int capacity;

	void enlarge()
	{
		const auto new_capacity = capacity * 2;
		const auto new_inner = (int*)malloc(new_capacity * sizeof(int));
		for (auto i = 0; i < capacity; i++)
			new_inner[i] = inner[i];
		free(inner);
		capacity = new_capacity;
		inner = new_inner;
	}

public:
	int length;

	Arr()
	{
		length = 0;
		capacity = 2;
		inner = (int*)malloc(capacity * sizeof(int));
	}

	int get(const int index) const
	{
		if (index < 0 || index >= capacity)
			throw out_of_range("out of range");
		return inner[index];
	}

	void set(const int index, const int value)
	{
		if (index < 0)
			throw out_of_range("out of range");
		while (index >= capacity)
			enlarge();
		if (index >= length)
		{
			for (auto i = length; i < index; i++)
				inner[i] = 0;
			length = index + 1;
		}
		inner[index] = value;
	}

	void push_back(const int value)
	{
		length++;
		set(length - 1, value);
	}

	int pop_back()
	{
		if (length == 0)
			throw out_of_range("out of range");
		length--;
		return get(length);
	}

	void remove_all()
	{
		length = 0;
	}

	~Arr()
	{
		free(inner);
	}
};

class Stack
{
private:
	int* inner;
	int capacity;

	void enlarge()
	{
		const auto new_capacity = capacity * 2;
		const auto new_inner = (int*)malloc(new_capacity * sizeof(int));
		for (auto i = 0; i < capacity; i++)
			new_inner[i] = inner[i];
		free(inner);
		capacity = new_capacity;
		inner = new_inner;
	}


public:
	int length;

	Stack()
	{
		length = 0;
		capacity = 2;
		inner = (int*)malloc(capacity * sizeof(int));
	}

	void push(const int value)
	{
		while (length >= capacity)
			enlarge();
		inner[length] = value;
		length++;
	}

	int pop()
	{
		if (length == 0)
		{
			throw out_of_range("out of range");
		}
		length--;
		return inner[length];
	}

	void remove_all()
	{
		length = 0;
	}

	~Stack()
	{
		free(inner);
	}
};

class Linked_List
{
	struct Node
	{
		Node *prev;
		Node *next;
		int value;
	};

private:
	Node *tail;
	Node *head;
	int length;

public:
	Linked_List()
	{
		tail = NULL;
		head = NULL;
		length = 0;
	}

	void set(int index, int value)
	{
		//тк список связный, то set() и get() работают только с существующими элементами
		if (index >= length)
		{
			throw out_of_range("out of range");
		}
		auto *current = tail;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		current->value = value;
	}

	int get(int index)
	{

		if (index > length)
		{
			throw out_of_range("out of range");
		}
		auto *current = tail;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		return current->value;
	}

	void push_back(int value)
	{
		auto *node = (Node*)malloc(sizeof(int));
		if (head != NULL)
			head->next = node;
		if (length == 0)
			tail = node;
		node->next = NULL;
		node->prev = head;
		node->value = value;
		head = node;
		length++;
	}

	int pop_back()
	{
		int value = head->value;
		head = head->prev;
		head->next = NULL;
		length--;
		return value;
	}

	void remove_all() {
		length = 0;
		auto *current = tail;
		while (current != NULL)
		{
			auto *next = current->next;
			current = next;
		}
		tail = NULL;
		head = NULL;
	}

	~Linked_List()
	{
		Node *next;
		while (next == tail->next)
		{
			delete tail;
			tail = next;
		}
	}
};

int main()
{
	Arr arr;
	Stack stack;
	Linked_List list;

	// do tests here

	return 0;
}