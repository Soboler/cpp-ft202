
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

template<class T>
class SmartPointer {
	

private:
	T* instance;
	int * counter;

public:
	SmartPointer() : instance(), counter() {
	}

	SmartPointer(T* instance) {
		this->instance = instance;
		counter = new int(1);
	}

	SmartPointer(const SmartPointer& pointer) : instance(pointer.instance), counter(pointer.counter) {
		if (counter) {
			++*counter;
		}
	}

	~SmartPointer() {
		release();
	}

	void release() {
		if (counter) {
			if (--*counter == 0) {
				delete counter;
				delete instance;
			}
		}

		counter = NULL;
		instance = NULL;
	}



	void Set(T* PointerObj) {
		release();
		counter = new size_t(1);
		instance = PoinerObj;
	}

	T* get() const {
		return counter ? instance : NULL;
	}

	SmartPointer& operator = (const SmartPointer& pointer) {
		if (this != &pointer) {
			release();
			instance = pointer.instance;
			counter = pointer.counter;
			if (counter) {
				++*counter;
			}
		}

		return *this;
	}

	T* operator -> () const {
		if (instance == nullptr) throw exception("Pointer deleted");
		return get();
	}

	T& operator * () const {
		return *get();
	}	
	
	int getPointersCount() {
		return counter ? *counter : -1;
	}

};
class Test {
public:
	std::string str() {
		return "test str";
	}
};



int main(int argc, const char * argv[]) {

	SmartPointer<Test> pointer = new Test();
	SmartPointer<Test> pointer2 = pointer;
	cout << pointer.get()->str() << endl;
	cout << pointer2->str() << endl;
	cout << pointer.get()->str() << endl;
	cout << pointer2->str() << endl;

	_getch();

	return 0;
}
