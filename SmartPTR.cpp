#include "pch.h"
#include "stdafx.h"
#include <iostream>

using namespace std;


template <class T>
class SmartPointer
{
	T* ptr = NULL;
	size_t* counter;

public:

	SmartPointer(T* value)
	{
	    ptr = value;
		counter = new size_t(1);
	}

	SmartPointer(const SmartPointer<T>& other)
	{
	    counter = other.counter;
		(*counter)++;
		ptr = other.ptr;
	}

	void Set(T* value)
	{
	    Release();
		ptr = value;
		counter = new size_t(1);
	}

	T& Get()
	{
		return *ptr;
	}

	void Release()
	{
		if (ptr == nullptr) {
		    return;
		}
		if (counter)
		{
			if (!(*counter--))
			{
				delete ptr;
				delete counter;
			}
			counter = NULL;
		}
		ptr = nullptr;
	}

	SmartPointer& operator=(const SmartPointer<T>& other)
	{
		ptr = other.ptr;
        counter = other.counter;
        (*counter)++;
		return *this;
	}

    ~SmartPointer()
	{
		Release();
	}
	
	T* operator->() const
	{
		return Get();
	}

	T& operator*() const
	{
		return *Get();
	}


};

int main()
{
	SmartPointer<int> prt0(new int(512));
	cout << prt0.Get() << "\n";	
	auto prt1 = prt0;
	cout << prt1.Get() << "\n";	
	SmartPointer<int> prt2(new int(324));
	cout << prt2.Get() << "\n";	
	prt0.Release();
	cout << prt1.Get() << " " << prt2.Get() << endl;
}