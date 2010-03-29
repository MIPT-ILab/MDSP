/**
 * main.cpp - Entry point of functional simulator (funcsim)
 * Copyright 2009 MDSP team
 */

#include "core.h"
#include "types.h"
#include "arg_parser.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	/* Check argument number */
	if ( checkArguments( argc))
	{
		/* ifstream is used to handle binary input file */
		ifstream in_bin;

		if ( openBinaryInputFile ( in_bin, argv[1]))
		{
			Core* core = new Core();
			core->init( 0x0000);
			core->loadBinary( in_bin);
			closeBinaryInputFile ( in_bin, argv[1]);
			core->run();

		}
	}
    return 0;
}
