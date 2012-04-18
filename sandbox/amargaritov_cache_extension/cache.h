/*
 * cache.h
 *
 *  Created on: Apr 16, 2012
 *      Author: art
 */

#ifndef CACHE_H_
#define CACHE_H_

#include <vector>
#include <cmath>
#include <stdlib.h>

using namespace std;
typedef unsigned int uint;
enum { full = 0};							// define for full-associative cache
enum { s1K = 1024, s2K = 2048, s4K = 4096, s8K = 8192, s16K = 16384, s32K = 32768,
	   s64K = 65536, s128K = 131072, s256K = 262144, s512K = 524288, s1M = 1048576};

/**
 * This structure emulates block for one line of data.
 */
struct Block
{
	Block();
	uint tag_;
	bool valid_;
};

//###############################################################################################
/**
 * This class emulates line of block, which consist of different ways, it is named "set".
 * Due to the fact that it contains information of replacement, you have to use different
 * type of sets for different algorithms of replacing which are inherited from this class.
 */
struct SetAbstract
{
	SetAbstract( uint ways);
	vector<Block> blocks_;
};

//###############################################################################################
/**
 * This class is base class for emulator of processor's cache.
 * It supports following settings:
 * 		size 	   		 	   - is a number of data bytes that can be stored in the cache,
 * 		ways 	   		 	   - is a number of associative ways in a set,
 * 								 for creating full-associative cache you can use define 'full'.
 * 		block_size 		 	   - is a number of Bytes in a data block,
 * 		addr_size_in_bit 	   - is a number of bits in address,
 * 		hit_time			   - is time which is spent on hit,
 * 		miss_time			   - is time which is spent on a request to next level
 * 							     of memory hierarchy.
 * All parameters should be given as 'unsigned int' value to constructor of base cache
 * object. By default class 'CacheAbstract' uses Random algorithm of replacement. The cache with
 * special algorithm of replacement should be implemented as separate class which
 * is inherited from this class. Possible caches are 'CacheRR' with RobinRound algorithm
 *  of replacement and 'CacheLRU' with LeastRecentlyUsed replacement algorithm. For more information
 * see "replacement.h".
 * Example of using: CacheAbstract( 1024, 4, 4, 32).
 * For creating user's caches see "replacement.h".
 */

template <typename Replacement = SetAbstract>
class CacheAbstract
{
protected:
	uint ways_; 				//number of ways can not only be a power of two
	uint block_size_in_bit_;
	uint sets_; 				//number of sets can only be a power of two
	uint set_addr_in_bit_;
	uint tag_in_bit_;

	uint miss_number_;
	uint request_number_;

	uint hit_time_;
	uint miss_time_;

	uint mask_index_;
	uint mask_tag_;

	/** Return index of cache for target address.*/
	uint getIndex( uint addr) { return addr >> block_size_in_bit_ & mask_index_;}

	/** Return tag of target address.*/
	uint getTag	 ( uint addr) { return addr >> ( block_size_in_bit_ + set_addr_in_bit_) & mask_tag_;};

	/** algorithms of replacement.
	 *  If there are no free blocks in the set
	 *  this algorithm will be used to calculate number of block in the set
	 *  which will be replace. */
	virtual uint replace(  Replacement* set)
	{
		return rand() % ways_;
	};

	/** Part of algorithm of replacement which occurs when it was hit.*/
	virtual void hit    (  Replacement* set, uint number_hit ) {};

	/**The data of cache */
	vector<Replacement> cache_;

public:
	CacheAbstract<Replacement>( uint size, 	  	  uint ways,
								uint block_size,  uint addr_size_in_bit,
								uint hit_time,	  uint miss_time)
	{
		/* Checking the template parameter to inherit from the abstract class 'SetAbstract'. */
		Replacement* ptr = 0;
		SetAbstract* prt_abstract = static_cast< SetAbstract*>( ptr);
		prt_abstract = 0; 				  //to prevent compiler warnings about useless variable.

		/* Constructor actions.*/
		miss_number_ = 0;
		request_number_ = 0;

		hit_time_ = hit_time;
		miss_time_ = miss_time;

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

		cache_.resize( sets_, Replacement( ways_));
	};


    /** Gets address and checks availability data for him in cache,
     *  if address was not found, it would be added to cache. */
    void processRead( uint addr)
    {
    	request_number_++;
    	uint index =  getIndex( addr);
    	uint tag   =  getTag( addr);

    	for ( uint i = 0; i < ways_; i++)
    	{
    		/* Finding address in cache.
    		 * If hit, do action which connected with algorithm of replacement and return. */
    		if ( ( cache_[index].blocks_[i].valid_) && ( cache_[index].blocks_[i].tag_ == tag))
    		{
    			hit( &cache_[index], i);
    			return;
    		}
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
    }
   	bool getTimeLatency ( uint addr, uint& time)
    {
       	//request_number_++;
   	   	uint index =  getIndex( addr);
   	   	uint tag   =  getTag( addr);
   	   	for ( uint i = 0; i < ways_; i++)
   	   	{
   	   		/* Finding address in cache.
   	   		 * If hit, do action which connected with algorithm of replacement and return. */
   	   		if ( ( cache_[index].blocks_[i].valid_) && ( cache_[index].blocks_[i].tag_ == tag))
   	   		{
   	   			hit( &cache_[index], i);
   	   			time = hit_time_;
   	   			return 1;
   	   		}
   	   	}
   	   	time = miss_time_;
   	   	//miss_number_++;
   	   	for ( uint i = 0; i < ways_; i++)
   	   	{
   	   		/* If cache has no-valid blocks for target index, new one will be written to this place.*/
   	   		if ( !cache_[index].blocks_[i].valid_)
   	   		{
   	   			cache_[index].blocks_[i].tag_ = tag;
   	   			cache_[index].blocks_[i].valid_ = 1;
   	    		return 0;
   	    	}
   	    }
    	/* If there are not free places for target index, replacing will be used.*/
   	    cache_[index].blocks_[replace( &cache_[index])].tag_ = tag;
   	    return 0;
    }

    /** Returns miss rate.*/
    double getMissRate() const
    {
    	if ( !request_number_) return -1;	        // exception, 'processRead' has to be used before
    	return ( double) miss_number_ / ( double) request_number_;
    };

	virtual ~CacheAbstract<Replacement>() {};
};

#endif /* CACHE_H_ */
