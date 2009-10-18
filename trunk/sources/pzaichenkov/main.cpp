/**
* main.cpp - Entry point of functional simulator (funcsim)
* Copyright 2009 MDSP team
*/

#include "operation.h"

int main()
{
    Operation *op1 = new Operation();
    op1->set(MOVE, BRR, NOP, NOP, 1, 1, 1, 1, 1, 1, 2);
    op1->dump();
    return 0;
}

