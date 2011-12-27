/**
 * @file:simmy.cpp 
 * Implementation of Simmy - the simple functional simulator
 * of the imaginary SIM architecture.
 * @author Andrey Pushkar
 */
/*
 * Copyright 2011 MDSP team
 */

#include "Simmy.h"


/* class Register implementation */

Instruction::Instruction()
{
    for ( hostUInt32 i = 0; i < INSTR_LEN; i++)
        bytes[ i] = 0; 
}

Instruction::Instruction( hostUInt8 *start)
{ 
    for ( hostUInt32 i = 0; i < INSTR_LEN; i++)
        bytes[ i] = intToBitset8( *( start + i)); 
}

void Instruction::setBytes( hostUInt8 *start)
{
    for ( hostUInt32 i = 0; i < INSTR_LEN; i++)
    {
        bytes[ i] = intToBitset8( *( start + i));
    }
}

bitset<8> Instruction::getOpcode()
{
    return bytes[ 0];
}


bitset<8> Instruction::getControl()
{
    return bytes[ 1];
}

bitset<8> Instruction::getOp1()
{
    return bytes[ 2];
}

hostSInt16 Instruction::getOp1Sign()
{
    return getControl()[ 2];
}

bitset<8> Instruction::getOp2L()
{
    return bytes[ 3];
}

bitset<8> Instruction::getOp2M()
{
    return bytes[ 4];
}

bitset<16> Instruction::getOp2()
{
    return getOp2M() + getOp2L();
    
}

hostSInt16 Instruction::getOp2Sign()
{
    return getControl()[ 3];
}

bool Instruction::op2IsARegister()
{
    return ( getControl()[ 2] == 0) ? true : false;
}

bool Instruction::op2IsAPositive()
{
    return ( getControl()[ 3] == 1) ? true : false;
}


/* class Register implementation */


Register::Register()
{
    sign = 1;
    bytes = bitset<16>( string( "0000000000000000"));    
}


Register::Register( bitset<16> value, hostSInt16 sgn)
{
    bytes = value;
    sign = sgn;
}

void Register::setValue( bitset<16> value)
{
    bytes = value;
}

bitset<16> Register::getValue()
{
    
    return bytes;
}


void Register::setSign( hostUInt8 sgn)
{
    sign = sgn;   
}

hostUInt8 Register::getSign()
{
    return sign;
}

//*********************************************


Simmy::Simmy( hostUInt8* bytes, hostUInt32 length)
{
    start = bytes;
    len = length;
}

hostSInt32 Simmy::Execute( hostUInt32 number_of_instrs)
{
    Instruction curr;
    for ( hostUInt32 i = 0; i < number_of_instrs; i++)
    {
        curr.setBytes( start+i*INSTR_LEN);
        selCallOp( curr);
    }
    return ( ( hostSInt32)regs[ 0].getValue().to_ulong()) * regs[ 0].getSign();
}


void Simmy::selCallOp( Instruction ins)
{
    switch ( ins.getOpcode().to_ulong())
    {
        case 1 : // and
        {
            instAnd( ins);
            break;
        }
        case 2 : // or
        {
            instOr( ins);
            break;
        }    
        case 3 : // xor
        {
            instXor( ins);
            break;
        }
        case 130 : // add
        {
            instAdd( ins);
            break;
        }
        case 131 : // sub
        {
            instSub( ins);
            break;
        }
        case 129 : // mul
        {
            instMul( ins);
            break;
        }
        case 128 : // div
        {
            instDiv( ins);
            break;
        }
        case 132 : // mov
        {
            instMov( ins);
            break;
        }
        case 68 : // not
        {
            instNot( ins);
            break;
        }
        case 192 : // dec
        {
            instDec( ins);
            break;
        }
        case 193 : // inc
        {
            instInc( ins);
            break;
        }
        case 194 : // ssgn
        {
            instSsgn( ins);
            break;
        }
        case 195 : // isgn
        {
            instIsgn( ins);
            break;
        }
    }
}

/**
 * The general policy of instruction implementation is to create the
 * temporary local register object, make all the calculations with it
 * and then assign it to one of the registers of the Simmy instance.
 */
/**
 * For most of arithmetic operations the general policy is to calculate
 * the resulting value in a temporary integer variable and then assign
 * it and it's sign to the register mentioned in the instruction.
 */

void Simmy::instAnd( Instruction ins)
{    
    Register reg; // temporary value
    if ( ins.op2IsARegister())
    {
        reg.setValue( regs[ ins.getOp1().to_ulong()].getValue() &= 
                     regs[ ins.getOp2().to_ulong()].getValue() );
        reg.setSign(regs[ ins.getOp1().to_ulong()].getSign() &
                    regs[ ins.getOp2().to_ulong()].getSign() );
    } else // op2 is a value
    {
        reg.setValue( regs[ ins.getOp1().to_ulong()].getValue() &= 
                     ins.getOp2() );
        reg.setSign(regs[ ins.getOp1().to_ulong()].getSign() &
                    ins.getOp2Sign());        
    }
    regs[ ins.getOp1().to_ulong()] = reg; // writing the result
}

