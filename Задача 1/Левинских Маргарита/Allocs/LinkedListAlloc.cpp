#include "pch.h"
#include <iostream>
using namespace std;


struct ArrElem
{
	int value;
	ArrElem* next;
};

class Arr
{
	ArrElem *root;
	size_t count; // кол-во ArrElem

public:
	Arr()
	{
		count = 0;
	}

	void add_root()
	{
		root = (ArrElem*)malloc(sizeof(ArrElem));
		root->next = NULL;
		count++;
	}

	int get(int index)
	{
		if (check_boundaries(index))
		{
			ArrElem *current = root;
			for (int i = 0; i < index; i++)
			{
				current = current->next;
			}
			return current->value;
		}
	}

	void set(int index, int value)
	{
		if (root == NULL)
		{
			add_root();
		}
		ArrElem *current = root;
		for (int i = 0; i < index; i++)
		{
			if (current->next == NULL)
			{
				current->next = (ArrElem*)malloc(sizeof(ArrElem));
			}
			current = current->next;
		}
		current->value = value;
	}

	int operator[](int index)
	{
		return get(index);
	}

	int pop_back()
	{
		if (count == 0) 
			throw out_of_range("No items");
		ArrElem *current = root;
		ArrElem *prev = root;
		for (int i = 0; i < count; i++)
		{
			prev = current;
			current = current->next;
		}
		int value = current->value;
		prev->next = NULL;
		delete current;
		count--;
		return value;
	}

	void push_back(int value)
	{
		if (root == NULL)
		{
			add_root();
			root->value = value;
		}
		else
		{
			ArrElem *current = root;
			while (current->next != NULL)
			{
				current = current->next;
			}
			current->next = (ArrElem*)malloc(sizeof(ArrElem));
			current->next->value = value;
			current->next->next = NULL;
			count++;
		}
	}

	void remove_all()
	{
		ArrElem *current = root;
		ArrElem *next;
		while (current != NULL)
		{
			next = current->next;
			delete current;
			current = next;
		}
		root = NULL;
	}

private:

	bool check_boundaries(int index)
	{
		if (index > count - 1 || index < 0)
		{
			throw out_of_range("Index was out of range");
		}
		return true;
	}
};