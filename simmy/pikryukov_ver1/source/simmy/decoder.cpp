/**
 * decoder.cpp
 *
 * Simmy Decoder
 *
 * @author Pavel Kryukov
 * Copyright 2012 MDSP team
*/

#include <cstdio>

#include "./decoder.h"

namespace Simmy {
void Decoder::decode(const BYTE * opcode, const Instr & instr) {
    p1.type  = Executor::Operand::REGISTER;
    p1.index = *(opcode + 2);
    switch (instr.type) {
        case Instr::T_BIN:
            if (*(opcode + 1) & (1 << 2)) {
                p2.type  = Executor::Operand::CONSTANT;
                p2.constant.value = (*(opcode + 4) << 8)  + *(opcode + 3);
                p2.constant.sign  = (*(opcode + 1) >> 3) & 1;
            }
            else {
                p2.type  = Executor::Operand::REGISTER;
                p2.index = *(opcode + 3);
            }
            break;
         case Instr::T_SGN:
            p2.type  = Executor::Operand::CONSTANT;
            p2.constant.sign  = (*(opcode + 1) >> 3) & 1;
            break;
        case Instr::T_UNR:
        default:
            break;
    }
}

void Decoder::printOperands(const Instr & instr, char* buf) const {
    char buf1[20];
    char buf2[20];
    this->printOp(p1, buf1);
    this->printOp(p2, buf2);
    switch (instr.type) {
        case Instr::T_BIN:
            std::sprintf(buf, "= %s %s", buf1, buf2);
            break;
         case Instr::T_SGN:
            std::sprintf(buf, "= %d, %s", p2.constant.sign, buf1);
            break;
        case Instr::T_UNR:
            std::sprintf(buf, "= %s", buf1);
            break;
        default:
            break;
    }
}

}