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

#include <simmy/types.h>
#include <simmy/decoder.h>

namespace Simmy {
class Simmy : private Decoder {
  private:
    BYTE* opcode;
  public:
    Simmy(BYTE* bytes);
    ~Simmy();
    void execute(unsigned number);
};
}

#endif
