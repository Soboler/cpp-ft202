#include "pch.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

class region
{
public:
	void* value;
	bool is_empty;
	region* buddy;
	region* next;
	region* prev;
	size_t size;

	region(void* _value, bool _is_empty,
		region* _buddy, region* _next,
		region* _prev, size_t _size)
	{
		value = _value;
		is_empty = _is_empty;
		buddy = _buddy;
		next = _next;
		prev = _prev;
		size = _size;
	}
	void copy_from(region* other)
	{
		size = other->size;
		buddy = other->buddy;
		is_empty = other->is_empty;
		next = other->next;
		prev = other->prev;
		value = other->value;
	}

	operator std::string()
	{
		ostringstream result;
		if (is_empty)
		{
			result << "Empty: True; " << "Size: " << size << " ";
		}
		else
		{
			result << "Empty: False; " << "Size: " << size << "; " << "Value: " << value << " ";
		}
		return result.str();
	}
};

class buddy_allocator
{
private:
	void* memory;
	region* first_region;
	size_t memory_size;

	region* find_smallest_region(size_t size)
	{
		auto reg = first_region;
		region* smallest_reg = nullptr;
		if (first_region->is_empty)
		{
			smallest_reg = first_region;
		}
		while (reg->next != nullptr)
		{
			if (reg->is_empty &&
				reg->size > size &&
				(smallest_reg == nullptr || reg->size < smallest_reg->size))
			{
				smallest_reg = reg;
			}
			reg = reg->next;
		}
		return smallest_reg;
	}

	region* split_region(region* region_to_split, size_t size)
	{
		while (region_to_split->size / 2 > size)
		{
			auto new_size = region_to_split->size / 2;
			auto first_region = new region(region_to_split->value, true, nullptr,
				nullptr, region_to_split->prev,
				new_size);
			auto second_region = new region((void*)((size_t)region_to_split->value + new_size), true, first_region,
				region_to_split->next, first_region, new_size);
			first_region->buddy = second_region;
			first_region->next = second_region;
			second_region->prev = first_region;

			if (region_to_split->prev != nullptr)
			{
				region_to_split->prev->next = first_region;
			}
			if (region_to_split->next != nullptr)
			{
				region_to_split->next->prev = second_region;
			}

			region_to_split = first_region;
		}
		return region_to_split;
	}

	region* find_region_by_value(void* value)
	{
		auto reg = first_region;
		while (reg->next != nullptr)
		{
			if (reg->value == value)
			{
				return reg;
			}
			reg = reg->next;
		}
		if (reg->value == value)
		{
			return reg;
		}
		return nullptr;
	}

	region* merge_regions(region* first, region* second)
	{
		auto result = new region(first->value, true, nullptr,
			second->next, first->prev,
			first->size + second->size);
		auto region_number = ((size_t)(result->value) - (size_t)memory) / result->size;
		if (region_number % 2 == 0)
		{
			auto buddy = find_region_by_value((char*)(size_t)result->value + result->size);
			result->buddy = buddy;
		}
		else
		{
			auto buddy = find_region_by_value((char*)(size_t)result->value - result->size);
			result->buddy = buddy;
		}
		return result;
	}

public:
	buddy_allocator(size_t size)
	{
		memory = malloc(size);
		first_region = new region(memory, true, nullptr, nullptr, nullptr, size);
		memory_size = size;
	}

	void* alloc(size_t size) // Выделяет блок памяти
	{
		auto region = find_smallest_region(size);
		if (region == nullptr)
		{
			throw std::exception("Cannot allocate more");
		}
		if (region->size / 2 > size)
		{
			auto new_region = split_region(region, size);
			new_region->is_empty = false;
			if (new_region->prev == nullptr)
			{
				first_region = new_region;
			}
			return new_region->value;
		}
		region->is_empty = false;
		return region->value;
	}

	void free(void* ptr) // Освобождает блок
	{
		auto reg = first_region;
		while (true)
		{
			if (reg->value == ptr)
			{
				reg->is_empty = true;
				while (reg->buddy != nullptr && reg->buddy->is_empty)
				{
					auto new_reg = merge_regions(reg, reg->buddy);
					reg->copy_from(new_reg);
					if (new_reg->next != nullptr && new_reg->next->buddy == new_reg)
					{
						new_reg = merge_regions(new_reg, new_reg->next);
					}
					else if (new_reg->prev != nullptr && new_reg->prev->buddy == new_reg)
					{
						new_reg = merge_regions(new_reg, new_reg->prev);
					}
					reg->copy_from(new_reg);
				}
				break;
			}

			if (reg->next == nullptr)
			{
				break;
			}
			reg = reg->next;
		}
	}

	void dump() // Выводит информацию о блоках
	{
		ostringstream result;
		auto reg = first_region;
		auto counter = 1;
		while (true)
		{
			result << counter << ") " << reg->operator basic_string<char>() << "\n";
			if (reg->next == nullptr)
			{
				break;
			}
			reg = reg->next;
			counter++;
		}
		cout << result.str() << "\n";
	}
};

int main()
{
	auto alloc = new buddy_allocator(1024);
	alloc->dump();
	auto first = alloc->alloc(100);
	auto second = alloc->alloc(100);
	auto third = alloc->alloc(100);
	alloc->dump();
	alloc->free(third);
	alloc->dump();
	alloc->free(second);
	alloc->dump();
	alloc->free(first);
	alloc->dump();
}
