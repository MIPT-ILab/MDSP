#pragma once

#include "memory.h"

/**
* Class for my own realization of the "read()" function
*/

class MyMemory: public MemoryModel
{
public:

	MemVal* read();
};
