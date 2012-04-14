/*
 * main.cpp
 *
 *  Created on: Apr 12, 2012
 *      Author: Artemy Margaritov
 */

#include "cache.h"
#include <fstream>

#define NUMWAYS 6
#define NUMSIZE 11
using namespace std;

int main ( int argc, char** argv)
{
    if ( argc != 3)
    {
        cout << "Error: not enough arguments. You should use: command [INPUT FILE] [OUTPUTFILE]." << endl;
        return -1;
    }
	ofstream output_file(  argv[2]);

	uint ways[NUMWAYS] = { 1, 2, 4, 8, 16, full};
	uint size[NUMSIZE] = { 1024,  2048,  4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576};

	for ( int i = 0; i < NUMWAYS; i++)
	{
		for ( int j = 0; j < NUMSIZE; j++)
		{
			output_file << calcMissRate( size[j], ways[i], 4, 32, argv[1]) << ", ";
		}
		output_file << endl;
	}
	output_file.close();
return 0;
}
