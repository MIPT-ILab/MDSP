/**
 * instr.h
 *
 * Simmy Instruction class
 *
 * @author Pavel Kryukov
 * Copyright 2012 MDSP team
*/

#ifndef INSTR_H
#define INSTR_H

#include <string>

#include "./types.h"
#include "./executor.h"

namespace Simmy
{

struct Instr
{
    std::string name;
    BYTE code;
    enum
    {
        T_BIN,
        T_UNR,
        T_SGN,
        T_NON,
    } type;
    void (Executor::*exec)();
};

}

#endif
