/**
 * types.h - Implementation of types that are independent of host system
 * The types are used in algorithms affected by size of a variable
 * @author Dmitry Ustyugov
 * Copyright 2009 MDSP team
 */

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
/* Operation code of ALU instruction. */
    NOP,
    ADD,
    SUB,
/* Operation code of MOVE instruction. */
    BRM,
    BRR,
    LD,
/* Operation code of PFLOW instruction. */
    JMP,
    JGT,
/* Operation code of SYS instruction. */
    HLT,
    INT,
/* Operation code of SIMD instruction. */
    PADD,
    PSUB,
    PMUL,
    PSAD,
    PDOT,
    PAVG,
    PMIN,
    PMAX,
    PCMPE,
    PAND,
    POR,
    PXOR,
    PNAND,
    PNOR,
    PSHL,
    PSHRL,
    PSHRA,
/* Code of reserved operation. */
    RESERVED
} OperCode;

typedef enum FlagType
{
    NO_FLAG,
    FLAG_NEG,       // negative
    FLAG_ZERO,      // zero
    FLAG_CARRY,     // carry out
    FLAG_OVERFLOW,  // overflow
    p_N0,
    p_Z0,
    p_C0,
    p_O0,
    p_N1,
    p_Z1,
    p_C1,
    p_O1,
    p_N2,
    p_Z2,
    p_C2,
    p_O2,
    p_N3,
    p_Z3,
    p_C3,
    p_O3
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