/*
 * main.cpp
 *
 *  Created on: Apr 18, 2012
 *      Author: art
 */

/**
 * Simple example of using cache performance.
 * Calculating average time to get data by address trace from file.
 */

#include <iostream>
#include <fstream>

#include "cache.h"
#include "replacement.h"

#define NUMWAYS 6
#define NUMSIZE 11

template <class Cache1, class Cache2>
uint cache2Latency( uint addr, Cache1* cache_L1, Cache2* cache_L2);

using namespace std;

int main ( int argc, char** argv)
{
	if ( argc != 2)
	{
		cerr << "Error: bad value of arguments. You should use: command [INPUT FILE]."
			 << endl;
	    return -1;
	}
/*
	uint ways[NUMWAYS] = { 1, 2, 4, 8, 16, full};
	uint size[NUMSIZE] = { 1024,  2048,  4096, 8192, 16384,
						   32768, 65536, 131072, 262144, 524288, 1048576};
*/
	//----------------------type------size--ways--blocksize--addrlen--hittime--misstime--limit_age
	CacheLRU* cacheL1 = new CacheLRU (  s4K,    4,         4,      32,       1,       0,     1024);
	CacheRR* cacheL2  = new CacheRR  ( s64K,  full,        4,      32,       5,      200);

	uint addr;
	uint count = 0;
	unsigned long time = 0;

	ifstream in( argv[1]);
	while ( !in.eof())
	{
		in >> hex >> addr;
		time += cache2Latency< CacheLRU, CacheRR>( addr,  cacheL1, cacheL2);
		count++;
	}
	delete cacheL1;
	delete cacheL2;

	/* Return average time of getting data for 2-levels cache. */
	if ( count) cout << (double) time / (double) count << endl;

//==================================================================================================
	//---------------type----size--ways--blocksize--addrlen--hittime--misstime--limit_age
	CacheRR* cache = new CacheRR ( s128K, full,         4,      32,       8,        200);
	in.clear();
	in.seekg(0);
	uint curtime;
	time = 0; count = 0;
	while ( !in.eof())
	{
		in >> hex >> addr;
		cache->getTimeLatency( addr, curtime);
		time += curtime;
		count++;
	}
	in.close();
	delete cache;

	/* Return average time of getting data for 1-level cache. */
	if ( count) cout << (double) time / (double) count << endl;
	return 0;
}

template <class Cache1, class Cache2>
uint cache2Latency( uint addr, Cache1* cache_L1, Cache2* cache_L2)
{
	uint time_L1, time_L2;
	if ( cache_L1->getTimeLatency ( addr, time_L1)) return time_L1;
	cache_L2->getTimeLatency ( addr, time_L2);
	return time_L1 + time_L2;
}
