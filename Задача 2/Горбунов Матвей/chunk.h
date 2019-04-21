#pragma once
class chunk
{
public:
	int *ptr;
	size_t size;
	chunk* prev;
	chunk* next;
	chunk* left;
	chunk* right;
	chunk* parent;
	bool is_free;
	int start;

	chunk(size_t size, chunk* parent);

	void split();
	void unite();

	~chunk();
};

