/**
 * @file: cache.cpp
 * Cache study exercise
 * @author Orlov Vasiliy
 * Copyright 2012 MDSP team
 */

#include "cache.h"

using namespace std;

Cache::Cache( unsigned int s, unsigned int w, unsigned int b, unsigned int a)
{
    unsigned int i, j;

    /* Calculation cache parametrs */
    if ( w == 0) ways = w = s / b; // full assotiation
    size = s;
    ways = w;
    block_size = b;
    set_number = s / b / w;
    miss_number = 0;
    request_number = 0;

    /* Creating our cache */
    cache = new unsigned int*[set_number];
    for ( i = 0;  i < set_number; i++)
        cache[i] = new unsigned int[ways];
    cache_bits = new unsigned char*[set_number];
    for ( i = 0;  i < set_number; i++)
        cache_bits[i] = new unsigned char[ways];

    /* Initialisation control bits */
    for ( i = 0; i < set_number; i++)
	{
        for ( j = 0; j < ways; j++)
		{
            if ( j == 0) cache_bits[i][j] = 2;
               else cache_bits[i][j] = 0;
		}
	}
}

void Cache::processRead( unsigned int addr)
{
    unsigned int set, tag, i, hit = 0;
	
    ++request_number;

    /* Decode adress */
	addr = addr / block_size; // deleting byte offset from adress
    set = addr % set_number; // getting set
    tag = addr / set_number; // getting tag

    /* Search data in cache */
    for ( i = 0; i < ways; ++i)
	    if ( ( tag == cache[set][i]) && ( ( cache_bits[set][i] % 2) == 1))
        {
		    hit = 1; // indicator cache hit
			break;
        }

    /* Processing miss */
    if ( hit ==0)
    {
        ++miss_number;
	    for ( i = 0; i < ways; ++i)
			if ( ( ( cache_bits[set][i] / 2) % 2) == 1)
	        {
                cache[set][i] = tag;
                cache_bits[set][i] = 1;
				if ( i == ( ways - 1)) cache_bits[set][0] += 2;
				     else  cache_bits[set][i+1] += 2;
                break;
	        }

    }

}

double Cache::getMissRate() const
{
    return ( double) miss_number / ( double) request_number;
}


