#include<iostream>
using namespace std;

template <typename T>
class SmartPointer {
protected:
	T *pointer;
	unsigned *ref_count;

	void del_ref() {
		--(*ref_count);
		if (ref_count == 0) {
			delete pointer;
			free(ref_count);
			pointer = NULL;
			ref_count = NULL;
		}
	}

public:
	SmartPointer() {
		pointer = NULL;
		ref_count = NULL;
	}

	~SmartPointer() {
		del_ref(); 
	}

	T Get() {
		return *pointer;
	}

	void Set(T *ptr) {
		pointer = ptr;
		ref_count = (unsigned*)malloc(sizeof(unsigned));
		*ref_count = 1;
	}

	void Release(){
		del_ref();
	}

	SmartPointer & operator=(SmartPointer & other_ptr) {
		if (*ref_count > 0) {
			del_ref();
		}
		if (this != &other_ptr) {
			pointer = other_ptr.pointer;
			ref_count = other_ptr.ref_count;
			++(*ref_count);
		}
		//cout << *ref_count << " " << *other_ptr.ref_count << endl;
		return *this;
	}

	T operator*() {
		return *pointer;
	}
	
	T* operator->() {
		return pointer;
	}
};

int main() {
	SmartPointer<int> ptr_int1;
	SmartPointer<int> ptr_int2;
	ptr_int1.Set(new int(1));
	ptr_int2.Set(new int(2));

	cout << ptr_int1.Get() << " " << &ptr_int1 << " " << *ptr_int1 << endl;
	cout << ptr_int2.Get() << " " << &ptr_int2 << " " << *ptr_int2 << endl;
	ptr_int1 = ptr_int2;
	cout << ptr_int2.Get() << " " << &ptr_int2 << " " << *ptr_int2 << endl;

	ptr_int2.Release();
	ptr_int1.Release();
}