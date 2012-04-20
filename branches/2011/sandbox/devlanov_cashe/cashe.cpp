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
    //number_change_activ_addr = 0;
    number_sets_priv = 1024 * size / ways / ( block_size + addr_size_in_bit / 8);
    bit_in_cashe_index = log2 (number_sets_priv);
    //cout << "bit_in_cashe_index = " << bit_in_cashe_index << endl;
    //2 ^ ( 1024 * size / ( block_size + addr_size_in_bit / 8)
    cash_array = new StructItem* [ 1024 * size / ( block_size + addr_size_in_bit / 8)];
	   
    for ( long int l = 0; l < number_sets_priv * ways; l++)
    {
    	cash_array[l] = new StructItem;	
    }
    mask = 0;//cout << "xasxaxasx" << endl;
    for ( int j = 0; j < ( addr_size_in_bit - bit_in_cashe_index); j++)
    {
    	mask = 1 | ( mask << 1);
    }
    //cout << "xasxaxasx" << endl;
    mask = mask << bit_in_cashe_index;
    cout << "MASK = " << mask << endl;
    mask = ~mask;
    //mask = ~mask;
    //cout << "MASK = " << mask << endl;
    cout << "number_sets_priv = " << number_sets_priv << endl;
    //cout << "( cash_array[ i + k])->cash_index = " << ( cash_array[ 0])->cash_index << endl;
    long int i = 0;
    
    while ( i != number_sets_priv * ways)
    {
       	cout << "i = " << i << " ";
       	long int k = 0;
       	for ( k = 0; k < ways; k++)
       	{
       		( cash_array[ i + k])->cash_index = i & mask;////cout << "helohelo" << endl;
       		( cash_array[ i + k])->activ_address = 0;
       		( cash_array[ i + k])->there_is = false;
       		( cash_array[ i + k])->number_change_activ_addr = 0;cout << "k = " << k << " ";
		}
		cout << "number_sets_priv * ways = " << number_sets_priv * ways << endl;
		cout << endl;
		i = i + ways;
		
	}
	cout << "helohelo" << endl;
}

void Cashe::processRead( unsigned int addr)
{
	number_all_request_priv++;
	long int i = 0;
	while ( ( addr & mask) != ( cash_array[i])->cash_index ) //edwefwefewf
	{
		i++;
	}

	for (int k = 0; k < ways; k++)
	{
		if ( ( ( cash_array[ i+k])->activ_address == addr & ( ~mask)) || ( ( cash_array[ i+k])->there_is == false));
		{
			( cash_array[ i+k])->activ_address = addr & ( ~mask);			
			( cash_array[ i+k])->there_is == true;
			hit_ratio_priv++;
			goto end_processRead;
		}
	}
	int add_index;
	add_index = ( ( cash_array[ i])->number_change_activ_addr);
	( cash_array[ i+add_index])->activ_address = addr & ( ~mask);
	cash_array[ i]->number_change_activ_addr++;
	miss_ratio_priv++;
end_processRead:
	return;
}

double Cashe::getMissRate()
{
	return miss_ratio_priv/number_all_request_priv;
}
