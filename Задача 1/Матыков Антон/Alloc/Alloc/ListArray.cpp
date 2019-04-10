#include "ListArray.h"

ListArray::ListArray() 
{
	//this->pEnd = NULL;
	this->pTop = NULL;
	this->nSize = -1;
}

void ListArray::push_back(int nVal) 
{
	ListElem* pNewElem = (ListElem*)malloc(sizeof(ListElem));
	pNewElem->nVal = nVal;
	pNewElem->pNext = NULL;
	if (this->pTop == NULL)
	{
		//this->pEnd->pNext = pNewElem;
		this->pTop = pNewElem;
		this->nSize++;
		return;
	}
	ListElem* pCurElem = this->pTop;
	while (pCurElem->pNext != NULL)
	{
		pCurElem = pCurElem->pNext;
	}
	pCurElem->pNext = pNewElem;
	this->nSize++;
}

void ListArray::push_front(int nVal) 
{
	ListElem* pNewElem = (ListElem*)malloc(sizeof(ListElem));
	pNewElem->nVal = nVal;
	if (this->pTop == NULL) 
	{
		this->pTop = pNewElem;
		this->nSize++;
		return;
	}
	pNewElem->pNext = this->pTop;
	this->pTop = pNewElem;
	this->nSize++;
}

int ListArray::pop_back() 
{
	ListElem* pCurElem = this->pTop;
	ListElem* pPrevElem = NULL;
	while (pCurElem->pNext != NULL) 
	{
		pPrevElem = pCurElem;
		pCurElem = pCurElem->pNext;
	}
	if (pCurElem != NULL) 
	{
		int nTemp = pCurElem->nVal;
		if (pPrevElem != NULL) 
			pPrevElem->pNext = NULL;
		else
			this->pTop = NULL;
		delete pCurElem;
		this->nSize--;
		return nTemp;
	}
}

size_t ListArray::size() 
{
	return this->nSize + 1;
}

void ListArray::erase() 
{
	ListElem* pCurElem = this->pTop;
	while (pCurElem != NULL)
	{
		ListElem* pNextElem = pCurElem->pNext ? NULL : pCurElem->pNext;
		delete pCurElem;
		pCurElem = pNextElem;
	}
	this->pTop = NULL;
	this->nSize = -1;
}

ListArray::~ListArray() 
{
	ListElem* pCurElem = this->pTop;
	while (pCurElem != NULL)
	{
		ListElem* pNextElem = pCurElem->pNext ? NULL : pCurElem->pNext;
		delete pCurElem;
		pCurElem = pNextElem;
	}
}