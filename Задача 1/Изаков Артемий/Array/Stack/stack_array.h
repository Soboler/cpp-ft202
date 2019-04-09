#pragma once

class stack_array
{
private:
	int* inner;

	int capacity;
	int length;

	void enlarge();

	void check_index(int index) const;

public:

	stack_array();

	void push_back(const int value);

	int pop_back();

	void remove_all();

	virtual ~stack_array();
};
