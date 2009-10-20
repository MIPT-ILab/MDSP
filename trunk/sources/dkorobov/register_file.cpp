/**
 * register_file.cpp - Implementation of register file (RF) model
 * Define classes and methods to operate with RF of simulated architecture
 * Copyright 2009 MDSP team
 * Designed by Dmitry Korobov
 */

#include "register_file.h"

/*Constructor*/
RegisterFileModel::RegisterFileModel( unsigned int number_of_registers,
									 unsigned int size_of_register_in_bytes)
{
	num_of_reg = number_of_registers;
	try
	{
		reg_file = new RegVal*[ num_of_reg];
	} catch ( std::bad_alloc)
	{
		cout << "Can't allocate memory for register file!\n";
	}

	for ( int i = 0; i < num_of_reg; i++)
	{
		try
		{
			reg_file[i] = new RegVal( size_of_register_in_bytes);
		} catch ( std::bad_alloc)
		{
			cout << "Can't allocate memory for register number " << i << "\n";
		}
	}
}

/*Destructor*/
RegisterFileModel::~RegisterFileModel()
{
	for (int i = 0; i < num_of_reg; i++)
	{
		delete reg_file[i];
	}

	delete [] reg_file;
}

RegVal* RegisterFileModel::readReg( physRegNum reg_num)
{
	if (reg_num < num_of_reg)
	{
		return reg_file[reg_num];
	} else
	{
		cout << "Error: number of register to be readed is out of range!\n";
		assert(0);
	}
}

void RegisterFileModel::writeReg(physRegNum reg_num, RegVal& reg_value)
{
	if (reg_num < num_of_reg)
	{
		*reg_file[reg_num] = reg_value;
	} else
	{
		cout << "Error: number of register to be written is out of range!\n";
		assert(0);
	}
}