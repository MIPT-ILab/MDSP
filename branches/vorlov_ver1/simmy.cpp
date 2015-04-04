/**
 * Simmy - simple educational simulator for SIM computer architecture
 * @author Orlov Vasiliy
 * Copyright 2011 MDSP team
 */

#include "simmy.h"

using namespace std;

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
        if ( !( control_byte & 8))
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