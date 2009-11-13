/**
* operation.cpp - Implementation of Operation class methods
* Copyright 2009 MDSP team
*/

#include "operation.h"

/**
* Set any operation
*/
void Operation::set( OperType type, OperCode opcode0, OperCode opcode1, OperCode opcode2,
                     hostUInt8 am, bool abit, bool rbit, 
                     hostUInt16 imm10, hostUInt16 imm16,
                     hostUInt8 rs1, hostUInt8 rs2, hostUInt8 rd)
{
}

/**
* Set an operation of MOVE type
*/
void Operation::set( OperType type, OperCode opcode0, 
                     hostUInt16 imm16, 
                     hostUInt8 rs1, hostUInt8 rd)
{
}

/**
* Encode operation in binary form
*/
MemVal* Operation::encode()
{
    MemVal* mem_value = new MemVal(4); // pointer to 32-bit (4 bytes)
                                       // instruction word

    return mem_value;
}

/**
* Decode an operation from binary form
*/
void Operation::decode(MemVal* mem_value)
{
}

/*
* Print an operation to console
*/
void Operation::dump()
{
}

/**
*
*/

void Operation::addFieldToInstructionWord( hostUInt16 field, int shift)
{
    field <<= shift;
    this->instr_word += field;                                     
}

