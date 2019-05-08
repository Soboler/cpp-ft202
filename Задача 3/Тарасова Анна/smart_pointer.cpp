#include <iostream>
using namespace std;

template <class T>
class SmartPointer
{
protected:
    T *valuePointer;
    size_t *referenceCounter;

public:
    SmartPointer()
    {
        valuePointer = NULL;
        referenceCounter = NULL;
    }

    SmartPointer(T *value)
    {
        valuePointer = value;
        referenceCounter = NULL;
    }

    ~SmartPointer()
    {
        Release();
    }

    void Set(T *value)
    {
        valuePointer = value;
        referenceCounter = new size_t(1);
    }

    T Get()
    {
        return *valuePointer;
    }

    void Release()
    {
        if (valuePointer != NULL)
        {
            if (*referenceCounter == 0)
            {
                delete valuePointer;
                delete referenceCounter;
                referenceCounter = NULL;
            }
            else
            {
                (*referenceCounter)--;
            }
            valuePointer = NULL;
        }
    }

    T operator*()
    {
        return *valuePointer;
    }

    T *operator->()
    {
        return valuePointer;
    }

    SmartPointer &operator=(SmartPointer<T> &otherSmartPointer)
    {
        valuePointer = otherSmartPointer.valuePointer;
        referenceCounter = otherSmartPointer.referenceCounter;
        (*referenceCounter)++;

        return *this;
    }
};

int main()
{
    SmartPointer<int> pointer1(new int(1));
    cout << "Pointer 1: " << pointer1.Get() << " " << *pointer1 << " " << &pointer1 << endl;
    SmartPointer<int> pointer2;
    pointer2.Set(new int(2));
    cout << "Pointer 2: " << pointer2.Get() << " " << *pointer2 << " " << &pointer2 << endl;
    pointer1 = pointer2;
    cout << "Pointer 1 after Pointer 2 assignment: " << pointer1.Get() << " " << *pointer1 << " " << &pointer1 << endl;
    pointer1.Release();
    pointer2.Release();

    return 0;
}
