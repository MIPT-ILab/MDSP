/**
 * register.h
 *
 * Simmy register file
 *
 * @author Pavel Kryukov
 * Copyright 2012 MDSP team
*/

#ifndef REGISTER_H
#define REGISTER_H

#include <string>

#include <simmy/types.h>

namespace Simmy
{

struct Register
{
    bool sign;
    WORD value;
    inline Register() : sign(false), value(0x00) {}
    inline Register( bool sign_, WORD value_) : sign( sign_), value( value_) {}
    Register(SDWORD number);
    SDWORD sdword() const;
    void print( char* buf) const;
};

class RegisterFile
{
    Register reg[16];
public:
    RegisterFile();

    void writereg( BYTE index, Register x);
    Register readreg( BYTE index) const;
    void printreg( BYTE index, char* buf) const;
};
}

#endif
