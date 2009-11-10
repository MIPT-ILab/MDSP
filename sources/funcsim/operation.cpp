/**
 * operation.cpp - Implementation of Operation class methods
 * Copyright 2009 MDSP team
 */

#include <iostream>

#include "operation.h"
#include "register_file.h"
#include "flags.h"

/**
 * Constructor with pointer to core. Pointer to core
 * is needed to access main structures (RF, flags, PC) of simulator.
 */
Operation::Operation( Core *core)
{
    this->core = core;
    this->clear();
}

/**
 * Default constructor
 */
Operation::Operation()
{
    this->clear();
}

/**
 * Set any operation
 */
void Operation::set( OperType type, OperCode opcode0, OperCode opcode1, OperCode opcode2,
                     hostUInt8 sd, hostUInt8 am, 
                     hostUInt16 imm10, hostUInt16 imm16,
                     hostUInt8 rs1, hostUInt8 rs2, hostUInt8 rd)
{
    switch ( type)
    {
        case MOVE:
            if ( am)
            {
                cout << "AM has to be set to 0 in MOVE\n";
            }
            if ( imm10)
            {
                cout << "Imm10 has to be set to 0 in MOVE\n";
            }
            if ( rs2)
            {
                cout << "Rs2 has to be set to 0 in MOVE\n";
            }
            if ( opcode1)
            {
                cout << "OpCode1 has to be set to 0 in MOVE\n";
            }
            if ( opcode2)
            {
                cout << "OpCode2 has to be set to 0 in MOVE\n";
            }
            this->set( MOVE, opcode0, sd, imm16, rs1, rd);
            break;
        case ALU:
            if ( sd)
            {
                cout << "SD has to be set to 0 in ALU\n";
            }
            if ( imm10)
            {
                cout << "Imm10 has to be set to 0 in ALU\n";
            }
            if ( imm16)
            {
                cout << "Imm16 has to be set to 0 in ALU\n";
            }
            this->set( ALU, opcode0, opcode1, opcode2, am, rs1, rs2, rd);
            break;
        case P_FLOW:
            if ( am)
            {
                cout << "AM has to be set to 0 in P_FLOW\n";
            }
            if ( imm10)
            {
                cout << "Imm10 has to be set to 0 in P_FLOW\n";
            }
            if ( rs1)
            {
                cout << "Rs1 has to be set to 0 in P_FLOW\n";
            }
            if ( rs2)
            {
                cout << "Rs2 has to be set to 0 in P_FLOW\n";
            }
            if ( opcode1)
            {
                cout << "OpCode1 has to be set to 0 in P_FLOW\n";
            }
            if ( opcode2)
            {
                cout << "OpCode2 has to be set to 0 in P_FLOW\n";
            }
            this->set( P_FLOW, opcode0, sd, rd, imm16);
            break;
        default:
            cout << "Illegal Type in set method\n";
            assert( 0);
    }
    this->type = type;
}

/*
 * Method defines the correlation between OperType and hostUInt32
 */
OperType Operation::getTypeFromInt32( hostUInt32 type)
{
    switch ( type)
    {
        default:
            printf( "Unknown operation type encoded in %x number\n", type);
            assert( 0);
        case 0:
            return MOVE;
        case 1:
            return ALU;
        case 2:
            return MAC;
        case 3:
            return DMAC;
        case 4:
            return SIMD;
        case 5:
            return P_FLOW;
    }
}

/*
 * Method defines the correlation between OperCode and hostUInt32
 */
OperCode Operation::getCodeFromInt32( OperType type, hostUInt32 code)
{  
    switch ( type)
    {
        case MOVE:
            switch ( code)
            {
                case 0:
                    return NOP;
                case 1:
                    return BRM;
                case 3:
                    return BRR;
                case 6:
                    return LD;
                default:
                    cout << "Illegal operation in MOVE\n";
                    assert( 0);
                    return NOP;
            }
            break;
        case ALU:
            switch ( code)
            {
                case 0:
                    return NOP;
                case 1:
                    return ADD;
                case 2:
                    return SUB;
                default:
                    cout << "Illegal operation in MOVE\n";
                    assert( 0);
                    return NOP;
            }
            break;
        case P_FLOW:
            switch ( code)
            {
                case 0:
                    return JMP;
                case 1:
                    return JGT;
                default:
                    cout << "Illegal operation in MOVE\n";
                    assert( 0);
                    return NOP;
            }
            break;
        default:
            cout << "Invalid operation type\n";
            assert( 0);
            return NOP;
    }
}


