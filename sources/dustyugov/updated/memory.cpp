/**
 * memory.cpp - Implementation of memory model
 * Define classes and method to operate with memory of simulated architecture
 * Copyright 2009 MDSP team
 */


#include <iostream>
#include <cassert>
#include <math.h>
#ifndef MEMORY_HEADER
#define MEMORY_HEADER
#include "memory.h"
#endif /* MEMORY_HEADER*/

/**
 * Implementation of class ByteLine
 */
ByteLine::ByteLine()
{
	byte_line = new vector<Byte>;
}

ByteLine::ByteLine( unsigned int count)
{
    byte_line = new vector<Byte>;
    try
    {
        (*byte_line).resize( count);
    }catch ( std::bad_alloc)
    {
        cout << "ERROR: Can not allocate memory!\n";
        assert( 0);
    }
}

ByteLine::ByteLine( const ByteLine& line)
{
    try
    {
        byte_line = new vector<Byte>( line.getSizeOfLine());
    }catch ( std::bad_alloc)
    {
        cout << "ERROR: Can not allocate memory!\n";
        assert( 0);
    }
    for ( unsigned int i = 0 ; i < line.getSizeOfLine(); i++)
    {
        ( *byte_line).at( i).setByteVal( line.getByteVal( i));
    }
}
ByteLine::ByteLine( const Byte& byte)
{
    try
    {
        byte_line = new vector<Byte>;
        ( *byte_line).push_back( byte);
    }catch ( std::bad_alloc)
    {
        cout << "ERROR: Can not allocate memory!\n";
        assert( 0);
    }
}

hostUInt8 ByteLine::getByteVal( unsigned int byte_num) const
{
    if ( byte_num > this->getSizeOfLine())
    {
        cout << "ERROR: Size of byte line is less than target byte number!\n";
        assert( 0);
    }
    if ( ( *byte_line).empty())
    {
        cout << "ERROR: Byte line is empty!\n";
        assert( 0);
    }
    return ( *byte_line).at( byte_num).getByteVal();
}

Byte ByteLine::getByte( unsigned int byte_num) const
{
    if ( byte_num > this->getSizeOfLine())
    {
        cout << "ERROR: Size of byte line is less than target byte number!\n";
        assert( 0);
    }
    if ( ( *byte_line).empty())
    {
        cout << "ERROR: Byte line is empty!\n";
        assert( 0);
    }
    return ( *byte_line).at( byte_num);
}

void ByteLine::setByte( unsigned int byte_num, const Byte& byte)
{
    if ( byte_num > this->getSizeOfLine())
    {
        cout << "ERROR: Size of byte line is less than target byte number!\n";
        assert( 0);
    }
    if ( ( *byte_line).empty())
    {
        cout << "ERROR: Byte line is empty!\n";
        assert( 0);
    }
    ( *byte_line).at( byte_num) = byte;
}


void ByteLine::addByte( const Byte& byte)
{
    try
    {
        ( *byte_line).push_back( byte);
    }catch ( std::bad_alloc)
    {
        cout << "ERROR: Can not allocate memory!\n";
        assert( 0);
    }
}
void ByteLine::resizeByteLine( unsigned int count)
{
    try
    {
        ( *byte_line).resize( count);
    }catch ( std::bad_alloc)
    {
        cout << "ERROR: Can not allocate memory!\n";
        assert( 0);
    }
}


/**
 * Implementation of class MemVal
 */

void MemVal::recountLenght()
{
    unsigned int temp = getSizeOfMemVal() % size_of_segmentation;
    if ( temp != 0 && size_of_segmentation != 1)
    {
        temp = size_of_segmentation - temp;
        temp += getSizeOfMemVal();
        resizeByteLine( temp);
    }
}

ByteLine MemVal::getByteLine( unsigned int index, unsigned int count) const
{
    if ( getSizeOfMemVal() < index + count)
    {
        cout << "ERROR: Size of MemVal is less than target byte number!\n";
        assert( 0);
    }
    ByteLine temp( count);
    for ( unsigned int i = 0; i < count ; i++)
    {
        temp.setByte( i, getByte( i + index));
    }
    return temp;
}
ByteLine MemVal::getByteLine() const
{
    ByteLine temp( getSizeOfMemVal());
    for ( unsigned int i = 0; i < getSizeOfMemVal(); i++)
    {
        temp.setByte( i, getByte( i));
    }
    return temp;
}

