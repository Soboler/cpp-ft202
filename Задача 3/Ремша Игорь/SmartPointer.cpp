#include <iostream>


using namespace std;


template <class T>
class SmartPointer
{
	T* ptr = NULL;
	size_t* count;

public:

	SmartPointer(T* value)
	{
	    ptr = value;
		count = new size_t(1);
	}

	SmartPointer(const SmartPointer<T>& other)
	{
	    count = other.count;
		(*count)++;
		ptr = other.ptr;
	}

	void Set(T* value)
	{
	    Release();
		ptr = value;
		count = new size_t(1);
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
		if (*(count) == 0)
		{
			delete ptr;
			delete count;
			count = NULL;
		}
		else {
			(*count)--;
		}
	
		ptr = nullptr;
	}

	SmartPointer& operator=(const SmartPointer<T>& other)
	{
		ptr = other.ptr;
        count = other.count;
        (*count)++;
		return *this;
	}

    ~SmartPointer()
	{
		Release();
	}
	
	T* operator->() const
	{
		return ptr;
	}

	T& operator*() const
	{
		return *ptr;
	}


};

int main()
{
	SmartPointer<int> prt(new int(256));
	cout << prt.Get() << "\n";
	
	auto prt1 = prt;
	cout << prt1.Get() << "\n";
	
	SmartPointer<int> prt2(new int(128));
	cout << prt2.Get() << "\n";
	
	prt.Release();
	cout << prt1.Get() << " " << prt2.Get() << endl;
}