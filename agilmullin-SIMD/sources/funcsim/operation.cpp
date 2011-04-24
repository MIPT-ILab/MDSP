/**
 * operation.cpp - Implementation of Operation class methods
 * @author Pavel Zaichenkov, Alexander Potashev, Mikhail Churikov
 * Copyright 2009 MDSP team
 */

#include "operation.h"
#include "memory.h"
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
    this->memory = this->core->GetMemory();
    this->RF = this->core->GetRF();
    this->APR = this->core->GetAPR();
    //this->PA = this->core->GetPA();
    //this->flags = this->core->GetFlags();
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

/**
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

/**
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
            return 0;   /* UNREACHABLE */
    }
}


/**
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
        case SIMD:
            switch ( code)
            {
                case 0:
                    return PADD;
                case 1:
                    return PSUB;
                case 2:
                    return PMUL;
                case 3:
                    return PSAD;
                case 4:
                    return PDOT;
                case 5:
                    return PAVG;
                case 6:
                    return PMIN;
                case 7:
                    return PMAX;
                case 8:
                    return PCMPE;
                case 9:
                    return PAND;
                case 10:
                    return POR;
                case 11:
                    return PXOR;
                case 12:
                    return PNAND;
                case 13:
                    return PNOR;
                case 14:
                    return PSHL;
                case 15:
                    return PSHRL;
                case 16:
                    return PSHRA;
                case 17: case 18: case 19:
                case 20: case 21: case 22:
                case 23: case 24: case 25:
                case 26: case 27: case 28:
                case 29: case 30: case 31:
                    return RESERVED;
                default:
                    cout << "Illegal operation in SIMD" << endl;
                    assert( 0);
                    return NOP;
            }
        default:
            cout << "Invalid operation type\n";
            assert( 0);
            return NOP;
    }
}

/**
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
                    return 0;   /* UNREACHABLE */
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
                    return 0;   /* UNREACHABLE */
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
                    return 0;   /* UNREACHABLE */
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
                    return 0;   /* UNREACHABLE */
            }
        case SIMD:
            switch ( code)
            {
                case PADD:
                    return 0;
                case PSUB:
                    return 1;
                case PMUL:
                    return 2;
                case PSAD:
                    return 3;
                case PDOT:
                    return 4;
                case PAVG:
                    return 5;
                case PMIN:
                    return 6;
                case PMAX:
                    return 7;
                case PCMPE:
                    return 8;
                case PAND:
                    return 9;
                case POR:
                    return 10;
                case PXOR:
                    return 11;
                case PNAND:
                    return 12;
                case PNOR:
                    return 13;
                case PSHL:
                    return 14;
                case PSHRL:
                    return 15;
                case PSHRA:
                    return 16;
                case RESERVED:
                    return 17;
                default:
                    cout << "Illegal operation in SIMD" << endl;
                    assert( 0);
                    return 0;   /* UNREACHABLE */
            }
        default:
            cout << "Invalid operation type\n";
            assert( 0);
            return 0;   /* UNREACHABLE */
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

/**
 * Set an operation of SIMD type
 */
void Operation::setSIMD( OperCode opcode0,
                         hostUInt8 am,
                         hostUInt8 ip,
                         hostUInt8 mao,
                         hostUInt8 d,
                         hostUInt8 imm5_rind,
                         hostUInt8 aprs,
                         hostUInt8 aprd_pad)
{
    this->clear();
    this->type = SIMD;
    this->opcode0 = opcode0;
    this->am      = am;
    this->ip      = ip;
    this->mao     = mao;
    this->d       = d;
    this->imm5 = this->rind = imm5_rind;
    this->aprs    = aprs;
    this->aprd = this->pad = aprd_pad;
}

/**
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
            cout << "brr r" << (int) this->rs1 << ", r" << (int) this->rd << ";" << endl;
            break;
        case LD:
            cout << "ld " << (int) this->sd << ", 0x" << (int) this->imm16 << ", r" << (int) this->rd << ";" << endl;
            break;
        default:
            critical( "Operation code is invalid in dumping MOVE");
    }
}

/**
 * Print ALU operation to the console
 */
