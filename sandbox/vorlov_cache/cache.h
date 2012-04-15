/**
 * @file: cache.h
 * Cache study exercise
 * @author Orlov Vasiliy
 * Copyright 2012 MDSP team
 */

#ifndef CACHE_H_
#define CACHE_H_

using namespace std;

class Cache
{
    unsigned int size;
    unsigned int ways;
    unsigned int block_size;
    unsigned int set_number;
    unsigned int miss_number;
    unsigned int request_number;

    /* cache pointers (rows are sets, coloms are ways) */
    unsigned int **cache; // for 0-32 bit tag
    unsigned char **cache_bits; // for valid bit(0th) and Round-Robin bit(1st)
   
public:
	Cache( unsigned int size, unsigned int ways, 
           unsigned int block_size, unsigned int set_number);
    void processRead( unsigned int addr);
    double getMissRate() const;
};

#endif
