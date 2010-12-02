/**
 * main.cpp - Entry point of functional simulator (funcsim)
 * Copyright 2009-2010 MDSP team
 */

#include <fstream>
#include <iostream>

#include "core.h"
#include "types.h"
#include "main_functions.h"
#include "config.h"
#include "scheduler.h"

using namespace std;

int main(int argc, char** argv)
{
    /* Analysing and handling of inserted arguments */
    Config handler;
    handler.handleArgs( argc, argv);
    
    Scheduler scheduler;

    scheduler.start_pc = 0x0000;
    scheduler.init( &handler);

    return 0;
}
