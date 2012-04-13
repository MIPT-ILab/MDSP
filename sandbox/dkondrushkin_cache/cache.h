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
   

public:

    Cache( unsigned int size, unsigned int ways,
           unsigned int block_size, 
           unsigned int addr_size_in_bit);

    void processRead( unsigned int addr);
    double getMissRate() const;
};


//=================================================================
//                 Implementation of Cache class
//=================================================================

Cache :: Cache( unsigned int size, unsigned int ways,
           unsigned int block_size, 
           unsigned int addr_size_in_bit)
{
    hostUInt32 prog_length;


}