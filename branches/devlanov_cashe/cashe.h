#ifndef CASHE_H
#define CASHE_H

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <fstream> 

struct StructItem
{
	long int activ_address;
	bool valid;
};


class Cashe
{
private:
	unsigned int size;
    unsigned int ways;
    unsigned int block_size;
    unsigned int addr_size_in_bit;
    unsigned int mask_tag;
    long int mask_index;
    long double miss_ratio_priv;
    long double hit_ratio_priv;
    long double number_all_request_priv;
    unsigned int number_sets_priv;
    unsigned int bit_in_cashe_index; 
    StructItem*** cash_array;
    long int round_robin_index;
    unsigned int block_offset;
    
public:
	Cashe( unsigned int sizeParam, unsigned int waysParam, unsigned int blockSizeParam, unsigned int addrSizeInBitParam);
    ~Cashe();
    void processRead( unsigned int addr);
    double getMissRate();
};
#endif
