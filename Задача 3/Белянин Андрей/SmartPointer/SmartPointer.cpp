#include "pch.h"
#include <iostream>

using namespace std;

template<typename TValue>
class SmartPointer
{
	TValue* value;
	int* count;

public:
	void Set(TValue *value)
	{
		Release();
		this->value = value;
		count = new int(1);
	}

	TValue* Get()
	{
		return value;
	}

	void Release()
	{
		if (value == nullptr)
			return;

		(*count)--;
		if (*count == 0)
		{
			delete value;
			delete count;
		}

		value = nullptr;
		count = nullptr;
	}

	TValue operator*() const
	{
		return *value;
	}

	TValue* operator->() const
	{
		return value;
	}

	SmartPointer& operator= (const SmartPointer &other)
	{
		value = other.value;
		count = other.count;
		(*count)++;		
		return *this;
	}

	~SmartPointer<TValue>()
	{
		Release();
	}
};

int main()
{
	SmartPointer<int> pointer;
	pointer.Set(new int(10));
	cout << *pointer.Get() << endl;

	SmartPointer<int> pointer2 = pointer;
	cout << *pointer2.Get() << endl;

	pointer.Release();
	cout << *pointer.Get() << endl;
	cout << *pointer2.Get() << endl;

	return 0;
};