/**
 * Set an operation of MOVE type
 */
void Operation::set( OperType type,
                     OperCode opcode0,
                     hostUInt8 sd,
                     hostUInt16 imm16,
                     hostUInt8 rs1,
                     hostUInt8 rd)
{
    if ( type == MOVE)
    {
        /* get OP */
        this->opcode0 = opcode0;

        switch ( opcode0)
        {
            case BRM:
                this->sd = sd;          // get S/D
                this->rs1 = rs1;        // get source
                this->rd = rd;          // get desitination
                if ( imm16)
                {
                    cout << "Imm16 has to be set to 0 in BRM\n";
                }
                break;
            case BRR:
                this->rs1 = rs1;        // get source
                this->rd = rd;          // get desitination
                if ( imm16)
                {
                    cout << "Imm16 has to be set to 0 in BRR\n";
                }
                if ( sd)
                {
                    cout << "SD has to be set to 0 in BRR\n";
                }
                break;
            case LD:
                this->imm16 = imm16;    // get source
                this->rd = rd;          // get desitination
                if ( rs1)
                {
                    cout << "Rs1 has to be set to 0 in LD\n";
                }
                if ( rs2)
                {
                    cout << "Rs2 has to be set to 0 in LD\n";
                }
                if ( sd)
                {
                    cout << "SD has to be set to 0 in LD\n";
                }
                break;
            default:
                cout << "Illegal operation code in MOVE\n";
                assert( 0);
        }
    }
    else
    {
        cout << "Unknown type is set (need MOVE type)\n";
    }
}

/**
 * Set an operation of ALU type
 */
void Operation::set( OperType type,
                     OperCode opcode0,
                     OperCode opcode1,
                     OperCode opcode2,
                     hostUInt8 am,
                     hostUInt8 rs1, 
                     hostUInt8 rs2, 
                     hostUInt8 rd)
{
    if ( type == ALU)
    {
        this->opcode0 = opcode0;
        this->opcode1 = opcode1;
        this->opcode2 = opcode2;
        this->am      = am;
        this->rs1     = rs1;
        this->rs2     = rs2;
        this->rd      = rd;
    }
    else
    {
        cout << "Unknown type is set (need ALU type)\n";
    }
}

/**
 * Set an operation of PFLOW type
 */
void Operation::set( OperType type,
                     OperCode opcode0,
                     hostUInt8 sd,
                     hostUInt8 rd,
                     hostUInt16 imm16)
{
    if ( type == P_FLOW)
    {
        this->opcode0 = opcode0;
        this->sd = sd;
        if ( !sd)
        {
            this->rd = rd;
            if ( imm16)
            {
                cout << "Imm16 has to be set to 0 in P_FLOW\n";
            }
        }
        else
        {
            this->imm16 = imm16;
            if ( rd)
            {
                cout << "Rd has to be set to 0 in P_FLOW\n";
            }
        }
    }
    else
    {
        cout << "Unknown type is set (need MOVE type)";
    }
}

/*
 * Print MOVE operation to the console
 * NOTE: printf is used here, because "cout <<" doesn't work properly with some types
 */
void Operation::dumpMOVE()
{
    switch ( this->opcode0)
    {
        case BRM:
            printf( "brm %i, r%i, r%i;\n", this->sd, this->rs1, this->rd);
            break;
        case BRR:
            printf( "brr r%i, r%i;\n", this->rs1, this->rd);
            break;
        case LD:
            printf( "ld %i, r%i, r%i;\n", this->sd, this->imm16, this->rd);
            break;
        default:
            cout << "Operation code is invalid in MOVE\n";
            assert( 0);
    }
}

/*
 * Print ALU operation to the console
 * NOTE: printf is used here, because "cout <<" doesn't work properly with some types
 */
void Operation::dumpALU()
{
    switch ( this->opcode1)
    {
        case ADD:
            printf( "add %i, r%i, r%i, r%i;\n", this->am, this->rs1, this-> rs2, this->rd);
            break;
        case SUB:
            printf( "sub %i, r%i, r%i, r%i;\n", this->am, this->rs1, this-> rs2, this->rd);
            break;
        default:
            cout << "Operation code is invalid in ALU\n";
            assert(0);
    }
}

/*
 * Print P_FLOW operation to the console
 * NOTE: printf is used here, because "cout <<" doesn't work properly with some types
 */
