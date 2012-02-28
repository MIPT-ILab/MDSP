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

namespace Simmy
{

void Register::print( char* buf) const
{
    std::sprintf( buf, "%ux%04x", this->sign, this->value);
}

RegisterFile::RegisterFile()
{
    for ( unsigned i = 0; i < sizeof(reg) / sizeof(reg[0]); ++i) {
        this->reg[i].value = 0;
        this->reg[i].sign  = false;
    }
}

void RegisterFile::writereg( BYTE index, Register x)
{
    this->reg[index] = x;
}

Register RegisterFile::readreg( BYTE index) const
{
    return this->reg[index];
}

void RegisterFile::printreg( BYTE index, char* buf) const
{
    const Register* const printedReg = &( this->reg[index]);
    std::sprintf( buf, "r%02u(%ux%04x)", index,
        printedReg->sign, printedReg->value);
}
}