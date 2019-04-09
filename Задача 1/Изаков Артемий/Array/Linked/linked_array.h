#pragma once
#include "node.h"

class linked_array
{
	node* head = NULL;
	node* tail = NULL;
	int length = 0;

public:
	void push_back(int value);

	int pop_back();

	void set(const int index, int value) const;

	int get(const int index) const;

	void remove_all();

	~linked_array();

private:
	void check_index(const int index) const;

	node* get_node(const int index) const;
};
