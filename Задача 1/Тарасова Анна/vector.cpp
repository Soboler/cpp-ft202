#include <iostream>
#include <cstdlib>

using namespace std;

template <typename T>
class Vector
{
  private:
    T *vectorPointer;
    int capacity;
    int length;
    int typeSize;
    static const int startCapacity = 16;

  public:
    Vector();
    void set(int id, T value);
    void push_back(T value);
    T get(int id);
    void removeAll();
};

template <typename T>
Vector<T>::Vector()
{
    typeSize = sizeof(T);
    capacity = startCapacity;
    length = 0;

    vectorPointer = (T *)malloc(typeSize * capacity);
    if (vectorPointer == NULL)
    {
        throw bad_alloc();
    }
}

template <typename T>
void Vector<T>::push_back(T value)
{
    if (length >= capacity)
    {
        int newCapacity = capacity * 2;
        T *newVectorPointer = (T *)malloc(typeSize * newCapacity);
        if (newVectorPointer == NULL)
        {
            throw bad_alloc();
        }
        memcpy(newVectorPointer, vectorPointer, typeSize * capacity);
        free(vectorPointer);
        capacity = newCapacity;
        vectorPointer = newVectorPointer;
    }

    vectorPointer[length] = value;
    length++;
}

template <typename T>
void Vector<T>::set(int id, T value)
{
    if (id >= length)
    {
        throw range_error("No such id in list");
    }

    vectorPointer[id] = value;
}

template <typename T>
T Vector<T>::get(int id)
{
    if (id >= length)
    {
        throw range_error("No such id in list");
    }
    return vectorPointer[id];
}

template <typename T>
void Vector<T>::removeAll()
{
    free(vectorPointer);
    length = 0;
    capacity = startCapacity;

    vectorPointer = (T *)malloc(typeSize * capacity);
    if (vectorPointer == NULL)
    {
        throw bad_alloc();
    }
}

int main()
{
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    cout << vec.get(1) << endl;
    vec.set(1, 3);
    cout << vec.get(1) << endl;
    vec.removeAll();

    return 0;
}
