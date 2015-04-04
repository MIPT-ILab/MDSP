/**
 * core.cpp - Implementation of Core class methods
 * Copyright 2009 MDSP team
 */

#include "core.h"
#include "operation.h"
#include "flags.h"
#include "register_file.h"
#include "memory.h"

/*
 * Constructor of the functional simulator core.
 * Creates architectural structures.
 */
Core::Core()
{
    this->memory = new MemoryModel( 1024);
    this->rf = new RegisterFileModel( 32, 2); // 32 16-bit registers
    this->flags = new Flags();
}

/*
 * Initialize the functional simulator.
 * Sets up start PC address.
 */
void Core::init( hostUInt16 start_pc)
{
    this->pc = start_pc;
}

/*
 * Run the functional simulator
 */
void Core::run()
{
    Operation* op;
    // MemVal* mem_value;

/*
    while( 1)
    {
*/
        op = new Operation( this);

        /* Fetch an operation */
        // MemVal* mem_value = op->fetch();

        /* Decode the operation */
        // op->decode( mem_value);

        /* Add 4 bytes (32 bits) to access next instruction */
        this->pc = this->pc + 4;

        /* Execute operation */
        // op->execute();

        delete( op);
/*
    }
*/
}

