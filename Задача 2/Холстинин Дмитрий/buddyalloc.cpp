/*
	Author: Kholstinin Dmitriy
*/
#include <iostream>
#include <vector>
#include <tuple>

const size_t BIT_DEPTH = sizeof(size_t) * 8;

struct Block
{
	int level;
	bool free;
	Block *prev;
	Block *next;
	uintptr_t ptr;

	Block(int level, bool free, uintptr_t pool, Block *prev = NULL, Block *next = NULL)
	{
		this->level = level;
		this->free = free;
		this->ptr = pool;
		this->prev = prev;
		this->next = next;
	}
};

class BuddyAllocator
{
	std::vector<Block*> blocks[BIT_DEPTH];
	void *pool;

	size_t ceil_power_of_2(size_t value)
	{
		value--;
		for (int i = 1; i < BIT_DEPTH; i <<= 1)
		{
			value |= value >> i;
		}
		return ++value;
	}

	int get_level(const size_t size)
	{
		return (int)ceil(log2(size));
	}

	size_t get_size(const int index)
	{
		return 1 << index;
	}

	Block* find_free_block(const int start)
	{
		for (int i = start; i < BIT_DEPTH; i++)
		{
			for (size_t j = 0; j < blocks[i].size(); j++)
			{
				if (blocks[i][j]->free)
				{
					return blocks[i][j];
				}
			}
		}
		return NULL;
	}

	void clamp(Block *source_left, Block *source_right, Block *target_left, Block *target_right)
	{
		target_left->prev = source_left->prev;
		if (source_left->prev)
		{
			source_left->prev->next = target_left;
		}
		target_right->next = source_right->next;
		if (source_right->next)
		{
			source_right->next->prev = target_right;
		}
	}

	Block* split(Block *block)
	{
		block->free = false;
		auto size = get_size(block->level);
		auto first = new Block(block->level - 1, true, block->ptr);
		auto second = new Block(block->level - 1, true, block->ptr + size / 2, first);
		first->next = second;
		clamp(block, block, first, second);
		blocks[first->level].push_back(first);
		blocks[second->level].push_back(second);
		return first;
	}

	std::tuple<Block*, int> find_block_by_pointer(const uintptr_t ptr)
	{
		for (int i = 0; i < BIT_DEPTH; i++)
		{
			for (size_t j = 0; j < blocks[i].size(); j++)
			{
				if (blocks[i][j]->ptr == ptr)
				{
					return std::make_tuple(blocks[i][j], j);
				}
			}
		}
		throw new std::invalid_argument("Invalid pointer");
	}

	void free(Block *block, int index)
	{
		block->free = true;
		auto even = index % 2 == 0;
		auto buddy = even ? block->next : block->prev;
		if (buddy && buddy->level == block->level && buddy->free)
		{
			if (!even)
			{
				std::swap(block, buddy);
			}
			index /= 2;
			auto common_block = blocks[block->level + 1][index];
			clamp(block, buddy, common_block, common_block);
			auto list = &blocks[block->level];
			list->erase(std::find(list->begin(), list->end(), block));
			list->erase(std::find(list->begin(), list->end(), buddy));
			free(common_block, index);
		}
	}

public:
	BuddyAllocator(size_t total_size)
	{
		total_size = ceil_power_of_2(total_size);
		auto level = get_level(total_size);
		pool = std::malloc(total_size);
		auto root = new Block(level, true, (uintptr_t)pool);
		blocks[level].push_back(root);
	}

	void* alloc(const size_t size)
	{
		auto level = get_level(ceil_power_of_2(size));
		auto block = find_free_block(level);
		if (!block)
		{
			return NULL;
		}
		for (auto i = block->level; i > level; i--)
		{
			block = split(block);
		}
		block->free = false;
		return (void*)block->ptr;
	}

	void free(void* ptr)
	{
		Block *block;
		int index;
		std::tie(block, index) = find_block_by_pointer((uintptr_t)ptr);
		free(block, index);
	}

	void dump()
	{
		for (size_t i = BIT_DEPTH - 1; i < BIT_DEPTH; i--)
		{
			if (blocks[i].empty())
			{
				continue;
			}
			std::cout << '#' << i << ":\t";
			auto size = get_size(i);
			for (auto j = blocks[i].begin(); j < blocks[i].end(); j++)
			{
				auto block = *j;
				auto separator = block->free ? " - " : " # ";
				std::cout << '[' << block->ptr << separator << block->ptr + size - 1 << ']';
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}

	~BuddyAllocator()
	{
		std::free(pool);
	}
};

int main()
{
	BuddyAllocator allocator(1024);
	allocator.dump();
	auto a = allocator.alloc(34);
	auto b = allocator.alloc(66);
	auto c = allocator.alloc(35);
	auto d = allocator.alloc(67);
	allocator.dump();
	allocator.free(b);
	allocator.dump();
	allocator.free(d);
	allocator.dump();
	allocator.free(a);
	allocator.dump();
	allocator.free(c);
	allocator.dump();
}
