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
    Config handler;
    handler.handleArgs( argc, argv);

    /* ifstream is used to handle binary input file */
    ifstream in_bin;
	if ( handler.getInputType())
	{
		openBinaryInputFile ( in_bin, handler.getBinaryFilename().c_str());
	}
	else
	{
		cout << "No ELF support provided\n";
		return -1;
	}

    Core* core = new Core();
    core->init( 0x0000);
    core->loadBinary( in_bin);

    closeBinaryInputFile ( in_bin, argv[1]);

    core->run();

    return 0;
}
