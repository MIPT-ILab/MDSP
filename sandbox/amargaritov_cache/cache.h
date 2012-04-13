/*
 * cache.h
 *
 *  Created on: Apr 12, 2012
 *      Author: Artemy Margaritov
 */

#ifndef CACHE_H_
#define CACHE_H_

#include <vector>

using namespace std;
typedef unsigned int uint;

struct Block;

double calcMissRate ( uint size, uint ways, uint block_size, uint addr_len, char* name);

class Cache
{
	uint ways_;
	uint block_size_;
	uint set_number_;
	uint miss_number_;
	uint request_number_;

	vector<vector<Block> > cache_;
	vector<uint> replaceable_;

public:
    Cache( unsigned int size, unsigned int ways,
           unsigned int block_size,
           unsigned int addr_size_in_bit);

    void processRead( unsigned int addr);
    double getMissRate() const;
};

struct Block
{
	Block();
	uint addr_;
	bool valid_;
};

#endif /* CACHE_H_ */
