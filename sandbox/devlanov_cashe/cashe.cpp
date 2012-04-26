/** @file cashe.cpp
 * An educational simulator cashe
 * @author Denis Evlanov
 * Copyright 2011 MDSP team
 * Created on: 19.04.2012 22:00
 */


#include "cashe.h"

using namespace std;

Cashe::Cashe( unsigned int sizeParam, unsigned int waysParam, unsigned int blockSizeParam, unsigned int addrSizeInBitParam)
{	
	size = sizeParam;
    ways = waysParam;
    block_size = blockSizeParam; //usually block_size = 4 byte
    addr_size_in_bit = addrSizeInBitParam; //usually addr_size_in_bit = 32
    miss_ratio_priv = 0;
    hit_ratio_priv = 0;
    number_all_request_priv = 0;
    mask_tag = 0;
    mask_index = 0;
    block_offset = log2( block_size);
   
    if ( ways != 0)
    {
    	number_sets_priv = size / ways / block_size;
    } else
    {
    	number_sets_priv = 1;
    	ways = size / block_size;
    }
    
    bit_in_cashe_index = log2 (number_sets_priv);
    
    cash_array = new StructItem** [ number_sets_priv];
	
	for ( long int l = 0; l < number_sets_priv; l++)
    {
    	cash_array[ l] = new StructItem* [ ways];
    	for (long int y = 0; y < ways; y++)
    	{
    		( cash_array[ l])[ y] = new StructItem;
    		( ( cash_array[l])[ y])->valid = 0;
    		( ( cash_array[l])[ y])->activ_address = 0;
    	}
    }
    
    for ( int j = 0; j < ( addr_size_in_bit - bit_in_cashe_index - block_offset); j++)
    {
    	mask_tag   = 1 | ( mask_tag << 1);
    }
    for ( int m = 0; m <  bit_in_cashe_index; m++)
    {
    	mask_index = 1 | ( mask_index << 1);
    }
    round_robin_index = 0;
}

Cashe::~Cashe()
{
	for ( long int l = 0; l < number_sets_priv; l++)
    {
    	for (long int y = 0; y < ways; y++)
    	{
    		delete ( ( cash_array[ l])[ y]);
    	}
    	delete [] (cash_array[ l]) ;
    }
    delete [] cash_array;
}

void Cashe::processRead( unsigned int addr)
{
	number_all_request_priv++;
	addr = addr >> block_offset;
	long int index = addr & mask_index;
	addr = addr >> bit_in_cashe_index;
	long int tag   = addr & mask_tag; 
	
	for (int k = 0; k < ways; k++)
	{
		if ( ( ( ( cash_array[ index])[ k])->activ_address == tag) && ( ( ( cash_array[ index])[ k])->valid == true))
		{
			hit_ratio_priv++;
			goto end_processRead;
		}
	}
	
	( ( cash_array[ index])[round_robin_index])->activ_address = tag;
	( ( cash_array[ index])[round_robin_index])->valid = true;
	if ( round_robin_index == ways - 1)
	{
		round_robin_index = 0;
	} else
	{
		round_robin_index++;
	}

	miss_ratio_priv++;
	end_processRead:
	return;	
}

double Cashe::getMissRate()
{
	return 1.0 * miss_ratio_priv / number_all_request_priv;
}
