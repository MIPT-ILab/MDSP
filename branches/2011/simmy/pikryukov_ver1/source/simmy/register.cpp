/**
 * register.cpp
 *
 * Simmy register file
 *
 * @author Pavel Kryukov
 * Copyright 2012 MDSP team
*/

#include <cstdio>

#include "./register.h"

namespace Simmy {

void Register::print(char* buf) const {
    std::sprintf(buf, "%ux%04x", this->sign, this->value);
}

RegisterFile::RegisterFile() {
    for (unsigned i = 0; i < sizeof(reg) / sizeof(reg[0]); ++i) {
        reg[i].value = 0;
        reg[i].sign  = false;
    }
}

void RegisterFile::writereg(BYTE index, Register x) {
    reg[index] = x;
}

Register RegisterFile::readreg(BYTE index) const {
    return reg[index];
}

void RegisterFile::printreg(BYTE index, char* buf) const {
    char value[10];
    this->reg[index].print(value);
    std::sprintf(buf, "r%02u(%s)", index, value);
}
}