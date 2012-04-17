/**
 * cache.cpp
 * @author Igor Smirnov
 * Copyright 2011 MDSP team
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include "cache.h"

using namespace std;


/**
 *           |31 30 ...............11 10|9 8 ........3 2|1         0|
 * Address:  |   Physical address tag   |  Cache index  |Byte offset|
 *
*/

Set::Set()
{
    block_to_replace = 0;
}


Way::Way()
{
    valid = false;
      tag = 0;
     data = 0;
}


Cache::Cache( unsigned int size, unsigned int ways,
              unsigned int block_size,
              unsigned int addr_size_in_bit)
{
    c_size = size;
    c_ways = ways;
    c_block_size = block_size;
    c_addr_size_in_bit = addr_size_in_bit;

    c_num_of_data_block  = (unsigned int)( (double)c_size / (double)c_block_size);
    c_byte_offset_in_bit = (unsigned int) log2( c_block_size);
    if ( ways == 0)
    {
        c_num_of_sets = 1;
        c_ways = c_num_of_data_block;
    } else
    {
        c_num_of_sets = c_num_of_data_block / c_ways;
    }
    c_set_size_in_bit = (unsigned int) log2( c_num_of_sets);

    c_tag_mask   = ( 1 << ( c_addr_size_in_bit - c_set_size_in_bit - c_byte_offset_in_bit)) - 1;
    c_index_mask = ( 1 << c_set_size_in_bit) - 1;

    cache = new struct Set[c_num_of_sets];
    for ( unsigned int i = 0; i < c_num_of_sets; i++)
    {
        cache[i].way = new struct Way[c_ways];
    }

    c_requests = 0;
    c_misses = 0;
    c_hits = 0;
};


Cache::~Cache()
{
    for ( unsigned int i = 0; i < c_num_of_sets; i++)
    {
        delete cache[i].way;
    }
    delete cache;
}



void cacheInfoPrint(unsigned int size, unsigned int ways)
{
    if (ways == 0)
    {
        cout << "Fully associative cache\n";
    }
    else if (ways > 1)
    {
        cout << ways << "-way set-associative cache\n";
    }
    else if (ways == 1)
    {
        cout << "Direct mapped cache\n";
    }
    cout << "cache size = " << size << " B";
}


void Cache::processRead( unsigned int addr)
{
    c_requests++;

    unsigned int index = ( addr >> c_byte_offset_in_bit) & c_index_mask;
    unsigned int tag   = ( addr >> ( c_byte_offset_in_bit + c_set_size_in_bit)) & c_tag_mask;

    for ( int i = 0; i < c_ways; i++)
    {
        if ( ( cache[index].way[i].tag == tag) && ( cache[index].way[i].valid != 0))
        {
            c_hits++;
            return;
        }
    }

    // still in function -> miss -> add new data instead of old;
    unsigned int replace = cache[index].block_to_replace;
    cache[index].way[replace].tag   = tag;
    cache[index].way[replace].valid = true;

    //Round Robin algorithm for data replacement
    cache[index].block_to_replace++;
    if ( cache[index].block_to_replace == c_ways)
         cache[index].block_to_replace = 0;

    c_misses++;
}


double Cache::getMissRate() const
{
    double miss_rate = (double)c_misses / (double)c_requests;
    cout << "\n" << " Miss rate = " << miss_rate;
    cout << "\n" << "  Hit rate = " << 1 - miss_rate << "\n";
    cout << "/-------------------
    -------\\" << "\n";

    return miss_rate;
}


double cacheStart( unsigned int size, unsigned int ways,
                   unsigned int block_size,
                   unsigned int addr_size_in_bit, char* input)
{
        cacheInfoPrint( size, ways);

        Cache* simulation = new Cache( size, ways, block_size, addr_size_in_bit);

        ifstream in_file( input);
        unsigned int address;
        while ( !in_file.eof())
        {
                in_file >> hex >> address;
                simulation->processRead( address);
        }
        in_file.close();

        double miss_rate = simulation->getMissRate();

        delete simulation;
        return miss_rate;
}
