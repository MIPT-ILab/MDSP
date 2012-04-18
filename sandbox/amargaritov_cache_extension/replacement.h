/*
 * replacement.h
 *
 *  Created on: Apr 17, 2012
 *      Author: art
 */

/**
 *  This file contain implementing of class caches with special algorithm of replacement.
 *  If you want to create a new emulator of cache with different algorithm of replacement you
 *  should create class 'SetNameOfRepalcement' which has to be inherited from class 'SetAbastarct'.
 *  And create new class 'CacheNameOfRepalcement' which has to be inherited from class
 *  'CacheAbstract<SetNameOfReplacement>' and has to have two virtual methods and public constructor:
 *  	(*)  virtual void hit( 'SetNameOfReplacement'* set, unsigned int number_hit),
 *  	(*)  virtual uint repalce ( 'SetNameOfReplacement'* set)
 *  which implement replacement algorithm.
 *  For example see implementation of class 'CacheLRU'.
 */

#ifndef REPLACEMENT_H_
#define REPLACEMENT_H_

#include "cache.h"
#include <vector>
#include <algorithm>

///==========================================================================================
///==============================### RoundRobin Cache ###====================================
///==========================================================================================
/* This class is special kind of set for cache with RR algorithm of replacment. */
struct SetRR: public SetAbstract
{
	SetRR( uint ways):SetAbstract( ways) { replaceable_ = 0;};
	uint replaceable_;
};

/**
 * This class is emulator of cache with RoundRobin algorithm of replacement. Every set in cache has
 * pointer of replacing block. If there was a miss the block by pointer will be replaced and pointer
 * will be increased. The pointer is closed loop.
 */
class CacheRR : public CacheAbstract< SetRR >
{
protected:
	virtual uint replace( SetRR* set)
	{
		if ( ++(set->replaceable_) ==  ways_) set->replaceable_ = 0;
		return set->replaceable_;
	}
	virtual void hit    ( SetRR* set, uint number_hit) {};

public:
	CacheRR( uint size, 			uint ways,     uint block_size,
			 uint addr_size_in_bit, uint hit_time, uint miss_time):
		     CacheAbstract<SetRR> ( size, 			  ways,     block_size,
									addr_size_in_bit, hit_time, miss_time) 	{};

	virtual ~CacheRR() {};
};

///==========================================================================================
///==============================### LeastRecentlyUsed Cache ###=============================
///==========================================================================================

/* This class is special kind of set for cache with LRU algorithm of replacment. */
struct SetLRU: public SetAbstract
{
	SetLRU( uint ways):SetAbstract( ways) {};
	vector<uint> age_;
};

/**
 * This class is emulator of cache with LeastRecentlyUsed algorithm of replacement.
 * If there was a hit age of all data besides hit data is increased, age of hit data decrease.
 * The parameter 'limit_age' is largest age of data in cache.
 */
class CacheLRU : public CacheAbstract< SetLRU >
{
protected:
	uint limit_age_;
	/* This method is part of replacement algorithm which happens when replacing is used. */
	virtual uint replace( SetLRU* set)
	{
		vector<uint>::iterator max_age = max_element( set->age_.begin(), set->age_.end());
		*max_age = 0;
		return max_age - set->age_.begin();
	};
	/* This method is part of replacement algorithm which happens when there was a hit. */
	virtual void hit    ( SetLRU* set, uint number_hit)
	{
		for ( uint i = 0; i < ways_; i++)
		{
			if ( i == number_hit && set->age_[i] > 0) { set->age_[i]--; continue; };
			if ( set->age_[i] < limit_age_) set->age_[i]++;
		}
	};

public:
	/* Constructor can use special fields of set structure. */
	CacheLRU( uint size, 			 uint ways,     uint block_size,
			  uint addr_size_in_bit, uint hit_time, uint miss_time,
			  uint limit_age										):
		CacheAbstract<SetLRU> ( size, 			 ways,     block_size,
							   addr_size_in_bit, hit_time, miss_time)
	{
		for ( uint i = 0; i < sets_; i++)
		{
			cache_[i].age_.resize ( ways_, limit_age);
		}
		limit_age_ = limit_age;
	};

	virtual ~CacheLRU() {};
};

#endif /* REPLACEMENT_H_ */
