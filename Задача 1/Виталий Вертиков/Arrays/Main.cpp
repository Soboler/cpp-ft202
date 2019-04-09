#include "pch.h"
#include "StackArray.h"
#include "LinkedArray.h"
#include "LinearArray.h"
#include <iostream>
using namespace std;

void test_linear()
{
	LinearArr* arr = new LinearArr(1000);

	arr->set(100, 100);
	printf("%d\n", arr->get(100));
	arr->set(2000, 200);
	arr->push_back(300);
	printf("%d\n", arr->pop_back());
	arr->remove_all();
	printf("\n");
}

void test_stack()
{
	StackArr* arr = new StackArr(100);

	for (int i = 0; i < 5; i++)
		arr->push_back(i);

	for (int i = 0; i < 5; i++)
		printf("%d\n", arr->pop_back());
	printf("\n");
}

void test_linked()
{
	LinkedArr* arr = new LinkedArr();
	for (int i = 0; i < 10; i++)
		arr->push_back(i);

	printf("%d", arr->get(2));
	arr->set(2, 100);
	printf("%d", arr->get(2));
}

int main()
{
	test_linear();
	test_stack();
	test_linked();
}