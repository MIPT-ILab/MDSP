/**
 * simmy.h
 *
 * Simmy core header
 *
 * @author Pavel Kryukov
 * Copyright 2012 MDSP team
*/

#ifndef CORE_H
#define CORE_H

#include "./types.h"
#include "./decoder.h"

namespace Simmy
{

class Simmy : private Decoder
{
private:
    const BYTE* opcode;
public:
    inline Simmy( const BYTE* bytes) : Decoder(), opcode( bytes) {}
    int execute( unsigned number);
};
}

#endif
