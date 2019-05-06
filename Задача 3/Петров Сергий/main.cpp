//
//  main.cpp
//  SmartPointer
//
//  Created by Сергий Петров on 03/05/2019.
//  Copyright © 2019 Сергий Петров. All rights reserved.
//

#include <iostream>
#include <vector>

template <class T>
class SmartPointer {
    T* ptr;
    size_t* count;
    
public:
    SmartPointer(T* p = NULL) {
        ptr = p;
        count = new size_t(1);
    }
    
    SmartPointer(const SmartPointer<T>& other) {
        ptr = other.ptr;
        count = other.count;
        (*count)++;
    }
    
    T& get() {
        return *ptr;
    }
    
    void set(T* p) {
        release();
        ptr = p;
        count = new size_t(1);
    }
    
    void release()
    {
        if (ptr)
        {
            std::cout << *count << " refs before release" << std::endl;
            if (--(*count) == 0)
            {
                delete ptr;
                delete count;
                return;
            }
            std::cout << *count << " refs after release" << std::endl;
            ptr = NULL;
            count = NULL;
        }
    }
    
    ~SmartPointer() { release(); }
    
    SmartPointer operator =(const SmartPointer& value) {
        ptr = value.ptr;
        count = value.count;
        (*count)++;
    }
    
    T& operator *() {  return *ptr; }
    
    T* operator ->() { return ptr; }

};

int main(int argc, const char * argv[]) {

    SmartPointer<int> pointer(new int());
    *pointer = 20;
    std::cout << *pointer << std::endl;
    pointer.set(new int(30));
    std::cout << pointer.get() << std::endl;
    SmartPointer<int> pointer2 = pointer;
    pointer.release();
    pointer2.release();
    
    {
        SmartPointer<std::vector<int>> ptr(new std::vector<int>(4, 20));
        (*ptr).pop_back();
        std::cout << ptr->size() << std::endl;
        {
            SmartPointer<std::vector<int>> ptr2 = ptr;
            (*ptr2).pop_back();
            std::cout << ptr2->size() << std::endl;
        }
        std::cout << ptr->size() << std::endl;
    }
    
    return 0;
}
