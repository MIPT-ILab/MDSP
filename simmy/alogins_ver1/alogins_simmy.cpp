/*
 *    simmy.cpp
 *    Implementation of Simmy : simple educational simulator
 *
 */
 /*   Copyright: Alvis Logins (025)
  *   Intel MDSP iLab group
  *   December 2011
  */

#include "stdafx.h"
#include <iostream>

#define INSTR_LENGTH 5
#define REG_NUM 16

#define DEBUG 1

using namespace std;
using namespace System;

class Simmy {

    /* The queue:
     * Execute (sets the memory)->fetcher->decoder->ALU->writeBack->pcUpdate->Execute->...
     * 
     * Each part calls directly to the next part
     * (As I understand, there is no bus or DMA in the microprocessor
     *  between its compinents. In this version, there is also no ports)
     * 
     * pcUpdate is responsible for starting the process and EOF control
     *
     * IMPORTANT! The OS is responsible for writing commands to VirtMem and
     * setting the PC to the first instruction. I don't realy know, how exactly
     * is realized the program ending in reality, so here I assumed that OS also
     * sets and controls the PC after program ending. So, Simmy will have global
     * variable ( implementation of OS), that defines the last/first line of command string.
     *
     * (There is no pipeline in this version)
     */

    unsigned char *instr_last_addr;
    unsigned char *instr_start_addr;

    /* Types:
     * - number_of_instrs: unsigned int
     * - pointer to the instruction: unsigned char
     * - register values: int
     * - pointer to the register: unsigned char
     *
     */

    // Performs operations. Target register is needed to call to writeBack
    void ALU( int x, int y, unsigned char opcode, unsigned char target_reg);
    
    // Parses the command & fetching values from RF
    void decoder( unsigned char *instruction);

    // Gets the command from MeM and gives it to decoder
    void fetcher();

    // Gets the result of ALU and writes it to RF
    void writeBack( int result, unsigned char target_reg);

    // Updates the program counter and controls the end of command line
    void pcUpdate();

    // Registers. Using: Registers reg( <number of registers> );
    class Registers;

    Registers *registers;

public:
    
    Simmy( unsigned char* bytes, unsigned int lenght);
    ~Simmy();
    
    // execute certain number of instructions
    int Execute ( unsigned int number_of_instrs);

    friend class Registers;
};

class Simmy::Registers {

    // Array of registers
    int *register_array;
    // Program counter
    unsigned char* pc;

    void write( unsigned char reg_num, int value)
    {
        register_array[ reg_num] = value;
        #ifdef DEBUG
        cout << "New value " << value << " was written in r" << (int)reg_num << endl;
        #endif
    }

    int read( unsigned char reg_num)
    {
        #ifdef DEBUG
        cout << "Reading from r" << (int)reg_num << ": " << register_array[ reg_num] << endl;
        #endif

        return register_array[ reg_num];
    }

    unsigned char* getPc()
    {
        return pc;
    }

    void setPc( unsigned char* new_value)
    {
        pc = new_value;
    }

    public:
        Registers()
        {
            #ifdef DEBUG
            cout << "Creating registers (" << REG_NUM << ")..." << endl;
            #endif
            register_array = (int *) malloc( sizeof( int) * REG_NUM);
            memset( register_array, 0, sizeof( int) * REG_NUM);
        }

        ~Registers()
        {
            cout << "Destroying registers." << endl;
            free( register_array);
        }

        void output()
        {
            int i;
            cout << "Register status:" << endl;
            for ( i = 0; i < REG_NUM; i++)
            {
                cout << register_array[i] << endl;
            }
        }

    friend class Simmy;
};

Simmy::Simmy( unsigned char* bytes, unsigned int length)
{
    instr_start_addr = bytes;
    instr_last_addr = bytes;
    instr_last_addr += length;

    registers = new Simmy::Registers();
    registers->setPc( instr_start_addr);
};

Simmy::~Simmy()
{
    delete registers;
};

int Simmy::Execute( unsigned int number_of_instr)
{
    unsigned int i;
    for ( i = 0; i < number_of_instr; i++)
    {
        fetcher();
    }
    
    Simmy::registers->output();

    return 0;
};

