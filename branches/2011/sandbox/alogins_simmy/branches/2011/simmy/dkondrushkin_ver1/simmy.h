/**
 * realisation of Simmy - educational simulator for SIM computer architecture
 * @author Dennis Kondrushkin
 * Copyright 2011 MDSP team
 */
#include "./funcsim/types.h"
using namespace std;

class Simmy {
    hostUInt8* instr_start_addr; // saves an address of the 1st instruction
    hostUInt32 prog_length; // size of instruction massive in bytes
    hostUInt8* instr_pointer; // IP ( instruction pointer)

    hostUInt16 registers[16]; // register massive

    /* Saves signs of registers,
     * which is a meaning of 4th bit ( 0 - negative, 1 - positive)
     * and 7 must be zeroes.
     * Note : zero ( 0) is positive ( its sign is 1)
     */
    hostUInt8 registers_sign[16]; 

    // enum for operation codes
    typedef enum OpCode
    {
        // bitwise logical operations
        AND = 1, OR, XOR,             // 0000 0001, 0000 0010, 0000 0011				 
        NOT = 68,	              // 0100 0100

        // integer arithmetics
        DEC = 192, INC, SSGN, ISGN,   // 1100 0000, 1100 0001, 1100 0010, 1100 0011
        DIV = 128, MUL, ADD, SUB, MOV // 1000 0000, 1000 0001, 1000 0010, 1000 0011, 1000 0100
    } OpCode;

public:
	
    // constructor gets address and length of instruction massive
    Simmy ( hostUInt8* bytes, hostUInt32 length);
    // Execute perform given number of instructons
    hostSInt32  Execute ( hostUInt32 number_of_instrs);

        /* 1. Operations with 1 operand */

    void complement( hostUInt8 register_number); // NOT

    void decrement( hostUInt8 register_number); // DEC
    void increment( hostUInt8 register_number); // INC
    void ssgn( hostUInt8 register_number, hostUInt8 sign ); // SSGN - set a new sign
    void isgn( hostUInt8 register_number); // ISGN - sign inversion


        /* 2. Operations with 2 operand 
	 * are realised in overload functions :
	 * one for register - register and
	 * another for register - value type of command
	 */

    void and( hostUInt8 register_number1, hostUInt8 register_number2);
    void and( hostUInt8 register_number1, hostUInt16 value,  hostUInt8 value_sign);

    void or( hostUInt8 register_number1, hostUInt8 register_number2);
    void or( hostUInt8 register_number1, hostUInt16 value,  hostUInt8 value_sign);
 
    void xor( hostUInt8 register_number1, hostUInt8 register_number2);
    void xor( hostUInt8 register_number1, hostUInt16 value,  hostUInt8 value_sign);

    void add( hostUInt8 register_number1, hostUInt8 register_number2);
    void add( hostUInt8 register_number1, hostUInt16 value,  hostUInt8 value_sign);

    void sub( hostUInt8 register_number1, hostUInt8 register_number2);
    void sub( hostUInt8 register_number1, hostUInt16 value,  hostUInt8 value_sign);
	
    void mul( hostUInt8 register_number1, hostUInt8 register_number2);
    void mul( hostUInt8 register_number1, hostUInt16 value,  hostUInt8 value_sign);

    void div( hostUInt8 register_number1, hostUInt8 register_number2);
    void div( hostUInt8 register_number1, hostUInt16 value,  hostUInt8 value_sign);
 
    void mov( hostUInt8 register_number1, hostUInt8 register_number2);
    void mov( hostUInt8 register_number1, hostUInt16 value,  hostUInt8 value_sign);
};


//=================================================================
//                 Implementation of Simmy class
//=================================================================

Simmy :: Simmy( hostUInt8* bytes, hostUInt32 length)
{
    instr_start_addr = bytes;
    prog_length = length;
    instr_pointer = instr_start_addr;
}

