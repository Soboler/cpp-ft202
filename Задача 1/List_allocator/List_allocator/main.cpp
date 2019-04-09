#include "pch.h"
#include <iostream>
#include "allocator_interface.h"
#include "linear_allocator.h"
#include "stack_allocator.h"
#include "linked_array_allocator.h"
#include <string>
#include <windows.h>

using namespace std;

auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

template <class T>
void print_error(T expected, T actual, const int index)
{
	SetConsoleTextAttribute(hConsole, 12);
	cout << "ERROR" << "\n" << "difference at index " << index << "\n";
	cout << "Expected " << expected;
	cout << "But was " << actual;
	SetConsoleTextAttribute(hConsole, 7);
}

void print_ok()
{
	SetConsoleTextAttribute(hConsole, 10);
	cout << "OK" << "\n";
	SetConsoleTextAttribute(hConsole, 7);
}

void test_insert(const string& arr_name, allocator_interface<int> &array)
{
	cout << "test_insert " << arr_name << "\n";
	const auto N = 10000;
	for (auto i = 0; i < N; i++)
		array.push_back(i);
	const auto all_elements = array.all_elements();
	for (auto i = 0; i < N; i++)
	{
		if (all_elements[i] == i) continue;
		print_error(i, all_elements[i], i);
		return;
	}
	print_ok();
}

void test_get(const string& arr_name, allocator_interface<int> &array)
{
	cout << "test_get " << arr_name << "\n";
	const auto N = 10000;
	for (auto i = 0; i < N; i++)
	{
		auto val = array.pop_back();
		if (val == 10000 - i - 1) continue;
		print_error(10000 - i - 1, val, i);
		return;
	}
	print_ok();
}

int main()
{
	linked_array_allocator<int> linked_array;
	stack_allocator<int> stack_array;
	linear_allocator<int> linear_array;
	allocator_interface<int>* arrays[3]{ &linked_array, &stack_array, &linear_array };
	for (auto& array : arrays)
		test_insert(array->class_name(), *array);

	for (auto& array : arrays)
		test_get(array->class_name(), *array);


	return 0;
}