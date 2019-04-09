#pragma once

#include "pch.h"
#include <iostream>

struct Node
{
	int value;
	Node* next;
};

class LinkedArr
{

	Node *head;
	size_t size;

public:
	LinkedArr();

	void set(int index, int value);

	int get(int index);

	int operator[](int index);

	int pop_back();

	void push_back(int value);

	void remove_all();

private:

	bool check_boundaries(int index);
};