hostSInt32  Simmy :: Execute ( hostUInt32 number_of_instrs)
{
    bool one_op_instr; // flag for type of operation ( one / two operators)

    hostUInt8* opcode_addr; // address of current operation and its meaning
    hostUInt8 opcode;		

    hostUInt8* control_byte_addr; // address of control byte and its meaning
    hostUInt8 control_byte;

    hostUInt8* register_number_addr; // address of register ( 1st operand) and its meaning
    hostUInt8 register_number;

    /* data for analysis of 2nd operand */
    bool type_op2;			// flag for type of 2nd operand
    hostUInt8 sign_op2;		// sign
    hostUInt8* op2_addr;	// address
    hostUInt16 val_op2;		// value
    hostUInt8 lsb_op2;		// LSB - the least significant byte


    for ( hostUInt32 i = 0; i < number_of_instrs; i++)
    {		

        // get the opcode value ( 1st byte)
        opcode_addr = instr_pointer;
        opcode = *opcode_addr;		
        one_op_instr = ( opcode & 64);	// 0100 or 1100 in the second part of byte in opcode 

        // get the cotrol byte value ( 2nd byte)
        control_byte_addr = instr_pointer + 1;
        control_byte = *control_byte_addr;

        // get the register number ( 3rd byte)
        register_number_addr = instr_pointer + 2;
        register_number = *register_number_addr;


        // analysing control byte
        if ( one_op_instr )
        {
            if ( opcode & 128)	// & 1000 000 - indication of 1 operand instructions for integer arithmetics
            {
                switch ( opcode)
                {
                    case DEC :
                        {
                            decrement( register_number);
                            break;
                        }
                    case INC : 
                        {
                            increment( register_number);
                            break;
                        }
                   case SSGN : 
                        {
			    ssgn( register_number, control_byte & 2);
                            break;
                        }
                   case ISGN : 
                        {
                            isgn( register_number);
                            break;
                        }
                }
            } else // 1 operand instructions for bitwise logical operations
            {
                complement( register_number);
            }
        } else	// 2 operand instructions
        {
            type_op2 = ( control_byte & 4); // & 0000 0100 - flag, that indicates what is in 2nd operand ( register - if 0, value - if 1)
            sign_op2 = ( control_byte & 8); // & 0000 1000 - gets a sign of 2nd operand
            op2_addr = instr_pointer + 3; // gets the address of 2nd operand LSB ( 4th byte in instruction)

            if ( type_op2)
            {
                val_op2 = *( ( hostUInt16*) op2_addr); // take 2 bytes from op2_addr
            } else
            {
                lsb_op2 = *( ( hostUInt8*) op2_addr); // take 1st byte from op2_addr ( LSB) - number of register
            }			

            if ( opcode & 128) // & 1000 0000 - indication of 2 operand instructions for integer arithmetics
            {
                switch ( opcode )
                {
                    case DIV : 
                        {
                            if ( type_op2)
                            {
                                div( register_number, val_op2, sign_op2);
                            } else
                            {
                                div( register_number, lsb_op2);
                            }
                            break;							
                        }
                    case MUL : 
                        {
                            if ( type_op2)
                            {
                                mul( register_number, val_op2, sign_op2);
                            } else
                            {
                                mul( register_number, lsb_op2);
                            }
                            break;
                        }
                    case ADD :						
                        {
                            if ( type_op2)
                                {
                                    add( register_number, val_op2, sign_op2);
                                } else
                                {
                                    add( register_number, lsb_op2);
                                }
                                break;
                        }
                    case SUB :
                        {
                            if ( type_op2)
                            {
                                sub( register_number, val_op2, sign_op2);
                            } else
                            {
                                sub( register_number, lsb_op2);
                            }
                            break;							
                        }
                    case MOV :
                        {
                            if ( type_op2)
                            {
                                mov( register_number, val_op2, sign_op2);
                            } else
                            {
                                mov( register_number, lsb_op2);
                            }
                            break;
                        }
                    }
                } else	// 2 operand instructions for bitwise logical operations
                {
                    switch ( opcode )
                        {
                            case AND : 
                                {
                                    if ( type_op2)
                                    {
                                        and( register_number, val_op2, sign_op2);
                                    } else
                                    {
                                        and( register_number, lsb_op2);
                                    }
                                    break;
                                }
                            case OR :
                                {
                                    if ( type_op2)
                                    {
                                        or( register_number, val_op2, sign_op2);
                                    } else
                                    {
                                        or( register_number, lsb_op2);
                                    }
                                    break;
                                }
                            case XOR :
                                {
                                    if ( type_op2)
                                    {
                                        xor( register_number, val_op2, sign_op2);
                                    } else
                                    {
                                        xor( register_number, lsb_op2);
                                    }
                                    break;
                                }
                        }
                }
        }

        // increase IP to execute next instruction
        instr_pointer += 5;
    }
	
    // return a value of register #0 with sign 
    if ( registers_sign[0])
    {
        return registers[0];
    } else
    {
        return -registers[0];
    }		
}


