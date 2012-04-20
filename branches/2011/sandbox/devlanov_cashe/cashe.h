#ifndef CASHE_H
#define CASHE_H

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cmath>

struct StructItem
{
	long int cash_index;
	long int activ_address;
	bool there_is;
	int number_change_activ_addr; // 0 < number_change_activ_addr < ways
};


class Cashe
{
private:
	unsigned int size;
    unsigned int ways;
    unsigned int block_size;
    unsigned int addr_size_in_bit;
    unsigned int miss_ratio_priv;
    unsigned int hit_ratio_priv;
    unsigned int number_all_request_priv;
    unsigned int number_sets_priv;
    unsigned int bit_in_cashe_index; 
    StructItem** cash_array;
    long int mask;
    //int number_change_activ_addr; // 0 < number_change_activ_addr < ways
    

public:
	Cashe( unsigned int sizeParam, unsigned int waysParam, unsigned int blockSizeParam, unsigned int addrSizeInBitParam);
    
    void processRead( unsigned int addr);
    double getMissRate();
};
#endif
