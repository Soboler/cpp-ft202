#pragma once

#include "pch.h"
#include <iostream>

class LinearArr
{
	int *arr;
	int size;
	int last;

public:
	LinearArr(int n);

	int get(int index);

	void set(int index, int value);

	int pop_back();

	int operator[](int index);

	void push_back(int value);

	void remove_all();

private:

	void extend();

	bool check_boundaries(int index);
};