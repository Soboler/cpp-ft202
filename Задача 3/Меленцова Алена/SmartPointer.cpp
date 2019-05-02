#include <iostream>

using namespace std;

template<typename T> // шаблон, чтобы можно было использовать указатель с любым типом данных
class SmartPointer //оболочка для обычного указателя, чтобы подчищать память за ним
{
public: // реализуем конструктор и деструктор

	SmartPointer(T *ptr)
	{
		this->ptr = ptr; //берем адрес в памяти, на который указывает тот указатель записываем в наш указатель
		ref_count = new int(1);
		cout << "constructor worked" << endl;
	}

	SmartPointer(const SmartPointer<T>& ref)
	{
		ref_count = &++*ref.ref_count;
		ptr = ref.ptr;
	}

	~SmartPointer()
	{
		Release();
		cout << "destructor worked" << endl;
	}

	T& operator*() const
	{
		return *ptr;
	}

	T& operator->() const
	{
		return ptr;
	}

	SmartPointer& operator=(const SmartPointer& p)
	{
		Release();
		ref_count = &++*ref.ref_count;
		object = ref.object;
	}

	bool isNull() const
	{
		return ref_count == 0;
	}

	T& Get()
	{
		return *ptr;
	}

	void Set(T *ptr)
	{
		this->ptr = ptr;
	}

private:
	void Release()
	{
		if (ref_count != 0 && !--*ref_count)
		{
			delete ref_count;
			delete ptr;
			ref_count = 0;
			ptr = 0;
		}
	}
	T *ptr;
	int *ref_count;
};


int main()
{
	SmartPointer<int> pointer = new int(5);
	cout << *pointer << " is our object" << endl;

	pointer.Set(new int(16543));
	cout << pointer.Get() << " object was changed on (16543) put to that place in memory" << endl;

	SmartPointer<int> pointer0 = SmartPointer<int>(pointer);

	pointer.~SmartPointer();
	cout << pointer0.Get() << " object (16543) was not automatically deleted" << endl;

	pointer0.~SmartPointer();
	cout << pointer0.isNull() << " object (16543) was automatically deleted" << endl;

	return 0;
}