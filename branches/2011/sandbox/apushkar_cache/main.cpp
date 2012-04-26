/**
 * @file:main.cpp
 * CacheStudyExercise
 * @author:Andriy Pushkar
 * Copyright 2012 MDSP team
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include "cache.h"

using namespace std;

int main (int argc, const char * argv[])
{
    if ( argc != 3)
    {
        cout << "Wrong number of command line arguments." << endl
        << "USAGE: ./cache mem_trace.txt miss_rate.csv" << endl;
        return 42;
    }
    
    const int WAYS[ 6] = { 1, 2, 4, 8, 16, 0};
    const int SIZES[ 11] = { 1024, 2048, 4096, 8192, 
                            16384, 32768, 65536, 131072, 
                            262144, 524288, 1048576};
    unsigned int addr;
    Cache * cache;
    
    ofstream fout( argv[2]);
    fout << setprecision( 6);
    
    for ( int j = 0; j < 6; j++)
    {
        for ( int i = 0; i < 11; i++)
        {
            ifstream fin( argv[1]);
            
            if (! fin.is_open())
            {
                cout << "Input file not found." << endl 
                << "USAGE: ./cache mem_trace.txt miss_rate.csv" << endl;
                return 42;
            }
            
            fin >> hex;
            
            if ( WAYS[ j] == 0)
            {
                cache = new Cache( SIZES[ i], SIZES[ i]/4, 4, 32);
                cout << "size: " << SIZES[ i] 
                    << " ways: " << SIZES[ i]/4 << endl;
            }
            else
            {
                cache = new Cache( SIZES[ i], WAYS[ j], 4, 32);
                cout << "size: " << SIZES[ i]
                    << " ways: " << WAYS[ j] << endl;
            }
            
            while ( fin >> addr) 
            {
                cache->processRead( addr);
            }
            
            fout << cache->getMissRate() << ", ";
            
            delete cache;
            
            fin.close();
        }
        fout << endl;
    }

    fout.close();
    
    return 0;
}

