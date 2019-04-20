#include "pch.h"
#include <iostream>

using namespace std;


class AllocUnit
{
public:
	int* pointer;
	AllocUnit* next;
	AllocUnit* prev;
	size_t size;
	size_t start;
	bool isFree;

	AllocUnit(int size)
	{
		pointer = (int*)malloc(size);
		this->size = size;
		isFree = true;
	}

	AllocUnit* unite(AllocUnit* part)
	{
		auto united = make_united(part->next, this->prev, this->start);
		delete part;
		delete this;
		return united;
	}

	AllocUnit* divide()
	{
		auto part_size = this->size / 2;
		auto left = new AllocUnit(part_size);
		auto right = new AllocUnit(part_size);
		this->make_divided(left, right, this->prev, this->next);
		return left;
	}

private:

	AllocUnit* make_united(AllocUnit* next, AllocUnit* prev, size_t index) 
	{
		AllocUnit* united = new AllocUnit(next->size * 2);
		prev->next = united;
		next->prev = united;
		united->next = next;
		united->prev = prev;
		united->start = index;
		return united;
	}

	void make_divided(AllocUnit* left, AllocUnit* right, AllocUnit* prev, AllocUnit* next)
	{
		prev->next = left;
		next->prev = right;
		left->next = right;
		left->prev = prev;
		right->next = next;
		right->prev = left;
		left->start = this->start;
		right->start = this->start + (this->size / 2);
	}
};


class BuddyAlloc
{
	size_t memory_size;
	AllocUnit *pointer;
	int count;

public:
	BuddyAlloc(size_t size)
	{
		this->memory_size = enough_memory(size);
		this->pointer = new AllocUnit(1);
		auto unit = new AllocUnit(this->memory_size);
		this->pointer->prev = pointer;
		this->pointer->next = unit;
		unit->prev = pointer;
		unit->next = unit;
		this->count = 1;
	}

	void free(void *ptr)
	{
		AllocUnit* unit = pointer;
		for (int i = 0; i < count; i++) 
		{
			unit = unit->next;
			if (unit->pointer == ptr)
			{
				unit->isFree = true;
				break;
			}
		}
		check_unite(unit);
	}

	void* allocate(size_t size) 
	{
		auto required_size = enough_memory(size);
		auto suit_unit = min_unit(required_size);
		if (suit_unit == NULL) 
		{
			throw invalid_argument("No enough unit");
			exit(1);
		}
		auto curr_size = suit_unit->size;
		while (curr_size > required_size) 
		{
			suit_unit = divide(suit_unit);
			curr_size = suit_unit->size;
		}
		suit_unit->isFree = false;
		return suit_unit->pointer;
	}

	void dump()
	{
		auto unit = pointer;
		for (int i = 0; i < count; i++) 
		{
			unit = unit->next;
			if (unit->isFree) 
			{
				std::cout << "free: ";
			}
			else 
			{
				std::cout << "occurred: ";
			}
			std::cout << unit->start << ", " << unit->start + unit->size - 1 << "\n";
		};
		std::cout << "\n";
	}

private:

	size_t enough_memory(size_t number)
	{
		size_t result = 1;
		while (result < number)
			result <<= 1;
		return result;
	}

	AllocUnit* min_unit(size_t needed_size) 
	{
		AllocUnit* suit_unit = NULL;
		auto min_suit_size = memory_size + 1;
		auto curr = pointer;
		for (int i = 0; i < count; i++) 
		{
			curr = curr->next;
			auto curr_size = curr->size;
			if (curr->isFree && needed_size <= curr_size && curr_size < min_suit_size)
			{
				min_suit_size = curr_size;
				suit_unit = curr;
			}
		};
		return suit_unit;
	}

	void check_unite(AllocUnit* unit) 
	{
		auto size = unit->size;
		auto offset = unit->start / size;
		auto part = (offset % 2 == 0) ? unit->next : unit->prev;
		auto delta = (offset % 2 == 0) ? -1 : 1;
		if (part->isFree && part->size == size &&
			part->start / size + delta == offset)
		{
			unit = unit->unite(part);
			this->count--;
			check_unite(unit);
		}
	}

	AllocUnit* divide(AllocUnit* unit)
	{
		AllocUnit* part = unit->divide();
		delete unit;
		this->count++;
		return part;
	}
};

int main(int argc, const char * argv[]) 
{
	auto alloc = BuddyAlloc(1000);
	auto ptr1 = alloc.allocate(5);
	for (auto i = 2; i < 5; i++)
	{
		alloc.allocate(5 * i);
		cout << "Step: " << i - 1 << "\n";
		alloc.dump();
	}
	alloc.free(ptr1);
	cout << "After free:\n";
	alloc.dump();
	return 0;
}