void Operation::dumpALU()
{
    switch ( this->opcode1)
    {
        case ADD:
            if ((am == 1) || ( am == 3))
            {
                cout << "add " << (int) this->am << ", 0x" << (int) this->imm10 << ", r" << (int) this->rd << ";" << endl;
            }
            else
            {
                cout << "add " << (int) this->am << ", r" << (int) this->rs1 << ", r" << (int) this->rs2 << ", r" << (int) this->rd << ";" << endl;
            }
            break;
        case SUB:
            if ((am == 1) || ( am == 3))
            {
                cout << "sub " << (int) this->am << ", 0x" << (int) this->imm10 << ", r" << (int) this->rd << ";" << endl;
            }
            else
            {
                cout << "sub " << (int) this->am << ", r" << (int) this->rs1 << ", r" << (int) this->rs2 << ", r" << (int) this->rd << ";" << endl;
            }
            break;
        case NOP:
            cout << "nop;" << endl;
            break;
        default:
            critical( "Operation code is invalid in dumping ALU");
    }
}

/**
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
            if( !this->sd)
                cout << "jmp " << (int) this->sd << ", r" << (int) temp << ";" << endl;
            else
                cout << "jmp " << (int) this->sd << ", 0x" << (int) temp << ";" << endl;
            break;
        case JGT:
            if( !this->sd)
                cout << "jgt " << (int) this->sd << ", r" << (int) temp << ";" << endl;
            else
                cout << "jgt " << (int) this->sd << ", 0x" << (int) temp << ";" << endl;
            break;
        default:
            critical( "Operation code is invalid in dumping P_FLOW");
    }
}

/**
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
            critical( "Operation code is invalid in dumping SYS");
    }
}

/**
 * Print SIMD operation to the console
 */
