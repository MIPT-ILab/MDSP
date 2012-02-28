/**
 * isa.cpp
 *
 * Simmy ISA
 *
 * @author Pavel Kryukov
 * Copyright 2012 MDSP team
*/

#include <cassert>

#include <simmy/executor.h>

#include "./isa.h"

namespace Simmy {
const Instr ISA::instrs[] = {
    // Logical binary instructions
    {"and ", 0x01, Instr::T_BIN, &Executor::f_and },
    {"or  ", 0x02, Instr::T_BIN, &Executor::f_or  },
    {"xor ", 0x03, Instr::T_BIN, &Executor::f_xor },
    // Arithmetical binary instructions
    {"add ", 0x82, Instr::T_BIN, &Executor::f_add },
    {"sub ", 0x83, Instr::T_BIN, &Executor::f_sub },
    {"mul ", 0x81, Instr::T_BIN, &Executor::f_mul },
    {"div ", 0x80, Instr::T_BIN, &Executor::f_div },
    {"mov ", 0x84, Instr::T_BIN, &Executor::f_mov },
    // Logical unary instruction
    {"not ", 0x44, Instr::T_UNR, &Executor::f_not },
    // Arithmetival unary instructions
    {"dec ", 0xC0, Instr::T_UNR, &Executor::f_dec },
    {"inc ", 0xC1, Instr::T_UNR, &Executor::f_inc },    
    {"ssgn", 0xC2, Instr::T_SGN, &Executor::f_ssgn},
    {"isgn", 0xC3, Instr::T_UNR, &Executor::f_isgn},
};

const size_t ISA::instrs_s = sizeof(instrs) / sizeof(instrs[0]);
const bool ISA::table_f = init_table();
signed ISA::table[(BYTE)~1] = {0};

bool ISA::init_table() {
    BYTE maxBYTE = ~1;
    for (BYTE opcode = 0; opcode < maxBYTE; ++opcode) {
        table[opcode] = -1;
        for (unsigned i = 0; i < ISA::instrs_s; i++) {
            if (ISA::instrs[i].code == opcode) {
                table[opcode] = i;
                break;
            }
        }
    }
    return true;
}

Instr ISA::find_instrs(BYTE opcode) {
    if (table[opcode] == -1) {
        assert(0);
    }
    return instrs[table[opcode]];
}
}