/**
* operation.cpp - Implementation of Operation class methods
* Copyright 2009 MDSP team
*/

#include "operation.h"

/**
* Constructor - Fill with zeros
*/

Operation::Operation()
{
    type    = NO_TYPE;
    opcode0 = NOP;
    opcode1 = NOP;
    opcode2 = NOP;
    sd      = 0;
    am      = 0;
    imm10   = 0;
    imm16   = 0;
    rs1     = 0;
    rs2     = 0;
    rd      = 0;
}
/**
* Set any operation
*/
void Operation::set( OperType type, OperCode opcode0, OperCode opcode1, OperCode opcode2,
                     hostUInt8 sd, hostUInt8 am, 
                     hostUInt16 imm10, hostUInt16 imm16,
                     hostUInt8 rs1, hostUInt8 rs2, hostUInt8 rd)
{
    this->type      = type;
    this->opcode0   = opcode0;
    this->opcode1   = opcode1;
    this->opcode2   = opcode2;
    this->sd        = sd;
    this->am        = am;
    this->imm10     = imm10;
    this->imm16     = imm16;
    this->rs1       = rs1;
    this->rs2       = rs2;
    this->rd        = rd;
}

/**
* Set an operation of MOVE type
*/
void Operation::set( OperType type, OperCode opcode0, 
                     hostUInt16 imm16, 
                     hostUInt8 rs1, hostUInt8 rd)
{
    this->type      = type;
    this->opcode0   = opcode0;
    this->imm16     = imm16;
    this->rs1       = rs1;
    this->rd        = rd;
}

/**
 * Get 4B value from MemVal
*/
hostUInt32 Operation::getMemoryValue(MemVal* mem_value)
{
    hostUInt32 value = 0;
    hostUInt8 temp = 0;
    for (int i = 0; i < 4; i++)
    {
        temp += mem_value->getByteVal(i);
        value += temp;
        value = value << 8;
    }
    return value;
}

/**
* Encode operation in binary form
*/
MemVal* Operation::encode()
{
    MemVal* mem_value = new MemVal(4); // pointer to 32-bit (4 bytes) instruction word

    return mem_value;
}

/**
* Decode an operation from binary form
*/
void Operation::decode( MemVal* mem_value)
{
    hostUInt32 bin_value = getMemoryValue(mem_value);
    /* we need to decode the type first to know how to decode further */
    this->type = decodeType(bin_value);
    /* choose decode type */
     switch ( this->type )
     {
            case MOVE:
                decodeMove(bin_value);
            case ALU:
                decodeAlu(bin_value);
                /* In this place we must update flags */
            case P_FLOW:
                decodePFlow(bin_value);
            default:
                cout << "Illegal type \n";
                assert(0);
     }
}

/**
* Decode Type value from binary form
*/
OperType Operation::decodeType(hostUInt32 bin_value)
{
    /* get value using the mask */
    hostUInt32 type_mask = 0xE0000000; // 11100000 bin, 224 dec
    OperType type = (OperType) (type_mask & bin_value);
    return type;
}

/**
* Decode MOVE command from binary form
*/
void Operation::decodeMove(hostUInt32 bin_value)
{
    /* skip type decoding as we already know the type */

    hostUInt32    op_mask = 0x1C000000; // OP mask
    hostUInt32    sd_mask = 0x00600000; // S/D mask
    hostUInt32    rs_mask = 0x000003E0; // RS mask
    hostUInt32    rd_mask = 0x0000001F; // RD mask
    hostUInt32 imm16_mask = 0x001FFFE0; // imm16 mask

    /* get OP */
    opcode0 = (OperCode) (op_mask & bin_value);

    switch (opcode0)
    {
            case BRM:
                sd = sd_mask & bin_value;       // get S/D
                rs1 = rs_mask & bin_value;      // get source
                rd = rd_mask & bin_value;       // get desitination
                break;
            case BRR:
                rs1 = rs_mask & bin_value;      // get source
                rd = rd_mask & bin_value;       // get desitination
                break;
            case LD:
                imm16 = imm16_mask & bin_value; // get imm16
                rd = rd_mask & bin_value;       // get desitination
                break;
            default:
                cout << "Illegal operation \n";
                assert(0);
    }
}

/**
* Decode ALU command from binary form
*/
void Operation::decodeAlu(hostUInt32 bin_value)
{
    /* skip type decoding as we already know the type */

    hostUInt32    logic_op_mask = 0x1C000000; // Logic OP mask
    hostUInt32    arith_op_mask = 0x03E00000; // Arithmetic OP mask
    hostUInt32    shift_op_mask = 0x001C0000; // Shift OP mask
    hostUInt32          am_mask = 0x00038000; // AM mask
    hostUInt32         rs1_mask = 0x00007C00; // RS1 mask
    hostUInt32         rs2_mask = 0x000003E0; // RS2 mask
    hostUInt32          rd_mask = 0x0000001F; // RD mask

    opcode0 = (OperCode) (logic_op_mask & bin_value);
    opcode1 = (OperCode) (arith_op_mask & bin_value);
    opcode2 = (OperCode) (shift_op_mask & bin_value);
    am = am_mask & bin_value;
    rs1 = rs1_mask & bin_value;
    rs2 = rs2_mask & bin_value;
    rd = rd_mask & bin_value;
}

/**
* Decode P_FLOW command from binary form
*/
void Operation::decodePFlow(hostUInt32 bin_value)
{
    /* skip type decoding as we already know the type */

    hostUInt32       op_mask = 0x1E000000; // OP mask
    hostUInt32       sd_mask = 0x00C00000; // SD mask
    hostUInt32    imm16_mask = 0x0000FFFF; // imm16 mask
    hostUInt32       rd_mask = 0x0000001F; // RD mask

    opcode0 = (OperCode) (op_mask & bin_value);
    sd = sd_mask & bin_value;
    if (!sd)
        rd = rd_mask & bin_value;
    else
        imm16 = imm16_mask & bin_value;
}

/*
* Print an operation to console
*/
void Operation::dump()
{
    cout << "--- Operation start ---" << endl;
    cout << "   TYPE: " <<    type << endl;
    cout << "OPCODE0: " << opcode0 << endl;
    cout << "OPCODE1: " << opcode1 << endl;
    cout << "OPCODE2: " << opcode2 << endl;
    cout << "     SD: " <<      sd << endl;
    cout << "     AM: " <<      am << endl;
    cout << "  IMM10: " <<   imm10 << endl;
    cout << "  IMM16: " <<   imm16 << endl;
    cout << "    RS1: " <<     rs1 << endl;
    cout << "    RS2: " <<     rs2 << endl;
    cout << "     RD: " <<      rd << endl;
    cout << "---  Operation end  ---" << endl;
}