void Simmy::instOr( Instruction ins)
{
    Register reg; // temporary value
    if ( ins.op2IsARegister())
    {
        reg.setValue( regs[ ins.getOp1().to_ulong()].getValue() |= 
                     regs[ ins.getOp2().to_ulong()].getValue() );
        reg.setSign(regs[ ins.getOp1().to_ulong()].getSign() |
                    regs[ ins.getOp2().to_ulong()].getSign() );
    } else // op2 is a value
    {
        reg.setValue( regs[ ins.getOp1().to_ulong()].getValue() |= 
                     ins.getOp2() );
        reg.setSign(regs[ ins.getOp1().to_ulong()].getSign() |
                    ins.getOp2Sign());        
    }
    regs[ ins.getOp1().to_ulong()] = reg;
}

void Simmy::instXor( Instruction ins)
{
    Register reg; // temporary value
    if ( ins.op2IsARegister())
    {
        reg.setValue( regs[ ins.getOp1().to_ulong()].getValue() ^= 
                     regs[ ins.getOp2().to_ulong()].getValue() );
                    reg.setSign(regs[ ins.getOp1().to_ulong()].getSign() ^
                    regs[ ins.getOp2().to_ulong()].getSign() );
    } else // op2 is a value
    {
        reg.setValue( regs[ ins.getOp1().to_ulong()].getValue() ^= 
                     ins.getOp2() );
        reg.setSign(regs[ ins.getOp1().to_ulong()].getSign() ^
                    ins.getOp2Sign());        
    }
    regs[ ins.getOp1().to_ulong()] = reg;
}

void Simmy::instAdd( Instruction ins)
{
    Register reg; // temporary value
    long tmp;
    if ( ins.op2IsARegister())
    {
        tmp = binToBip(regs[ ins.getOp1().to_ulong()].getSign() )*
                regs[ ins.getOp1().to_ulong()].getValue().to_ulong() + 
                binToBip(regs[ ins.getOp2().to_ulong()].getSign() )*
                regs[ ins.getOp2L().to_ulong()].getValue().to_ulong();
                reg.setValue( tmp);
        
        reg.setSign( tmp > 0 ? 1 : 0);
        
    } else // op2 is a value
    {
        tmp = binToBip(regs[ ins.getOp1().to_ulong()].getSign())*
            regs[ ins.getOp1().to_ulong()].getValue().to_ulong() + 
            binToBip( ins.getOp2Sign())*
            ins.getOp2().to_ulong();
        reg.setValue( tmp);
        
        reg.setSign( tmp > 0 ? 1 : 0);    
    }
    regs[ ins.getOp1().to_ulong()] = reg;    
}

void Simmy::instSub( Instruction ins)
{
    Register reg; // temporary value
    long tmp;
    
    if ( ins.op2IsARegister())
    {
        tmp = binToBip(regs[ ins.getOp1().to_ulong()].getSign() )*
                regs[ ins.getOp1().to_ulong()].getValue().to_ulong() - 
                binToBip(regs[ ins.getOp2().to_ulong()].getSign() )*
                regs[ ins.getOp2L().to_ulong()].getValue().to_ulong();
        reg.setValue( tmp);
        
        reg.setSign( tmp > 0 ? 1 : 0);
        
    } else // op2 is a value
    {
        tmp = binToBip( regs[ ins.getOp1().to_ulong()].getSign())*
                regs[ ins.getOp1().to_ulong()].getValue().to_ulong() - 
                binToBip( ins.getOp2Sign())*
                ins.getOp2().to_ulong();
        reg.setValue( tmp);
        
        reg.setSign( tmp > 0 ? 1 : 0);    
    }
    regs[ ins.getOp1().to_ulong()] = reg;    
}

void Simmy::instMul( Instruction ins)
{
    Register reg; // temporary value
    long tmp;
    
    if ( ins.op2IsARegister())
    {
        tmp = binToBip( regs[ ins.getOp1().to_ulong()].getSign() )*
                regs[ ins.getOp1().to_ulong()].getValue().to_ulong()* 
                binToBip(regs[ ins.getOp2().to_ulong()].getSign() )*
                regs[ ins.getOp2L().to_ulong()].getValue().to_ulong();
                reg.setValue( tmp);
            
        reg.setSign( tmp > 0 ? 1 : 0);
        
    } else // op2 is a value
    {
        tmp = binToBip( regs[ ins.getOp1().to_ulong()].getSign())*
                regs[ ins.getOp1().to_ulong()].getValue().to_ulong()* 
                binToBip( ins.getOp2Sign())*
                ins.getOp2().to_ulong();
        reg.setValue( tmp);
        
        reg.setSign( tmp > 0 ? 1 : 0);    
    }
    regs[ ins.getOp1().to_ulong()] = reg;    
    
}

