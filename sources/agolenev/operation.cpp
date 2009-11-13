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
    this->type = type;
    this->opcode0 = opcode0;
    this->imm16 = imm16;
    this->rs1 = rs1;
    this->rd = rd;
    addFieldToInstructionWord( type, type_shift);
    addFieldToInstructionWord( opcode0, opcode0_shift);
    addFieldToInstructionWord( imm16, imm16_shift);
    addFieldToInstructionWord( rs1, rs_shift);
    instr_word += rd;
}

/**
* Set an operation of ALU type
*/


void Operation::set( OperType type, OperCode opcode0, OperCode opcode1, OperCode opcode2,
                     hostUInt8 am, hostUInt16 imm10, 
                     hostUInt8 rs1, hostUInt8 rs2, hostUInt8 rd)
{
    this->type = type;
    this->opcode0 = opcode0;
    this->opcode1 = opcode1;
    this->opcode2 = opcode2;
    this->am = am;
    this->imm10 = imm10;
    this->rs1 = rs1;
    this->rs1 = rs2;
    this->rd = rd;
    addFieldToInstructionWord( type, type_shift);
    addFieldToInstructionWord( opcode0, opcode0_shift);
    addFieldToInstructionWord( imm16, imm16_shift);
    addFieldToInstructionWord( rs1, rs_shift);
    instr_word += rd;
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
* Add field to instruction word
*/

void Operation::addFieldToInstructionWord( hostUInt16 field, int shift)
{
    this->instr_word += ( field << shift);                                     
}

