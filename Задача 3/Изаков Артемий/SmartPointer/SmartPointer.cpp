#include <iostream>

using namespace std;

template <typename T>
class smart_pointer
{
	T* value = nullptr;
	size_t* count = nullptr;

public:
	smart_pointer(T* value) : value(value), count(new size_t(1))
	{
	}

	smart_pointer() = default;

	smart_pointer(const smart_pointer<T>& other)
	{
		*this = other;
	}

	T get()
	{
		return *value;
	}

	void set(T* new_value)
	{
		release();
		value = new_value;
		count = new size_t(1);
	}

	void release()
	{
		if (value == nullptr)
			return;
		(*count)--;
		if (*count != 0)
			return;
		delete value;
		delete count;
		value = nullptr;
		count = nullptr;
	}

	T& operator*()
	{
		return (*value);
	}

	T* operator->()
	{
		return value;
	}

	smart_pointer& operator=(const smart_pointer<T>& other)
	{
		value = other.value;
		count = other.count;
		(*count)++;
		return *this;
	}

	~smart_pointer<T>()
	{
		release();
	}
};

int main()
{
	smart_pointer<int> ptr(new int(123));
	cout << ptr.get() << endl;

	auto ptr2 = ptr;
	cout << *ptr2 << endl;

	auto ptr3 = new smart_pointer<int>(new int(456));
	cout << ptr3->get() << endl;

	ptr.release();
	cout << ptr.get() << " " << ptr2.get() << endl;
}
