#include "operation.h"

/**
* Set any operation
*/
void Operation::set( OperType type, OperCode opcode0, OperCode opcode1, OperCode opcode2,
                     hostUInt8 am, bool abit, bool rbit, 
                     hostUInt16 imm10, hostUInt16 imm16,
                     hostUInt8 rS1, hostUInt8 rS2, hostUInt8 rD)
{
}

/**
* Set an operation of MOVE type
*/
void Operation::set( OperType type, OperCode opcode0, 
                     hostUInt16 imm16, 
                     hostUInt8 rS1, hostUInt8 rD)
{
}

/**
* Encode operation in binary form
*/
void Operation::encode()
{
}

/**
* Decode an operation from binary form
*/
void Operation::decode()
{
}

/*
* Print an operation to console
*/
void Operation::dump()
{
}
