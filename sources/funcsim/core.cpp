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

        this->pc++;

        /* Execute operation */
        // op->execute();

        delete( op);
/*
    }
*/
}
