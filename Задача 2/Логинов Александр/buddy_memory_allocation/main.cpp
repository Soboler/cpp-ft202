#include <iostream>
#include <math.h>
using namespace std;


struct node
{
    bool allocated;
    bool free;
    int order;
    node* left;
    node* right;
    void* ptr;

    node(int order, void* ptr)
    {
        allocated = false;
        free = true;
        this->order = order;
        this->ptr = ptr;
        left = NULL;
        right = NULL;
    }

    ~node()
    {
        delete left;
        delete right;
    }
};


class buddy_memory_allocator
{
    void * _start;
    node* tree;
    int max_order;

    static int get_order(size_t size)
    {
        return ceil(log2((int)size));
    }

    static void* get_ptr_with_offset(void* ptr, int offset)
    {
        return (void *) ((char *) ptr + offset);
    }

    static void* _malloc(size_t size, node *current_node)
    {
        if (pow(2, current_node->order) < size || current_node->free == 0)
            return nullptr;
        bool current_size_is_valid = pow(2, current_node->order) >= size && pow(2, current_node->order - 1) < size;
        if (current_size_is_valid && !current_node->allocated)
        {
            current_node->free = false;
            return current_node->ptr;
        }
        else
        {
            if (!current_node->left && !current_node->right) {
                current_node->allocated = true;
                current_node->left = new node(current_node->order - 1, current_node->ptr);
                current_node->right = new node(current_node->order - 1, get_ptr_with_offset(current_node->ptr, (int)pow(2, current_node->order) / 2) );
            }
            auto cur_ptr = _malloc(size, current_node->left);
            if (cur_ptr != nullptr) {
                current_node->allocated = true;
                return cur_ptr;
            }
            else {
                cur_ptr = _malloc(size, current_node->right);
                if (cur_ptr != nullptr)
                    current_node->allocated = true;
                return cur_ptr;
            }
        }
    }

    static void _dump(node* current_node)
    {
        if (!current_node)
            return;
        if (current_node->allocated == 1) {
            wcout << L"Блок размера " << pow(2, current_node->order) << L", находищийся по адресу " << current_node->ptr
                  << L", поделен на два" << endl;

            }
        if (current_node->free == 0) {
            wcout << L"Блок размера " << pow(2, current_node->order) << L", находищийся по адресу "
                  << current_node->ptr << L", выделен"
                  << endl;
        }
        else {
            _dump(current_node->left);
            _dump(current_node->right);
        }
    }

    static bool _free(void* ptr, node* current_node)
    {
        if (!current_node)
            return false;
        if (current_node->ptr == ptr && current_node->free == 0)
        {
            current_node->free = true;
            current_node->allocated = false;
            return true;
        }
        node* explore_node = current_node->ptr == ptr ? current_node->left : current_node->right;
        node* neighboring_node = current_node->ptr == ptr ? current_node->right : current_node->left;
        auto was_deleted = _free(ptr, explore_node);
        if (neighboring_node->free == 1 && neighboring_node->allocated == 0 && explore_node->allocated == 0)
            current_node->allocated = false;
        if (was_deleted)
        {
            delete current_node->left;
            delete current_node->right;
            current_node->left = current_node->right = NULL;
        }
        return false;
    }
public:
    buddy_memory_allocator(size_t init_size)
    {
        max_order = get_order(init_size);
        auto size = (size_t)pow(2, max_order);
        _start = malloc(size);
        tree = new node(max_order, _start);
    }
    ~buddy_memory_allocator()
    {
        free(_start);
        delete tree;
    }

    void* Malloc(size_t size)
    {
        return _malloc(size, tree);
    }

    void Dump()
    {
        _dump(tree);
    }

    void Free(void* ptr)
    {
        _free(ptr, tree);
    }
};

void test_allocate_and_free_once()
{
    wcout << L"Тест 'Выделение и освобождение памяти 1 раз'" << endl;
    wcout << L"Создали аллокатор с 1024б" << endl;
    auto allocator = buddy_memory_allocator(1024);
    wcout << L"Выделили 100б" << endl;
    auto ptr = allocator.Malloc(100);
    allocator.Dump();
    cout << endl;
    wcout << L"Освободили 100б" << endl;
    allocator.Free(ptr);
    allocator.Dump();
    cout << "____________________________________" << endl << endl;
}

void test_allocate_and_free()
{
    wcout << L"Тест 'Выделение дважды и освобождение памяти 1 раз'";
    wcout << L"Создали аллокатор с 10000б" << endl;
    auto allocator = buddy_memory_allocator(10000);
    wcout << L"Выделили 500б (*)" << endl;
    auto ptr = allocator.Malloc(500);
    allocator.Dump();
    cout << endl;
    wcout << L"Выделили 2000б" << endl;
    allocator.Malloc(2000);
    allocator.Dump();
    cout << endl;
    wcout << L"Освободили (*)" << endl;
    allocator.Free(ptr);
    allocator.Dump();
    cout << "____________________________________" << endl << endl;
}
void test_alloc_full_memory()
{
    wcout << L"Тест 'Выделение всей памяти'" << endl;
    wcout << L"Создали аллокатор с 512б" << endl;
    auto al = buddy_memory_allocator(512);
    for(int i = 0; i < 511; i++)
        al.Malloc(1);
    wcout << L"Выделили 511 раз по 1б\nВыделим еще два раза.\nПервый выделит, после него закончилась память и мы получим nullptr" << endl;
    cout << al.Malloc(1) << endl;
    cout << al.Malloc(1) << endl;
    cout << "____________________________________" << endl << endl;
}

int main() {
    setlocale(LC_ALL,"");
    test_allocate_and_free_once();
    test_allocate_and_free();
    test_alloc_full_memory();
    return 0;
}