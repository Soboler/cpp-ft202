
#include <iostream>
#include <cmath>
#include "Block.h"
#include "pch.h"

Block::Block(int size1) {
	ptr = (int*)malloc(size1);
	size = size1;
	isFree = true;
}

Block::~Block() {
	free(ptr);
}
