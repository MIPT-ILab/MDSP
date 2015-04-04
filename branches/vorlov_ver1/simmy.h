/**
 * Simmy.h
 * @author Orlov Vasiliy
 * Copyright 2011 MDSP team
 */

#ifndef SIMMY_H_
#define SIMMY_H_

#include <iostream>
#include "types.h"

using namespace std;

class Simmy
{  
    hostUInt8* instr_addr; // address of current instruction
    hostUInt8 reg; // register which rewrites in current instruction
    hostUInt16 r[16]; // register file
    hostSInt8 r_sign[16]; // signes of registers
    hostUInt8 opcode; // opcode of current insruction
    hostUInt16 op1; // operand 1 of current insruction
    hostUInt16 op2; // operand 2 of current insruction
    hostSInt8 op1_sign; // sign og operand 1
    hostSInt8 op2_sign; // sign of operand 2
    bool bit2; // bit #2 in concrol byte
    
    void decodeInstr(); // decode 5 byte sequence to usable variables
    void executeInstr(); // execute current instruction
public:
    Simmy( hostUInt8* bytes, hostUInt32 lenght); //gets byte sequence
    
    /* execute certain number of instructions
     * returns value of r0
     */
    hostSInt32 execute ( hostUInt32 number_of_instrs);
};
#endif