/**
 * main_functions.cpp - Functions used to be called from the main
 * @author Pavel Zaichenkov
 * Copyright 2009 MDSP team
 */

#include <fstream>
#include <iostream>
#include <cassert>

#include "main_functions.h"

using namespace std;

/*
 * Check argument number in program call
 */

/* 
    * Useless function!
*/
/*
int checkArguments(int argc)
{
    int param_number = 2;
    if (argc != param_number)
    {
        cout << "There should be " << param_number - 1 << " argument(s)" << endl;
        assert(0);
    }
    return 1;
}
*/

/*
 * Safe binary input file opening ("test.bin", for instance).
 * Checks for all possible errors.
 * Returns 1 if there weren't any errors, in case of errors returns 0.
 */
int openBinaryInputFile(ifstream& input, const char* filename)
{
    cout << "Input file: " << filename << endl;
    input.open (filename, ifstream::binary);
    if(input.fail())
    {
        cout << "Error opening " << filename << endl;
        input.close();
        return 0;
    }
    return 1;
}

/*
 * Safe binary input file closing ("test.bin", for instance).
 * Checks for all possible errors.
 * Returns 1 if there weren't any errors, in case of errors returns 0.
 */
int closeBinaryInputFile(ifstream& input, const char* filename)
{
    if (input.is_open())
    {
        input.close();
    }
    return 1;
}

