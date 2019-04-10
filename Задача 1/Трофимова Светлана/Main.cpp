#include "pch.h"
#include <iostream>
#include "Alloc.cpp"


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
}
