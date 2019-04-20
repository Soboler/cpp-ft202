#pragma once
class Block
{
public:
	Block* right;
	Block* left;
	int* ptr;
	int start;
	bool isFree;
	int size;

	Block(int size1);
	~Block();
};