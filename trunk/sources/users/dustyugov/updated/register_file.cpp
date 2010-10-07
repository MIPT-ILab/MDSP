/**
 * register_file.cpp - Implementation of register file (RF) model
 * Define classes and methods to operate with RF of simulated architecture
 * Copyright 2009 MDSP team
 * Designed by Dmitry Korobov
 */

#include "register_file.h"

/* Constructor */
RegisterFileModel::RegisterFileModel( unsigned int number_of_registers,
									  unsigned int size_of_register_in_bytes)
{
    num_of_reg = number_of_registers;
    try
    {
        /* We try to allocate memory for the array of pointers to registers */
        reg_file = new RegVal*[ num_of_reg];
    } catch ( std::bad_alloc)
    {
	    cout << "Can't allocate memory for register file!\n";
        assert( 0);// Exit the program if we can't allocate memory.
    }

    for ( unsigned int i = 0; i < num_of_reg; i++)
    {
        try
        {
            /* We try to allocate memory for the register */
            reg_file[ i] = new RegVal( size_of_register_in_bytes);
        } catch ( std::bad_alloc)
        {
            /*
             * If allocation failed we report the number of the register
             * for which we can't allocate memory and then we exit the program.
             */
            cout << "Can't allocate memory for register number " << i << "\n";
            assert( 0);
        }
    }
}

/* Destructor */
RegisterFileModel::~RegisterFileModel()
{
    /* Deallocate memory of each register */
    for ( unsigned int i = 0; i < num_of_reg; i++)
    {
        delete reg_file[ i];
    }

    /* Deallocate memory of the array of registers */
    delete [] reg_file;
}

/* Read a logical set of bytes (RegVal) form physical register with number reg_num */
RegVal* RegisterFileModel::readReg( physRegNum reg_num)
{
    /*
     * We should check is 'reg_num' less than or equal to the greatest serial number
     * of elements of register value array. Because we can't read non-existent element.
     */
    if ( reg_num < num_of_reg)
    {
        return reg_file[ reg_num];
    } else
    {
        /* If 'reg_num' is incorrect report the error and exit the program */
        cout << "Error: number of register to be readed is out of range!\n";
        assert( 0);
    }
}

/* Write a logical set of bytes (RegVal) to physical register with number reg_num */
void RegisterFileModel::writeReg( physRegNum reg_num, RegVal& reg_value)
{
    /*
     * We should check is 'reg_num' less than or equal to the greatest serial number
     * of elements of register value array. Because we can't write to non-existent element.
     */
    if ( reg_num < num_of_reg)
    {
        *reg_file[ reg_num] = reg_value;
    } else
    {
        /* If 'reg_num' is incorrect report the error and exit the program */
        cout << "Error: number of register to be written is out of range!\n";
        assert( 0);
    }
}

