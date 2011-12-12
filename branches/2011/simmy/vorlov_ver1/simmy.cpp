/**
 * Simmy.h - simple educational simulator for SIM computer architecture
 * @author Orlov Vasiliy
 * Copyright 2011 MDSP team
 */

//#include <./types.h>
#include <iostream>

using namespace std;

#ifndef TYPES_H
#define TYPES_H


#if defined(_WIN32) || defined(_WIN64)


/* Signed 8-bit integer type */
typedef signed __int8 hostSInt8;
/* Signed 16-bit integer type */
typedef signed __int16 hostSInt16;
/* Signed 32-bit integer type */
typedef signed __int32 hostSInt32;
/* Signed 64-bit integer type */
typedef signed __int64 hostSInt64;
/* Unsigned 8-bit integer type */
typedef unsigned __int8 hostUInt8;
/* Unsigned 16-bit integer type */
typedef unsigned __int16 hostUInt16;
/* Unsigned 32-bit integer type */
typedef unsigned __int32 hostUInt32;
/* Unsigned 64-bit integer type */
typedef unsigned __int64 hostUInt64;
/* Single precision 32-bit float type */
typedef float hostFloat32;
/* Double precision 64-bit float type */
typedef double hostFloat64;


#else


/* Signed 8-bit integer type */
typedef signed char hostSInt8;
/* Signed 16-bit integer type */
typedef signed short hostSInt16;
/* Signed 32-bit integer type */
typedef signed int hostSInt32;
/* Signed 64-bit integer type */
typedef signed long long hostSInt64;
/* Unsigned 8-bit integer type */
typedef unsigned char hostUInt8;
/* Unsigned 16-bit integer type */
typedef unsigned short hostUInt16;
/* Unsigned 32-bit integer type */
typedef unsigned int hostUInt32;
/* Unsigned 64-bit integer type */
typedef unsigned long long hostUInt64;
/* Single precision 32-bit float type */
typedef float hostFloat32;
/* Double precision 64-bit float type */
typedef double hostFloat64;


#endif


/* Type for mathematical memory address */
typedef hostUInt32 mathAddr;


/* Type for phisical register numeration */
typedef hostUInt32 physRegNum;


/* Operation type */
typedef enum OperType
{
    MOVE,
    ALU,
    MAC,
    DMAC,
    SIMD,
    P_FLOW,
    SYS
} OperType;


/* Operation code */
typedef enum OperCode
{
    NOP,
    BRM,
    BRR,
    LD,
    ADD,
    SUB,
    JMP,
    JGT,
    HLT,
    INT
} OperCode;


typedef enum FlagType
{
    NO_FLAG,
    FLAG_NEG,  // negative
    FLAG_ZERO,  // zero
    FLAG_CARRY,  // carry out
    FLAG_OVERFLOW   // overflow
} FlagType;


/* Enumeration for Byte & Byteline classes' output */
typedef enum OutputFormat
{
    BIN, 
    DEC, 
    HEX
} OutputFormat;


/* Enumeration for conversion hostUInt8, 16, 32 into Byteline */
typedef enum OrderType
{
    HIGH_FIRST,
    LOW_FIRST
} OrderType;
typedef enum ConversionType
{
    HUINT8,
    HUINT16,
    HUINT32
} ConversionType;


#endif /* TYPES_H */

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

Simmy::Simmy ( hostUInt8* bytes, hostUInt32 lenght)
{
    instr_addr = bytes;
}

hostSInt32 Simmy::execute ( hostUInt32 number_of_instrs)
{
    hostUInt32 i;
    for ( i = 0; i < number_of_instrs; ++i)
    {
        decodeInstr();
        executeInstr();
        instr_addr = instr_addr + 5;
        cout << "\n\nregisters:" <<r[0]*r_sign[0] << "\n" << r[1]*r_sign[1] << "\n" << r[2]*r_sign[2] << "\n\n";
    }                  
    return r[0]*r_sign[0];
}

void Simmy::decodeInstr()
{  
     
    hostUInt8 control_byte;
     
    opcode = *instr_addr; // get the opcode value
    cout << "opcode = " << (int)opcode << "\n";
    control_byte = *(instr_addr + 1); // get the cotrol byte value
    cout << "control_byte = " <<(int) control_byte << "\n";
    reg = *(instr_addr + 2); // get the register number
     cout << "reg = " << (int)reg << "\n"   ;
    op1 = r[reg]; // get the opernd 1 value
      cout << "op1 = " << (int)op1 << "\n";
    op1_sign = r_sign[reg]; // get the sign of operand 1
    cout << "op1_sign = " << (int)op1_sign << "\n";
    bit2 = control_byte & 2; // get the bit2
    cout << "bit2 = " <<(int) bit2<< "\n";
    
    /* get the opernd 2 sign and value */
    if ( !( control_byte & 4)) 
    {
        op2 = r[ *( instr_addr + 3)];
        op2_sign = r_sign[ *( instr_addr + 3)];
    } else
    {
        op2 = *( ( hostUInt16*)( instr_addr + 3));
        if ( control_byte & 8)
            op2_sign = -1;
                else
                    op2_sign = 1;
    } cout << "op2 = " << (int)op2<< "\n"; cout << "op2_sign = " << (int)op2_sign<< "\n";
}

