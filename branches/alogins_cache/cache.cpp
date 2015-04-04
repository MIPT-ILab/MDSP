/**
 * @file:chache.cpp 
 * Implementation of caches
 */
 /*
  * Copyright Alvis Logins
  * 2012 MIPT MDSP project
  */
  
#include <iostream>
#include "cache.h"
#include <stdlib.h>
#include <fstream>

using namespace std;
  
Cache :: Cache( unsigned int size, unsigned int ways,
           unsigned int block_size, 
           unsigned int addr_size_in_bit)
{
	unsigned int i,j;
	
	c_size = size;
	c_ways = ways;
	c_block_size = block_size;
	if (addr_size_in_bit > 32)
	{
		cout << "Error! Adresses are too big. They can't be longer than 32 bit (unsigned int)." << endl;
	}
	c_addr_size_in_bit = addr_size_in_bit;
	cout << "Creating cache: ( size " << size << "b; ways " << ways << ")" << endl;
	//ind - index (number of lines)
	ind = (unsigned int) ((c_size / c_block_size) / c_ways);
	//cout << "Number of lines: " << ind << endl;
	/* creating table of cache. Each line consist of ways + 1 c_line, where
	 * in "tag" the current roundRobin cursor is placed.
	 * Every way is c_line type
	 */
	cache = new c_line * [ind];
	for (i=0; i<ind; i++)
	{
		cache[i] = new c_line[ways+1];
		for ( j = 0; j < ways; j++)
		    cache[ i][ j].v =0;
		cache[ i][ways].tag = 0;
	}
	
	/* Index mask is created depanded on number of ways of size
	 * Length of the mask must fit the number of lines
	 * if do not fit exactly - write error (wrond size of cache)
	 * So, size of the cache MUST be the power of 2.
	 */
	
	i = 0;
	j = 1;
	while (j != ind)
	{
		j = j*2;
		i = i+1;
	}
	if ((j > ind) && (j != 2))
	{
		cout << "Error! The size of cache, adress and number of ways do not match." << endl;
		exit(1);
	}
	//now i = length in bites of cache index in address
	index_mask = j-1;
	//get offset mask: number of words in data. MUST BE the power of 2;
	i = 0;
	j = 1;
	while ((j != c_block_size) && (j < c_block_size))
	{
		j = j*2;
		i = i+1;
	}
	if (j > c_block_size)
	{
		cout << "Error! The length of data block must be the power of 2." << endl;
		exit(1);
	}
	offset_mask = j-1;
	offset_mask_length = i;
	//place bites on the left (on the length of offset)
	index_mask = index_mask<<offset_mask_length;
	//1111 1111 1111 -> mask with 0000 1111 1111 -> 0000 1111 1111 -> invert - get result
	
	tag_mask = ~((~(0)) & (index_mask + offset_mask));
	
	//cout << "tag" << tag_mask<< "; index " << index_mask << "; offset" << offset_mask << endl;
}

void Cache :: processRead( unsigned int addr)
{
    unsigned int i, index;
    //cout << "New address: " << addr << "... \n";
    requests = requests + 1;
    //cout << "Looking for index: " << endl;
    index = ((addr & index_mask) >> offset_mask_length);
    //cout << index << endl;
    for (i=0; i< c_ways; i++)
    {
        //cout << "checking this index in array" << endl;
        //cout << cache[ index][ i].v << " " << cache[ index][ i].tag << " " << ( addr & tag_mask) << endl;
        if ( ( cache[ index][ i].v == 1) && ( cache[ index][ i].tag == ( addr & tag_mask)))
        {
            //cout << "found." << endl;
            return;
        }
    }
    misses = misses + 1; 
    //cout << " NOT found. Replaced at: " << cache[ index][ c_ways].tag << endl;
    cache[ index][ cache[ index][ c_ways].tag].v = 1;
    cache[ index][ cache[ index][ c_ways].tag].tag = (addr & tag_mask); 
   
    if ( cache[ index][ c_ways].tag++ > c_ways)
        cache[ index][ c_ways].tag = 0;
    return;
}

double Cache :: getMissRate() const
{ 
    if (requests == 0)
    {
        cout << "Error! Trying to get statistics from emptiness." << endl;
        exit(1);
    }
    return (double) misses/requests;
}

int main( int argc, char **argv)
{
    if ( argc < 3)
    {
        printf( "Usage: cache <source text file> <output csv file>\n");
        return 0;
    }

    ofstream output_f ( argv[2]);
    ifstream input_f ( argv[1]);
    unsigned int address;
    Cache* cache;
    int way, size;

    output_f << "Ways, 1 KB, 2 KB, 4 KB, 8 KB, 16 KB, 32 KB, 64 KB, 128 KB, 256 KB, 516 KB, 1024 KB\n";

    for (way = 1; way <= 16; way=way*2)
    {
        output_f << way << ", ";
        for (size = 1; size <= 1024; size=size*2)
        {
        
            //size in bytes, ways, block of data, address size in bits
            cache = new Cache( size*1024, way, 4, 32);
            while ( !input_f.eof())
            {
                input_f >> hex >> address;
                cache->processRead( address);
            }
            input_f.clear();
            input_f.seekg (0,ios_base::beg);
            output_f << cache->getMissRate() << ", ";
        }    
        output_f << "\n";
    }
    //full
	output_f << "Full, ";
    for (size = 1; size <= 1024; size=size*2)
    {
    
        //ways = size in bytes / size of data block in bytes
        cache = new Cache( size*1024, size*256, 4, 32);
        while ( !input_f.eof())
        {
            input_f >> hex >> address;
            cache->processRead( address);
        }
        input_f.clear();
        input_f.seekg (0,ios_base::beg);
        output_f << cache->getMissRate() << ", ";
    }    
    output_f << "\n";
	
    
    
    input_f.close();
    output_f.close();
    cout << "Ready." << endl;
   
    return 0; 
} 
