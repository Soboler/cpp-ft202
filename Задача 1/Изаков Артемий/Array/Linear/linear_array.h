#pragma once

class linear_array
{
private:
	int* inner;

	int capacity;
	int length;

	void enlarge();

	void check_index(const int index) const;

public:

	linear_array();

	int get(const int index) const;

	void set(const int index, const int value) const;

	void push_back(const int value);

	int pop_back();

	void remove_all();

	~linear_array();
};
