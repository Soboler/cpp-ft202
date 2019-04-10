#include "LinearArray.h"

LinearArray::LinearArray() 
{
	this->nMemSize = START_LENGTH_LINEAR * sizeof(int);
	this->pEnd = 0;
	this->nSize = START_LENGTH_LINEAR;
	this->pMem = (int*)malloc(this->nMemSize);
}

int& LinearArray::operator[](size_t nIndex)
{
	if (nIndex < this->pEnd)
		return this->pMem[nIndex];
}

size_t LinearArray::size() 
{
	return this->pEnd;
}

void LinearArray::set(size_t nIndex, int nVal) 
{
	if (nIndex < this->pEnd)
		this->pMem[nIndex] = nVal;
}

void LinearArray::pushBack(int nVal) 
{
	if (this->pEnd>= this->nSize) 
	{
		int* pTemp = (int*)malloc(this->nMemSize * 2);
		memcpy(pTemp, this->pMem, this->nMemSize);
		free(this->pMem);
		this->pMem = pTemp;
		this->nMemSize *= 2;
		this->nSize *= 2;
	}
	this->pMem[this->pEnd] = nVal;
	this->pEnd += 1;
	//this->nSize += sizeof(int);
}

void LinearArray::erase() 
{
	free(pMem);
	this->pMem = (int*)malloc(START_LENGTH_LINEAR * sizeof(int));
	this->pEnd = 0;
}

LinearArray::~LinearArray() 
{
	free(pMem);
}