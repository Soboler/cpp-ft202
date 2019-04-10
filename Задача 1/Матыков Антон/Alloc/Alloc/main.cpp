#include "LinearArray.h"
#include "ListArray.h"
#include "StackArray.h"
#include <stdio.h>

#define ELEM_VALUES 32
#define SET_VALUE 9

int TestLinearArray() 
{
	size_t nErr = 0;
	LinearArray ar = LinearArray();
	nErr += ar.size() != 0;
	for (int i = 0; i < ELEM_VALUES; i++) 
	{
		ar.pushBack(i);
	}
	nErr += ar.size() != ELEM_VALUES;
	for (int i = 0; i < ELEM_VALUES; i++) 
	{
		nErr += ar[i] != i;
	}
	//ar.set(ELEM_VALUES - 1, SET_VALUE);
	//nErr += ar[ELEM_VALUES - 1] != SET_VALUE;
	ar.erase();
	nErr += ar.size() != 0;
	return nErr;
}

int TestListArray() 
{
	size_t nErr = 0;
	ListArray list = ListArray();
	nErr += list.size() != 0;
	for (int i = 0; i < ELEM_VALUES; i++)
	{
		list.push_back(i);
	}
	nErr += list.size() != ELEM_VALUES;
	for (int i = ELEM_VALUES - 1; i >= 0; i--)
	{
		nErr += list.pop_back() != i;
	}
	for (int i = 0; i < ELEM_VALUES; i++)
	{
		list.push_front(i);
	}
	nErr += list.size() != ELEM_VALUES;
	list.erase();
	nErr += list.size() != 0;
	return nErr;
	
}

int TestStackArray() 
{
	size_t nErr = 0;
	StackArray ar = StackArray();
	nErr += ar.size() != 0;
	for (int i = 0; i < ELEM_VALUES; i++)
	{
		ar.push(i);
	}
	nErr += ar.size() != ELEM_VALUES;
	for (int i = ELEM_VALUES - 1; i >= 0; i--)
	{
		nErr += ar.pop() != i;
	}
	for (int i = 0; i < ELEM_VALUES; i++)
	{
		ar.push(i);
	}
	ar.erase();
	nErr += ar.size() != 0;
	return nErr;
}

int main(int argc, char* argv[]) 
{
	printf("Error val Linear: %d\nError val List: %d\nError val Stack: %d\n",
		TestLinearArray(), TestListArray(), TestStackArray());
}