void Simmy :: complement( hostUInt8 register_number)
{
    registers[register_number] = ~ registers[register_number];
    registers_sign[register_number] = 8 & ( ~ registers_sign[register_number]); // sign must be saved in 4th bit
}

void Simmy :: decrement( hostUInt8 register_number)
{
    if ( registers_sign[register_number]) // positive
    {
        if ( registers[register_number]) // != 0
        {
            --registers[register_number]; // -1
        } else // == 0
        {
            ++registers[register_number]; // +1
            registers_sign[register_number] = 0; // change the sign on negative
        }
    } else // negative
    {
        ++registers[register_number]; // +1
    }
}


void Simmy :: increment( hostUInt8 register_number)
{
    if ( registers_sign[register_number]) // positive
    {
        ++registers[register_number]; // +1
    } else // negative
    {
        --registers[register_number]; // -1
        if ( ! registers[register_number]) // == 0
        {
            registers_sign[register_number] = 8; // change the sign on positive
        }
    }
}


void Simmy :: ssgn ( hostUInt8 register_number, hostUInt8 sign )
{
     registers_sign[register_number] = (sign << 2); // in given value "sign" sign is in 2nd bit ( but must be in 4th)
}


void Simmy :: isgn ( hostUInt8 register_number)
{
     registers_sign[register_number] = 8 & ( ~ registers_sign[register_number]); // inverse all sign' byte and gets only 4th bit
}


void Simmy :: and( hostUInt8 register_number1, hostUInt8 register_number2)
{
     registers[register_number1] = registers[register_number1] & registers[register_number2];
     registers_sign[register_number1] = registers_sign[register_number1] & registers_sign[register_number2];
}

void Simmy :: and( hostUInt8 register_number1, hostUInt16 value, hostUInt8 value_sign)
{
     registers[register_number1] = registers[register_number1] & value;
     registers_sign[register_number1] = registers_sign[register_number1] & value_sign;
}


void Simmy :: or( hostUInt8 register_number1, hostUInt8 register_number2)
{
     registers[register_number1] = registers[register_number1] | registers[register_number2];
     registers_sign[register_number1] = registers_sign[register_number1] | registers_sign[register_number2];
}

void Simmy :: or( hostUInt8 register_number1, hostUInt16 value, hostUInt8 value_sign)
{
     registers[register_number1] = registers[register_number1] | value;
     registers_sign[register_number1] = registers_sign[register_number1] | value_sign;
}

void Simmy :: xor( hostUInt8 register_number1, hostUInt8 register_number2)
{
     registers[register_number1] = registers[register_number1] ^ registers[register_number2];
     registers_sign[register_number1] = registers_sign[register_number1] ^ registers_sign[register_number2];
     registers_sign[register_number1] = 8 & registers_sign[register_number1]; // gets only 4th bit
}

void Simmy :: xor( hostUInt8 register_number1, hostUInt16 value, hostUInt8 value_sign)
{
     registers[register_number1] = registers[register_number1] ^ value;
     registers_sign[register_number1] = registers_sign[register_number1] ^ value_sign;
     registers_sign[register_number1] = 8 & registers_sign[register_number1]; // gets only 4th bit
}


void Simmy :: add( hostUInt8 register_number1, hostUInt8 register_number2)
{
     if ( registers_sign[register_number1] == registers_sign[register_number2]) // sign are identical
     {
         registers[register_number1] = registers[register_number1] + registers[register_number2]; // register1 + register2
     } else // sign aren't identical
     {
         if ( registers[register_number1] >= registers[register_number2]) // meaning of the 1st register is bigger than the 2nd
         {
             registers[register_number1] = registers[register_number1] - registers[register_number2]; // register1 -  register2
         } else // meaning of the 1st register is less than the 2nd
         {
             registers[register_number1] = registers[register_number2] - registers[register_number1]; // register2 -  register1
             registers_sign[register_number1] = registers_sign[register_number2]; // change the sign on the register2's sign
         }
     }
}

