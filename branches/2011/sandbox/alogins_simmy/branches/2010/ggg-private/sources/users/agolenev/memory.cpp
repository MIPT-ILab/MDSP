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

ByteLine::ByteLine( unsigned int num_of_bytes_in_line) 
{
    if ( num_of_bytes_in_line == 0)
    {
        cout << "ERROR: Size of the line can not be equal to 0 bytes!\n";
        assert(0);
    }

    byte_line = new Byte[num_of_bytes_in_line];
    if ( !byte_line)
    {
        cout << "ERROR: Can not allocate memory!\n";
        assert(0);
    }
        
    size_of_line = num_of_bytes_in_line;
}

hostUInt8 ByteLine::getByteVal( unsigned int byte_num)
{
    if ( byte_num > size_of_line)
    {
        cout << "ERROR: Size of byte line is less than target byte number!\n";
        assert(0);
    }
        
    return byte_line[byte_num].getByteVal();
}

void ByteLine::setByteVal( unsigned int byte_num, hostUInt8 byte_val)
{
    if ( byte_num > this->size_of_line)
    {
        cout << "ERROR: Size of byte line is less than target byte number!\n";
        assert(0);
    }
        
    byte_line[byte_num].setByteVal(byte_val);
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
