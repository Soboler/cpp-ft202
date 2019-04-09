#pragma once
#include <cstddef>

struct node
{
	node* previous = NULL;
	int value;
	node* next = NULL;

	node(int value);
};
