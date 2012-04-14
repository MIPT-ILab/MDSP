//============================================================================
// Name        : cashe.cpp
// Author      : Artemy Margaritov
// Version     :
// Copyright   : MDSP
// Description : Emulator of caches
//============================================================================

#include <iostream>
#include <fstream>
#include <cmath>
#include "cache.h"
using namespace std;

Cache::Cache( unsigned int size,
			  unsigned int ways,
			  unsigned int block_size,
			  unsigned int addr_size_in_bit)
{
	miss_number_ = 0;
	request_number_ = 0;
	if ( ways == full)
	{
		ways_ = size / block_size;
		set_addr_in_bit_ = 0;
		sets_ = 1;
	} else
	{
		ways_ = ways;
		set_addr_in_bit_ = (uint)log2( size / ( block_size * ways));
		sets_ = 1 << set_addr_in_bit_;
	}
	block_size_in_bit_ = (uint)log2( block_size);
	tag_in_bit_ = addr_size_in_bit - set_addr_in_bit_ - block_size_in_bit_;

	mask_index_ =  ( 1 << set_addr_in_bit_) - 1;
	mask_tag_   =  ( 1 << tag_in_bit_) - 1;

	cache_.resize( sets_, Set( ways_));
}

void Cache::processRead( unsigned int addr)
{
	request_number_++;
	uint index =  getIndex( addr);
	uint tag   =  getTag( addr);

	for ( uint i = 0; i < ways_; i++)
	{
		/* Finding address in cache.*/
		if ( ( cache_[index].blocks_[i].valid_) && ( cache_[index].blocks_[i].tag_ == tag)) return; // hit
	}
	miss_number_++;
	for ( uint i = 0; i < ways_; i++)
	{
		/* If cache has no-valid blocks for target index, new one will be written to this place.*/
		if ( !cache_[index].blocks_[i].valid_)
		{
			cache_[index].blocks_[i].tag_ = tag;
			cache_[index].blocks_[i].valid_ = 1;
			return;
		}
	}
	/* If there are not free places for target index, replacing will be used.
	 * It is implementation of round-robin (RR) policy of replacing.*/
	cache_[index].blocks_[cache_[index].replaceable_++].tag_ = tag;
	if ( cache_[index].replaceable_ ==  ways_) cache_[index].replaceable_ = 0;
}

double Cache::getMissRate() const
{
    return ( double) miss_number_ / ( double) request_number_;
}

uint Cache::getIndex( uint addr)
{
		return addr >> block_size_in_bit_ & mask_index_;
}

uint Cache::getTag( uint addr)
{
	return addr >> ( block_size_in_bit_ + set_addr_in_bit_) & mask_tag_;
}


Set::Set( uint ways)
{
	blocks_.resize( ways, Block());
	replaceable_ = 0;
}


Block::Block()
{
	tag_   = 0;
	valid_ = 0;
}


double calcMissRate ( uint size, uint ways, uint block_size, uint addr_len, char* file_name)
{
	Cache* cache = new Cache( size, ways, block_size, addr_len);
	cout << "Size: " << size << ", ways: " << ways << " ..." ;//<< endl;
	ifstream in( file_name);
	uint addr;
	while ( !in.eof())
	{
		in >> hex >> addr;
		cache->processRead( addr);
	}
	in.close();
	delete cache;
	cout << " Done." << endl;
	return cache->getMissRate();
}
