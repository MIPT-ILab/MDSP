/** @file cashe.cpp
 * An educational simulator cashe
 * @author Denis Evlanov
 * Copyright 2011 MDSP team
 * Created on: 19.04.2012 22:00
 */


#include "cashe.h"

using namespace std;

Cashe::Cache( unsigned int sizeParam, unsigned int waysParam, 
              unsigned int blockSizeParam, unsigned int addrSizeInBitParam)
{
	size = sizeParam;
    ways = waysParam;
    block_size = blockSizeParam; //usually block_size = 4 byte
    addr_size_in_bit = addrSizeInBitParam; //usually addr_size_in_bit = 32
    miss_ratio_priv = 0;
    number_all_request_priv = 0;
    number_sets_priv = 1024 * size / ways / ( block_size + addrSizeInBit / 8);
    bit_in_cashe_index = log2 number_sets_priv;
    cash_array = new long int[ 2 ^ ( 1024 * size / ( block_size + addrSizeInBit / 8)];
    mask = 0;
    for ( int j = 0; j < ( addr_size_in_bit - bit_in_cashe_index); j++)
    {
    	mask = 1 | ( mask << 1);
    }
    
    mask = mask << bit_in_cashe_index;
    mask = ~mask;
    
    for ( long int i = 0; i < bit_in_cashe_index; i++)
    {
       	cash_array[i] = i & mask;
	}
}

void processRead( unsigned int addr)
{
	number_all_request_priv++;
	long int i = 0;
	while ( ( addr & mask) > cash_array[i] )
	{
		i++;
	
	
}
    
