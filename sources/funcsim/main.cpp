/**
 * main.cpp - Entry point of functional simulator (funcsim)
 * Copyright 2009 MDSP team
 */

#include "operation.h"
#include "test.h"
#include "core.h"

int main()
{
    Core* core = new Core();
    core->init( 0x0000);
    core->run();

    //test();

    return 1;
}
