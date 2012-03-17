/**
 * isa.h
 *
 * Simmy ISA
 *
 * @author Pavel Kryukov
 * Copyright 2012 MDSP team
*/

#ifndef ISA_H
#define ISA_H

#include <simmy/types.h>
#include <simmy/instr.h>

namespace Simmy
{

class ISA
{
private:
    static const Instr instrs[];
    static const size_t instrs_s;
public:
    static Instr find_instrs( BYTE opcode);
};
}

#endif
