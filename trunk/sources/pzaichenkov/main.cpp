/**
* main.cpp - Entry point of functional simulator (funcsim)
* Copyright 2009 MDSP team
*/

#include "operation.h"

int main()
{
    Operation *op1 = new Operation();
    op1->set(MOVE, BRR, NOP, NOP, 0, 0, 0, 0, 1, 0, 2);
    op1->dump();
    return 0;
}