void Operation::dumpPFLOW()
{
    /* As in these operations an argument can be either Rd or Imm16 we use this variable */
    hostUInt16 temp;
    if ( !this->sd)
    {
        temp = this->rd;
    }
    else
    {
        temp = this->imm16;
    }
    switch ( this->opcode0)
    {
        case JMP:
            printf( "jmp %i, r%i;\n", this->sd, temp);
            break;
        case JGT:
            printf( "jgt %i, r%i;\n", this->sd, temp);
            break;
        default:
            cout << "Operation code is invalid in ALU\n";
            assert(0);
    }
}

/**
 * Get 4 Byte value from MemVal
 *
 * We have the part of memory of the type "MemVal".
 * The task is to convert "MemVal" to a standart hostUInt32.
 * In this way, it is quite easy to deal with bitwise operators.
 *
 * WARNING: This method gets ONLY the first 4 bytes from MemVal.
 * To prevent some misunderstandings we have to avoid using this method
 * with MemVal's whose size is not equals 4 bytes.
 *
 * May be it is better to implement this method in MemVal class.
 */
void Operation::setInstrWord( MemVal* mem_value)
{
    /* Perform check for MemVal's size. Should be 4 bytes */
    if ( mem_value->getSizeOfMemVal() != 4)
    {
        cout << "Size of MemVal must be 4 bytes\n";
        assert(0);
    }
    
    hostUInt32 value = 0;   // returned value
    hostUInt8 temp = 0;     // temporary variable
    for ( int i = 0; i < 4; i++) // we are confident that MemVal's size is 4 bytes
    {
        temp += mem_value->getByteVal( i);
        value += temp;
        value = value << 8; // move byte to the older rank
    }
    this->instr_word = value;
}

/*
 * Set memory block from instruction word (binary representation)
 */
void Operation::setMemBlock( MemVal* mem_value)
{
}

/**
 * Get Value from memory by mask and shift (bitwise operators)
 * EXAMPLE:
 * instr_word = 101010001001001001010010110111 (32-bit number)
 * mask       = 111000000000000000000000000000 (Let's get first 3 bits.
 *                                             Type value in our case)
 * temp = instr_word & mask =                  (Bitwise operator AND)
 *              101000000000000000000000000000
 * temp >> shift =                            (In this case SHIFT must be 29)
 *              000000000000000000000000000101
 * Finally, we've got 101 number. It is P_FLOW type!
 */
hostUInt32 Operation::getValueByMask( hostUInt32 mask, int shift)
{
    hostUInt32 temp = this->instr_word & mask;
    temp = temp >> shift;
    return temp;
}

/**
 * Encode operation in binary form
 */
MemVal* Operation::encode()
{
/*
    MemVal* mem_value = new MemVal(4); // pointer to 32-bit (4 bytes) instruction word

    return mem_value;
*/
    return NULL; // delete it later
}


/**
 * Decode an operation from binary form
 */
void Operation::decode( MemVal* mem_value)
{
    this->setInstrWord( mem_value);
    /* we need to decode the type (MOVE, ALU, etc) first to know how to decode further */
    this->type = this->decodeType();
    
    /* 
     * Choose decode type. It's important to implement it's 
     * own decode methode for each command type
     */
    switch ( this->type)
    {
        case MOVE:
            this->decodeMOVE();
            break;
        case ALU:
            this->decodeALU();
            break;
        case P_FLOW:
            this->decodePFLOW();
            break;
        default:
            cout << "Illegal type in decode()\n";
            assert( 0);
     }
}

/**
 * Decode Type value from binary form
 * Here we use
 * mask = 1110000000000000000000000000000 and
 * shift = 29 to get type value (the elderest 3-bits)
 */
OperType Operation::decodeType()
{
    /* get value using the mask */
    hostUInt32 type_mask = 0xE0000000; // 11100000 bin, 224 dec
    OperType type = this->getTypeFromInt32( this->getValueByMask( type_mask, 29));
    return type;
}

/**
 * Decode MOVE command from binary form
 * All mask are set as it is described in architecture.
 */
