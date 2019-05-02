#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <string>
#include <queue>
#pragma comment(linker, "/STACK:128777216")
using namespace std;
#define pii pair<int,int>
#define ll long long

template <typename TValue>
class SmartPointer
{
private:
	TValue* value_;
	size_t* counter_;

	void Attach(const SmartPointer& other)
	{
		counter_ = other.counter_;
		(*counter_)++;
		value_ = other.value_;
	}

public:
	explicit SmartPointer(TValue *value) : value_(value)
	{
		counter_ = new size_t();
		*counter_ = 1;
	}

	SmartPointer(const SmartPointer<TValue>& ref)
	{
		counter_ = ref.counter_;
		(*counter_)++;
		value_ = ref.value_;
	}

	TValue* operator->() const
	{
		return value_;
	}

	TValue operator *() const
	{
		if (value_ == nullptr)
			throw exception("Object is deleted! Can't use operator *");
		return *value_;
	}

	SmartPointer& operator =(SmartPointer &other)
	{
		Release();
		Attach(other);
		return *this;
	}

	~ SmartPointer<TValue>()
	{
		Release();
	}

	void Set(TValue* value) 
	{
		Release();
		counter_ = new size_t(1);
		value_ = value;
	}

	TValue* Get()
	{
		return value_;
	}

	void Release()
	{
		if (!value_)
			return;
		(*counter_)--;
		if ((*counter_) == 0)
		{
			cout << "Object is deleted\n";
			delete value_;
			delete counter_;
		}
		value_ = NULL;
		counter_ = nullptr;
	}

};
int main()
{
	SmartPointer<int> v1(new int(1));
	SmartPointer<int> v2 = v1;
	SmartPointer<int> v3 = v2;
	cout << *v1 << ' ' << *v2 << ' ' << *v3 << '\n';
	v2.~SmartPointer();
	v3.~SmartPointer();
	v1.~SmartPointer();
	cout << '\n';
	v1.Set(new int(2));
	cout << *v1 << "\n\n";
	
	v2 = v1;
	v1.Set(new int(10));
	cout << *v1 << '\n';
	cout << *v2 << '\n';
	cout << '\n';

	cout << v1.Get() << '\n';
	cout << v2.Get() << '\n';
	cout << '\n';

	vector<int> ar(2, 10);
	SmartPointer<vector<int>> vector_pointer(new vector<int>(2, 10));
	vector_pointer->push_back(11);
	for (auto u: *vector_pointer.Get())
	{
		cout << u << ' ';
	}
	cout << "\n\n";
	vector_pointer.Release();
	cout << '\n';
	cout << vector_pointer.Get() << '\n';


	return 0;
}