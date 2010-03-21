/**
 * core.h - Header of Core class which defines
 * fields and methods used to run the simulator
 * Copyright 2009 MDSP team
 */

#ifndef CORE_H
#define CORE_H

#include <cassert>
#include "types.h"
#include "cout_wrapper.h"

class MemoryModel;
class RegisterFileModel;
class Flags;

/**
 * Class of simulator's core description
 */
class Core
{
    hostUInt16 pc; // 16-bit program counter
    MemoryModel* memory;
    RegisterFileModel* rf;
    Flags* flags;

public:
    Core();

    /* Get methods */
    hostUInt16 GetPC() { return this->pc; }
    MemoryModel* GetMemory() { return this->memory; }
    RegisterFileModel* GetRF() { return this->rf; }
    Flags* GetFlags() { return this->flags; }

    void init( hostUInt16 start_pc);
    void run();

};

#endif /* CORE_H */

