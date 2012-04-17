/**
 * cache.cpp
 * @author Igor Smirnov
 * Copyright 2011 MDSP team
 */

#include <iostream>
#include <fstream>
#include "cache.h"

#define FULL 0
#define WAYS 6
#define SIZE 11

using namespace std;


int main (int argc, char** argv)
{
    if (argc != 3)
    {
        cout << "Main: Wrong number of arguments. You should write input and output file\n";
        return -1;
    }

    unsigned int cache_ways[WAYS] = {1, 2, 4, 8, 16, FULL};
    unsigned int cache_size[SIZE] = {1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576};

    ofstream output(argv[2]);

    for (int i = 0; i < WAYS; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            output << cacheStart(cache_size[j], cache_ways[i], 4, 32, argv[1]) << ", ";
        }
        output << "\n";
    }

    output.close();
    return 0;
}
