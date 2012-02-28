/**
 * simmy.cpp
 *
 * Simmy core
 *
 * @author Pavel Kryukov
 * Copyright 2012 MDSP team
*/

#include <cstdio>

#include <simmy/types.h>
#include <simmy/isa.h>
#include <simmy/instr.h>

#include "./simmy.h"

namespace Simmy {

Simmy::Simmy(BYTE* bytes) : Decoder(), opcode(bytes) {}
Simmy::~Simmy() {}

void Simmy::execute(unsigned number) {
    unsigned executed = 0;
    do {
        // Decode
        const Instr instr = ISA::find_instrs(*opcode);
        this->decode(opcode, instr);

        char operands[30];
        this->printOperands(instr, operands);

        (this->*(instr.exec))();

        char destination[20];
        this->printOp(p1, destination);

        std::printf("%s %s %s\n", instr.name.c_str(), destination, operands);

        opcode += 5;
        ++executed;
    }
    while (executed < number);
}
}  // namespace Simmy
