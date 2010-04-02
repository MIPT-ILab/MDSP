/**
 * memory.cpp - Implementation of memory model
 * Define classes and method to operate with memory of simulated architecture
 * @author Dmitry Ustyugov
 * Copyright 2009 MDSP team
 */


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
    output = DEFAULT_OUT;
}

ByteLine::ByteLine( unsigned int count)
{
    byte_line = new vector<Byte>;
    output = DEFAULT_OUT;
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
    output = DEFAULT_OUT;
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
    output = DEFAULT_OUT;
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

/* Conversion functions ByteLine into hostUInt8, hostUInt16, hostUInt32 */
hostUInt8 ByteLine::getHostUInt8()
{
    return this->getByteVal( 0);
}

hostUInt16 ByteLine::getHostUInt16()
{
    hostUInt8 temp[] = { this->getByteVal( 1), this->getByteVal( 0)};
    hostUInt16 var = 0;
    var += temp[ 0];
    var = ( var << 8);
    var += temp[ 1];
    return var;
}

hostUInt32 ByteLine::getHostUInt32()
{
    hostUInt8 temp[] = { this->getByteVal( 3), this->getByteVal( 2), 
        this->getByteVal( 1), this->getByteVal( 0)};
    hostUInt32 var = 0;
    for ( int i = 0; i < 3; i++)
    {
        var += temp[ i];
        var = ( var << 8);
    }
    var += temp[3];
    return var;
}

/* Private functions converting hostUInt8,16,32 into vector<Byte> *byte_line */
void ByteLine::convert8( vector<Byte> *byte_line, hostUInt8 var)
{
    Byte byte( var);
    ( *byte_line).push_back( byte);
}

void ByteLine::convert16( vector<Byte> *byte_line, hostUInt16 var, OrderType type)
{
    hostUInt8 temp[2] = { 0, 0};
    for ( int i = 0; i < 2; i++)
    {
        for( int k = 0; k < 8; k++)
        {
            if ( var & 1)
                temp[ i] += ( 1 << k);
            var = ( var >> 1);
        }
    }
    Byte byte[] = { temp[ 0], temp[ 1]};
    if ( type == HIGH_FIRST)
    {
        for ( int i = 0; i < 2; i++)
            ( *byte_line).push_back( byte[ i]);
    } else
    {
        for ( int i = 2; i > 0; i--)
            ( *byte_line).push_back( byte[ i-1]);
    }
}

void ByteLine::convert32( vector<Byte> *byte_line, hostUInt32 var, OrderType type)
{
    hostUInt8 temp[4] = { 0, 0, 0, 0};
    for ( int i = 0; i < 4; i++)
    {
        for( int k = 0; k < 8; k++)
        {
            if ( var & 1)
                temp[ i] += ( 1 << k);
            var = ( var >> 1);
        }
    }
    Byte byte[] = { temp[ 0], temp[ 1], temp[ 2], temp[ 3]};
    if ( type == HIGH_FIRST)
    {
        for ( int i = 0; i < 4; i++)
            ( *byte_line).push_back( byte[ i]);
    } else
    {
        for ( int i = 4; i > 0; i--)
            ( *byte_line).push_back( byte[ i-1]);
    }
}

/* Conversion constructors hostUInt8, hostUInt16 and hostUInt32 in Byteline */
ByteLine::ByteLine( hostUInt8 var, OrderType type)
{
    output = DEFAULT_OUT;
    try
    {
        byte_line = new vector<Byte>;
        convert8( byte_line, var);
    }catch ( std::bad_alloc)
    {
        cout << "ERROR: Can not allocate memory!\n";
        assert( 0);
    }
}

ByteLine::ByteLine( hostUInt16 var, OrderType type)
{
    output = DEFAULT_OUT;
    try
    {
        byte_line = new vector<Byte>;
        convert16( byte_line, var, type);
    }catch ( std::bad_alloc)
    {
        cout << "ERROR: Can not allocate memory!\n";
        assert( 0);
    }
}
ByteLine::ByteLine( hostUInt32 var, OrderType type)
{
    output = DEFAULT_OUT;
    try
    {
        byte_line = new vector<Byte>;
        convert32( byte_line, var, type);
    }catch ( std::bad_alloc)
    {
        cout << "ERROR: Can not allocate memory!\n";
        assert( 0);
    }
}

ByteLine::ByteLine(unsigned int var, ConversionType ctype, OrderType type)
{
    output = DEFAULT_OUT;
    switch( ctype)
    {
    case HUINT8:
        try
        {
           byte_line = new vector<Byte>;
           convert8( byte_line, var);
        }catch ( std::bad_alloc)
        {
            cout << "ERROR: Can not allocate memory!\n";
            assert( 0);
        }
        break;
    case HUINT16:
        try
        {
            byte_line = new vector<Byte>;
            convert16( byte_line, var, type);
        }catch ( std::bad_alloc)
        {
            cout << "ERROR: Can not allocate memory!\n";
            assert( 0);
        }
        break;
    case HUINT32:
        try
        {
            byte_line = new vector<Byte>;
            convert32( byte_line, var, type);
        }catch ( std::bad_alloc)
        {
            cout << "ERROR: Can not allocate memory!\n";
            assert( 0);
        }
        break;
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


ByteLine MemoryModel::readBL(  mathAddr read_ptr, unsigned int num_of_bytes)
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

MemVal MemoryModel::read(  mathAddr read_ptr, unsigned int num_of_bytes)
{
    MemVal mv( readBL( read_ptr, num_of_bytes));
    return mv;
}

/* Reading funcs returning hostUInt8, 16, 32 */
hostUInt8 MemoryModel::read8( mathAddr addr)
{
    ByteLine bl = readBL( addr, 1);
    return bl.getHostUInt8();
}

hostUInt16 MemoryModel::read16( mathAddr addr)
{
    ByteLine bl = readBL( addr, 2);
    return bl.getHostUInt16();
}

hostUInt32 MemoryModel::read32( mathAddr addr)
{
    ByteLine bl = readBL( addr, 4);
    return bl.getHostUInt32();
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

/* Writing hostUInt8, 16, 32 funcs */
void MemoryModel::write8( mathAddr write_ptr, const hostUInt8 val)
{
    ByteLine bl( val, HIGH_FIRST);
    write( write_ptr, bl);
}

void MemoryModel::write16( mathAddr write_ptr, const hostUInt16 val)
{
    ByteLine bl( val, HIGH_FIRST);
    write( write_ptr, bl);
}

void MemoryModel::write32( mathAddr write_ptr, const hostUInt32 val)
{
    ByteLine bl( val, HIGH_FIRST);
    write( write_ptr, bl);
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
