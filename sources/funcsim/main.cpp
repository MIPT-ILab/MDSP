/**
 * main.cpp - Entry point of functional simulator (funcsim)
 * Copyright 2009 MDSP team
 */

#include "core.h"
#include "test.h"

int main()
{
    Core* core = new Core();
    core->init( 0x0000);
    core->run();

    test();

    return 0;
}
