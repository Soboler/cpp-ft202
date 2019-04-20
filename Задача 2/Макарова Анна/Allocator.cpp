#include "pch.h"
#include <iostream>
#include <vector>

class MemoryPiece {
public:
	MemoryPiece* next;
	void* startPtr;
	int size;
	bool isFree;
	int sizeOfData;
	std::vector <MemoryPiece*> neighbours;

	MemoryPiece(int size, void* ptr) {
		//size must be pow of 2
		this->size = size;
		startPtr = ptr;
		isFree = true;
		sizeOfData = 0;
	}

	void capture(int dataSize) {
		isFree = false;
		sizeOfData = dataSize;
	}

	void free() {
		isFree = true;
		sizeOfData = 0;
	}

	void split() {
		size = size / 2;

		auto nextPiece = next;
		auto secondPartPiece = new MemoryPiece(size, (bool*)startPtr + size);
		next = secondPartPiece;
		(*secondPartPiece).next = nextPiece;

		neighbours.push_back(secondPartPiece);
		(*secondPartPiece).neighbours.push_back(this);

	}

	void tryMerge() {
		if (!isFree)
			return;
		while (!neighbours.empty()) {
			auto lastNeighbour = neighbours.back();
			if (lastNeighbour->startPtr > startPtr) {
				if (  neighbours.back()->size == size && lastNeighbour->isFree) {
					size *= 2;
					next = next->next;
				}
				else
					break;
			}
			else {
				if (neighbours.back()->size == size && lastNeighbour->isFree) {
					lastNeighbour->size*= 2;
					lastNeighbour->next = next;
				}
				else
					break;
			}
			neighbours.pop_back();
		}
	}
};

class Allocator {
	int fullSize;
	MemoryPiece* firstPiece;

public:
	Allocator(int size) {
		fullSize = size;
		auto ptr = malloc(size);
		firstPiece = new MemoryPiece(size, ptr);
	}

	void* alloc(int size) {
		auto piece = firstPiece;
		while (!piece->isFree || piece->size < size)
			piece = piece->next;
		while (size <= piece->size / 2)
			piece->split();
		piece->capture(size);
		return piece->startPtr;
	}

	void free(void* ptr) {
		auto piece = firstPiece;
		while (piece->startPtr != ptr)
			piece = piece->next;
		piece->free();
		piece->tryMerge();
	}

	void dump() {
		auto piece = firstPiece;
		std::cout << "format: startIndex, size, is free, size of data\n";
		while (piece->next != NULL) {
			std::cout << piece->startPtr << ", " << piece->size << ", " << piece->isFree << ", " << piece->sizeOfData << "\n";
			piece = piece->next;
		}
	}
};

int main()
{
	Allocator allocator = Allocator(1024);
	allocator.alloc(35);
	auto p = allocator.alloc(7);
	allocator.alloc(120);

	std::cout << "Allocator after add 35, 7, 120\n";
	allocator.dump();

	allocator.free(p);
	std::cout << "\nAllocator after free ptr of 7\n";
	allocator.dump();

	std::getchar();
}
