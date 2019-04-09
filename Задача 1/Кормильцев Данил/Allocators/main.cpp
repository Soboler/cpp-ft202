#include "pch.h"
#include <iostream>
#include <string>
#include "linear.h"
#include "LinkedList.h"
#include "Stack.h"

void test_linked_list()
{
	auto linked_s = new linked_list<const char>();
	linked_s->push_back("a");
	linked_s->push_back("b");
	linked_s->push_back("c");
	auto test_value_1 = linked_s->get(1);
	linked_s->set(1, "d");
	auto test_value_2 = linked_s->get(1);
}

void test_linear_list()
{
	auto _linear = new linear<int>();
	_linear->push_back(1);
	_linear->push_back(2);
	_linear->push_back(3);
	auto test_value_1 = _linear->get(1);
	_linear->set(1, 4);
	auto test_value_2 = _linear->get(1);
	auto test_value_3 = _linear->pop_back();
	auto test_value_4 = _linear->pop_back();
}

void test_stack()
{
	auto stack_arr = new stack<int>();
	stack_arr->push_back(1);
	stack_arr->push_back(2);
	stack_arr->push_back(3);
	auto test_value_1 = stack_arr->pop_back();
	auto test_value_2 = stack_arr->pop_back();
	auto test_value_3 = stack_arr->pop_back();
}

int main()
{
	test_linked_list();
	test_linear_list();
	test_stack();
}