void Simmy::decoder( unsigned char *instruction)
{
    // create a simple instruction basing on the following pattern:
    //
    //    Start address                                                Start address 
    //  of the next instr                                              of the instr
    //         ↓                                                           ↓
    //        N+5         N+4         N+3         N+2         N+1          N
    //         ↓           ↓           ↓           ↓           ↓           ↓
    // Next    │ MSB of op2│ LSB of op2│    op1    │  Control  │   Opcode  │  Previous 
    // instr   │ 0100 0000 │ 0100 1101 │ 0000 0011 │ 0000 0100 │ 0100 1101 │  instr
    //                                                    ││
    //                                       sign of op2 ―┘│
    //                                        type of op2 ―┘   
    #ifdef DEBUG
    cout << "Decoder: got a new instruction... ";
    #endif

    // get the start address of the instr
    unsigned char* instr_start_addr = instruction;

    // get the opcode value
    unsigned char* opcode_addr = instr_start_addr;
    unsigned char opcode = *opcode_addr;

    // get the cotrol byte value
    unsigned char* control_byte_addr = instr_start_addr + 1;
    unsigned char control_byte = ( *control_byte_addr);

    
    bool type_op2 = control_byte & 4; // != 0 only if the 3rd bit is 1;
    // 1 => value; 0 => register
    bool sign_op2 = control_byte & 8; // != 0 only if the 4th bit is 1;
   
    // get the value of op1
    unsigned char* op1_addr = instr_start_addr + 2;
    int val_op1 = *( ( unsigned char*) op1_addr); // take 1 byte from op1_addr

    // get the value of op2
    unsigned char* op2_addr = instr_start_addr + 3;
    int val_op2 = *( ( unsigned short*) op2_addr);
    
    // apply the sign
    if ( !sign_op2 && type_op2) {
        val_op2 = -1 * val_op2;
    }

    #ifdef DEBUG
    cout << "Result: \n"
         << "\t - opcode: " << ( unsigned char) opcode << "\n"
         << "\t - operand_2 = " << ( type_op2 ? "" : "r") << val_op2 << "\n"
         << "\t - operand_1 = r" << val_op1 << "\n";
    #endif

    //get values from registers
    int x = 0;
    int y = 0;

    x = Simmy::registers->read( val_op1); 
    if ( !( type_op2))
    {
        y = Simmy::registers->read( val_op2);
    } else
    {
        y = val_op2;
    }  

    Simmy::ALU( x, y, opcode, val_op1);
};

void Simmy::fetcher()
{
    unsigned char* next_instruction;

    next_instruction = Simmy::registers->getPc();
    #ifdef DEBUG
    cout << "Fetcher: next instruction on "<< (int ) next_instruction << endl;
    #endif
    decoder( next_instruction);
};

void Simmy::ALU( int x, int y, unsigned char opcode, unsigned char target_reg)
{
    /* Result of the operation is ALWAYS saved in the register pointed
     * in the first operand. It will be saved by other part of the Simmy,
     * not ALU.
     *
     * In operation with 2 operands: op1 is represented as x, op2 - as y.
     */
    #ifdef DEBUG
    cout << "ALU: processing " << x << " <" << opcode << "> " << y << endl;
    #endif

    int result = 0;

    switch ( opcode)
    {
        /* Logical operations with 2 operands */
        case 1:
            // AND (0000 0001)
            result = x & y;
        break;
        case 2:
            // OR
            result = x | y;
        break;
        case 3:
            // XOR
            result = x ^ y;
        break;

        /* Arithmetics with 2 operands */
        case 130:
            // ADD (1000 0010)
            result = x + y;
        break;
        case 131:
            // SUB
            result = x - y;
        break;
        case 129:
            // MUL
            result = x * y;
        break;
        case 128:
            // DIV
            result = x / y;
        break;
        case 132:
            // MOV
            result = y;
        break;

        /* Logical operations with one operand. Working only with x. */
        case 68:
            // NOT (0100 0100)
            result = x ^ 255;
        break;

        /* Arithmetics with one operand */
        case 192:
            // DEC (1100 0000)
            result = x - 1;
        break;
        case 193:
            // INC
            result = x + 1;
        break;
        case 194:
            // SSGN
            // x - new sign. y - value (SSGN 1, r3);
            if ( ( y < 0) && ( x == 1))
                result = (-1) * y;
        break;
        case 195:
            // ISGN
            result = (-1) * x;
        break;
    }

    writeBack( result, target_reg);
};

void Simmy::writeBack( int result, unsigned char target_reg)
{
    Simmy::registers->write( target_reg, result);
    pcUpdate();   
};

void Simmy::pcUpdate()
{
    unsigned char* next_instruction;

    next_instruction = Simmy::registers->getPc();
    #ifdef DEBUG
    cout << "pcUpdate: current instruction on "<< ( int) next_instruction
         << ". Trying to update...";
    #endif

    if ( next_instruction + INSTR_LENGTH > instr_last_addr)
    {
        cout << "Error! Command is out of memory: \n"
             << "\t Next pointer: " << (int ) (next_instruction + 1)
             << "\n \t Max pointer: " << (int ) instr_last_addr << "\n";
        system("pause");
        exit( -1);
    } else {
        cout << "OK" << endl;
        next_instruction += INSTR_LENGTH;
        Simmy::registers->setPc( next_instruction);
    }
};

int main()
{
    #ifdef DEBUG
    unsigned char bytes[18] = {

        /* MOV r1, 5 */
        132,
        12,  
        1,  
        5, 
        0, 

        /* MOV r3, r1 */
        132,
        8,
        3,
        1,
        0,

        /* ADD r3, r1 */
        130,
        8,
        3,
        1,
        0

    };
    

    Simmy simmy( bytes, 18);
    simmy.Execute( 3);
    system("pause");
    #endif

    return 0;
}