void Simmy::executeInstr()
{    
    
    /* Emulate instruction AND */
    if ( opcode == 1)
    {
        r[reg] = op1 & op2;
        if (( op1_sign == 1) && ( op2_sign == 1))
            r_sign[reg] = 1;
                else
                    r_sign[reg] = -1;
       
    }
    
    /* Emulate instruction OR */
    if ( opcode == 2)
    {
        r[reg] = op1 | op2;
        if (( op1_sign == 1) || ( op2_sign == 1))
            r_sign[reg] = 1;
                else
                    r_sign[reg] = -1;
    }
    
    /* Emulate instruction XOR */
    if ( opcode == 3)
    {
        r[reg] = op1 ^ op2;
        if (( op1_sign  == op2_sign))
            r_sign[reg] = 0;
                else
                    r_sign[reg] = 1;
    }
    
    /* Emulate instruction ADD */
    if ( opcode == 130)
    {
        if ( op1 > op2)
        {
            if( (op1_sign == 1) && (op2_sign == -1))
            {
                r[reg] = op1 - op2;
                r_sign[reg] = 1;
            }
            if( (op1_sign == 1) && (op2_sign == 1))
            {
                r[reg] = op1 + op2;
                r_sign[reg] = 1;
            }
            if( (op1_sign == -1) && (op2_sign == -1))
            {
                r[reg] = op1 + op2;
                r_sign[reg] = -1;
            }   
            if( (op1_sign == -1) && (op2_sign == 1))
            {
                r[reg] = op1 - op2;
                r_sign[reg] = -1;
            }       
        }  
        if ( op1 <= op2)
        {
            if( (op1_sign == 1) && (op2_sign == -1))
            {
                r[reg] = op2 - op1;
                r_sign[reg] = -1;
            }
            if( (op1_sign == 1) && (op2_sign == 1))
            {
                r[reg] = op1 + op2;
                r_sign[reg] = 1;
            }
            if( (op1_sign == -1) && (op2_sign == -1))
            {
                r[reg] = op1 + op2;
                r_sign[reg] = -1;
            }   
            if( (op1_sign == -1) && (op2_sign == 1))
            {
                r[reg] = op2 - op1;
                r_sign[reg] = 1;
            }    
        }             
    }
    
     /* Emulate instruction SUB */
     if ( opcode == 131)
    {
        if ( op1 > op2)
        {
            if( (op1_sign == 1) && (op2_sign == -1))
            {
                r[reg] = op1 + op2;
                r_sign[reg] = 1;
            }
            if( (op1_sign == 1) && (op2_sign == 1))
            {
                r[reg] = op1 - op2;
                r_sign[reg] = 1;
            }
            if( (op1_sign == -1) && (op2_sign == -1))
            {
                r[reg] = op1 + op2;
                r_sign[reg] = -1;
            }   
            if( (op1_sign == -1) && (op2_sign == 1))
            {
                r[reg] = op1 - op2;
                r_sign[reg] = -1;
            }  
        }       
        if ( op1 <= op2)
        {
            if( (op1_sign == 1) && (op2_sign == -1))
            {
                r[reg] = op2 + op1;
                r_sign[reg] = +1;
            }
            if( (op1_sign == 1) && (op2_sign == 1))
            {
                r[reg] = op2 - op1;
                r_sign[reg] = -1;
            }
            if( (op1_sign == -1) && (op2_sign == -1))
            {
                r[reg] = op2 + op1;
                r_sign[reg] = 1;
            }   
            if( (op1_sign == -1) && (op2_sign == 1))
            {
                r[reg] = op2 + op1;
                r_sign[reg] = -1;
            }  
        }               
    }
    
    /* Emulate instruction MUL */
    if ( opcode == 129)
    {
        r[reg] = op1 * op2;
        if (( op1_sign  == op2_sign))
            r_sign[reg] = 1;
                else
                    r_sign[reg] = -1;
    }
        
    /* Emulate instruction DIV */
    if ( opcode == 128)
    {
        r[reg] = op1 / op2;
        if (( op1_sign  == op2_sign))
            r_sign[reg] = 1;
                else
                    r_sign[reg] = -1;
    }    
    
    /* Emulate instruction MOV */
    if ( opcode == 132)
    {
        r[reg] = op2;
        r_sign[reg] = op2_sign;
    }    
         
    /* Emulate instruction NOT */
    if ( opcode == 68)
    {
        r[reg] = ~op1;
        r_sign[reg] = r_sign[reg] * (-1);
    }    
    
    /* Emulate instruction DEC */
    if ( opcode == 192)
    {
        if ( op1 == 0 )
        {
            r[reg] = 1;
            r_sign[reg] = -1;
        } else
        {    
            if ( r_sign[reg] == 1) 
               --r[reg];
                   else
                       ++r[reg];
        }
    }    
    
    /* Emulate instruction INC */
    if ( opcode == 193)
    {
        if ( op1 == 0 )
        {
            r[reg] = 1;
            r_sign[reg] = 1;
        } else
        {    
            if ( r_sign[reg] == 1) 
               --r[reg];
                   else
                       ++r[reg];
        }
    }    
    
    /* Emulate instruction SSGN */
    if ( opcode == 194)
        if( bit2 == 0)
        {
            r_sign[reg] == -1;
        } else
        {
            r_sign[reg] == 1; 
        }  
                    
    /* Emulate instruction ISGN */
    if ( opcode == 195) r_sign[reg] = r_sign[reg] * (-1);
  
}

int main()
{
    hostUInt32 c;
    hostUInt8 a[55] = {132, 12, 1, 5, 0,   130, 12, 1, 3, 0,   132, 4, 2, 4, 0,   128, 0, 1, 2, 0,   132, 0, 0, 1, 0,
                       195,  0, 1, 0, 0,   194,  2, 1, 0, 0,   193, 0, 2, 0, 0,   192, 0, 0, 0, 0,    68, 0, 2, 0, 0,
                         1,  0, 0, 1, 0      };
    Simmy b(a, 1);
    cout << b.execute(11);
    cin >> c;
    
    return 0;
}
