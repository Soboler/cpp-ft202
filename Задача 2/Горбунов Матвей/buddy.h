#pragma once
#include "chunk.h"
class buddy
{
private:
	size_t size;
	chunk* first;
	void print(chunk* chunk);
public:
	buddy(size_t size);
	void* Alloc(size_t size);
	void Free(void *ptr);
	void Dump();
	~buddy();
};

