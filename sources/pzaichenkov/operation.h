/**
 * operation.h - Header of Operation class,
 * which defines an instruction fields
 * Copyright 2009 MDSP team
 */

#ifndef OPERATION_H
#define OPERATION_H

#include <iostream>
#include <cassert>
#include "types.h"
#include "memory.h"

using namespace std;

/**
 * Class of operation description
 */
class Operation
{
    OperType type;
    OperCode opcode0, opcode1, opcode2; // all 3 opcodes are needed for ALU only

    /* bit fields are used for memory saving */
    hostUInt8 sd:2; // S/D field
    hostUInt8 am:3; // addressing mode field
    hostUInt16 imm10:10;
    hostUInt16 imm16;
    hostUInt8 rs1:5, rs2:5, rd:5;

    /* get type */
    OperType decodeType( hostUInt32 bin_value);

    /* methods used for each type */
    void decodeMOVE( hostUInt32 bin_value);
    void decodeALU( hostUInt32 bin_value);
    void decodePFLOW( hostUInt32 bin_value);

    void setMOVE( OperCode opcode0,
                  hostUInt8 sd,
                  hostUInt16 imm16,
                  hostUInt8 rs1,
                  hostUInt8 rd);
    void setALU( OperCode opcode0,
                 OperCode opcode1,
                 OperCode opcode2,
                 hostUInt8 am,
                 hostUInt8 rs1,
                 hostUInt8 rs2,
                 hostUInt8 rd);

    void setPFLOW( OperCode opcode0,
                   hostUInt8 sd,
                   hostUInt8 rd,
                   hostUInt16 imm16);

    void dumpMOVE();
    void dumpALU();
    void dumpPFLOW();
    
    /* Helper methods */
    hostUInt32 getInstrWord( MemVal* mem_value);
    hostUInt32 getValueByMask( hostUInt32 bin_value, hostUInt32 mask, int shift);


public:
    Operation();

    /* Get methods */
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
    inline hostUInt8 getSD() { return this->sd; }
    inline hostUInt16 getImm10() { return this->imm10; }
    inline hostUInt16 getImm16() { return this->imm16; }
    inline hostUInt8 getSReg1() { return this->rs1; }
    inline hostUInt8 getSReg2() { return this->rs2; }
    inline hostUInt8 getDReg() { return this->rd; }
    
    /* Set methods */
    inline void setType( OperType type) { this->type = type; }
    inline void setOpcode( unsigned num, OperCode opcode)
    {
        switch ( num)
        {
            case 0:
                this->opcode0 = opcode;
                break;
            case 1:
                this->opcode1 = opcode;
                break;
            case 2:
                this->opcode2 = opcode;
                break;
            default:
                cout << "Illegal operation code number\n";
                assert(0);
        }
    }
    inline void setSD( hostUInt8 sd) { this->sd = sd; }
    inline void setAM( hostUInt8 am) { this->am = am; }
    inline void setImm10( hostUInt16 imm10) { this->imm10 = imm10; }
    inline void setImm16( hostUInt16 imm16) { this->imm16 = imm16; }
    inline void setSReg1( hostUInt8 rs1) { this->rs1 = rs1; }
    inline void setSReg2( hostUInt8 rs2) { this->rs2 = rs2; }
    inline void setDReg( hostUInt8 rd) { this->rd = rd; }

    inline void clear()
    {
        this->type = NO_TYPE;
        this->opcode0 = this->opcode1 = this->opcode2 = NOP;
        this->sd = this->am = 0;
        this->imm10 = this->imm16 = 0;
        this->rs1 = this->rs2 = this->rd = 0;
    }

    void set( OperType type, OperCode opcode0, OperCode opcode1, OperCode opcode2,
              hostUInt8 sd, hostUInt8 am, 
              hostUInt16 imm10, hostUInt16 imm16,
              hostUInt8 rs1, hostUInt8 rs2, hostUInt8 rd);

    MemVal* encode();
    void decode( MemVal* mem_value);
    void dump();

};

#endif

