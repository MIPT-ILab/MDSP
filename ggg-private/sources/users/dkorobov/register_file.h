/**
 * register_file.h - Specification of register file (RF) model
 * Define classes and methods to operate with RF of simulated architecture
 * Copyright 2009 MDSP team
 */

#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include <iostream>
#include <cassert>
#include "types.h"
#include "memory.h"

/**
 * class RegVal implements a object to interaction with RF 
 */

class RegVal: public ByteLine
{
  
public:
    /* Constructors and destructor */
    RegVal( unsigned int size_in_bytes): ByteLine( size_in_bytes)
    {
    }

    ~RegVal()
    {
    }

    RegVal& operator =( RegVal& reg_val)
    {
        if ( this->getSizeOfLine() != reg_val.getSizeOfLine())
	    {
		    cout << "Error: you can write to RegVal with the equal length only!\n";
		    assert( 0);
        }
        int sz_of_ln = this->getSizeOfLine();

        for ( int i = 0; i < sz_of_ln; i++)
        {
            this->setByteVal( i, reg_val.getByteVal( i));
        }

        return ( *this);
    }
};

/**
 * class RegisterFileModel implements RF of simulated architecture and infrastructure to operate with it
 */

class RegisterFileModel 
{
    RegVal** reg_file;          // Array of RegVal*
    unsigned int num_of_reg;    // Number of registers in the register file

public:
	
    /* Constructors and destructor */
    RegisterFileModel( unsigned int number_of_registers, unsigned int size_of_register_in_bytes);
    ~RegisterFileModel();
     
    /* Read a logical set of bytes (RegVal) form physical register with number reg_num */
    RegVal* readReg( physRegNum reg_num);
     
    /* Write a logical set of bytes (RegVal) to physical register with number reg_num */
    void writeReg( physRegNum reg_num, RegVal& reg_value);
};

#endif /* REGISTER_FILE_H */