void Operation::dumpSIMD()
{
    cout << "Operation has to be set to SIMD with" << endl;
    cout << "opcode0=";
        switch (opcode0)
        {
                case PADD:
                    cout << "PADD" << endl;
                    break;
                case PSUB:
                    cout << "PSUB" << endl;
                    break;
                case PMUL:
                    cout << "PMUL" << endl;
                    break;
                case PSAD:
                    cout << "PSAD" << endl;
                    break;
                case PDOT:
                    cout << "PDOT" << endl;
                    break;
                case PAVG:
                    cout << "PAVG" << endl;
                    break;
                case PMIN:
                    cout << "PMIN" << endl;
                    break;
                case PMAX:
                    cout << "PMAX" << endl;
                    break;
                case PCMPE:
                    cout << "PCMPE" << endl;
                    break;
                case PAND:
                    cout << "PAND" << endl;
                    break;
                case POR:
                    cout << "POR" << endl;
                    break;
                case PXOR:
                    cout << "PXOR" << endl;
                    break;
                case PNAND:
                    cout << "PNAND" << endl;
                    break;
                case PNOR:
                    cout << "PNOR" << endl;
                    break;
                case PSHL:
                    cout << "PSHL" << endl;
                    break;
                case PSHRL:
                    cout << "PSHRL" << endl;
                    break;
                case PSHRA:
                    cout << "PSHRA" << endl;
                    break;
                case RESERVED:
                    cout << "Reserved" << endl;
                    break;
                default:
                    cout << "unknown" << endl;
        }
    cout << "AM=" << (int) this->getAM() << " IP=" << (int) this->getIP();
    cout << " MAO=" << (int) this->getMAO() << " D=" << (int) this->getD() << endl;
    cout << "Row offset=" << (int) this->getImm5() << " Aux Register=" << (int) this->getRInd() << endl;
    cout << "Source base address=" << (int) this->getAprS() << endl;
    cout << "Destination base address=" << (int) this->getAprD() << " S/D ACR=" << (int) this->getPaD() << endl;
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

/**
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

/**
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
        case SIMD:
            this->encodeSIMD();
            break;
        default:
            warning("Illegal operation code: 0x%x", getInstrWord());
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
        case SIMD:
            this->decodeSIMD();
            break;
        default:
            critical( "Illegal operation type in decode: 0x%x", getInstrWord());
     }

    /*
     * We need to set instr word again (see the beginning of this method) because
     * it is cleared by decodeXXX() functions.
     */
    this->setInstrWord( mem_value);
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
            critical( "Illegal operation in MOVE");
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

/**
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
/**
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

/**
 * Encode SYS command to a binary form
 */
void Operation::encodeSYS()
{
    setValueByShift( getInt32FromCode( SYS, this->opcode0), 25);
    setValueByShift( this->imm8, 0);
}

/**
 * Decode SIMD command from binary form
 * All mask are set as it is described in architecture.
 */
void Operation::decodeSIMD()
{
    /* skip type decoding as we already know the type */

    const hostUInt32          op_mask = 0x1F000000; // Opcode mask
    const hostUInt32          am_mask = 0x00E00000; // AM mask
    const hostUInt32          ip_mask = 0x00100000; // IP mask
    const hostUInt32         mao_mask = 0x000FF000; // MAO mask
    const hostUInt32           d_mask = 0x00000800; // D mask
    const hostUInt32   imm5_rind_mask = 0x000007C0; // Row offset/Aux. register mask
    const hostUInt32        aprs_mask = 0x00000038; // Source base address mask
    const hostUInt32    aprd_pad_mask = 0x00000007; // Destination base address/ SD ACR mask

    /* temporary fields */
    OperCode opcode0 = this->getCode( SIMD, this->getValueByMask( op_mask, 24));;
    hostUInt32          am = this->getValueByMask( am_mask, 21);       // AM
    hostUInt32          ip = this->getValueByMask( ip_mask, 20);       // IP
    hostUInt32         mao = this->getValueByMask( mao_mask, 12);      // MAO
    hostUInt32           d = this->getValueByMask( d_mask, 11);        // D
    hostUInt32   imm5_rind = this->getValueByMask( imm5_rind_mask, 6); // Row offset/Aux. register
    hostUInt32        aprs = this->getValueByMask( aprs_mask, 3);      // Source base address
    hostUInt32    aprd_pad = this->getValueByMask( aprd_pad_mask, 0);  // Destination base address/ SD ACR

    this->setSIMD( opcode0, am, ip, mao, d, imm5_rind, aprs, aprd_pad);
}
/**
 * Encode SIMD command to a binary form
 */
void Operation::encodeSIMD()
{
    setValueByShift( getInt32FromCode( SIMD, this->opcode0), 24);
    setValueByShift( am, 21);
    setValueByShift( ip, 20);
    setValueByShift( mao, 12);
    setValueByShift( d, 11);
    if ( imm5==rind)
    {
        setValueByShift( imm5, 6);
    }
    else
    {
        assert( 0);
    }
    setValueByShift( aprs, 3);
    if ( aprd==pad)
    {
        setValueByShift( aprd, 0);
    }
    else
    {
        assert( 0);
    }
}

/**
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
        case SIMD:
            this->dumpSIMD();
            break;
        default:
            warning( "Unknown operation type in dump: 0x%x", getInstrWord());
    }
}

/**
 * Execute the operation
 */
void Operation::execute()
{
	/* Print "execute" and current PC */
	cout << "execute PC=0x" << core->GetPC() << endl;
		
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
        case SIMD:
            this->executeSIMD();
            break;
        default:
            cout << "Invalid operation type\n";
            assert( 0);
    }
}

/**
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
                    memory->write16( ( mathAddr)rd, 
                                    RF->read16( ( physRegNum)rs1));
                    break;
                case 1:
                    RF->write16( ( physRegNum)rd, 
                                memory->read16( (  mathAddr)rs1));
                    break;
                default:
                    assert( 0);
            }   
            break;
        case BRR:
            RF->write16( ( physRegNum)rd, RF->read16( ( physRegNum)rs1));
            break;
        case LD:
            switch ( sd)
            {
                case 0:
                    RF->write16( ( physRegNum)rd, imm16);
                    break;
                case 1:
                    memory->write16( ( mathAddr)rd, imm16);
                    break;
                default:
                    assert( 0);
            }
            break;
        default:
            assert( 0);
    }
}

/**
 * Execute the operation of ALU type
 */
