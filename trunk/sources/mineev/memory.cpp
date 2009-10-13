/**
 * memory.cpp - Implementation of memory model
 * Define classes and method to operate with memory of simulated architecture
 * Copyright 2009 MDSP team
 */
 
#include <iostream>
#include <cassert>
#ifndef MEMORY_HEADER
#define MEMORY_HEADER
#include "memory.h"
#endif /* MEMORY_HEADER*/

/**
 * Implementation of class ByteLine
 */
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
    for ( int i = 0 ; i < line.getSizeOfLine(); i++)
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

void ByteLine::setByteVal( unsigned int byte_num, hostUInt8 byte_val)
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
    ( *byte_line).at( byte_num).setByteVal( byte_val);
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

/**
 * Implementation of class MemVal
 */

MemVal::MemVal( unsigned int number_of_bytes_in_mem_val)
{
    byte_line = new ByteLine( number_of_bytes_in_mem_val);
    if ( !byte_line)
    {
        cout << "ERROR: Can not allocate memory!\n";
        assert(0);
    }
}
