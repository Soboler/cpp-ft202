/*
	Author: Kholstinin Dmitriy
*/

#include <iostream>

class LinearAllocator
{
	const size_t DEFAULT_CAPACITY = 1024;
	const int TRASH_VALUE = INT_MIN;

	size_t capacity = DEFAULT_CAPACITY;
	size_t size;
	int *pool;

	void resize(size_t new_size)
	{
		capacity = new_size;
		int *new_pool = (int*)std::malloc(capacity);
		for (size_t i = 0; i < size; i++)
		{
			new_pool[i] = pool[i];
		}
		std::free(pool);
		pool = new_pool;
	}

public:
	LinearAllocator()
	{
		pool = (int*)std::malloc(capacity);
	}

	~LinearAllocator()
	{
		std::free(pool);
	}

	void push_back(int value)
	{
		set(size, value);
	}

	int pop_back()
	{
		return pool[size > 0 ? --size : 0];
	}

	void remove_all()
	{
		while (size > 0)
		{
			pool[--size] = TRASH_VALUE;
		}
	}

	int get(size_t i)
	{
		if (i < 0 || i >= size)
		{
			throw std::invalid_argument("Index out of range");
		}
		return pool[i];
	}

	void set(size_t i, int value)
	{
		size_t required_capacity = (i + 1) * sizeof(value);
		if (required_capacity > capacity)
		{
			resize((required_capacity / DEFAULT_CAPACITY + 1) * DEFAULT_CAPACITY);
		}
		size_t next_size = (i > size ? i : size) + 1;
		for (; size < next_size; size++)
		{
			pool[size] = TRASH_VALUE;
		}
		pool[i] = value;
	}
};

class StackAllocator
{
	const size_t DEFAULT_CAPACITY = 1024;

	size_t capacity = DEFAULT_CAPACITY;
	size_t size;
	int *pool;

	void resize(size_t new_size)
	{
		capacity = new_size;
		int *new_pool = (int*)std::malloc(capacity);
		for (size_t i = 0; i < size; i++)
		{
			new_pool[i] = pool[i];
		}
		std::free(pool);
		pool = new_pool;
	}

public:
	StackAllocator()
	{
		pool = (int*)std::malloc(capacity);
	}

	~StackAllocator()
	{
		std::free(pool);
	}

	void push_back(int value)
	{
		size_t next_size = size + 1;
		if (next_size * sizeof(value) > capacity)
		{
			resize(capacity + DEFAULT_CAPACITY);
		}
		pool[size] = value;
		size = next_size;
	}

	int pop_back()
	{
		return pool[size > 0 ? --size : 0];
	}

	void remove_all()
	{
		size = 0;
	}
};

class LinkedListAllocator
{
	struct Item
	{
		Item *prev, *next;
		int *pool;

		Item(size_t capacity)
		{
			prev = NULL;
			next = NULL;
			pool = (int*)std::malloc(capacity);
		}
	};

	const size_t DEFAULT_CAPACITY = 16;
	const size_t ITEM_SIZE = DEFAULT_CAPACITY / sizeof(int);

	size_t capacity = DEFAULT_CAPACITY;
	size_t size;
	size_t number_of_items;
	Item *head, *tail;

	void resize(size_t new_size)
	{
		capacity = new_size;
		for (size_t i = DEFAULT_CAPACITY * number_of_items; i < new_size; i += DEFAULT_CAPACITY)
		{
			Item *item = new Item(DEFAULT_CAPACITY);
			item->prev = tail;
			tail->next = item;
			tail = item;
			number_of_items++;
		}
	}

	Item* get_item(size_t index)
	{
		index /= ITEM_SIZE;
		Item *item;
		if (index <= number_of_items / 2)
		{
			item = head;
			for (size_t i = 0; i < index; i++)
			{
				item = item->next;
			}
		}
		else
		{
			item = tail;
			index = number_of_items - index - 1;
			for (size_t i = 0; i < index; i++)
			{
				item = item->prev;
			}
		}
		return item;
	}

	int& get_element(Item* item, size_t index)
	{
		return item->pool[index % ITEM_SIZE];
	}

public:
	LinkedListAllocator()
	{
		head = new Item(DEFAULT_CAPACITY);
		tail = head;
		number_of_items = 1;
	}

	~LinkedListAllocator()
	{
		Item *next;
		while (next = head->next)
		{
			delete head;
			head = next;
		}
	}

	void push_back(int value)
	{
		set(size, value);
	}

	int pop_back()
	{
		if (size > 0)
		{
			size--;
		}
		return get_element(get_item(size), size);
	}

	void remove_all()
	{
		size = 0;
	}

	int get(size_t i)
	{
		if (i < 0 || i >= size)
		{
			throw std::invalid_argument("Index out of range");
		}
		return get_element(get_item(i), i);
	}

	void set(size_t i, int value)
	{
		Item *item;
		size_t required_capacity = (i + 1) * sizeof(value);
		if (required_capacity > capacity)
		{
			resize((required_capacity / DEFAULT_CAPACITY + 1) * DEFAULT_CAPACITY);
			item = tail;
		}
		else
		{
			item = get_item(size);
		}
		get_element(item, i) = value;
		size = (i > size ? i : size) + 1;
	}
};

int main()
{
	LinkedListAllocator arr;
	for (size_t i = 0; i < 100; i++)
	{
		arr.set(i, i);
		std::cout << arr.get(i) << '\n';
	}
	arr.push_back(100);
	for (size_t i = 0; i < 50; i++)
	{
		std::cout << arr.pop_back() << '\n';
	}
	arr.remove_all();
}
