/**
 * cache.h - Header of Cache class which defines
 * 
 * Copyright 2010 MDSP team
 */

#ifndef _NWAYCACHE_H_
#define _NWAYCACHE_H_

// An N-Way set associative cache
// Features:
//   Linear memory
//   Random algorithm used for memory retirement


#include <stddef.h>
#include <new>
#include <vector>
#include <map>
#include "types.h"
#include <math.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cassert>




//Forward declarations ad nauseam
/*
* class T - class of address
* class D - class of date
* class R - retirement class 
* size_t N - number of cache block
* size_t A - number of way of asocative
* class Hasher - hash function if it used
* 
*/
using namespace std;

template <class T, class D, unsigned int  N, unsigned int A, class R> class Cache;
template <class T, class D, unsigned int  N, unsigned int A > class Bucket;


/* 
* class implement feature of status cache line
*/
class StateBucket
{
	unsigned int valid_bit;
	//...other
public:
	StateBucket()
	{
		valid_bit = 1;
		//..other
	}
	void setValid( unsigned int bit)
	{
		valid_bit = bit;
	}
	unsigned getValid() const
	{
		return valid_bit;
	}
};
typedef map < unsigned int, StateBucket, std::less< unsigned int> > bucketMap;//include teg and status
template <class T, class D, unsigned int  N, unsigned int A >  ostream& operator<<( ostream&, Bucket<T,D,N,A>&);

template <class T, class D, unsigned int  N, unsigned int A > 
class Bucket 
{
	typedef Bucket< T, D, N, A> self_t;
	bucketMap *line;

	//closed 
	self_t& operator= ( const self_t&);
		
	unsigned int countTeg(const T& address);
	string toStringOfBin( const T& address);//represent address in bin form (expample 16bit addr: addr = 15 , string = "0000000000001111" 
	unsigned int toDecFromBin(  const string&, unsigned int, unsigned int);//numeration from 31 to 0(for 32 bits)
	

public:
	Bucket();
	Bucket( const T& address);
	Bucket( const self_t&);//for cache constructor
	
	unsigned int getSize() const
	{
		return (*line).size();
	}
	

	unsigned int countIndex(const T& address);
	void add( const T&, bucketMap::iterator);
	
    bucketMap::iterator getFirstIter() const
    {
        bucketMap::iterator pos;
        return pos = ( *line).begin();
    }
  
    bucketMap::iterator getLastIter() const
    {
        bucketMap::iterator pos;
        return pos = ( *line).end();
    }

	bool operator== ( const T& address);//find in cache bucket specified address
	friend ostream& operator<< <>( ostream& os,  Bucket<T,D,N,A>&);
	//template <class T, class D, unsigned int  N, unsigned int A, class R> friend class Cache;

};

template <class T, class D, unsigned int  N, unsigned int A > 
Bucket<T,D,N,A>::Bucket( const T &address)
{
	StateBucket temp;
	unsigned int teg = countTeg( address);
	line = new bucketMap;
	(*line)[ teg] =  temp;
}
template <class T, class D, unsigned int  N, unsigned int A > 
Bucket<T,D,N,A>::Bucket( const Bucket<T,D,N,A>& bucket)
{
	 try
    {
        line = new bucketMap;
    }catch ( std::bad_alloc)
    {
        cout << "ERROR: Can not allocate memory!\n";
        assert( 0);
    }
	bucketMap::iterator pos;
	StateBucket temp;
	for( pos = bucket.getFirstIter(); pos != bucket.getLastIter();++pos)
	{
		temp.setValid(pos->second.getValid());
		(*line)[ (pos->first)] = temp;			
	}
}
template <class T, class D, unsigned int  N, unsigned int A > 
Bucket<T,D,N,A>::Bucket()
{
	StateBucket temp;
	temp.setValid( 0);
	unsigned int teg = 0;
	line = new bucketMap;
	(*line)[ teg] =  temp;
}

template <class T, class D, unsigned int  N, unsigned int A >
inline std::string Bucket<T,D,N,A>::toStringOfBin( const T &address)
{
	string temp = "";
	for ( short i = sizeof(T)*8 - 1; i >= 0; i--) 
    { 
        temp += ( ( 1 << i) & address ? '1' : '0'); 
    }
	return temp;
}
template <class T, class D, unsigned int  N, unsigned int A >
inline unsigned int Bucket<T,D,N,A>::countIndex(const T& address)
{
	unsigned int size_of_index = log((double)(N/A))/log(2.0);
	string addr_str = toStringOfBin( address);
	unsigned int index = toDecFromBin( addr_str,sizeof(T)*8 /*-  log( (double)sizeof( D))/log(2.0) */- size_of_index , size_of_index);
	return index;
}
template <class T, class D, unsigned int  N, unsigned int A >
inline unsigned int Bucket<T,D,N,A>::toDecFromBin( const string& str,unsigned int left, unsigned int count)
{
	unsigned int dec = 0;
	for ( short i = left ; count > 0; i++) 
    {
		count--;
		string temp = "";
		temp = str[i];
		dec += ldexp(atof(temp.c_str()),(double)count); 
	}
	return dec;
}
template <class T, class D, unsigned int  N, unsigned int A >
inline unsigned int Bucket<T,D,N,A>::countTeg(const T &address)
{
	string addr_str = toStringOfBin( address);
	unsigned int size_of_teg = sizeof(T)*8  - log((double)(N/A))/log(2.0) /*-  log( (double)sizeof( D))/log(2.0) */;
	unsigned int teg = 	 toDecFromBin( addr_str, 0, size_of_teg);
	return teg;
}



