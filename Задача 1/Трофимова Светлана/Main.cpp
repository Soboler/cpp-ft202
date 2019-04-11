#include "pch.h"
#include <iostream>
#include "Alloc.cpp"
#include "Stack.cpp"
#include"LinkedList.cpp"


int main()
{
	Arr d = Arr(1024);
	d.set(1, 2);
	d.set(2, 3);
	d.set(100, 100);
	d.set(1000, 1000);
	d.set(10000, 10000);
	std::cout << d.get(1) << std::endl;
	std::cout << d.get(100) << std::endl;
	std::cout << d.get(1000) << std::endl;
	d.remove_all(1024);
    	std::cout << d.get(100); 
	
	Stack s = Stack(1024);
	s.push_back(4);
	s.push_back(32);
	std::cout << s.pop() << std::endl;
	std::cout << s.pop_back() << std::endl;
	std::cout << s.pop_back() << std::endl;
	s.remove_all(1024);
	s.pop();
	
	LinkedList l = LinkedList();
	l.set(1, 2);
	l.push_back(45);
	std::cout << l.pop() << std::endl;
	l.set(10, 5);
	std::cout << l.get(1) << std::endl;
	std::cout << l.pop_back() << std::endl;
	l.remove_all();
	l.pop_back();
}
