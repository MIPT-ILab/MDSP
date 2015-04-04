/**
 * @file:cache.h
 * CacheStudyExercise
 * @author:Andriy Pushkar
 * Copyright 2012 MDSP team
 */

#ifndef CacheStudyExercise_cache_h
#define CacheStudyExercise_cache_h

#include <vector>
#include <cmath>
#include <iostream> 

using namespace std;

/**
 * Class Block implements a data block. Each Block stores the value
 * and the flag of being ready to be replaced with another one for
 * the implementation of RR strategy
 */

class Block
{
private:
    bool erase_ready_priv; 
    unsigned int tag_priv;
public:
    Block();
    void setEraseReady( bool erase_ready);
    bool getEraseReady(); // true if it is this block's turn to be erased
    void setValue( unsigned int addr);
    unsigned int getValue();
};

/** 
 * Class Set implements the idea of associativity - each Set stored in 
 * Cache can contain more than one block of data
 */

class Set
{
private:
    vector < Block > body;
public:
    void setValue( unsigned int addr); 
    bool getValue( unsigned int addr);
    void resize( unsigned int ways);
};

/**
 *  Class Cache declaration
 */

class Cache
{
public:
    Cache( unsigned int size, unsigned int ways,
          unsigned int block_size, 
          unsigned int addr_size_in_bit);
    void processRead( unsigned int addr);
    double getMissRate() const;
    unsigned int getSize();
    unsigned int getWays();
    unsigned int getBlockSize();
    unsigned int getAddrSizeInBit();
private:
    unsigned int miss_num, hit_num;
    unsigned int size_priv, ways_priv, 
                block_size_priv, 
                addr_size_in_bit_priv;
    vector < Set > cache;
};


/*
 * Class Util provides some useful routines for address parsing
 */

class Util
{
private:
    static unsigned int size_priv, ways_priv, 
                        block_size_priv, 
                        addr_size_in_bit_priv;
public:
    static double binaryLog( double n);
    /**
     * upperPowOfTwo function returns the closest (bigger or equal) power
     * of 2
     */
    static unsigned int upperPowOfTwo( double n);
    static unsigned int getIndex( unsigned int addr);
    static unsigned int getTag( unsigned int addr);
    /**
     * This function is aimed at initializing the Util class, it's called
     * in the constructor of the Cache class to pass to the parsing utilities
     * current cache parameters
     */
    static void setCacheParameters( unsigned int size, 
                                   unsigned int ways,
                                   unsigned int block_size, 
                                   unsigned int addr_size_in_bit);
};

#endif
