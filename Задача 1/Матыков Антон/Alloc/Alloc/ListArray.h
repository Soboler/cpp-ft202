#include <Windows.h>

struct ListElem 
{
	ListElem* pNext;
	int nVal;
};


class ListArray 
{
public:
	ListArray();
	~ListArray();
	void push_back(int nVal);
	void push_front(int nVal);
	int pop_back();
	size_t size();
	void erase();
private:
	ListElem* pTop;
	//ListElem* pEnd;
	size_t nSize;
};