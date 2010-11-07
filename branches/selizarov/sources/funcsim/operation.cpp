/**
 * operation.cpp - Implementation of Operation class methods
 * @author Pavel Zaichenkov, Alexander Potashev
 * Copyright 2009 MDSP team
 */

#include "operation.h"
#include "memory.h"
#include "register_file.h"

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
                     hostUInt8 imm8, hostUInt16 imm10, hostUInt16 imm16,
                     hostUInt8 rs1, hostUInt8 rs2, hostUInt8 rd)
{
    switch ( type)
    {
        this->clear();
        this->type = type;
        case MOVE:
            if ( am)
            {
                cout << "AM has to be set to 0 in MOVE\n";
            }
            if ( imm8)
            {
                cout << "Imm8 has to be set to 0 in MOVE\n";
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
            this->setMOVE( opcode0, sd, imm16, rs1, rd);
            break;
        case ALU:
            if ( sd)
            {
                cout << "SD has to be set to 0 in ALU\n";
            }
            if ( imm16)
            {
                cout << "Imm16 has to be set to 0 in ALU\n";
            }
            this->setALU( opcode0, opcode1, opcode2, am, imm10, rs1, rs2, rd);
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
            this->setPFLOW( opcode0, sd, rd, imm16);
            break;
        case SYS:
            if ( opcode1)
            {
                cout << "OpCode1 has to be set to 0 in SYS\n";
            }
            if ( opcode2)
            {
                cout << "OpCode2 has to be set to 0 in SYS\n";
            }
            if ( sd)
            {
                cout << "SD has to be set to 0 in SYS\n";
            }
            if ( am)
            {
                cout << "AM has to be set to 0 in SYS\n";
            }
            if ( imm10)
            {
                cout << "imm10 has to be set to 0 in SYS\n";
            }
            if ( imm16)
            {
                cout << "imm16 has to be set to 0 in SYS\n";
            }
            if ( rs1)
            {
                cout << "Rs1 has to be set to 0 in SYS\n";
            }
            if ( rs2)
            {
                cout << "Rs2 has to be set to 0 in SYS\n";
            }
            if ( rd)
            {
                cout << "Rd has to be set to 0 in SYS\n";
            }
            this->setSYS(opcode0, imm8);
            break;
        default:
            cout << "Illegal Type in set method\n";
            assert( 0);
    }
}

/*
 * Method defines the correlation between OperType and hostUInt32
 */
OperType Operation::getType( hostUInt32 type)
{
    switch ( type)
    {
        default:
            cout << "Unknown operation type encoded in "<< (int) type << " number" << endl;
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
        case 6:
            return SYS;
    }
}

/*
 * Method defines the correlation between hostUInt32 and OperType
 */
hostUInt32 Operation::getInt32FromType( OperType type)
{
    switch ( type)
    {
        case MOVE:
            return 0;
        case ALU:
            return 1;
        case MAC:
            return 2;
        case DMAC:
            return 3;
        case SIMD:
            return 4;
        case P_FLOW:
            return 5;
        case SYS:
            return 6;
        default:
            cout << "Unknown operation type encoded in "<< (int) type << " type" << endl;
            assert( 0);
    }
}


/*
 * Method defines the correlation between OperCode and hostUInt32
 */
OperCode Operation::getCode( OperType type, hostUInt32 code)
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
                    cout << "Illegal operation in ALU\n";
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
                    cout << "Illegal operation in P_FLOW\n";
                    assert( 0);
                    return NOP;
            }
            break;
        case SYS:
            switch ( code)
            {
                case 0:
                    return HLT;
                case 1:
                    return INT;
                default:
                    cout << "Illegal operation in SYS\n";
                    assert( 0);
                    return NOP;
            }
        default:
            cout << "Invalid operation type\n";
            assert( 0);
            return NOP;
    }
}

/*
 * Method defines the correlation between OperCode and hostUInt32
 */
