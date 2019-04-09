#include "pch.h"
#include "LinkedArray.h"
using namespace std;


LinkedArr::LinkedArr()
{
	size = 0;
}

void LinkedArr::set(int index, int value)
{
	if (check_boundaries(index))
	{
		Node *current = head;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		current->value = value;
	}
}

int LinkedArr::get(int index)
{
	if (check_boundaries(index))
	{
		Node *current = head;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		return current->value;
	}
}

int LinkedArr::operator[](int index)
{
	return get(index);
}

int LinkedArr::pop_back()
{
	if (size == 0) throw out_of_range("No items");
	Node *current = head;
	Node *prev = head;
	while (current->next != NULL)
	{
		prev = current;
		current = current->next;
	}
	int value = current->value;
	prev->next = NULL;
	delete current;
	size -= 1;
	return value;
}

void LinkedArr::push_back(int value)
{
	if (head == NULL)
	{
		head = (Node*)malloc(sizeof(Node));
		head->value = value;
		head->next = NULL;
		size += 1;
	}
	else
	{
		Node *current = head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = (Node*)malloc(sizeof(Node));
		current->next->value = value;
		current->next->next = NULL;
		size += 1;
	}
}

void LinkedArr::remove_all()
{
	Node *current = head;
	Node *next;
	while (current != NULL)
	{
		next = current->next;
		delete current;
		current = next;
	}
	head = NULL;
}


bool LinkedArr::check_boundaries(int index)
{
	if (index > size - 1 || index < 0)
	{
		throw out_of_range("Index was out of range");
	}
	return true;
}