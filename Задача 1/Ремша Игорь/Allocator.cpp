#include<pch.h>
#include<iostream>
using namespace std;

class LinearArr {
private:
	const size_t BASE_SIZE = 1024;
	int *arr;
	int offset;
	int lastIndex;
	size_t const int_size = sizeof(int);
	size_t SIZE;

	void resize()
	{
		SIZE *= 2;
		int *newArr = (int*)malloc(2 * SIZE * sizeof(int));
		memcpy(newArr, arr, SIZE);
		delete[] arr;
		arr = newArr;
	}


public:
	LinearArr()
	{
		SIZE = BASE_SIZE;
		arr = (int*)malloc(SIZE);
		offset = 0;
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
		arr[index] = value;
		offset++;
	}

	void push_back(int value)
	{
		offset++;
		lastIndex++;
		size_t necessary_size = sizeof(value) *(lastIndex + 1);
		while (necessary_size > SIZE)
		{
			resize();
		}
		arr[lastIndex] = value;
	}

	int get(size_t index)
	{
		if (index < 0 || index >= SIZE)
		{
			throw range_error("Index is out of range");
		}
		return arr[index];
	}

	int pop_back()
	{

		if (offset == 0)
		{
			throw out_of_range("no elements left");
		}
		return arr[lastIndex];
	}

	void remove_all()
	{
		for (int i = 0; i < offset; i++)
		{
			arr[i] = INT_MIN;
		}
		free(arr);
		offset = 0;
		lastIndex = 0;
		arr = (int*)malloc(BASE_SIZE);
	}
};

class StackAllocator
{
private:
	const size_t BASE_SIZE = 1024;
	int *arr;
	int offset;
	size_t const int_size = sizeof(int);
	size_t SIZE;

	void resize()
	{
		SIZE *= 2;
		int *newArr = (int*)malloc(2 * SIZE * sizeof(int));
		memcpy(newArr, arr, SIZE);
		delete[] arr;
		arr = newArr;
	}

public:
	StackAllocator()
	{
		SIZE = BASE_SIZE;
		arr = (int*)malloc(SIZE);
		offset = 0;
	}
	void push_back(int value)
	{
		offset++;
		size_t necessary_size = sizeof(value) *(offset);
		while (necessary_size > SIZE)
		{
			resize();
		}
		arr[offset - 1] = value;
	}

	int pop_back()
	{
		if (offset == 0)
		{
			throw out_of_range("no elements left");
		}

		offset--;
		return arr[offset];
	}

	void remove_all()
	{
		for (int i = 0; i < offset; i++)
		{
			arr[i] = INT_MIN;
		}
		free(arr);
		offset = 0;
		arr = (int*)malloc(BASE_SIZE);
	}
};


struct Node {
	int value;
	Node* next;
};

class LinkedAllocator
{
private:
	Node* head;
	size_t length;


public:
	LinkedAllocator() 
	{
		head = (Node*)malloc(sizeof(Node));
		head->next = NULL;
		length = 1;
	}

	void set(int index, int value) 
	{
		Node* current = head;
		for (int i = 0; i < index; i++) 
		{
			if (current->next == NULL) 
			{
				current->next = (Node*)malloc(sizeof(Node));
			}
			current = current->next;
		}
		current->value = value;
	}

	int get(int index) 
	{
		if (index < length && index >= 0) 
		{
			Node* current = head;
			for (int i = 0; i < index; i++) 
			{
				current = current->next;
			}
			return current->value;
		}
	}

	void push_back(int value) 
	{
		Node *current = head;
		while (current->next != NULL) 
		{
			current = current->next;
		}
		current->next = (Node*)malloc(sizeof(Node));
		length++;
		current->next->value = value;
		current->next->next = NULL;
	}

	int pop_back() 
	{
		if (length == 0) 
		{ throw out_of_range("No items"); 
		}

		Node* current = head;
		while (current->next != NULL) 
		{
			Node* current = current->next;
		}
		int value = current->value;
		length--;
		delete current;
		return value;
		
	}

	void remove_all() 
	{
		Node* current = head;
		while (current != NULL) 
		{
			Node* next = current->next;
			delete current;
			current = next;
		}
		head = (Node*)malloc(sizeof(Node));
		head->next = NULL;
		length = 1;
	}
};




int main() {
	cout << "LinearArr:" << endl;
	LinearArr arr;
	arr.set(0, 0);
	arr.set(1, 1);
	arr.set(256, 256);
	cout << arr.get(256) << endl;
	arr.set(2, 3);
	cout << arr.get(1) << endl;
	cout << arr.get(2) << endl;
	arr.remove_all();
	cout << arr.get(0) << endl;
	arr.set(4, 4);
	arr.set(128, 128);
	arr.push_back(129);
	cout << arr.pop_back() << endl;
	cout << arr.pop_back() << endl;
	cout << "LinearArr - END\n" << endl;

	cout << "StackAllocator:" << endl;
	StackAllocator stackArr;
	stackArr.push_back(1);
	stackArr.push_back(2);
	stackArr.push_back(3);
	cout << stackArr.pop_back() << endl;
	cout << stackArr.pop_back() << endl;
	cout << stackArr.pop_back() << endl;
	stackArr.push_back(4);
	cout << stackArr.pop_back() << endl;
	cout << "StackAllocator - END\n" << endl;

	cout << "LinkedAllocator:" << endl;
	LinkedAllocator linkedArr;
	linkedArr.set(0, 0);
	cout << linkedArr.get(0) << endl;
	cout << "LinkedAllocator - END\n" << endl;

}