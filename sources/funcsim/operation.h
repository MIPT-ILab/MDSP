/**
* operation.h - header of Operation class,
* which defines an instruction fields
* Copyright 2009 MDSP team
*/

#ifndef OPERATION_H
#define OPERATION_H

#include <iostream>
#include <cassert>
#include "types.h"

using namespace std;

/**
* Class of operation description
*/
class Operation
{
    OperType type;
    OperCode opcode0, opcode1, opcode2; // all three opcodes needed
                                        // for ALU instruction only
    hostUInt8 am; // addressing mode field
    bool abit, rbit;
    hostUInt16 imm10, imm16;
    hostUInt8 rS1, rS2, rD;

public:
    Operation() {};

    inline OperType getType() { return this->type; }
    inline OperCode getOpcode( unsigned num)
    {
        switch ( num)
        {
            case 0:
                return this->opcode0;
            case 1:
                return this->opcode1;
            case 2:
                return this->opcode2;
            default:
                cout << "Illegal operation code number\n";
                assert(0);
        }
    }
    inline hostUInt8 getAM() { return this->am; }
    inline bool getABit() { return this->abit; }
    inline bool getRBit() { return this->rbit; }
    inline hostUInt16 getImm10() { return this->imm10; }
    inline hostUInt16 getImm16() { return this->imm16; }
    inline hostUInt8 getSReg1() { return this->rS1; }
    inline hostUInt8 getSReg2() { return this->rS2; }
    inline hostUInt8 getDReg() { return this->rD; }

    inline void clear()
    {
        this->type = NO_TYPE;
        this->opcode0 = this->opcode1 = this->opcode2 = NOP;
        this->am = 0;
        this->abit = this->rbit = 0;
        this->imm10 = this->imm16 = 0x0000;
        this->rS1 = this->rS2 = this->rD = 0;
    }

    void set( OperType type, OperCode opcode0, OperCode opcode1, OperCode opcode2,
              hostUInt8 am, bool abit, bool rbit, 
              hostUInt16 imm10, hostUInt16 imm16,
              hostUInt8 rS1, hostUInt8 rS2, hostUInt8 rD);
    
    void set( OperType type, OperCode opcode0, 
              hostUInt16 imm16, 
              hostUInt8 rS1, hostUInt8 rD);

    void encode();
    void decode();
    void dump();

};

#endif

