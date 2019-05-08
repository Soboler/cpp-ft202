#include "pch.h"
#include <iostream>

template <class T>
class SmartPointer {

	T* value;
	int* counter;

public:
	SmartPointer() {
		this->value = NULL;
		counter = NULL;
	}

	~SmartPointer() {
		release();
	}

	T get() {
		return *value;
	}

	void set(T *other_value) {
		release();
		value = other_value;
		counter = new int(1);
	}

	void release() {
		*counter--;
		if (counter == 0) {
			delete value;
			delete counter;
			value = NULL;
			counter = NULL;
		}
	}

	SmartPointer operator=(const SmartPointer& other) {
		release();
		value = other.value;
		counter = other.counter;
		(*counter)++;
		return *this;
	}

	T* operator->()
	{
		return value;
	}

	T operator*()
	{
		return *value;
	}
};


int main()
{
	SmartPointer<int> sp1;
	sp1.set(new int(1));
	SmartPointer<int> sp2;
	sp2.set(new int(2));

	std::cout << sp1.get() << ", " << &sp1 << "\n";
	std::cout << sp2.get() << ", " << &sp2 << "\n";

	sp1 = sp2;
	std::cout << sp1.get() << ", " << &sp1 << "\n";

	sp1.release();
	std::getchar();
}