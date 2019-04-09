#pragma once

#include "pch.h"
#include <iostream>

class StackArr
{
	int *arr;
	int size;
	int last;

public:
	StackArr(int n);

	int pop_back();

	void push_back(int value);

	void remove_all();

private:

	void extend();
};