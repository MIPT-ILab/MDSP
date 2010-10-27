/**
* main.cpp - Entry point of functional simulator (funcsim)
* Copyright 2009 MDSP team
*/

#include "read_realization.h"
#include <iostream>

int main()
{
	MyMemory* mm = new MyMemory;
	MemVal* a = mm->read();
	for (int i = 1; i <= 3; i++)
	{
		std::cout << (int)(a->getByteVal(i)) << "\n";
	}
	delete mm;
    return 0;
}

