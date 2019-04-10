#include "StackArray.h"

StackArray::StackArray() 
{
	
	this->pCurTop = 0;
	this->nSize = START_LENGTH_STACK * sizeof(int);
	this->pMem = (int*)malloc(this->nSize);
}

void StackArray::push(int nVal) 
{
	if (this->pCurTop >= this->nSize/sizeof(int)) 
	{
		this->pMem = (int*)realloc(this->pMem, this->nSize * 2);
		//memcpy(pTemp, this->pMem, this->nSize/sizeof(int));
		//delete[] this->pMem;
		//this->pMem = pTemp;
		this->nSize *= 2;
	}
	this->pMem[this->pCurTop] = nVal;
	this->pCurTop += 1;
}

int StackArray::pop() 
{
	if (this->pCurTop > 0) 
	{
		this->pCurTop--;
		return this->pMem[this->pCurTop];
	}
		
}

size_t StackArray::size() 
{
	return this->pCurTop;
}

void StackArray::erase() 
{
	free(pMem);
	this->pMem = (int*)malloc(START_LENGTH_STACK * sizeof(int));
	this->pCurTop = 0;
}

StackArray::~StackArray() 
{
	free(pMem);
}