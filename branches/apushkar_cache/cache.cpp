/**
 * @file:cache.cpp
 * CacheStudyExercise
 * @author:Andriy Pushkar
 * Copyright 2012 MDSP team
 */

#include "cache.h"

/**
 * Class Block implementation
 */


Block::Block()
{
    erase_ready_priv = true;
    tag_priv = -1;
}

void Block::setEraseReady( bool erase_ready)
{
    erase_ready_priv = erase_ready;
}

bool Block::getEraseReady()
{    
    return erase_ready_priv;
}

void Block::setValue( unsigned int tag)
{
    tag_priv = tag;
}

unsigned int Block::getValue()
{
    return tag_priv;
}


/**
 * Class Set implementation
 */


void Set::setValue( unsigned int tag)
{    
    for ( int i = 0; i < body.size(); i++)
    {
        if ( body[ i].getEraseReady()) // the block is ready to be removed
        {
            body[ i].setValue( tag);
            body[ i].setEraseReady( false);
            /* we will replace the i+1th block next time */
            body[ ( i + 1) % body.size()].setEraseReady( true); 
            return;
        }
    }
}

bool Set::getValue( unsigned int tag)
{
    for ( int i = 0; i < body.size(); i++)
    {
        if ( body[i].getValue() == tag)
            return true;
    }
    return false;
}

void Set::resize( unsigned int ways)
{
    body.resize( ways);
}

/**
 * Class Cache implementation
 */


Cache::Cache( unsigned int size, unsigned int ways,
             unsigned int block_size, 
             unsigned int addr_size_in_bit)
{
    size_priv = size;
    ways_priv = ways;
    block_size_priv = block_size;
    addr_size_in_bit_priv = addr_size_in_bit;
    
    hit_num = 0;
    miss_num = 0;
   
    /* we have to send to the Util class current cache settings */
    Util::setCacheParameters( size, ways, block_size, addr_size_in_bit);
    
    cache.resize( size_priv / ( block_size_priv * ways_priv)); 
    
    for ( int i = 0; i < cache.size(); i++)
    {
        cache[ i].resize( ways_priv);
    }
}


void Cache::processRead( unsigned int addr)
{
    unsigned int index, tag;
    index = Util::getIndex( addr);
    tag = Util::getTag( addr);
    
    if ( cache[ index].getValue( tag)) 
    {
        hit_num++;
    }
    else
    {
        miss_num++;
        cache[ index].setValue( tag);
    }
}


double Cache::getMissRate() const
{
    return ( double) ( ( double) miss_num / ( miss_num + hit_num));
}


unsigned int Cache::getSize()
{
    return size_priv;
}

unsigned int Cache::getWays()
{
    return ways_priv;
}

unsigned int Cache::getBlockSize()
{
    return block_size_priv;
}

unsigned int Cache::getAddrSizeInBit()
{
    return addr_size_in_bit_priv;
}

/**
 * Class Util implementation
 */

unsigned int Util::size_priv;
unsigned int Util::ways_priv;
unsigned int Util::block_size_priv;     
unsigned int Util::addr_size_in_bit_priv;


double Util::binaryLog( double n)
{
    return log( n) / log( 2);
}

unsigned int Util::upperPowOfTwo( double n)
{
    return ( int)ceil( binaryLog( n));
}

unsigned int Util::getIndex( unsigned int addr)
{
    unsigned int index, index_len, blocks_num, index_mask;
    
    addr = addr >> (int) upperPowOfTwo( block_size_priv); 
    blocks_num = size_priv / block_size_priv; 
    index_len = ( int) ceil( binaryLog( ( blocks_num / ways_priv)));
    index_mask = ( int) pow( 2, ( double)index_len) - 1;
    
    index = addr & index_mask;
    
    return index;
}


unsigned int Util::getTag( unsigned int addr)
{
    unsigned int index_len, blocks_num, tag;
    
    unsigned int byte_offset_len =  ( int) upperPowOfTwo( block_size_priv);
    blocks_num = size_priv / block_size_priv;
    index_len = ( int) ceil( binaryLog( ( blocks_num / ways_priv)));
    
    tag = addr >> ( index_len + byte_offset_len);
    
    return tag;
}


void Util::setCacheParameters( unsigned int size, unsigned int ways,
                        unsigned int block_size, 
                        unsigned int addr_size_in_bit)
{
    size_priv = size; 
    ways_priv = ways; 
    block_size_priv = block_size; 
    addr_size_in_bit_priv = addr_size_in_bit;
}
