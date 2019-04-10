#include <Windows.h>
#define START_LENGTH_LINEAR 16
class LinearArray 
{
public :
	LinearArray();
	~LinearArray();
	int& operator [](size_t nIndex);
	size_t size();
	void pushBack(int nVal);
	void erase();
	void set(size_t nIndex, int nVal);

private:
	int* pMem;
	size_t nSize;
	size_t nMemSize;
	size_t pEnd;
};