void Simmy::instDiv( Instruction ins)
{
    Register reg; // temporary value
    long tmp;
    
    if ( ins.op2IsARegister())
    {
        tmp = binToBip( regs[ ins.getOp1().to_ulong()].getSign()) *
                regs[ ins.getOp1().to_ulong()].getValue().to_ulong()/
                binToBip(regs[ ins.getOp2().to_ulong()].getSign()) *
                regs[ ins.getOp2L().to_ulong()].getValue().to_ulong();
        reg.setValue( tmp);
        
        reg.setSign( tmp > 0 ? 1 : 0);
        
    } else // op2 is a value
    {
        tmp = binToBip( regs[ ins.getOp1().to_ulong()].getSign()) *
                regs[ ins.getOp1().to_ulong()].getValue().to_ulong() / 
                binToBip( ins.getOp2Sign()) *
                ins.getOp2().to_ulong();
        reg.setValue( tmp);
        
        reg.setSign( tmp > 0 ? 1 : 0);    
    }
    regs[ ins.getOp1().to_ulong()] = reg;    
    
}

void Simmy::instMov( Instruction ins)
{
    if ( ins.op2IsARegister())
    { 
        regs[ ins.getOp1().to_ulong()].setValue( 
                regs[ ins.getOp2L().to_ulong()].getValue());
        regs[ ins.getOp1().to_ulong()].setSign( 
                regs[ ins.getOp2L().to_ulong() ].getSign());
        
    } else // op2 is a value
    {
        regs[ ins.getOp1().to_ulong()].setValue( ins.getOp2M() +
                                                ins.getOp2L());
        regs[ ins.getOp1().to_ulong()].setSign( ins.getOp2Sign());
    }
}

void Simmy::instNot( Instruction ins)
{
    Register reg;
    reg.setValue( ~( regs[ ins.getOp1().to_ulong()].getValue()));
    reg.setSign( ~( regs[ ins.getOp1().to_ulong()].getSign()));    
    regs[ ins.getOp1().to_ulong()] = reg;    
}

void Simmy::instDec( Instruction ins)
{
    Register reg;
    long tmp;
    tmp = regs[ ins.getOp1().to_ulong()].getValue().to_ulong() - 1;
    reg.setValue( abs(tmp));
    reg.setSign( tmp > 0 ? 1 : 0);
    regs[ ins.getOp1().to_ulong()] = reg;    
}

void Simmy::instInc( Instruction ins)
{
    Register reg;
    long tmp;
    tmp = regs[ ins.getOp1().to_ulong()].getValue().to_ulong() + 1;
    reg.setValue( abs(tmp));
    reg.setSign( tmp > 0 ? 1 : 0);
    regs[ ins.getOp1().to_ulong()] = reg;      
}

void Simmy::instSsgn( Instruction ins)
{
    Register reg;
    reg.setSign( ins.getOp1Sign());
    regs[ ins.getOp1().to_ulong()] = reg;    
}

void Simmy::instIsgn( Instruction ins)
{
    Register reg;
    reg.setSign( ~( regs[ ins.getOp1().to_ulong()].getSign()));
    regs[ ins.getOp1().to_ulong()] = reg;    
}

/* mapping the binary values (0,1) to bipolar (-1; 1) */
hostSInt16 binToBip( hostUInt8 n)
{
    return 2*n-1;
}

/* mapping the bipolar values (-1; 1) to binary (0,1) */
hostUInt8 bipToBin( hostSInt16 n)
{
    return ( n+1)/2;
}

/* concatenating bitsets (to form a register value, for example) */
bitset<16> operator+(bitset <8> MSB, bitset<8> LSB)
{
    return bitset<16>( MSB.to_string() + LSB.to_string());
}

/* creating the bitset of 8 values from an integer number */
bitset<8> intToBitset8( hostUInt32 n)
{
    return bitset <8>( n);
}

/* creating the bitset of 16 values from an integer number */
bitset<16> intToBitset16( hostUInt32 n)
{
    return bitset <16>( n);
}

/* resizing the bitset */
bitset<16> lengthenBitSet( bitset<8> b)
{
    return b + bitset<8>( string( "00000000"));
}

/* resizing the bitset */
bitset<8> shortenBitSet( bitset<16> b)
{
    bitset<8> result;
    for ( hostUInt32 i = 0; i < 8; i++)
    {
        result[ i] = b[ i];
    }
    return result;
}
