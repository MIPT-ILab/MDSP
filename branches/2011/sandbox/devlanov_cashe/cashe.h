#ifndef CASHE_H
#define CASHE_H

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cmath>

class Cashe
{
private:
	unsigned int size;
    unsigned int ways;
    unsigned int block_size;
    unsigned int addr_size_in_bit;
    unsigned int miss_ratio_priv;
    unsigned int number_all_request_priv;
    unsigned int number_sets_priv;
    unsigned int bit_in_cashe_index; 
    long int *cash_array;
    long int mask;
    

public:
	Cashe::Cache( unsigned int sizeParam, unsigned int waysParam, 
                  unsigned int blockSizeParam, unsigned int addrSizeInBit);
    
    void processRead( unsigned int addr);
    double getMissRate() const;
};
#endif
