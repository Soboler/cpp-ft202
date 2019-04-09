#include "pch.h"
#include "linked_array.h"
#include <stdexcept>

using namespace std;

void linked_array::push_back(const int value)
{
	auto* new_node = new node(value);

	if (head == NULL)
	{
		head = new_node;
		tail = new_node;
	}
	else
	{
		tail->next = new_node;
		new_node->previous = tail;
		tail = new_node;
	}
	length++;
}

int linked_array::pop_back()
{
	if (length == 0)
		throw out_of_range("no elements left");

	const auto value = head->value;

	if (length == 1)
	{
		delete head;
		head = NULL;
		tail = NULL;
		return value;
	}

	auto* previous_node = tail->previous;
	previous_node->next = NULL;

	delete tail;

	tail = previous_node;
	length--;

	return value;
}

void linked_array::set(const int index, const int value) const
{
	check_index(index);

	auto* new_node = new node(value);
	auto* old_node = get_node(index);

	new_node->previous = old_node->previous;
	new_node->next = old_node->next;

	old_node->previous->next = new_node;
	old_node->next->previous = new_node;

	delete old_node;
}

int linked_array::get(const int index) const
{
	check_index(index);
	return get_node(index)->value;
}

void linked_array::remove_all()
{
	if (length == 0)
		return;

	auto* current_node = head->next;
	while (current_node != NULL)
	{
		delete current_node->previous;
		current_node = current_node->next;
	}
	delete tail;

	head = NULL;
	tail = NULL;
	length = 0;
}

linked_array::~linked_array()
{
	remove_all();
}

void linked_array::check_index(const int index) const
{
	if (index < 0 || index >= length)
		throw out_of_range("index out of range");
}

node* linked_array::get_node(const int index) const
{
	auto* current = head;
	auto current_index = 0;

	while (current_index < index)
	{
		current = current->next;
		current_index++;
	}

	return current;
}
