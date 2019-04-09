#pragma once
template<class T>
class allocator
{
public:
	virtual T pop_back() = 0;
	virtual void push_back() = 0;
	virtual T get(int index) = 0;
	virtual void set(int index, T value) = 0;
};