void MemVal::writeByteLine( const ByteLine& line, unsigned int index)
{
    if ( getSizeOfMemVal() < index + line.getSizeOfLine())
    {
        cout << "ERROR: Size of MemVal is less than target byte number!\n";
        assert( 0);
    }
    for ( unsigned int i = 0; i < line.getSizeOfLine(); i++)
    {
        setByte( i + index, line.getByte( i));
    }
}
void MemVal::writeByteLine( const ByteLine & line)
{
    if ( getSizeOfMemVal() < line.getSizeOfLine())
    {
        cout << "ERROR: Size of MemVal is less than target byte number!\n";
        assert( 0);
    }
    for ( unsigned int i = 0; i < line.getSizeOfLine(); i++)
    {
        setByte( i, line.getByte( i));
    }
}




/**
 * Implementation of Memory Model
 */

MemoryModel::MemoryModel( unsigned int size)
{
	mem_model = new memMap;
	size_of_segmentation = size;

}


ByteLine MemoryModel::read(  mathAddr read_ptr, unsigned int num_of_bytes)
{
	if ( ( *mem_model).empty())
	{
		cout << "ERROR!\n";
        assert( 0);
	}

	memMap::iterator pos, start, end;
	start = find( read_ptr);
	mathAddr temp_addr = start->first;
	end = find( read_ptr + num_of_bytes - 1);
	if ( start == ( *mem_model).end() || end == ( *mem_model).end())
	{
		cout << "ERROR!\n";
        assert( 0);
	}
	MemVal memval = start->second;
	for ( pos = start; pos != end; ++pos)
	{
		if ( countDistance( pos) > 0)
		{
			cout << "ERROR!\n";
			assert( 0);
		}
		mergeMemVal( pos, &memval);

	}
	( *mem_model).erase( start, end);
	( *mem_model).erase( end);
	( *mem_model)[ temp_addr] = memval;
	return memval.getByteLine( read_ptr - temp_addr, num_of_bytes);


}



void MemoryModel::mergeMemVal( memMap::iterator pos, MemVal *mem_val)
{
	if ( countDistance( pos) > 0)
	{
			mem_val->resizeMemVal( ( pos + 1)->first - pos->first);
	}
		( *mem_val) = ( *mem_val) + ( pos + 1)->second;
}



void MemoryModel::write( mathAddr write_ptr, const ByteLine& line)
{
	memMap::iterator pos, start, end ;
	start = findOrInit( write_ptr);
	mathAddr temp_addr = start->first;
	end = findOrInit( write_ptr + line.getSizeOfLine() - 1);

	MemVal memval = start->second;
	for ( pos = start; pos != end; ++pos)
	{
		mergeMemVal( pos, &memval);

	}
	( *mem_model).erase( start, end);
	( *mem_model).erase( end);

	memval.writeByteLine( line, write_ptr - temp_addr);
	( *mem_model)[ temp_addr] = memval;
}


memMap::iterator MemoryModel::findOrInit( mathAddr ptr)
{
	memMap::iterator pos;
	MemVal temp( size_of_segmentation);
	mathAddr addr = ptr - ( ptr % size_of_segmentation);

	for ( pos = ( *mem_model).begin(); pos != ( *mem_model).end(); ++pos)
	{
		if ( pos == ptr)
		{
			return pos;
		}
		if ( ( pos->first) > ptr)
		{
			( *mem_model)[ addr] = temp;
			pos = ( *mem_model).find( addr);
			return pos;

		}
	}
	( *mem_model)[ addr] = temp;
	pos = ( *mem_model).find( addr);
	return pos;

}


memMap::iterator MemoryModel::find( mathAddr ptr)
{
	memMap::iterator pos;
	mathAddr adrr;
	adrr = ptr - ( ptr % size_of_segmentation);
	for ( pos = ( *mem_model).begin(); pos != ( *mem_model).end(); ++pos)
	{
		if ( pos == ptr)
		{
			return pos;
		}
	}
	return pos = ( *mem_model).end();
}

unsigned int MemoryModel::countDistance( const memMap::iterator pos)
{
	return ( pos + 1)->first - ( pos->first + ( pos->second).getSizeOfMemVal());
}