hostUInt32 Operation::getInt32FromCode( OperType type, OperCode code)
{
    switch ( type)
    {
        case MOVE:
            switch ( code)
            {
                case NOP:
                    return 0;
                case BRM:
                    return 1;
                case BRR:
                    return 3;
                case LD:
                    return 6;
                default:
                    cout << "Illegal operation in MOVE\n";
                    assert( 0);
            }
            break;
        case ALU:
            switch ( code)
            {
                case NOP:
                    return 0;
                case ADD:
                    return 1;
                case SUB:
                    return 2;
                default:
                    cout << "Illegal operation in ALU\n";
                    assert( 0);
            }
            break;
        case P_FLOW:
            switch ( code)
            {
                case JMP:
                    return 0;
                case JGT:
                    return 1;
                default:
                    cout << "Illegal operation in P_FLOW\n";
                    assert( 0);
            }
            break;
        case SYS:
            switch ( code)
            {
                case HLT:
                    return 0;
                case INT:
                    return 1;
                default:
                    cout << "Illegal operation in SYS\n";
                    assert( 0);
            }
        default:
            cout << "Invalid operation type\n";
            assert( 0);
    }
}


/**
 * Set an operation of MOVE type
 */
void Operation::setMOVE( OperCode opcode0,
                         hostUInt8 sd,
                         hostUInt16 imm16,
                         hostUInt8 rs1,
                         hostUInt8 rd)
{
    this->clear();
    this->type = MOVE;
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
            this->sd = sd;
            if ( rs1)
            {
                cout << "Rs1 has to be set to 0 in LD\n";
            }
            if ( rs2)
            {
                cout << "Rs2 has to be set to 0 in LD\n";
            }
            break;
        default:
            cout << "Illegal operation code in MOVE\n";
            assert( 0);
    }
}

/**
 * Set an operation of ALU type
 */
void Operation::setALU( OperCode opcode0,
                        OperCode opcode1,
                        OperCode opcode2,
                        hostUInt8 am,
                        hostUInt16 imm10,
                        hostUInt8 rs1,
                        hostUInt8 rs2,
                        hostUInt8 rd)
{
    this->clear();
    this->type = ALU;
    this->opcode0 = opcode0;
    this->opcode1 = opcode1;
    this->opcode2 = opcode2;
    this->rd      = rd;
    this->am      = am;

    assert( imm10 <= 0x3ff);
    switch ( am )
    {
        case 0:
            this->rs1 = rs1;
            this->rs2 = rs2;
            if ( imm10)
            {
                cout << "Imm10 has to be set to 0 in ALU with flag AM = 0\n";
            }
            break;
        case 1:
            this->imm10 = imm10;
            if ( rs1)
            {
                cout << "Rs1 has to be set to 0 in ALU with flag AM = 1\n";
            }
            if ( rs2)
            {
                cout << "Rs2 has to be set to 0 in ALU with flag AM = 1\n";
            }
            break;
        case 2:
            this->rs1 = rs1;
            this->rs2 = rs2;
            if ( imm10)
            {
                cout << "Imm10 has to be set to 0 in ALU with flag AM = 2\n";
            }
            break;
        case 3:
            this->imm10 = imm10;
            if ( rs1)
            {
                cout << "Rs1 has to be set to 0 in ALU with flag AM = 3\n";
            }
            if ( rs2)
            {
                cout << "Rs2 has to be set to 0 in ALU with flag AM = 3\n";
            }
            break;
            default:
            {
                cout << "Invalid value of AM in ALU\n";
                assert(0);
            }
    }
}

/**
 * Set an operation of PFLOW type
 */
void Operation::setPFLOW( OperCode opcode0,
                          hostUInt8 sd,
                          hostUInt8 rd,
                          hostUInt16 imm16)
{
    this->clear();
    this->type = P_FLOW;
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
        this->rd = rd;
        if ( rd)
        {
            cout << "Rd has to be set to 0 in P_FLOW\n";
        }
    }
}

