/**
 * @file:simmy.h 
 * The header file for Simmy - the simple functional simulator
 * of the imaginary SIM architecture.
 * @author Andrey Pushkar
 */
/*
 * Copyright 2011 MDSP team
 */
#ifndef SIMMY_H
#define SIMMY_H

#include <bitset>
#include <string>
#include <map>
#include "types.h"

#define INSTR_LEN 5

using namespace std;


/**
 * The definitions of some useful routines are presented here.
 */

bitset<8> intToBitset8( hostUInt32 n);
bitset<16> intToBitset16( hostUInt32 n);

/**
 * A helper for fancy mapping binary (0,1) characters to bipolar (-1,1)
 */
hostSInt16 binToBip( hostUInt8 n);
hostUInt8 bipToBin( hostSInt16 n);


/**
 * A helper for concatenating bitsets.
 */
bitset<16> operator+(bitset <8> LSB, bitset<8> MSB);

/**
 *  A pair of helpers for stretching the bitsets.
 */
bitset<16> lengthenBitSet( bitset<8> b); // like .zfill() method in Python
bitset<8> shortenBitSet( bitset<16> b);



/** 
 * Class Instruction implements (what is, actually, obvious)
 * the abstaction of a Sim archtecture instruction.
 * By now the instruction contains 5 bytes (what is mentioned in
 * the INSTR_LEN define).
 */

class Instruction
{
public:
    Instruction();
    Instruction( hostUInt8 *start);
    /* needed if we hadn't set the instruction bytes in constructor: */
    void setBytes( hostUInt8 *start); 
    bitset<8> getOpcode();
    bitset<8> getControl();
    bitset<8> getOp1();
    hostSInt16 getOp1Sign();
    bitset<8> getOp2L();
    bitset<8> getOp2M();
    bitset<16> getOp2();
    hostSInt16 getOp2Sign();
    bool op2IsARegister();
    bool op2IsAPositive();
    
private:
    bitset<8> bytes[ INSTR_LEN]; //instruction parts from right to left
};

/**
 * Class Register implenets a simple register of 16 bits + 1 bit for 
 * the sign of register's value.
 */

class Register
{
public:
    Register();
    Register( bitset<16> value, hostSInt16 sgn);
    void setValue( bitset<16> value);
    void setValue( hostSInt64 value);
    bitset <16> getValue();
    void setSign( hostUInt8  sgn);
    hostUInt8 getSign();
    
private:
    hostUInt8 sign; // binary format - 0 or 1
    bitset<16> bytes; 
};

/**
 *  The main class implements the functional simulation through taking
 *  the pointer to the array of bytes and it's lenght and the
 *  number of instructions from that array to execute.
 */
class Simmy
{
public:
    /* constructor */
    Simmy ( hostUInt8* bytes, hostUInt32 lenght);
    /* execute certain number of instructions */
    hostSInt32 execute( hostUInt32 number_of_instrs);
    
private:
    
    /* select and call operation */
    void selCallOp( Instruction ins);
    
    void instAnd( Instruction ins);
    void instOr( Instruction ins);
    void instXor( Instruction ins);
    void instAdd( Instruction ins);
    void instSub( Instruction ins);
    void instMul( Instruction ins);
    void instDiv( Instruction ins);
    void instMov( Instruction ins);
    void instNot( Instruction ins);
    void instDec( Instruction ins);
    void instInc( Instruction ins);
    void instSsgn( Instruction ins);
    void instIsgn( Instruction ins);
    
    Register regs[ 16];

    
    hostUInt8 *start;
    hostUInt32 len;
    
    
};



#endif
