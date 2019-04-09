#include <iostream>
#include <cstdlib>

using namespace std;

template <typename T>
struct Element
{
    T value;
    Element *next;
};

template <typename T>
class LinkedList
{
  private:
    Element<T> *firstElement;
    Element<T> *lastElement;
    int length;
    int typeSize;

  public:
    LinkedList();
    void pushBack(T value);
    T popBack();
    T get(int id);
    void set(int id, T value);
    void removeAll();
};

template <typename T>
LinkedList<T>::LinkedList()
{
    typeSize = sizeof(Element<T>);
    firstElement = NULL;
    lastElement = NULL;
    length = 0;
};

template <typename T>
void LinkedList<T>::pushBack(T value)
{
    Element<T> *newBlockPointer = (Element<T> *)malloc(typeSize);
    if (newBlockPointer == NULL)
    {
        throw bad_alloc();
    }

    if (length == 0)
    {
        firstElement = newBlockPointer;
    }

    if (lastElement != NULL)
    {
        lastElement->next = newBlockPointer;
    }

    lastElement = newBlockPointer;
    newBlockPointer->value = value;
    newBlockPointer->next = NULL;
    length++;
}

template <typename T>
T LinkedList<T>::popBack()
{
    T result = lastElement->value;
    if (lastElement != firstElement)
    {
        Element<T> *elementToPop = lastElement;
        Element<T> *currentElement = firstElement;
        while (currentElement->next != elementToPop)
        {
            currentElement = currentElement->next;
        }
        currentElement->next = NULL;
        lastElement = currentElement;
        length--;
        free(elementToPop);
    }
    else
    {
        removeAll();
    }

    return result;
}

template <typename T>
T LinkedList<T>::get(int id)
{
    if (id >= length)
    {
        throw range_error("No such id in list");
    }
    Element<T> *currentElement = firstElement;
    for(int i = 0; i != id; i++)
    {
        currentElement = currentElement->next;
    }

    return currentElement->value;
}

template <typename T>
void LinkedList<T>::set(int id, T value)
{
    if (id >= length)
    {
        throw range_error("No such id in list");
    }

    Element<T> *currentElement = firstElement;
    for(int i = 0; i != id; i++)
    {
        currentElement = currentElement->next;
    }

    currentElement->value = value;
}

template <typename T>
void LinkedList<T>::removeAll()
{
    Element<T> *currentElement = firstElement;
    Element<T> *nextElement = NULL;
    while (currentElement != NULL)
    {
        nextElement = currentElement->next;
        free(currentElement);
        currentElement = nextElement;
    }
    length = 0;
    firstElement = NULL;
    lastElement = NULL;
}

int main()
{
    LinkedList<int> list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    cout << list.popBack() << endl;
    cout << list.get(1) << endl;
    list.set(1, 100500);
    cout << list.get(1) << endl;
    list.removeAll();
    return 0;
}
