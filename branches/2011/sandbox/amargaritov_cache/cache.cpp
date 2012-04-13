//============================================================================
// Name        : cashe.cpp
// Author      : Artemy Margaritov
// Version     :
// Copyright   : MDSP
// Description : Emulator of caches
//============================================================================

#include <iostream>
#include <fstream>
#include "cache.h"
using namespace std;

Cache::Cache( unsigned int size,
			  unsigned int ways,
			  unsigned int block_size,
			  unsigned int addr_size_in_bit)
{
	miss_number_ = 0;
	request_number_ = 0;
	if ( ways == 0)
	{
		ways_ = size / block_size;
		set_number_ = 1;
	} else
	{
		ways_ = ways;
		set_number_= size / block_size / ways;
	}
	block_size_ = block_size;
	cache_.resize( ways_);
	for ( uint i = 0; i < ways_; i++)
	{
		cache_[i].resize ( set_number_, Block());
	}
	replaceable_.resize ( set_number_, 0);
}

void Cache::processRead( unsigned int addr)
{
	request_number_++;
	addr /= block_size_;
	uint index = addr % set_number_;
	for ( uint i = 0; i < ways_; i++)
	{
		if ( ( cache_[i][index].valid_) && ( cache_[i][index].addr_ == addr)) return;
	}
	miss_number_++;
	for ( uint i = 0; i < ways_; i++)
	{
		if ( !cache_[i][index].valid_)
		{
			cache_[i][index].addr_ = addr;
			cache_[i][index].valid_ = 1;
			return;
		}
	}
	cache_[replaceable_[index]++][index].addr_ = addr;
	replaceable_[index] %=  ways_;
}

double Cache::getMissRate() const
{
    return ( double) miss_number_ / ( double) request_number_;
}

Block::Block()
{
	addr_  = 0;
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
