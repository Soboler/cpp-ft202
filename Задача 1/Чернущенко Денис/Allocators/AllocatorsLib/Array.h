#ifndef ALLOCATOR_ARRAY_H
#define ALLOCATOR_ARRAY_H

class Array
{
public:
    virtual ~Array() = default;

    virtual int& operator[] (int index) = 0;
    virtual void push(int item) = 0;
    virtual int pop() = 0;
    virtual int get(int index) = 0;
    virtual void set(int item, int index) = 0;
    virtual void removeAll() = 0;

    virtual int getLength() = 0;
};

#endif // ALLOCATOR_ARRAY_H