/**
 * Set an operation of SYS type
 */
void Operation::setSYS( OperCode opcode0,
                        hostUInt8 imm8)
{
    this->clear();
    this->type = SYS;
    this->opcode0 = opcode0;
    this->imm8 = imm8;

    switch ( opcode0)
    {
        case HLT:
            if ( imm8)
            {
                cout << "Imm8 has to be set to 0 in HLT\n";
            }
            break;
        case INT:
            break;
        default:
            cout << "Illegal operation code in SYS\n";
            assert( 0);
    }
}

/*
 * Print MOVE operation to the console
 */
void Operation::dumpMOVE()
{
    switch ( this->opcode0)
    {
        case BRM:
            cout << "brm " << (int) this->sd << ", r" << (int) this->rs1 << ", r" << (int) this->rd << ";" << endl;
            break;
        case BRR:
            cout << "brr " << (int) this->rs1 << ", r" << (int) this->rd << ";" << endl;
            break;
        case LD:
            cout << "ld " << (int) this->sd << ", r" << (int) this->imm16 << ", r" << (int) this->rd << ";" << endl;
            break;
        default:
            cout << "Operation code is invalid in MOVE\n";
            assert( 0);
    }
}

/*
 * Print ALU operation to the console
 */
void Operation::dumpALU()
{
    switch ( this->opcode1)
    {
        case ADD:
            if ((am == 1) || ( am == 3))
            {
                cout << "add " << (int) this->am << ", " << (int) this->imm10 << ", r" << (int) this->rd << ";" << endl;
            }
            else
            {
                cout << "add " << (int) this->am << ", r" << (int) this->rs1 << ", r" << (int) this->rs2 << ", r" << (int) this->rd << ";" << endl;
            }
            break;
        case SUB:
            if ((am == 1) || ( am == 3))
            {
                cout << "sub " << (int) this->am << ", " << (int) this->imm10 << ", r" << (int) this->rd << ";" << endl;
            }
            else
            {
                cout << "sub " << (int) this->am << ", r" << (int) this->rs1 << ", r" << (int) this->rs2 << ", r" << (int) this->rd << ";" << endl;
            }
            break;
        default:
            cout << "Operation code is invalid in ALU\n";
            assert(0);
    }
}

/*
 * Print P_FLOW operation to the console
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
            cout << "jmp " << (int) this->sd << ", r" << (int) temp << ";" << endl;
            break;
        case JGT:
            cout << "jgt " << (int) this->sd << ", r" << (int) temp << ";" << endl;
            break;
        default:
            cout << "Operation code is invalid in P_FLOW\n";
            assert(0);
    }
}

/*
 * Print SYS operation to the console
 */
void Operation::dumpSYS()
{
    switch ( this->opcode0)
    {
        case HLT:
            cout << "hlt;" << endl;
            break;
        case INT:
            cout << "int 0x" << hex << (int) this->imm8 << dec << ";" << endl;
            break;
        default:
            cout << "Operation code is invalid in SYS\n";
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
        temp = mem_value->getByteVal( i);
        value += temp;
        if ( i != 3)
        {
            value = value << 8; // move byte to the older rank
        }
    }
    this->instr_word = value;
}

/*
 * Set memory block from instruction word (binary representation)
 */
