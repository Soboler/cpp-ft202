#include<iostream>

using namespace std;


class Block {
private:
	Block *prev = nullptr;

public:
	int *pointer;
	size_t size;
	bool empty;
	Block *next = nullptr;

	Block *first = nullptr;
	Block *second = nullptr;
	Block *parent = nullptr;

	Block(size_t size, Block* parent) {
		this->size = size;
		pointer = (int*)malloc(size);
		empty = true;
		parent = parent;
	}

	~Block()
	{
		empty = true;
		free(pointer);
		first = nullptr;
		second = nullptr;
		prev = nullptr;
		next = nullptr;
		parent = nullptr;
	}

	void split() {
		empty = false;

		first = new Block(this->size / 2, this);
		second = new Block(this->size / 2, this);

		second->next = next;
		if (next != nullptr)
			next->prev = second;

		if (prev != nullptr) {
			prev->next = first;
		}
		first->prev = prev;

		first->next = second;
		second->prev = first;

		next = nullptr;
		prev = nullptr;
	}

	void merge() {
		prev = first->prev;
		next = second->next;
		first = second->next;
		
		first->~Block();
		second->~Block();

		first = nullptr;
		second = nullptr;
	}

	void print() {
		cout << "addr: " << pointer;
		cout << ", size: " << size;
		cout << ", empty: " << (empty ? "true" : "false") << "; " << endl;
	}
};


class BuddyAllocator {
private:

	size_t size;
	Block* first;

	size_t getPower(int s)
	{
		int power = log2(s);
		if (pow(2, power) < s)
			return pow(2, power + 1);
		return pow(2, power);
	}

public:
	BuddyAllocator(size_t size) {
		this->size = size;
		size_t index = getPower(size);
		first = new Block(size, nullptr);
	}

	void* Alloc(size_t size) {
		Block *curr = first;
		if (curr == nullptr)
			throw exception("There's no enough space");
		while (!(curr->size == size && curr->empty))
		{
			if (curr->empty && (log2(curr->size) > ceil(log2(size)))) {
				curr->split();
				if (curr == first) 
					first = curr->first;
				curr = curr->first;
			}
			else {
				curr = curr->next;
			}
			if (curr == nullptr)
				throw exception("There's no enough space");
		}
		curr->empty = false;
		return curr->pointer;
	}

	void Free(void *ptr) {
		Block* curr = first;
		
		while (curr->pointer != ptr)
		{
			curr = curr->next;
		}
		while (true) {
			curr->empty = true;
			curr = curr->parent;
			if (curr != nullptr && curr->first->empty && curr->second->empty) {
				if (curr->first == first)
					first = curr;
				curr->merge();
			}
			else {
				break;
			}
		}
	}

	void Dump() {
		Block* curr = first;
		while (curr != nullptr) {
			curr->print();
			curr = curr->next;
		}
	}
};


int main() {
	BuddyAllocator allocator = BuddyAllocator(128);
	void *r1 = allocator.Alloc(32);
	void *r2 = allocator.Alloc(64);
	void *r3 = allocator.Alloc(16);
	void *r4 = allocator.Alloc(16);
	allocator.Dump();
	cout << "--------" << endl;

	allocator.Free(r1);
	allocator.Dump();
	cout << "--------" << endl;

	allocator.Alloc(32);
	allocator.Dump();
	cout << "--------" << endl;

	try {
		allocator.Free(r1);
		allocator.Alloc(128);
	}
	catch(exception e){
		cout << "There's no enough space" << endl;
	}
	allocator.Dump();
	cout << "--------" << endl;
}