#include <iostream>
#include <vector>

template<class T>
class SmartPointer
{
	T *ptr;
	size_t *counter;

	void attach(const SmartPointer &other)
	{
		ptr = other.ptr;
		counter = other.counter;
		(*counter)++;
	}

public:

	explicit SmartPointer(T* value)
	{
		ptr = value;
		counter = new size_t(1);
	}

	SmartPointer(const SmartPointer &other)
	{
		attach(other);
	}

	~SmartPointer()
	{
		release();
	}

	T get()
	{
		return *ptr;
	}

	void set(T* value)
	{
		release();
		ptr = value;
		counter = new size_t(1);
	}

	void release()
	{
		if (ptr)
		{
			if (--(*counter) == 0)
			{
				delete ptr;
				delete counter;
			}
			ptr = NULL;
			counter = NULL;
		}
	}

	SmartPointer operator=(const SmartPointer &other)
	{
		release();
		attach(other);
		return *this;
	}

	T* operator->()
	{
		return ptr;
	}

	T operator*()
	{
		return get();
	}
};

int main()
{
	{
		SmartPointer<std::vector<int>> ptr(new std::vector<int>(1, 1));
		std::cout << *(*ptr).begin() << '\n';
		{
			SmartPointer<std::vector<int>> ptr2 = ptr;
			std::cout << ptr2->size() << '\n';
			{
				SmartPointer<std::vector<int>> ptr3(ptr2);
				std::cout << ptr3.get()[0] << '\n';
				ptr3.release();
				ptr3.set(new std::vector<int>(2, 2));
				std::cout << ptr3.get()[1] << '\n';
			}
		}
	}
}