void Operation::executeALU()
{
    hostSInt16 result = 0;
    hostSInt32 firstOperand, secondOperand;
    Flags* flags;
    flags = this->core->GetFlags();
    switch ( this->opcode1)
    {
        case NOP: 
            /// stall  
            break;
        case ADD:
            switch ( this->am)
            {
                case 0:  /*Register direct addresing mode, use rS1,rS2, rD*/
                    firstOperand = RF->read16( ( physRegNum)rs1);
                    secondOperand = RF->read16( ( physRegNum)rs2);
                    result = firstOperand + secondOperand;
                    RF->write16( ( physRegNum)rd, result);
                    break;
                case 1:  /*Register direct and immediate data, use imm10, rD*/
                    firstOperand = RF->read16( ( physRegNum)rd);
                    secondOperand = ( hostSInt16)imm10;
                    result = firstOperand + secondOperand;
                    RF->write16( ( physRegNum)rd, result);
                    break;
                case 2:  /*Register indirect mode( memory), use rS1, rS2, rD*/
                    firstOperand = memory->read16( (  mathAddr)rs1);
                    secondOperand = memory->read16( (  mathAddr)rs2);
                    result = firstOperand + secondOperand;
                    memory->write16( ( mathAddr)rd, result);
                    break;
                case 3:  /*Register indirect with immediate, use imm10, rD*/
                    firstOperand = memory->read16( (  mathAddr)rd);
                    secondOperand = ( hostSInt16)imm10;
                    result = firstOperand + secondOperand;
                    memory->write16( ( mathAddr)rd, result);
                    break;
                default:
                    assert( 0);
            }
            if ( ( firstOperand + secondOperand) >= 0x0FFFF) 
                    flags->setFlag( FLAG_OVERFLOW, true);
            else flags->setFlag( FLAG_OVERFLOW, false);
            if ( firstOperand & secondOperand) 
                    flags->setFlag( FLAG_CARRY, true);
            else flags->setFlag( FLAG_CARRY, false);
            break;
        case SUB:
            switch ( this->am)
            {
                case 0:  /* Register direct addresing mode, use rS1,rS2, rD*/
                    firstOperand = RF->read16( ( physRegNum)rs1);
                    secondOperand = RF->read16( ( physRegNum)rs2);
                    result = firstOperand - secondOperand;
                    RF->write16( ( physRegNum)rd, result);
                    break;
                case 1:  /* Register direct and immediate data, use imm10, rD*/
                    firstOperand = RF->read16( ( physRegNum)rd);
                    secondOperand = ( hostSInt16)imm10;
                    result = firstOperand - secondOperand;
                    RF->write16( ( physRegNum)rd, result);
                    break;
                case 2:  /* Register indirect mode( memory), use rS1, rS2, rD*/
                    firstOperand = memory->read16( (  mathAddr)rs1);
                    secondOperand = memory->read16( ( mathAddr)rs2);
                    result = firstOperand - secondOperand;
                    memory->write16( ( mathAddr)rd, result);
                    break;
                case 3:  /* Register indirect with immediate, use rS1, rS2, rD*/
                    firstOperand = memory->read16( (  mathAddr)rd);
                    secondOperand = ( hostSInt16)imm10;
                    result = firstOperand - secondOperand;;
                    memory->write16( ( mathAddr)rd, result);
                    break;
                default:
                    assert( 0);   
            }
            if ( firstOperand & ( (!secondOperand) + 1)) 
                    flags->setFlag( FLAG_CARRY, true);
            else flags->setFlag( FLAG_CARRY, false);
            break;
        default:
            assert( 0);
    }
    /* Update flag register after execution */
    if ( result == 0) flags->setFlag( FLAG_ZERO, true);
    else flags->setFlag( FLAG_ZERO, false);
    if ( result < 0) flags->setFlag( FLAG_NEG, true);
    else flags->setFlag( FLAG_NEG, false);
}

/**
 * Execute the operation of P_FLOW type
 */
void Operation::executePFlow()
{
    Flags* flags;
    flags = this->core->GetFlags();
    /* Read flag register before execution */
    switch ( this->opcode0)
    {
        case JMP: /*Unconditional branch*/
            switch ( this->sd)
            {
                case 0:  /*Destination is in rD*/
                    this->core->SetPC( RF->read16( ( physRegNum)rd));
                    break;
                case 1:  /*Destination is in imm16*/
                    this->core->SetPC( imm16);
                    break;
                default:
                    assert( 0);
            }   
            break;
        case JGT:  /* Conditional branch*/
            if ( flags->getFlag( FLAG_NEG))
            {
                switch ( this->sd)
                {
                    case 0:  /*Destination is in rD*/
                        this->core->SetPC(  RF->read16( ( physRegNum)rd));
                        break;
                    case 1:  /*Destination is in imm16*/
                        this->core->SetPC( imm16);
                        break;
                    default:
                        assert( 0);
                }
            } 
            break;
        default:
            assert( 0);
    }

}