void Operation::setMemBlock( MemVal* mem_value)
{
    ByteLine line(4);
    line.setByte( 0, Byte( getValueByMask( 0xFF000000, 24)));
    line.setByte( 1, Byte( getValueByMask( 0x00FF0000, 16)));
    line.setByte( 2, Byte( getValueByMask( 0x0000FF00, 8)));
    line.setByte( 3, Byte( getValueByMask( 0x000000FF, 0)));
    mem_value->writeByteLine(line);
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

/*
 * Enables to set some value on a determined position in the instruction word
 */
void Operation::setValueByShift( hostUInt32 value, int shift)
{
    this->instr_word = instr_word + (value << shift);
}

/**
 * Encode operation in binary form
 */
MemVal* Operation::encode()
{
    MemVal* mem_value = new MemVal(4); // pointer to 32-bit (4 bytes) instruction word
    this->setInstrWord(mem_value);
    encodeType();
    switch ( this->type)
    {
        case MOVE:
        this->encodeMOVE();
            break;
        case ALU:
            this->encodeALU();
            break;
        case P_FLOW:
            this->encodePFLOW();
            break;
        case SYS:
            this->encodeSYS();
            break;
        default:
            cout << "Illegal type in encode()\n";
            assert( 0);
    }
    setMemBlock(mem_value);
    return mem_value;

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
        case SYS:
            this->decodeSYS();
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
    OperType type = this->getType( this->getValueByMask( type_mask, 29));
    return type;
}

/**
 * Encode Type value from the field this->type
 */
void Operation::encodeType()
{
    setValueByShift( getInt32FromType(this->type), 29);
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
    OperCode opcode0 = NOP;
    hostUInt8 sd = 0, rs1 = 0, rd = 0;
    hostUInt16 imm16 = 0;

    /* get OP */
    opcode0 = this->getCode( MOVE, this->getValueByMask( op_mask, 26));

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
            rd = this->getValueByMask( rd_mask, 0);      // get desitination
            sd = this->getValueByMask( sd_mask, 21);     // get S/D
            break;
        default:
            cout << "Illegal operation in MOVE\n";
            assert( 0);
    }
    this->setMOVE( opcode0, sd, imm16, rs1, rd);
}

/**
 * Encode MOVE command to a binary form
 * Necessary bytes are set in the determined position
 * All mask are set as it is described in architecture.
 */
void Operation::encodeMOVE()
{
    setValueByShift( getInt32FromCode( MOVE, this->opcode0), 26);
    switch ( this->opcode0)
    {
        case BRM:
            setValueByShift( this->sd, 21);     // set S/D
            setValueByShift( this->rs1, 5);     // set source
            setValueByShift( this->rd, 0);      // set destination
            break;
        case BRR:
            setValueByShift( this->rs1, 5);     // set source
            setValueByShift( this->rd, 0);      // set destination
            break;
        case LD:
            setValueByShift( this->imm16, 5);   // set imm16
            setValueByShift( this->rd, 0);      // set destination
            setValueByShift( this->sd, 21);     // set S/D
            break;
        default:
            cout << "Illegal operation in MOVE\n";
            assert( 0);
    }
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
    hostUInt32       imm10_mask = 0x00007FE0; // Imm10 mask
    hostUInt32         rs1_mask = 0x00007C00; // RS1 mask
    hostUInt32         rs2_mask = 0x000003E0; // RS2 mask
    hostUInt32          rd_mask = 0x0000001F; // RD mask

    /* temporary fields */
    OperCode opcode0, opcode1, opcode2;
    hostUInt8 am, rs1, rs2, rd;

    opcode0 = this->getCode( ALU, this->getValueByMask( logic_op_mask, 26));
    opcode1 = this->getCode( ALU, this->getValueByMask( arith_op_mask, 21));
    opcode2 = this->getCode( ALU, this->getValueByMask( shift_op_mask, 18));
    imm10 = this->getValueByMask( imm10_mask, 5);
    rs1 = this->getValueByMask( rs1_mask, 10);
    rs2 = this->getValueByMask( rs2_mask, 5);
    rd = this->getValueByMask( rd_mask, 0);
    am = this->getValueByMask( am_mask, 15);
    /* imm10, rs1, rs2 values depend on the am flag.
     * To set values correctly it is necessary to null some of these values
     * in order to avoid warnings
     */
    if ((am == 0) || (am == 2))
    {
        imm10 = 0;
    }
    else if ((am == 1) || (am == 3))
    {
        rs1 = 0;
        rs2 = 0;
    }
    this->setALU( opcode0, opcode1, opcode2, am, imm10, rs1, rs2, rd);
}

