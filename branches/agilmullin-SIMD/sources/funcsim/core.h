/**
 * core.h - Header of Core class which defines
 * fields and methods used to run the simulator
 * @author Pavel Zaichenkov
 * Copyright 2009 MDSP team
 */

#ifndef CORE_H
#define CORE_H

#include <cassert>
#include <fstream>

#include "log.h"
#include "types.h"

class MemoryModel;
class RegisterFileModel;
class Flags;

using namespace std;

/**
 * Class of simulator's core description
 */
class Core : public log
{
    hostUInt16 pc; // 16-bit program counter
    MemoryModel* memory;
    RegisterFileModel* rf;
    Flags* flags;
    bool stop; // shows if instruction execution is stopped
    bool disasmPrint;

public:
    Core();

    /* Get methods */
    inline hostUInt16 GetPC() { return this->pc; }
    inline MemoryModel* GetMemory() { return this->memory; }
    inline RegisterFileModel* GetRF() { return this->rf; }
    inline Flags* GetFlags() { return this->flags; }
    inline bool GetStop() { return this->stop; }
    inline void setDisasmPrint( bool value) { this->disasmPrint = value; } 



    void init( hostUInt16 start_pc);
    int loadBinary ( ifstream& input);

    hostUInt64 run( hostUInt64 requested );


    void Stop() { this->stop = true; }   // stop instruction execution
    void Start() { this->stop = false; } // start instruction execution
};

#endif /* CORE_H */

