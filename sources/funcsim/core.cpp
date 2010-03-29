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
    /*
     * Infinite loop ("while (1)") should be here.
     * To avoid assert interruption ("break") should be realized in the assembler.
     * As there isn't any "return" instruction in the assembler at the moment,
     * check for "zero" instruction will be held.
     */
	while (1)
	{
	    Operation* op;

		/* Read instruction */
		MemVal* mem_value ( (MemVal*) new ByteLine( memory->read32(this->GetIP()), HIGH_FIRST));

		/* check for "zero" instruction */
		if (!mem_value->getHostUInt32())
		{
			break;
		}

		op = new Operation( this);

		//cout << memory->read32(this->GetIP()) << endl;

		/* Decode the operation */
	    op->decode( mem_value);

	    //cout << op->encode()->getHostUInt32() << endl;
	    //op->dump();

	    /* Add 4 bytes (32 bits) to access next instruction */
	    this->pc = this->pc + 4;

	    /* Execute operation */
	    // op->execute();
        delete( op);
    }

}

/*
 * Load instructions to the memory from the stream (file)
 */
int Core::loadBinary( ifstream& input)
{
	hostUInt32 buffer;
	for ( mathAddr addr = 0x0000000A; !input.eof(); addr += 4)
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
