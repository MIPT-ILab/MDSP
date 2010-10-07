/**
 * core.h - Header of Core class which defines
 * fields and methods used to run the simulator
 * Copyright 2009 MDSP team
 */

#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <cassert>
#include "types.h"

class RegisterFileModel;
class Flags;

class Core
{
    hostUInt16 pc; // program counter
    RegisterFileModel* rf;
    Flags* flags;

public:
    Core() {};

    /* Get methods */
    hostUInt16 GetPC() { return this->pc; }
    RegisterFileModel* GetRF() { return this->rf; }
    Flags* GetFlags() { return this->flags; }

    void init( hostUInt16 start_pc);
    void run();

};

#endif /* CORE_H */
