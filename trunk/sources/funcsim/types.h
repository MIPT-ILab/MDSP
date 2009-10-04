#ifndef TYPES_H
#define TYPES_H

#ifdef WINDOWS

#include <assert.h>

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

#include <assert.h>

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

#endif /* !WINDOWS */

typedef enum OperType
{
    NO_TYPE,
    MOVE,
    ALU,
    MAC,
    DMAC,
    P_FLOW
} OperationType;

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

#endif