void Operation::decodeMOVE()
{
    /* skip type decoding as we already know the type */

    hostUInt32    op_mask = 0x1C000000; // OP mask
    hostUInt32    sd_mask = 0x00600000; // S/D mask
    hostUInt32    rs_mask = 0x000003E0; // RS mask
    hostUInt32    rd_mask = 0x0000001F; // RD mask
    hostUInt32 imm16_mask = 0x001FFFE0; // imm16 mask

    /* temporary fields */
    OperCode opcode0;
    hostUInt8 sd, rs1, rd;
    hostUInt16 imm16;

    /* get OP */
    opcode0 = this->getCodeFromInt32( MOVE, this->getValueByMask( op_mask, 26));

    switch ( opcode0)
    {
        case BRM:
            sd = this->getValueByMask( sd_mask, 21);     // get S/D
            rs1 = this->getValueByMask( rs_mask, 5);     // get source
            rd = this->getValueByMask( rd_mask, 0);      // get desitination
            break;
        case BRR:
            rs1 = this->getValueByMask( rs_mask, 5);     // get source
            rd = this->getValueByMask( rd_mask, 0);      // get desitination
            break;
        case LD:
            imm16 = this->getValueByMask( imm16_mask, 5);// get imm16
            rd = this->getValueByMask( sd_mask, 0);      // get desitination
            break;
        default:
            cout << "Illegal operation in MOVE\n";
            assert( 0);
    }
    this->set( MOVE, opcode0, sd, imm16, rs1, rd);
}

/**
 * Decode ALU command from binary form
 * All mask are set as it is described in architecture.
 */
void Operation::decodeALU()
{
    /* skip type decoding as we already know the type */

    hostUInt32    logic_op_mask = 0x1C000000; // Logic OP mask
    hostUInt32    arith_op_mask = 0x03E00000; // Arithmetic OP mask
    hostUInt32    shift_op_mask = 0x001C0000; // Shift OP mask
    hostUInt32          am_mask = 0x00038000; // AM mask
    hostUInt32         rs1_mask = 0x00007C00; // RS1 mask
    hostUInt32         rs2_mask = 0x000003E0; // RS2 mask
    hostUInt32          rd_mask = 0x0000001F; // RD mask

    /* temporary fields */
    OperCode opcode0, opcode1, opcode2;
    hostUInt8 am, rs1, rs2, rd;

    opcode0 = this->getCodeFromInt32( ALU, this->getValueByMask( logic_op_mask, 26));
    opcode1 = this->getCodeFromInt32( ALU, this->getValueByMask( arith_op_mask, 21));
    opcode2 = this->getCodeFromInt32( ALU, this->getValueByMask( shift_op_mask, 18));
    am = this->getValueByMask( am_mask, 15);
    rs1 = this->getValueByMask( rs1_mask, 10);
    rs2 = this->getValueByMask( rs2_mask, 5);
    rd = this->getValueByMask( rd_mask, 0);
    this->set( ALU, opcode0, opcode1, opcode2, am, rs1, rs2, rd);
}

/**
 * Decode P_FLOW command from binary form
 * All mask are set as it is described in architecture.
 */
void Operation::decodePFLOW()
{
    /* skip type decoding as we already know the type */

    hostUInt32       op_mask = 0x1E000000; // OP mask
    hostUInt32       sd_mask = 0x00C00000; // SD mask
    hostUInt32    imm16_mask = 0x0000FFFF; // imm16 mask
    hostUInt32       rd_mask = 0x0000001F; // RD mask

    /* temporary fields */
    OperCode opcode0;
    hostUInt8 sd, rd;
    hostUInt16 imm16;
    
    opcode0 = this->getCodeFromInt32( P_FLOW, this->getValueByMask( op_mask, 25));
    sd = this->getValueByMask( sd_mask, 23);

    if ( !sd)
    {
        rd = this->getValueByMask( rd_mask, 0);
    }
    else
    {
        imm16 = this->getValueByMask( imm16_mask, 0);
    }
    this->set( P_FLOW, opcode0, sd, rs1, imm16);
}

/*
* Print an operation to console
*/
void Operation::dump()
{
    switch ( this->type)
    {
        case MOVE:
            this->dumpMOVE();
            break;
        case ALU:
            this->dumpALU();
            break;
        case P_FLOW:
            this->dumpPFLOW();
            break;
        default:
            cout << "Can't print to console, because operation has illegal type\n";
            assert( 0);
    }
}

/*
 * Execute the operation
 */
void Operation::execute()
{
    switch ( this->type)
    {
        case MOVE:
            this->executeMove();
            break;
        case ALU:
            this->executeALU();
            break;
        case P_FLOW:
            this->executePFlow();
            break;
        default:
            cout << "Invalid operation type\n";
            assert( 0);
    }
}

/*
 * Execute the operation of MOVE type
 */
void Operation::executeMove()
{
}

/*
 * Execute the operation of ALU type
 */
void Operation::executeALU()
{

    /* Update flag register after execution */
}

/*
 * Execute the operation of P_FLOW type
 */
void Operation::executePFlow()
{
    /* Read flag register before execution */

}