/**
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

/**
 * Execute the operation of SIMD type
 */
void Operation::executeSIMD()
{   
    /* ip -> mao -> first operand -> am -> second operand -> result -> d -> destination -> flags */

    /* dp0 - dp3 descibe in which order the parallel data path are accesing the memories in the memory bank. */
    const hostUInt8 unused = 4; // Mark for unused data path.
    hostUInt8 dp0 = (this->mao>>6)&0x03;
    hostUInt8 dp1 = (this->mao>>4)&0x03;
    hostUInt8 dp2 = (this->mao>>2)&0x03;
    hostUInt8 dp3 = (this->mao>>0)&0x03;
    
    if ( ( aprs<0) || ( aprs>8))
    {
        cout << "Invalid Source Base Address in SIMD instruction." << endl;
        assert( 0);
    }
    mathAddr sba = this->APR->read16( ( physRegNum)aprs); // Source base address

    switch ( ip)
    {
        case 0:
            if ( dp1==dp0) 
                dp1 = unused;
            if ( ( dp2==dp0) || ( dp2==dp1) ) 
                dp2 = unused;
            if ( ( dp3==dp0) || ( dp3==dp1) || ( dp3==dp2) ) 
                dp3 = unused;
            break;
        case 1:
            if ( dp0==0) dp0 = unused;
            if ( dp1==1) dp1 = unused;
            if ( dp2==2) dp2 = unused;
            if ( dp3==3) dp3 = unused;
            break;
        default:
            cout << "Invalid IP in SIMD instruction." << endl;
            assert( 0);
    }

    /* Getting source data from memory. */
    hostSInt32 operand1dp0 = 0, operand2dp0 = 0, resultdp0;
    hostSInt32 operand1dp1 = 0, operand2dp1 = 0, resultdp1;
    hostSInt32 operand1dp2 = 0, operand2dp2 = 0, resultdp2;
    hostSInt32 operand1dp3 = 0, operand2dp3 = 0, resultdp3;

    switch ( ip)
    {
        case 0:
                operand1dp0 = ( hostSInt32) memory->read8( dp0, sba);
            if ( dp1!=unused)
                operand1dp1 = ( hostSInt32) memory->read8( dp1, sba);
            if ( dp2!=unused)
                operand1dp2 = ( hostSInt32) memory->read8( dp2, sba);
            if ( dp3!=unused)
                operand1dp3 = ( hostSInt32) memory->read8( dp3, sba);
            break;
        case 1:
            if ( dp0!=unused)
                operand2dp0 = ( hostSInt32) memory->read16( dp0, sba);
            if ( dp1!=unused)
                operand2dp1 = ( hostSInt32) memory->read16( dp1, sba);
            if ( dp2!=unused)
                operand2dp2 = ( hostSInt32) memory->read16( dp2, sba);
            if ( dp3!=unused)
                operand2dp3 = ( hostSInt32) memory->read16( dp3, sba);
            break;
        default:
            cout << "Invalid IP in SIMD instruction." << endl;
            assert( 0);
    }    

    cout << "look:" << (unsigned int) sba << endl;

    switch ( am)
    {
        case 0: // Register indirect
            break;
        case 1: // Register indirect, post incremented by 1 (++)
            sba++;
            break;
        case 2: // Register indirect, post decremented by 1 (--)
            sba--;
            break;
        case 3: // Index addressing 
            sba += this->RF->read16( ( physRegNum)rind);
            break;
        case 4: // Register indirect, post incremented by offset
            sba += imm5 + this->RF->read16( 29);
            break;
        case 5: // Register indirect, post decremented by offset
            sba -= imm5 + this->RF->read16( 29);
            break;
        case 6: case 7:
            cout << "SIMD supports only indirect addressing modes." << endl;
            assert( 0);
            break;
        default:
            cout << "Invalid AM in SIMD instruction." << endl;
            assert( 0);
    }

    cout << "look:" << (unsigned int) sba << endl;
    //APR->write16( aprs, sba);

    switch ( ip)
    {
        case 0:
                operand2dp0 = ( hostSInt32) memory->read8( dp0, sba);
            if ( dp1!=unused)
                operand2dp1 = ( hostSInt32) memory->read8( dp1, sba);
            if ( dp2!=unused)
                operand2dp2 = ( hostSInt32) memory->read8( dp2, sba);
            if ( dp3!=unused)
                operand2dp3 = ( hostSInt32) memory->read8( dp3, sba);
            break;
        case 1:
            if ( dp0!=unused)
                operand2dp0 = ( hostSInt32) memory->read16( dp0, sba);
            if ( dp1!=unused)
                operand2dp1 = ( hostSInt32) memory->read16( dp1, sba);
            if ( dp2!=unused)
                operand2dp2 = ( hostSInt32) memory->read16( dp2, sba);
            if ( dp3!=unused)
                operand2dp3 = ( hostSInt32) memory->read16( dp3, sba);
            break;
        default:
            cout << "Invalid IP in SIMD instruction." << endl;
            assert( 0);
    }

    switch ( opcode0)
    {
        case PADD: // An addition
            resultdp0 = operand1dp0 + operand2dp0;
            resultdp1 = operand1dp1 + operand2dp1;
            resultdp2 = operand1dp2 + operand2dp2;
            resultdp3 = operand1dp3 + operand2dp3;
            break;
        case PAND: // Bitwise AND
            resultdp0 = operand1dp0 & operand2dp0;
            resultdp1 = operand1dp1 & operand2dp1;
            resultdp2 = operand1dp2 & operand2dp2;
            resultdp3 = operand1dp3 & operand2dp3;
            break;
        case PAVG: // Average Value
            resultdp0 = ( operand1dp0 + operand2dp0 )/2;
            resultdp1 = ( operand1dp1 + operand2dp1 )/2;
            resultdp2 = ( operand1dp2 + operand2dp2 )/2;
            resultdp3 = ( operand1dp3 + operand2dp3 )/2;
            break;
        case PCMPE: // Compare to zero
            resultdp0 = ( operand1dp0 == operand2dp0 ) ? 1 : 0;
            resultdp1 = ( operand1dp1 == operand2dp1 ) ? 1 : 0;
            resultdp2 = ( operand1dp2 == operand2dp2 ) ? 1 : 0;
            resultdp3 = ( operand1dp3 == operand2dp3 ) ? 1 : 0;
            break;
        case PDOT: // DOT multiplication product
            resultdp0 = abs( operand1dp0 * operand2dp0) + abs( operand1dp1 * operand2dp1) +
                        abs( operand1dp2 * operand2dp2) + abs( operand1dp3 * operand2dp3);
            resultdp3 = resultdp2 = resultdp1 = resultdp0;
            break;
        case PMAX: // A maximum value
            resultdp0 = ( operand1dp0 > operand2dp0 ) ? operand1dp0 : operand2dp0;
            resultdp1 = ( operand1dp1 > operand2dp1 ) ? operand1dp1 : operand2dp1;
            resultdp2 = ( operand1dp2 > operand2dp2 ) ? operand1dp2 : operand2dp2;
            resultdp3 = ( operand1dp3 > operand2dp3 ) ? operand1dp3 : operand2dp3;
            break;
        case PMIN: // A minimum value
            resultdp0 = ( operand1dp0 < operand2dp0 ) ? operand1dp0 : operand2dp0;
            resultdp1 = ( operand1dp1 < operand2dp1 ) ? operand1dp1 : operand2dp1;
            resultdp2 = ( operand1dp2 < operand2dp2 ) ? operand1dp2 : operand2dp2;
            resultdp3 = ( operand1dp3 < operand2dp3 ) ? operand1dp3 : operand2dp3;
            break;
        case PMUL: // A Multiplication
            resultdp0 = operand1dp0 * operand2dp0;
            resultdp1 = operand1dp1 * operand2dp1;
            resultdp2 = operand1dp2 * operand2dp2;
            resultdp3 = operand1dp3 * operand2dp3;
            break;
        case PNAND: // Bitwise NAND
            resultdp0 = !( operand1dp0 & operand2dp0 );
            resultdp1 = !( operand1dp1 & operand2dp1 );
            resultdp2 = !( operand1dp2 & operand2dp2 );
            resultdp3 = !( operand1dp3 & operand2dp3 );
            break;
        case PNOR: // Bitwise NOR
            resultdp0 = !( operand1dp0 | operand2dp0 );
            resultdp1 = !( operand1dp1 | operand2dp1 );
            resultdp2 = !( operand1dp2 | operand2dp2 );
            resultdp3 = !( operand1dp3 | operand2dp3 );
            break;
        case POR: // Bitwise OR
            resultdp0 = operand1dp0 | operand2dp0;
            resultdp1 = operand1dp1 | operand2dp1;
            resultdp2 = operand1dp2 | operand2dp2;
            resultdp3 = operand1dp3 | operand2dp3;
            break;
        case PSAD: // Sum of Absolute Differences
            cout << "Sum of Absolute Differences is not implemented yet." << endl;
            break;
        case PSHL: // Bitwise logic left shift
            cout << "Bitwise logic left shift is not implemented yet." << endl;
            break;
        case PSHRA: // Bitwise arithmetic right shift
            cout << "Bitwise arithmetic right shift is not implemented yet." << endl;
            break;
        case PSHRL: // Bitwise logic right shift
            cout << "Bitwise logic right shift is not implemented yet." << endl;
            break;
        case PSUB: // A substraction
            resultdp0 = operand1dp0 + operand2dp0;
            resultdp1 = operand1dp1 + operand2dp1;
            resultdp2 = operand1dp2 + operand2dp2;
            resultdp3 = operand1dp3 + operand2dp3;
            break;
        case PXOR: // Bitwise XOR
            resultdp0 = operand1dp0 ^ operand2dp0;
            resultdp1 = operand1dp1 ^ operand2dp1;
            resultdp2 = operand1dp2 ^ operand2dp2;
            resultdp3 = operand1dp3 ^ operand2dp3;
            break;
        case RESERVED:
            cout << "Reserved operation in SIMD instruction." << endl;
            break;
        default:
            cout << "Wrong opcode in SIMD instruction" << endl;
            assert( 0);
    }

    /* destination showes where should result be: in the memory or accumulator register. */
    const hostUInt8 mem = 0;
    const hostUInt8 acr = 1;
    hostUInt8 destination;
    switch ( this->d)
    {
        case 0:
            destination = mem;
            break;
        case 1:
            destination = acr;
            break;
        default:
            cout << "Invalid D field in SIMD instruction." << endl;
            assert( 0);
    }

    physAddr dba = this->APR->read16( ( physRegNum)aprd); // Destination base address

    switch ( destination)
    {
        case mem:
            if ( ip==0)
            {
                if ( dp0!=unused)
                    this->memory->write8( dp0, dba, (hostSInt8) resultdp0);
                if ( dp1!=unused)
                    this->memory->write8( dp1, dba, (hostSInt8) resultdp1);
                if ( dp2!=unused)
                    this->memory->write8( dp2, dba, (hostSInt8) resultdp2);
                if ( dp3!=unused)
                    this->memory->write8( dp3, dba, (hostSInt8) resultdp3);
            }
            else if ( ip==1)
            {
                if ( dp0!=unused)
                    this->memory->write16( dp0, (mathAddr) aprd, (hostSInt16) resultdp0);
                if ( dp1!=unused)
                    this->memory->write16( dp1, (mathAddr) aprd, (hostSInt16) resultdp1);
                if ( dp2!=unused)
                    this->memory->write16( dp0, (mathAddr) aprd, (hostSInt16) resultdp2);
                if ( dp3!=unused)
                    this->memory->write16( dp0, (mathAddr) aprd, (hostSInt16) resultdp3);
            }
            break;
        case acr:
            cout << "Parallel accumulator register is not implemented yet." << endl;
            break;
        default:
            cout << "Invalid destination in SIMD instruction." << endl;
            assert( 0);
    }

    cout << "Debug print" << endl;
    cout << operand1dp0 << " " << operand2dp0 << " " << resultdp0 << endl;
    cout << operand1dp1 << " " << operand2dp1 << " " << resultdp1 << endl;
    cout << operand1dp2 << " " << operand2dp2 << " " << resultdp2 << endl;
    cout << operand1dp3 << " " << operand2dp3 << " " << resultdp3 << endl;
    cout << "where to " << (hostUInt32) dba << endl;

    /* Update flag register after execution. */
    if ( dp0!=unused){
    }
    if ( dp1!=unused){
    }
    if ( dp2!=unused){
    }
    if ( dp3!=unused){
    }
}