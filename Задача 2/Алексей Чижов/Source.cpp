#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;
#define byte unsigned char

class Allocator
{
	byte* array_;
	size_t degrees_of_two = 23;
	size_t size_ = 1 << degrees_of_two;
	size_t shift = 2 * sizeof(size_t);
	struct block
	{
		size_t size_block;
		bool used;
		union {
			pair<block*, block*> neighbors_blocks;
			byte data[1];
		};
	};
	block* blocks_[24]{};
	size_t blocks_mask_;

	static inline unsigned int __fastcall bsr(unsigned int x)
	{
		_asm { bsr eax, x }
	}

	static inline unsigned int __fastcall bsf(unsigned int x)
	{
		_asm { bsf eax, x }
	}

	size_t nearest_degree_of_two(size_t size)
	{
		return bsr(size - 1) + 1;
	}

	block* remove_block(size_t index)
	{
		block* current = blocks_[index];
		if (current->neighbors_blocks.second == nullptr)
			blocks_mask_ = blocks_mask_ & (~(1 << index));
		else
		{
			blocks_[index] = current->neighbors_blocks.second;
			blocks_[index]->neighbors_blocks.first = nullptr;
		}
		current->size_block = index;
		current->used = true;
		return current;
	}

	void remove_block(block* removing_block)
	{
		auto block_index = removing_block->size_block;
		auto left_neighbor = removing_block->neighbors_blocks.first;
		auto right_neighbor = removing_block->neighbors_blocks.second;
		if (left_neighbor == nullptr && right_neighbor == nullptr)
		{
			blocks_mask_ &= ~(1 << (block_index));
			return;
		}
		if (right_neighbor != nullptr)
			right_neighbor->neighbors_blocks.first = left_neighbor;
		if (left_neighbor != nullptr)
			left_neighbor->neighbors_blocks.second = right_neighbor;
	}

	void add_block(block* block)
	{
		auto index = block->size_block;
		auto size_block = 1 << index;
		block->used = false;
		block->neighbors_blocks.first = nullptr;
		if (size_block & blocks_mask_)
		{
			block->neighbors_blocks.second = blocks_[index];
			blocks_[index]->neighbors_blocks.first = block;
		}
		else
		{
			blocks_mask_ |= size_block;
			block->neighbors_blocks.second = nullptr;
		}
		blocks_[index] = block;
	}

public:

	Allocator(size_t size)
	{
		degrees_of_two = nearest_degree_of_two(size);
		size_ = 1 << degrees_of_two;
		block* next_block = static_cast<block*>(malloc(size_));
		array_ = reinterpret_cast<byte*>(next_block);
		next_block->size_block = degrees_of_two;
		add_block(next_block);
	}
	void* alloc(size_t size)
	{
		size_t closest_size = 1 << nearest_degree_of_two(size + shift);
		size_t suitable_blocks_mask = ~(closest_size - 1);
		size_t free_suitable_blocks_mask = suitable_blocks_mask & blocks_mask_;
		size_t index_of_smallest_suitable_block = bsf(free_suitable_blocks_mask);
		block* next_block = remove_block(index_of_smallest_suitable_block);
		while (closest_size <= 1 << (next_block->size_block - 1))
		{
			next_block->size_block--;
			block* free_block = reinterpret_cast<block*>(reinterpret_cast<byte*>(next_block) + (1 << next_block->size_block));
			free_block->size_block = next_block->size_block;
			add_block(free_block);
		}
		return next_block->data;
	}

	void dump()
	{
		block* last_byte = reinterpret_cast<block*>(array_ + (1 << degrees_of_two));
		block* current_block = reinterpret_cast<block*>(array_);
		cout << "Block infos:\n";
		cout << "Blocks mask: " << bitset<24>(blocks_mask_) << '\n';
		while (current_block != last_byte)
		{
			auto size_block = 1 << current_block->size_block;
			block* next_block = reinterpret_cast<block*>(reinterpret_cast<byte*>(current_block) + size_block);
			cout << hex << current_block << ' ';
			cout << dec << (current_block->used ? "used" : "free") << " size: " << (1 << current_block->size_block) << '\n';
			current_block = next_block;
		}
		cout << "End on information\n";
	}

	void free(void* ptr)
	{
		 block* cleared_block = reinterpret_cast<block*>((byte*)ptr - shift);
		 
		 while (true)
		 {
			 auto shift_from_start = (size_t)((byte*)cleared_block - array_);
			 auto start_address_of_data = (size_t)array_;
			 auto block_size = 1 << cleared_block->size_block;
			 block* nearest_block = (block*)((shift_from_start ^ block_size) + start_address_of_data);
			 if (cleared_block->size_block == degrees_of_two || nearest_block->used || nearest_block->size_block != cleared_block->size_block)
				 break;
		     remove_block(nearest_block);
			 cleared_block = (block*)min((size_t)nearest_block, (size_t)cleared_block);
			 cleared_block->size_block++;
		 }
		 add_block(cleared_block);
	}
};


int main()
{
	Allocator allocator(1 << 23);
	allocator.dump();
	vector<void*> data;
	for (auto i = 0; i < 10; i++)
	{
		data.push_back(allocator.alloc(40));
	}
	allocator.dump();
	allocator.free(data[9]);
	allocator.free(data[5]);
	allocator.free(data[0]);
	allocator.dump();
	allocator.free(data[4]);
	allocator.dump();
	void* data1 = allocator.alloc((1 << 18) - 8);
	allocator.dump();
	void* data2 = allocator.alloc((1 << 18) - 8);
	allocator.dump();
	allocator.free(data1);
	allocator.free(data2);
	allocator.dump();
	allocator.alloc(40);
	allocator.alloc(40);
	allocator.dump();
	return 0;
}