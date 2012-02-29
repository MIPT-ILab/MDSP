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

Register::Register( SDWORD number)
{
    this->sign  = number >= 0;
    this->value = this->sign ? (WORD)number : (WORD)(-number);
}

SDWORD Register::sdword() const {
    return this->sign ? this->value : -(this->value);
}

void Register::print( char* buf) const
{
    std::sprintf( buf, "%c%04x", this->sign ? ' ' : '-', this->value);
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
    std::sprintf( buf, "r%02u(%c%04x)", index,
        printedReg->sign ? ' ' : '-', printedReg->value);
}
}