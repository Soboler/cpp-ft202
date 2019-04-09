#include <iostream>
#include <cstdlib>

using namespace std;

template <typename T>
class Stack
{
  private:
    T *stackPointer;
    int capacity;
    int top;
    int typeSize;
    static const int startCapacity = 16;

  public:
    Stack();
    void pushBack(T value);
    T popBack();
    void removeAll();
};

template <typename T>
Stack<T>::Stack()
{
    typeSize = sizeof(T);
    capacity = startCapacity;
    top = 0;

    stackPointer = (T *)malloc(typeSize * capacity);
    if (stackPointer == NULL)
    {
        throw bad_alloc();
    }
}

template <typename T>
void Stack<T>::pushBack(T value)
{
    if (top >= capacity)
    {
        int newCapacity = capacity * 2;
        T *newStackPointer = (T *)malloc(typeSize * newCapacity);
        if (newStackPointer == NULL)
        {
            throw bad_alloc();
        }
        memcpy(newStackPointer, stackPointer, typeSize * capacity);
        free(stackPointer);
        capacity = newCapacity;
        stackPointer = newStackPointer;
    }

    stackPointer[top] = value;
    top++;
}

template <typename T>
T Stack<T>::popBack()
{
    T value = stackPointer[top - 1];
    stackPointer[top - 1] = 0;
    top--;
    return value;
}

template <typename T>
void Stack<T>::removeAll()
{
    free(stackPointer);
    top = 0;
    capacity = startCapacity;

    stackPointer = (T *)malloc(typeSize * capacity);
    if (stackPointer == NULL)
    {
        throw bad_alloc();
    }
}

int main()
{
    Stack<int> stack;
    stack.pushBack(1);
    stack.pushBack(2);
    cout << stack.popBack() << endl;
    cout << stack.popBack() << endl;
    stack.removeAll();

    return 0;
}
