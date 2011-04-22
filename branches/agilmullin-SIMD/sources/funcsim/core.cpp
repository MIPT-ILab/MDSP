/**
 * core.cpp - Implementation of Core class methods
 * @author Pavel Zaichenkov
 * Copyright 2009 MDSP team
 */

#include "core.h"
#include "operation.h"
#include "flags.h"
#include "register_file.h"
#include "memory.h"

#include <fstream>

using namespace std;

/*
 * Constructor of the functional simulator core.
 * Creates architectural structures.
 */
Core::Core()
{
    this->memory = new MemoryModel( 1024);
    this->rf = new RegisterFileModel( 32, 2); // 32 16-bit registers
    this->apr = new RegisterFileModel( 8, 2); // Address Pointer Registers
    //this->pa  = new RegisterFileModel( 8, 3); // Parallel Accumulator Register 8 20-bit
                                              // It should be 20-bit, but now it's 24-bit.
    this->flags = new Flags();
    this->disasmPrint = false;
}

/*
 * Initialize the functional simulator.
 * Sets up start PC address.
 */
void Core::init( hostUInt16 start_pc)
{
    this->pc = start_pc;
    this->flags->init();
    this->stop = false;
    warning("Init. Start PC: 0x%X",start_pc);
}

/*
 * Run the functional simulator
 */

hostUInt64 Core::run( hostUInt64 requested)

{
    //number of steps the core has made
    hostUInt64 steps=0;


    /*
     * Infinite loop ("while (1)") should be here.
     * To avoid assert interruption ("break") should be realized in the assembler.
     * As there isn't any "return" instruction in the assembler at the moment,
     * check for "zero" instruction will be held.
     */
    while ( steps < requested )
    {
        Operation* op;

        /* Read instruction */
        MemVal* mem_value ( (MemVal*) new ByteLine( memory->read32(this->GetPC()), HIGH_FIRST));

        /* check for "zero" instruction */
        /* if (!mem_value->getHostUInt32())
        {
            break;
        } */

        op = new Operation( this);

        //cout << memory->read32(this->GetPC()) << endl;

        /* Decode the operation */
        op->decode( mem_value);
        
        //op->encode();

        /* Execute operation */
        op->execute();
        
        /* Disassembling */
        if ( disasmPrint )
        {
            op->dump();
        }

        delete( op);

        /* Add 4 bytes (32 bits) to access next instruction */
        this->pc = this->pc + 4;

        steps++;

        /* Check if it is necessary to stop instruction execution */
        if ( GetStop())
        {
            break;
        }
    }


    warning("Number of steps executed: %d", steps);
    return steps;
}

/*
 * Load instructions to the memory from the stream (file)
 */
int Core::loadBinary( ifstream& input)
{
    hostUInt32 buffer;
    for ( mathAddr addr = this->pc; !input.eof(); addr += 4)
    {
        buffer = 0;
        input.read( (char*) &buffer, 4);
        if (buffer)
        {
            this->memory->write32(addr, buffer );
        }
    }
    return 1;
}

