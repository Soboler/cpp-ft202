#include <Windows.h>
#define START_LENGTH_STACK 16
class StackArray 
{
public:
	StackArray();
	~StackArray();
	int pop();
	void push(int nVal);
	size_t size();
	void erase();
private:
	size_t nSize;
	int* pMem;
	size_t pCurTop;
	size_t pCurEnt;
};