/*
 * Encode ALU command to a binary form
 * Necessary bytes are set in the determined position
 * All mask are set as it is described in architecture.
 */
void Operation::encodeALU()
{
    setValueByShift( getInt32FromCode( ALU, this->opcode0), 26);
    setValueByShift( getInt32FromCode( ALU, this->opcode1), 21);
    setValueByShift( getInt32FromCode( ALU, this->opcode2), 18);
    setValueByShift( this->am, 15);
    if ((this->am == 1) || (this->am == 3))
    {
        setValueByShift( this->imm10, 5);
    }
    else
    {
        setValueByShift( this->rs1, 10);
        setValueByShift( this->rs2, 5);
    }
    setValueByShift( this->rd, 0);
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
    hostUInt8 sd = 0, rd = 0;
    hostUInt16 imm16 = 0;

    opcode0 = this->getCode( P_FLOW, this->getValueByMask( op_mask, 25));
    sd = this->getValueByMask( sd_mask, 23);

    if ( !sd)
    {
        rd = this->getValueByMask( rd_mask, 0);
    }
    else
    {
        imm16 = this->getValueByMask( imm16_mask, 0);
    }
    this->setPFLOW( opcode0, sd, rd, imm16);
}

/*
 * Encode P_FLOW command to a binary form
 * Necessary bytes are set in the determined position
 * All mask are set as it is described in architecture.
 */
void Operation::encodePFLOW()
{
    setValueByShift( getInt32FromCode( P_FLOW, this->opcode0), 25);
    setValueByShift( this->sd, 23);
    if( !this->sd)
    {
        setValueByShift( this->rd, 0);
    }
    else
    {
        setValueByShift( this->imm16, 0);
    }
}

/**
 * Decode SYS command from binary form
 */
void Operation::decodeSYS()
{
    /* skip type decoding as we already know the type */

    hostUInt32       op_mask = 0x1E000000; // OP mask
    hostUInt32     imm8_mask = 0x000000FF; // imm8 mask

    /* temporary fields */
    OperCode opcode0;
    hostUInt8 imm8;

    opcode0 = this->getCode( SYS, this->getValueByMask( op_mask, 25));
    imm8 = this->getValueByMask( imm8_mask, 0);

    this->setSYS( opcode0, imm8);
}

/*
 * Encode SYS command to a binary form
 */
void Operation::encodeSYS()
{
    setValueByShift( getInt32FromCode( SYS, this->opcode0), 25);
    setValueByShift( this->imm8, 0);
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
        case SYS:
            this->dumpSYS();
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
        case SYS:
            this->executeSYS();
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
    switch ( opcode0)
    {
        case BRM:
            switch ( sd)
            {
                case 0:
                    core->GetMemory()->write16( ( mathAddr)rd, 
                        core->GetRF()->read16( ( physRegNum)rs1));
                    break;
                case 1:
                    core->GetRF()->write16( ( physRegNum)rd, 
                        core->GetMemory()->read16( (  mathAddr)rs1));
                    break;
                default:
                    assert( 0);
            }   
            break;
        case BRR:
            core->GetRF()->write16( ( physRegNum)rd, 
                core->GetRF()->read16( ( physRegNum)rs1));
            break;
        case LD:
            switch ( sd)
            {
                case 0:
                    core->GetRF()->write16( ( physRegNum)rd, imm16);
                    break;
                case 1:
                    core->GetMemory()->write16( ( mathAddr)rd, imm16);
                    break;
                default:
                    assert( 0);
            }
            break;
        default:
            assert( 0);
    }
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

/*
 * Execute the operation of SYS type
 */
void Operation::executeSYS()
{
    switch ( opcode0)
    {
        case HLT:
            this->core->Stop();  // stop instruction execution
            break;
        case INT:
            /* Interruption handling should be here */
            break;
        default:
            assert ( 0);
    }
}



