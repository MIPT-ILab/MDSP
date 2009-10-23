/**
 * operation.cpp - Implementation of Operation class methods
 * Copyright 2009 MDSP team
 */

#include "operation.h"
#include "register_file.h"
#include "flags.h"

/**
 * Constructor with pointer to core. Pointer to core 
 * is needed to access main structures (RF, flags, PC) of simulator.
 */
Operation::Operation( Core *core)
{
    this->core = core;
    this->clear();
}

/**
 * Set any operation
 */
void Operation::set( OperType type, OperCode opcode0, OperCode opcode1, OperCode opcode2,
                     hostUInt8 sd, hostUInt8 am, 
                     hostUInt16 imm10, hostUInt16 imm16,
                     hostUInt8 rs1, hostUInt8 rs2, hostUInt8 rd)
{
}

/**
 * Set an operation of MOVE type
 */
void Operation::set( OperType type, OperCode opcode0, 
                     hostUInt8 sd, hostUInt16 imm16, 
                     hostUInt8 rs1, hostUInt8 rd)
{
}

/**
 * Set an operation of ALU type
 */
void Operation::set( OperType type, OperCode opcode0, OperCode opcode1, OperCode opcode2,
                     hostUInt8 am, hostUInt16 imm10, 
                     hostUInt8 rs1, hostUInt8 rs2, hostUInt8 rd)
{
}

/**
 * Set an operation of P_FLOW type
 */
void Operation::set( OperType type, OperCode opcode0,
                     hostUInt8 sd, hostUInt16 imm16, 
                     hostUInt8 rd)
{
}

/**
 * Encode operation in binary form
 */
MemVal* Operation::encode()
{
/*
    MemVal* mem_value = new MemVal(4); // pointer to 32-bit (4 bytes) instruction word

    return mem_value;
*/
    return NULL; // delete it later
}

/**
 * Decode an operation from binary form
 */
void Operation::decode( MemVal* mem_value)
{
}

/*
 * Print an operation to console
 */
void Operation::dump()
{
}

/*
 * Set instruction word (binary representation) from memory block
 */
void Operation::setInstrWord( MemVal* mem_value)
{
    /*
    this->instr_word = ... 
    */
}

/*
 * Set memory block from instruction word (binary representation)
 */
void Operation::setMemBlock( MemVal* mem_value)
{
}

/*
 * Execute the operation
 */
void Operation::execute()
{
    switch ( this->type)
    {
        case MOVE:
            this->executeMove();
            break;
        case ALU:
            this->executeALU();
            break;
        case P_FLOW:
            this->executePFlow();
            break;
        default:
            cout << "Invalid operation type\n";
            assert( 0);
    }
}

/*
 * Execute the operation of MOVE type
 */
void Operation::executeMove()
{
}

/*
 * Execute the operation of ALU type
 */
void Operation::executeALU()
{

    /* Update flag register after execution */
}

/*
 * Execute the operation of P_FLOW type
 */
void Operation::executePFlow()
{
    /* Read flag register before execution */

}
