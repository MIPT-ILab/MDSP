/**
 * simmy.cpp
 *
 * Simmy core
 *
 * @author Pavel Kryukov
 * Copyright 2012 MDSP team
*/

#include <cstdio>

#include "./types.h"
#include "./isa.h"
#include "./instr.h"
#include "./simmy.h"

namespace Simmy
{

int Simmy::execute(unsigned number)
{
    unsigned executed = 0;
    do
    {
        // Decode
        const Instr instr = ISA::find_instrs( *opcode);
        this->decode( opcode, instr);
        
        // Take image of operands
        char operands[30];
        this->printOperands( instr, operands);

        // Execute
        (this->*( instr.exec))();

        // Trace
        char destination[20];
        this->printOp( p1, destination);
        std::printf( "%s %s %s\n", instr.name.c_str(), destination, operands);

        // Next instruction
        opcode += 5;
    }
    while ( ++executed < number);
    return reg.getValue( 0);
}
}  // namespace Simmy
