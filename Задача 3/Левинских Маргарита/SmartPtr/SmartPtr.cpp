// SmartPtr.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

template <class T>
class SmartPtr
{
	T* Ptr;
	size_t* Count;

	T* AddRef(SmartPtr& Other, T* Ptr) {
		Count = Other.Count;
		(*Count)++;
		printf("AddRef %d\n", (*Count));
		return Ptr;
	}

	void InitRef() {
		Count = new size_t;
		(*Count) = 1;
	}

public:
	SmartPtr()
	{
		Ptr = 0;
	}

	SmartPtr(T* TObj) : Ptr(TObj)
	{
		InitRef();
	}

	SmartPtr(SmartPtr& Other)
	{
		Ptr = AddRef(Other, Other.Ptr);
	}

	T Get()
	{
		return *Ptr;
	}

	void Set(T* TObj)
	{
		Ptr = TObj;
		InitRef();
	}

	T operator*()
	{
		return *Ptr;
	}

	T* operator->()
	{
		return Ptr;
	}

	SmartPtr& operator=(SmartPtr& Other) {
		Release();
		Ptr = AddRef(Other, Other.Ptr);
		return *this;
	}

	void Release()
	{
		if (!Count)
		{
			return;
		}
		(*Count)--;
		size_t R = (*Count);
		printf("Release %d\n", R);

		if (R == 0)
		{
			delete Count;
			Count = 0;
			delete Ptr;
			Ptr = 0;
		}
	}

	~SmartPtr()
	{
		Release();
	}
};

class TestObj
{
	int X;

public:

	size_t Count = 1;

	TestObj(TestObj& Other)
	{
		X = Other.X;
		printf("New Test Object %d\n", X);
	}

	TestObj()
	{
		X = 0;
		printf("New Test Object 0\n");
	}

	TestObj(int X1) : X(X1)
	{
		printf("New Test Object %d\n", X);
	}

	int GetX()
	{
		printf("Get Test Object, %d\n", X);
		return X;
	}

	~TestObj()
	{
		printf("Deleted Test Object, %d\n", X);
	}
};

int main()
{
	SmartPtr<TestObj> P1;
	SmartPtr<TestObj> P2(new TestObj(10));
	SmartPtr<TestObj> P3;
	P3.Set(new TestObj(15));
	P1 = P2;
	SmartPtr<TestObj> P4(P2);
	P4.Get().GetX();
}