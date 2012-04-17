/**
 * cache.cpp
 * @author Igor Smirnov
 * Copyright 2011 MDSP team
 */

#ifndef CACHE_H_INCLUDED
#define CACHE_H_INCLUDED

struct Way
{
    Way();
    bool valid;
    unsigned int tag;
    unsigned int data;  //not used in this simulation
};

struct Set
{
    Set();
    struct Way* way;
    unsigned int block_to_replace; //For replacing we will use Round Robin algorithm
};


/**
 * Cache is a class constructor that allows to customize almost all cache parameters:
 * size is a number of data bytes that can be stored in the cache,
 * i.e. if the block size is 16 Bytes then the number of data blocks in the cache is size/16.
 * ways is a number of associative ways in a set, i.e. how many blocks are referred by the same index.
 * block_size is a number of Bytes in a data block.
 * addr_size_in_bit is a number of bits in address.
*/
class Cache
{
    unsigned int c_size;
    unsigned int c_ways;
    unsigned int c_block_size;
    unsigned int c_addr_size_in_bit;

    unsigned int c_num_of_data_block;
    unsigned int c_byte_offset_in_bit;
    unsigned int c_num_of_sets;
    unsigned int c_set_size_in_bit;

    unsigned int c_tag_mask;
    unsigned int c_index_mask;

    struct Set* cache;

    unsigned int c_requests;
    unsigned int c_misses;
    unsigned int c_hits;

public:
    Cache( unsigned int size, unsigned int ways,
           unsigned int block_size,
           unsigned int addr_size_in_bit);
   ~Cache();

    void processRead( unsigned int addr);
    double getMissRate() const;
    double Cache::getHitRate() const;
};

void cacheInfoPrint( unsigned int size, unsigned int ways);

double cacheStart( unsigned int size, unsigned int ways,
                   unsigned int block_size,
                   unsigned int addr_size_in_bit, char* input);

#endif // CACHE_H_INCLUDED
