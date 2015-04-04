/**
 * @file: miss_rate_study.cpp
 * Cache study exercise
 * @author Orlov Vasiliy
 * Copyright 2012 MDSP team
 */

#include "cache.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    unsigned int addr;
    int i;

    cout << "Cache Simulator has started. Please wait...\n";

    /* Initialization cache objects*/
    int number = 66; // number of caches examined
    Cache o[66] = 
    {
        Cache( 1024, 1, 4, 32), Cache( 2048, 1, 4, 32), Cache( 4096, 1, 4, 32), Cache( 8192, 1, 4, 32), Cache( 16384, 1, 4, 32), 
        Cache( 32768, 1, 4, 32), Cache( 65536, 1, 4, 32), Cache( 131072, 1, 4, 32), Cache( 262144, 1, 4, 32), 
        Cache( 524288, 1, 4, 32), Cache( 1048576, 1, 4, 32), 

        Cache( 1024, 2, 4, 32), Cache( 2048, 2, 4, 32), Cache( 4096, 2, 4, 32), Cache( 8192, 2, 4, 32), Cache( 16384, 2, 4, 32), 
        Cache( 32768, 2, 4, 32), Cache( 65536, 2, 4, 32), Cache( 131072, 2, 4, 32), Cache( 262144, 2, 4, 32), 
        Cache( 524288, 2, 4, 32), Cache( 1048576, 2, 4, 32), 

        Cache( 1024, 4, 4, 32), Cache( 2048, 4, 4, 32), Cache( 4096, 4, 4, 32), Cache( 8192, 4, 4, 32), Cache( 16384, 4, 4, 32), 
        Cache( 32768, 4, 4, 32), Cache( 65536, 4, 4, 32), Cache( 131072, 4, 4, 32), Cache( 262144, 4, 4, 32), 
        Cache( 524288, 4, 4, 32), Cache( 1048576, 4, 4, 32), 

        Cache( 1024, 8, 4, 32), Cache( 2048, 8, 4, 32), Cache( 4096, 8, 4, 32), Cache( 8192, 8, 4, 32), Cache( 16384, 8, 4, 32), 
        Cache( 32768, 8, 4, 32), Cache( 65536, 8, 4, 32), Cache( 131072, 8, 4, 32), Cache( 262144, 8, 4, 32), 
        Cache( 524288, 8, 4, 32), Cache( 1048576, 8, 4, 32), 

        Cache( 1024, 16, 4, 32), Cache( 2048, 16, 4, 32), Cache( 4096, 16, 4, 32), Cache( 8192, 16, 4, 32), Cache( 16384, 16, 4, 32), 
        Cache( 32768, 16, 4, 32), Cache( 65536, 16, 4, 32), Cache( 131072, 16, 4, 32), Cache( 262144, 16, 4, 32), 
        Cache( 524288, 16, 4, 32), Cache( 1048576, 16, 4, 32), 

        Cache( 1024, 256, 4, 32), Cache( 2048, 512, 4, 32), Cache( 4096, 1024, 4, 32), Cache( 8192, 2048, 4, 32), Cache( 16384, 4096, 4, 32), 
        Cache( 32768, 8192, 4, 32), Cache( 65536, 16384, 4, 32), Cache( 131072, 32768, 4, 32), Cache( 262144, 65536, 4, 32), 
        Cache( 524288, 131072, 4, 32), Cache( 1048576, 262144, 4, 32)

	};

    /* Simulate cache work*/ 
    ifstream fin( argv[1]);
    while( !fin.eof())
    {
        fin >> hex >> addr;
        for ( i = 0; i < number; ++i)
           o[i].processRead( addr); // reading current instruction by each cache
    }
    fin.close();

    /* Getting CSV output file*/
    ofstream fout( argv[2]);
	fout.precision(6); // set output format to 6 digits after point
	fout.setf( ios::fixed);
    for ( i = 0; i < number; ++i)
	{
        fout << o[i].getMissRate(); // get missrate of each cache
        
		/* Insertion separators */
        if ( ( ( i + 1) % 11) == 0) 
        {
            fout << '\n';
        } else 
		{ 
            fout << ',' << ' ';
        }

	}
    fout.close();

    cout << "Cache Simulator successfully finished." << endl;

    return 0;
}
