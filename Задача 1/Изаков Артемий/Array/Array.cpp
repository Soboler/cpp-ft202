#include "pch.h"
#include <iostream>
#include <string>
#include "Linear/linear_array.h"
#include "Stack/stack_array.h"
#include "Linked/linked_array.h"

using namespace std;

void test_linear();
void test_stack();
void test_linked();

void write_heading(const string& heading);

int main()
{
	test_linear();
	test_stack();
	test_linked();

	cout << endl;

	return 0;
}

void test_linear()
{
	write_heading("linear");
	linear_array linear;

	linear.push_back(1);
	linear.push_back(2);
	linear.push_back(100);
	linear.push_back(4);

	linear.set(2, 3);

	linear.pop_back();

	for (auto i = 0; i < 3; i++)
		cout << linear.get(i) << " ";

	linear.remove_all();
}

void test_stack()
{
	write_heading("stack");
	stack_array stack;

	for (auto i = 0; i < 10; i++)
		stack.push_back(i);

	for (auto i = 0; i < 10; i++)
		cout << stack.pop_back() << " ";

	stack.remove_all();
}

void test_linked()
{
	write_heading("linked");
	linked_array linked;

	linked.push_back(1);
	linked.push_back(2);
	linked.push_back(100);
	linked.push_back(4);

	linked.set(2, 3);

	linked.pop_back();

	for (auto i = 0; i < 3; i++)
		cout << linked.get(i) << " ";

	linked.remove_all();
}

void write_heading(const string& heading)
{
	cout << "\n\n-----=== " + heading + " ===-----\n\n";
}
