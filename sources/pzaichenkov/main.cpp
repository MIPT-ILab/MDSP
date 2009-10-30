/**
 * main.cpp - Entry point of functional simulator (funcsim)
 * Copyright 2009 MDSP team
 */

#include "operation.h"
#include "test.h"
#include "core.h"
#include "register_file.h"
#include <iostream>
#include <stdio.h>
int main()
{
    Core* core = new Core();
    core->init( 0x0000);
    core->run();

    //test();
    Operation *op1 = new Operation();
    op1->set(MOVE, BRR, NOP, NOP, 0, 0, 0, 0, 1, 0, 2);
    op1->dump();
    MemVal* mem_value = new MemVal(4);
    mem_value = op1->encode();
    printf("%i\n", mem_value->getByteVal(0));
    return 0;
}
