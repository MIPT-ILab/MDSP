/**
 * main_functions.cpp - Functions used to be called from the main
 * @author Pavel Zaichenkov
 * Copyright 2009 MDSP team
 */

#ifndef MAIN_FUNC_H
#define MAIN_FUNC_H


using namespace std;

/*
 * Check argument number in program call
 */
/*
int checkArguments(int argc);
*/

/*
 * Safe binary input file opening ("test.bin", for instance).
 * Checks for all possible errors.
 * Returns 1 if there weren't any errors, in case of errors returns 0.
 */
int openBinaryInputFile(ifstream& input, const char* filename);


/*
 * Safe binary input file closing ("test.bin", for instance).
 * Checks for all possible errors.
 * Returns 1 if there weren't any errors, in case of errors returns 0.
 */
int closeBinaryInputFile(ifstream& input, const char* filename);

#endif