#include "pch.h"
#include <iostream>

using namespace std;


class stack
{
	int* arr_;
	int ptr_;
	int size_;

	void extend_array()
	{
		int* temp = new int[size_ * 2];
		for (int i = 0; i < size_; i++) {
			temp[i] = arr_[i];
		}
		size_ = size_ * 2;
		delete[] arr_;
		arr_ = temp;
	}

public:
	stack()
	{
		size_ = 64;
		arr_ = new int[size_];
		ptr_ = 0;
	}

	int pop()
	{
		ptr_--;
		return arr_[ptr_];
	}

	void push(int value)
	{
		if (ptr_ > size_)
		{
			extend_array();
		}
		arr_[ptr_] = value;
		ptr_++;
	}

	int count()
	{
		return ptr_;
	}
};

class linear
{
	int* arr_;
	int size_;
	int max_index_;

	void extendarray()
	{
		int* temp = new int[size_ * 2];
		for (int i = 0; i < size_; i++) {
			temp[i] = arr_[i];
		}
		size_ = size_ * 2;
		delete[] arr_;
		arr_ = temp;
	}

public:
	int& operator[] (const int index)
	{
		return arr_[index];
	}

	linear()
	{
		size_ = 64;
		arr_ = new int[size_];
		max_index_ = 0;
	}

	int get(int index)
	{
		if (index > size_)
			throw "Argument out of range";
		return arr_[index];
	}

	void set(int index, int value)
	{
		while (index > size_)
			extendarray();

		if (index > max_index_)
			max_index_ = index;

		arr_[index] = value;
	}

	void remove_all()
	{
		int* temp = new int[size_];
		delete[] arr_;
		arr_ = temp;
	}

	void push_back(int value)
	{
		set(max_index_ + 1, value);
	}

	int pop_back()
	{
		return arr_[max_index_];
	}

	~linear()
	{
		delete[] arr_;
	}
};

class linked
{
	int index_;
	int value_;
	linked* next_;
	linked* prev_;

public:
	linked()
	{
		index_ = 0;
	}

	void set(int index, int value)
	{
		if (index_ == index)
		{
			value_ = value;
		}
		else if (index > index_)
		{
			linked* current = this;
			while (true)
			{
				if (current->next_ == NULL)
				{
					current->next_ = new linked;
					current->next_->index_ = index;
					current->next_->value_ = value;
					current->next_->prev_ = current;
					break;
				}
				if (current->next_->index_ == index)
				{
					current->next_->value_ = value;
					break;
				}
				if (current->next_->index_ > index)
				{
					linked* new_node = new linked;
					new_node->index_ = index;
					new_node->value_ = value;
					new_node->prev_ = current;
					new_node->next_ = current->next_;
					current->next_->prev_ = new_node;
					current->next_ = new_node;
					break;
				}
				if (current->next_->index_ < index)
				{
					current = current->next_;
				}
			}
		}
		else if (index < index_)
		{
			linked* current = this;
			while (true)
			{
				if (current->prev_ == NULL)
				{
					current->prev_ = new linked;
					current->prev_->index_ = index;
					current->prev_->value_ = value;
					current->prev_->next_ = current;
					break;
				}
				if (current->prev_->index_ == index)
				{
					current->prev_->value_ = value;
					break;
				}
				if (current->prev_->index_ > index)
				{
					linked* new_node = new linked;
					new_node->index_ = index;
					new_node->value_ = value;
					new_node->prev_ = current;
					new_node->prev_ = current->prev_;
					current->prev_->next_ = new_node;
					current->prev_ = new_node;
					break;
				}
				if (current->prev_->index_ < index)
				{
					current = current->prev_;
				}
			}
		}
	}

	int get(int index)
	{
		if (index_ == index)
			return value_;

		if (index > index_)
		{
			if (next_ == NULL)
				throw "Argument out of range";

			return next_->get(index);
		}

		if (index < index_)
		{
			if (prev_ == NULL)
				throw "Argument out of range";

			return prev_->get(index);
		}
	}
};

int main()
{
	//LINEAR
	cout << "LINEAR" << endl;
	linear linear_arr;
	linear_arr.set(0, 0);
	linear_arr.set(0, 1);
	linear_arr.set(100, 100);
	linear_arr.set(20, 20);

	cout << linear_arr.get(0) << endl;
	cout << linear_arr.get(100) << endl;
	cout << linear_arr.get(20) << endl;

	//STACK
	cout << endl << "STACK" << endl;
	stack stack_arr;
	stack_arr.push(1);
	stack_arr.push(2);
	stack_arr.push(6);


	cout << stack_arr.pop() << endl;
	cout << stack_arr.pop() << endl;
	cout << stack_arr.pop() << endl;

	//LINKED
	cout << endl << "LINKED" << endl;
	linked linked_arr;
	linked_arr.set(1, 1);
	linked_arr.set(2, 2);
	linked_arr.set(6, 6);
	linked_arr.set(3, 3);
	linked_arr.set(-1, -1);
	linked_arr.set(1, 10);

	cout << linked_arr.get(1) << endl;
	cout << linked_arr.get(2) << endl;
	cout << linked_arr.get(6) << endl;
	cout << linked_arr.get(-1) << endl;
	cout << linked_arr.get(3) << endl;
}