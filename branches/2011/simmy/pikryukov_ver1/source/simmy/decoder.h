/**
 * decoder.h
 *
 * Simmy Decoder
 *
 * @author Pavel Kryukov
 * Copyright 2012 MDSP team
*/

#ifndef DECODER_H
#define DECODER_H

#include <string>

#include <simmy/executor.h>
#include <simmy/instr.h>

namespace Simmy {
class Decoder : protected Executor {
  protected:
    void decode(const BYTE* opcode, const Instr & instr);
    void printOperands(const Instr & instr, char* buf) const;
    Decoder();
    ~Decoder();
};
}

#endif