template <class T, class D, unsigned int  N, unsigned int A >
inline bool Bucket<T,D,N,A>::operator ==( const T& address)
{
		unsigned int temp_teg = countTeg( address);
		bucketMap::iterator pos;
		pos = (*line).find( temp_teg);

		if( pos != (*line).end() && pos->second.getValid() == 1 )
		{
			return true;
		}
	return false;
}

template <class T, class D, unsigned int  N, unsigned int A >
inline void Bucket<T,D,N,A>::add( const T &address, bucketMap::iterator pos)
{
	StateBucket temp;
	temp.setValid(1);
	bucketMap::iterator it;
	for( it = (*line).begin(); it!= (*line).end(); ++it)
	{
		if( it->second.getValid() == 0)
		{
			pos = it;
		}
	}
	(*line).erase( pos);
	
	unsigned int teg = countTeg( address);
	
	(*line)[ teg] =  temp;
	
}

template <class T, class D, unsigned int  N, unsigned int A >
ostream& operator<< ( ostream& os,  Bucket<T,D,N,A>& bucket)
{
	bucketMap::iterator pos;
	
	for( pos = bucket.getFirstIter(); pos!= bucket.getLastIter(); ++pos)
	{
		os << (unsigned int)(pos->first) << " | "<< (unsigned int)(pos->second.getValid())<<"\n";
	}
	  
    return os;
}

template<class K> struct GenerateRetaiment 
{
	
};

		

template<class K> struct GenericHasher 
{
	static unsigned long hash(const K& k) 
	{ 
		return (unsigned long)k; 
	}
};

template <class T, class D, unsigned int  N, unsigned int A > 
class Random
{
public:
	bucketMap::iterator doAlgorithm( const Bucket< T, D, N, A>& bucket)
	{
		srand ( time(NULL) );
		unsigned int size = bucket.getSize();
		unsigned int temp = rand() % size ;
		bucketMap::iterator pos = bucket.getFirstIter();
		for ( short i = 0 ; i < temp; ++i)
		{
			++pos;
		}
		return pos;
		
	}
};


template <class T, class D, unsigned int  N, unsigned int A ,class R>  ostream& operator<<( ostream&,  Cache<T,D,N,A,R>&);
template <class T , class D , unsigned int N , unsigned int A , class R = class Random<T,D,N,A> > 

class Cache 
{	
	typedef  Cache<T,D,N,A,R> Self_t;
	typedef  Bucket<T,D,N,A> bucket_t;
	typedef  vector< bucket_t> cacheVector;
	
	R retaitment;
	cacheVector	*cache_t;
		
	unsigned long num_hits;
	unsigned long num_misses;
	
	//closed
	Cache(const Self_t&); 
	Self_t& operator=(const Self_t&); 
			
public:
	
	Cache();
	~Cache()
	{ 
		delete cache_t;
	}
	
	
	bool find( const T &address);
	bool insert( const T &address);
	typename cacheVector::iterator getFirstIter() const
    {
        cacheVector::iterator pos;
        return pos = ( *cache_t).begin();
    }
  
    typename vector<Bucket<T,D,N,A> >::iterator getLastIter() const
    {
        cacheVector::iterator pos;
        return pos = ( *cache_t).end();
    }
	friend ostream& operator<< <>( ostream& os,  Self_t&);
	
};
template <class T, class D,unsigned int N, unsigned int A, class R > 
inline Cache<T,D,N,A,R>::Cache()
	: num_hits(0), num_misses(0)
{
	try
	{
		cache_t = new vector< bucket_t >(N/A);
    
	}catch ( std::bad_alloc)
	{
		cout << "ERROR: Can not allocate memory!\n";
		assert( 0);
	}
	
}

template <class T, class D,unsigned int N, unsigned int A, class R > 
bool Cache<T,D,N,A,R>::find( const T &address)
{
	bucket_t temp;
	unsigned int pos = temp.countIndex( address);
	if( ( *cache_t).at( pos) == address)
	{
		num_hits++;
		return true;
	}
	num_misses++;
	return false;
} 

template <class T, class D, unsigned int N, unsigned int A, class R > 
bool Cache<T,D,N,A,R>::insert( const T &address)
{
	if( find( address))
	{
		num_hits++;
		return false;
	}
	bucket_t temp;
	unsigned int pos = temp.countIndex( address);
	( *cache_t).at( pos).add( address,retaitment.doAlgorithm( (*cache_t).at( pos)));
	return true;
	
}

template <class T, class D, unsigned int  N, unsigned int A ,class R>
ostream& operator<< ( ostream& os,  Cache<T,D,N,A,R>& cache)
{
	Cache<T,D,N,A,R>::cacheVector::iterator pos;
	
	for( pos = cache.getFirstIter(); pos!= cache.getLastIter(); ++pos)
	{
		os << (*pos)<<"\n";
	}
	  
    return os;
}


#endif

