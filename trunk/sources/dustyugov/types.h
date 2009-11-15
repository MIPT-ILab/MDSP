/**
 * types.h - Implementation of types that are independent of host system
 * The types are used in algorithms affected by size of a variable
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
    P_FLOW
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
    JGT
} OperCode;

typedef enum FlagType
{
    NO_FLAG,
    N,  // negative
    Z,  // zero
    C,  // carry out
    O   // overflow
} FlagType;

#endif /* TYPES_H */
