/**
 * realisation of simple patamatrized programm cache model 
 * for research how miss rate depends on cache size and associativity
 * @author Dennis Kondrushkin
 * Copyright 2012 MDSP team
 */
#include "types.h"
using namespace std;

class Cache
{
    hostUInt32 cache_length; // store number of indexes in cache

    hostUInt32 index_length; // store length of index field in address
    hostUInt32 index_field; // store bit mask "11...1" , which length is length of index field

    hostUInt32 block_length; // store length of block field (offset) in address

    hostUInt32 ways_number; // store number of ways in cache

    hostUInt32 miss;
    hostUInt32 request;

    struct Way  // struct for storing all data with same index in cache
    {
        hostUInt32* set; 
        hostUInt8* valid; // store valid flags
        hostUInt32 next_out_id; // needed for round-robin        
    };

    Way* cache_massive; // main massive for storing data addresses, which are in sscache 

public:

    Cache( unsigned int size, unsigned int ways,
           unsigned int block_size, 
           unsigned int addr_size_in_bit);
    ~Cache();

    void processRead( unsigned int addr);
    double getMissRate() const;
};


//=================================================================
//                 Implementation of Cache class
//=================================================================


// initializing and count all class datamembers
Cache :: Cache( unsigned int size, unsigned int ways,
                unsigned int block_size, 
                unsigned int addr_size_in_bit)
{
    hostUInt32 val;
    hostUInt32 i, j;

    // getting number of indexes
    cache_length = size / ( ways * block_size);

    // getting log2( number of indexes) = bits in index infield
    index_length = 0; 
    val = cache_length - 1;
    while ( val != 0)
    {
        index_length++;
        val = val >> 1;
    }

    // making mask 11...1 for index field
    index_field = 0;
    for ( i = 0; i < index_length; i++)
    {
        index_field = index_field << 1;
        index_field++;
    }   

    // getting log2( number of block_size) = offset field length in bits
    block_length = 0;
    val = block_size - 1;
    while ( val != 0)
    {
        block_length++;
        val = val >> 1;
    }
 
    // creating cache as a dynamic two-dymensional massive
    cache_massive = new Way[cache_length];
    for ( i = 0; i < cache_length; i++)
    {
        cache_massive[i].next_out_id = 0; // number of the block where first data will be saved
        cache_massive[i].set = new hostUInt32 [ways]; 
        cache_massive[i].valid = new hostUInt8 [ways];
        for ( j = 0; j < ways; j++) // making cache clean
        {
            cache_massive[i].set[j] = 0;
            cache_massive[i].valid[j] = 0;
        }
    }

    ways_number = ways;
    miss = 0;
    request = 0;
}


Cache :: ~Cache()
{
    hostUInt32 i;

    for ( i = 0; i < cache_length; i++)
    {
        delete[] cache_massive[i].set;
        delete[] cache_massive[i].valid;
    }
    delete[] cache_massive;
}


void Cache :: processRead( unsigned int addr)
{
    hostUInt32 index, tag;
    hostUInt32 miss_flag;
    hostUInt32 i;

    // getting index and tag
    index = addr >> block_length;
    tag = index >> index_length;
    index = index & index_field;
    
    miss_flag = 1;
    for ( i = 0; i < ways_number; i++)
    {
        if ( ( cache_massive[index].set[i] == tag)
             && ( cache_massive[index].valid[i] == 1))
        {
            miss_flag = 0;
            break;
        }
    }

    // put absent data in the cache, set valit flag and chainging round-robin number
    if ( miss_flag == 1)
    {
        miss++;
        cache_massive[index].set[cache_massive[index].next_out_id] = tag;
        cache_massive[index].valid[cache_massive[index].next_out_id] = 1;
        cache_massive[index].next_out_id++;
        cache_massive[index].next_out_id = cache_massive[index].next_out_id & ( ways_number - 1);
    } 
    request++;
}


double Cache :: getMissRate() const
{
    if ( request == 0)
    {
        cout << "\n Can't show miss rate: no one request has been done.";
            return -1;
    } else
    {
        return ( ( double)miss) / ( ( double)request);
    }
}