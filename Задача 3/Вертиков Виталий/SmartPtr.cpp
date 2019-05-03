#include "pch.h"
#include <iostream>

template <class T>
class SmartPtr
{
	T* Ptr;
	size_t* Count = 0;

public:
	SmartPtr() { Ptr = 0; }

	void Set(T* ptr) {
		Release();
		Ptr = ptr;
		Count = new size_t(1);
	}

	T& Get()
	{
		return *Ptr;
	}

	T* CopyPtr(SmartPtr& Other, T* Ptr) {
		Count = Other.Count;
		(*Count)++;
		return Ptr;
	}

	void Release() {
		if (!Ptr) {
			return;
		}

		(*Count)--;
		if (*Count == 0) {
			delete Count;
			delete Ptr;
			Ptr = 0;
			Count = 0;
		}
	}


	SmartPtr& operator=(SmartPtr& Other) {
		Release();
		Ptr = CopyPtr(Other, Other.Ptr);
		return *this;
	}

	~SmartPtr() {
		Release();
	}

	T* operator->() {
		return Ptr;
	}
};

class Obj {
public:
	int b;
	Obj(int a) {
		b = a;
	}
};

int main()
{
	SmartPtr<Obj> P1;
	P1.Set(new Obj(1));
	SmartPtr<Obj> P2;
	P2.Set(new Obj(2));
	P1 = P2;
	printf("%d", P1.Get().b);
}