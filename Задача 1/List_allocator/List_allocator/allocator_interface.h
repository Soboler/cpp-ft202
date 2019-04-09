#pragma once
#include <string>

template<class T>
class allocator_interface
{
protected:
	virtual T get(int index) = 0;
	virtual void set(int index, T value) = 0;

public:
	virtual int size() = 0;
	virtual void push_back(T value) = 0;
	virtual T pop_back() = 0;
	virtual T* all_elements() = 0;
	virtual std::string class_name() = 0;
};
