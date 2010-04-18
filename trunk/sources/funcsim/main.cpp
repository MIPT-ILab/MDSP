/**
 * main.cpp - Entry point of functional simulator (funcsim)
 * Copyright 2009 MDSP team
 */

#include <fstream>
#include <iostream>

#include "core.h"
#include "types.h"
#include "main_functions.h"
#include "config.h"

using namespace std;

int main(int argc, char** argv)
{
    /* Analysing and handling of inserted arguments */
    Config handler( argc, argv);
    handler.handleArgs();

    /* Check arguments number */
    checkArguments( argc);

    /* ifstream is used to handle binary input file */
    ifstream in_bin;
    openBinaryInputFile ( in_bin, argv[1]);

    Core* core = new Core();
    core->init( 0x0000);
    core->loadBinary( in_bin);

    closeBinaryInputFile ( in_bin, argv[1]);

    core->run();

    return 0;
}
