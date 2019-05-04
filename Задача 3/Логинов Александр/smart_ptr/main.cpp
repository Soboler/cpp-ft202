#include <iostream>

using namespace std;


template <class T>
class smart_ptr{
    T* object = nullptr;
    int* count = new int(0);

public:

    int get_count()
    {
        return *count;
    }

    smart_ptr(T* obj)
    {
        object = obj;
        (*count)++;
    }

    smart_ptr() {}

    T* operator ->()
    {
        return object;
    }

    smart_ptr& operator=(smart_ptr &  other)
    {
        if (object)
        {
            (*count)--;
            if (*count == 0) {
                wcout << L"Объект удален" << endl;
                delete object;
            }
            object = nullptr;
            (*count) = 0;
        }
        count = other.count;
        (*count)++;
        object = other.object;
        return *this;
    }

    T operator*()
    {
        return *object;
    }

    T& Get()
    {
        return *(object);
    }

    void Set(T* new_object)
    {
        if (--(*count) == 0) {
            delete object;
            wcout << L"Объект удален" << endl;
        }
        object = new_object;
        count = new int(1);
    }

    void Release()
    {
        if (--(*count) == 0) {
            wcout << L"Объект удален" << endl;
            delete object;
            delete count;
        }
        object = nullptr;
        count = new int(0);
    }

    ~smart_ptr()
    {
        Release();
    }
};

class TestObj
{
public:
    int a;
};

void test_with_test_object()
{
    smart_ptr<TestObj> ptr(new TestObj());
    wcout << L"Создан умный указатель от типа TestObj" << endl;
    wcout << L"ptr->a  => " << ptr->a << endl;
    ptr->a = 100;
    wcout << L"Назначим ptr->a = 100;" << endl;
    wcout << L"ptr->a  => " << ptr->a << endl;
}


void test_with_simple_type()
{
    smart_ptr<int> ptr(new int(1));
    wcout << L"Создан умный указатель от типа int со значением 1" << endl;
    wcout << L"ptr.Get() => " << ptr.Get() << endl;
    wcout << L"Количество ссылок у ptr: " << ptr.get_count() << endl;
    wcout << L"ptr_1 = ptr" << endl;
    smart_ptr<int> ptr_1;
    ptr_1 = ptr;
    wcout << L"Количество ссылок у ptr: " << ptr.get_count() << endl;
    wcout << L"ptr.Set(new int(5124))" << endl;
    ptr.Set(new int(5124));
    wcout << L"ptr.Get() => " << ptr.Get() << endl;
    wcout << L"ptr.Release()" << endl;
    ptr.Release();
    wcout<< L"Количество ссылок у ptr: " << ptr.get_count() << endl;
}

int main() {
    setlocale(LC_ALL,"");
    test_with_simple_type();
    cout << "___________________________________________" << endl;
    test_with_test_object();
    cout << "___________________________________________" << endl;
    return 0;
}