void Simmy :: add( hostUInt8 register_number1, hostUInt16 value,  hostUInt8 value_sign)
{
     if ( registers_sign[register_number1] == value_sign) // sign are identical
     {
         registers[register_number1] = registers[register_number1] + value; // register1 + value
     } else // sign aren't identical
     {
         if ( registers[register_number1] >= value) // meaning of the 1st register is bigger than the value
         {
             registers[register_number1] = registers[register_number1] - value; // register1 -  value
         } else // meaning of the 1st register is less than the value
         {
             registers[register_number1] = value - registers[register_number1]; // value -  register1
             registers_sign[register_number1] = value_sign; // change the sign on the value's sign
         }
     }
}


void Simmy :: sub( hostUInt8 register_number1, hostUInt8 register_number2)
{
    if ( registers_sign[register_number1] != registers_sign[register_number2]) // sign aren't identical
    {
        registers[register_number1] = registers[register_number1] + registers[register_number2]; // register1 + register2
    } else // sign are identical
    {
        if ( registers[register_number1] >= registers[register_number2]) // meaning of the 1st register is bigger than the 2nd
        {
            registers[register_number1] = registers[register_number1] - registers[register_number2]; // register1 - register2
        } else // meaning of the 1st register is less than the 2nd
        {
            registers[register_number1] = registers[register_number2] - registers[register_number1]; // register2 - register1
            registers_sign[register_number1] = 8 & ( ~registers_sign[register_number1]); // inverse the sign
        }
    }
}

void Simmy :: sub( hostUInt8 register_number1, hostUInt16 value,  hostUInt8 value_sign)
{
    if ( registers_sign[register_number1] != value_sign) // sign aren't identical
    {
        registers[register_number1] = registers[register_number1] + value; // register1 + value
    } else // sign are identical
    {
        if ( registers[register_number1] >= value) // meaning of the 1st register is bigger than the value
        {
            registers[register_number1] = registers[register_number1] - value; // register1 - value
        } else // meaning of the 1st register is less than the value
        {
            registers[register_number1] = value - registers[register_number1]; // value -  register1
            registers_sign[register_number1] = 8 & ( ~registers_sign[register_number1]); // inverse the sign
        }
    }
}


void Simmy :: mul( hostUInt8 register_number1, hostUInt8 register_number2)
{
    registers[register_number1] = registers[register_number1] * registers[register_number2];
    registers_sign[register_number1] =  8 & ( ~ ( registers_sign[register_number1] ^ registers_sign[register_number2])); 
}

void Simmy :: mul( hostUInt8 register_number1, hostUInt16 value,  hostUInt8 value_sign)
{
    registers[register_number1] = registers[register_number1] * value;
    registers_sign[register_number1] = 8 & ( ~ ( registers_sign[register_number1] ^ value_sign));
}


void Simmy :: div( hostUInt8 register_number1, hostUInt8 register_number2)
{
    registers[register_number1] = registers[register_number1] / registers[register_number2];
    registers_sign[register_number1] =  8 & ( ~ ( registers_sign[register_number1] ^ registers_sign[register_number2]));
}

void Simmy :: div( hostUInt8 register_number1, hostUInt16 value,  hostUInt8 value_sign)
{
    registers[register_number1] = registers[register_number1] / value;
    registers_sign[register_number1] = 8 & ( ~ ( registers_sign[register_number1] ^ value_sign));
}


void Simmy :: mov( hostUInt8 register_number1, hostUInt8 register_number2)
{
    registers[register_number1] = registers[register_number2];
    registers_sign[register_number1] = registers_sign[register_number2];
}

void Simmy :: mov( hostUInt8 register_number1, hostUInt16 value,  hostUInt8 value_sign)
{
    registers[register_number1] = value;
    registers_sign[register_number1] = value_sign;
}