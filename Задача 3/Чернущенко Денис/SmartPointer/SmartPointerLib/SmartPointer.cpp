#ifndef SMARTPOINTER_SMARTPOINTER_H
#define SMARTPOINTER_SMARTPOINTER_H

#include <cstddef>
#include <iostream>

template <typename T>
class SmartPointer
{
public:
    explicit SmartPointer(T* basePointer) : basePointer(basePointer) { }

    ~SmartPointer()
    {
        if (basePointer != nullptr) Release();
    }

    SmartPointer(const SmartPointer<T>& otherPointer)
    {
        if (basePointer != nullptr) Release();

        copyPointer(otherPointer);
    }

    SmartPointer<T>& operator=(const SmartPointer<T>& otherPointer)
    {
        if (basePointer != nullptr) Release();
        copyPointer(otherPointer);

        return *this;
    }

    T* const operator->() const
    {
        if (basePointer == nullptr) throw std::runtime_error(nullptrErrorMessage);
        return basePointer;
    }

    T& operator*() const
    {
        if (basePointer == nullptr) throw std::runtime_error(nullptrErrorMessage);
        return *basePointer;
    }

    T& Get() const
    {
        return **this;
    }

    void Set(T* pointerToNewObject)
    {
        if (basePointer == nullptr) throw std::runtime_error(nullptrErrorMessage);
        Release();

        basePointer = pointerToNewObject;
        pointersCount = new size_t(1);
    }

    void Release()
    {
        if (basePointer == nullptr) throw std::runtime_error(nullptrErrorMessage);

        if (--(*pointersCount) == 0)
        {
            delete pointersCount;
            delete basePointer;

            pointersCount = nullptr;
        }

        basePointer = nullptr;
    }

private:
    const char* nullptrErrorMessage = "Instance points to nullptr.";

    T* basePointer = nullptr;
    size_t* pointersCount = new size_t(1);

    void copyPointer(const SmartPointer& otherPointer)
    {
        basePointer = otherPointer.basePointer;
        pointersCount = otherPointer.pointersCount;

        if (basePointer != nullptr)
            (*pointersCount)++;
    }
};


#endif //SMARTPOINTER_SMARTPOINTER_H
