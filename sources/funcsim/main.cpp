/**
 * main.cpp - Entry point of functional simulator (funcsim)
 * Copyright 2009 MDSP team
 */

#include "core.h"
#include "types.h"
#include "main_functions.h"
#include "handle_args.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	/*
	* Analysing and handling of inserted arguments
	* see description in "handle_args.h
	*/
	char test_file[file_name_size] = "\0";
	char log_file[file_name_size] = "\0";
	handleArgs( argc, argv, test_file, log_file);
	
	/* Check arguments number */
	checkArguments( argc);

	/* ifstream is used to handle binary input file */
	ifstream in_bin;
	openBinaryInputFile ( in_bin, argv[1]);

    Core* core = new Core();
    core->init( 0x0000000A);
    core->loadBinary( in_bin);

	closeBinaryInputFile ( in_bin, argv[1]);

	core->run();

	return 0;
}
