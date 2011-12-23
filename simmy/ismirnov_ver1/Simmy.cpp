/**
 * Simmy.cpp
 * @author Igor Smirnov
 * Copyright 2011 MDSP team
 */

#include <iostream>
#include <cstring>
#include "types.h"

using namespace std;

#define MAX_registres 16

/*Instructions:
 *  1000 0000   128   DIV        Integer devision
 *  1000 0001   129   MUL        Integer multiplication
 *  1000 0010   130   ADD        Integer addition
 *  1000 0011   131   SUB        Integer subtraction
 *  1000 0100   132   MOV        Move a value into a register
 *  1100 0000   192   DEC        Integer decrement
 *  1100 0001   193   INC        Integer increment
 *  1100 0010   194   SSGN       Set a new sign
 *  1100 0011   195   ISGN       Sign inversion
 *  0000 0001     1   AND        Bitwise logical AND
 *  0000 0010     2   OR         Bitwise logical OR
 *  0000 0011     3   XOR        Bitwise exclusive OR
 *  0100 0100    68   NOT        Bitwise logical negation
 */
enum Integer_arithmetics        { DIV = 128, MUL, ADD, SUB, MOV, DEC = 192, INC, SSGN, ISGN };
enum Bitwise_logical_operations { AND = 1, OR, XOR, NOT = 68 };

hostSInt32  Unknown_Op = 0; //Is equal to one if there was an attempt to execute an existing command
hostSInt32 Access_Fail = 0; //Is equal to one if there was an attempt to appeal to non-existent register

class Register
{
    public:
        hostUInt16 r[MAX_registres]; //Array of registres r0...r15;
        bool reg_sign[MAX_registres];


        void Check_State();  //Print state of all registres after each execution;
                Register() { for (hostSInt32 i = 0; i < MAX_registres; i++) r[i] = 0; };
};


void Register:: Check_State()
{
    for (hostSInt32 i = 0; i < MAX_registres; i++)
    {
        hostUInt8 c;
        c = ((reg_sign[i] == 0) && (r[i] != 0)) ? '-' : ' ';
        cout << "r[" << i << "] =" << c << r[i] << "; ";
        if ((i % 8 == 0) && (i != 0)) cout << "\n";


    }
    cout << "\n----------------------------------------------------------------------------------------------\n\n";
}

//----------------------------------------------------------------------------------------------------------

class Simmy: public Register
{
    hostUInt8* instr_adress;
    hostUInt8  opcode;
    char* true_name;
    hostUInt16 op1;
    hostUInt16 op2;
    hostSInt32 reg_num;
    hostSInt32 op2_num;
    bool op1_sign;
    bool op2_sign;
    bool op2_type;

    void Parsing ();    //Function to decode array of instructions. It will fill all fields in class Simmy except instr_adress;
    void Execution ();
    void Info_Print (); //Print information about executed command
    public:
        Simmy ( hostUInt8* bytes, hostUInt32 lenght);

        /* Execute certain number of instructions
           When the given number of instructions is
           executed the method returns a value of r0.*/
       hostUInt32 Execute ( hostUInt32 number_of_instrs);
};


Simmy:: Simmy( hostUInt8* bytes, hostUInt32 lenght): Register()
{
    instr_adress = bytes;
}


hostUInt32 Simmy:: Execute( hostUInt32 number_of_instrs)
{
    for (int i = 0; i < number_of_instrs; i++, instr_adress += 5)
    {
        Parsing ();
        Execution ();
        if ((Unknown_Op) || (Access_Fail)) goto Exit;
        Info_Print ();
        Check_State ();
    }
Exit:
    return r[0];
}


void Simmy:: Parsing()
{
    hostUInt8* byte_of_instr = instr_adress;
    true_name = " ";
    //N
    opcode = *byte_of_instr;
    //N+1
    byte_of_instr++;
    if ( (*byte_of_instr) & 2 ) op1_sign = 1;   //positive
                           else op1_sign = 0;   //negative


    if ( (*byte_of_instr) & 4 ) op2_type = 1;   //value
                           else op2_type = 0;   //register


    if ( (*byte_of_instr) & 8 ) op2_sign = 1;   //positive
                           else op2_sign = 0;   //negative
    //N+2
    if (*(++byte_of_instr) > MAX_registres)
    {
        Access_Fail = 1;
        printf ("***\nUnable to access to r[%d]. Simmy contains only %d registres\n***\n", *(byte_of_instr), MAX_registres);
        return;
    }
    op1 = r[*(byte_of_instr)];
    reg_num = *byte_of_instr;
    //N+3
    op2 = *((hostUInt16* )(++byte_of_instr));
    if (op2_type == 0)
    {
        op2_sign = reg_sign[op2];
        op2_num = op2;
        op2 = r[op2_num];
    }

}


void Simmy:: Execution ()
{
RE:
    switch (opcode)
    {
        //Integer_arithmetics
        case (DIV): if (op2 == 0) printf("Error: division by zero\n");
                    else
                    {
                        r[reg_num] = op1 / op2;
                        if (reg_sign[reg_num] == op2_sign) reg_sign[reg_num] = 1;
                                                      else reg_sign[reg_num] = 0;
                    }
                    true_name = "DIV";
                    break;

        case (MUL): r[reg_num] = op1 * op2;
                    if (reg_sign[reg_num] == op2_sign) reg_sign[reg_num] = 1;
                                                  else reg_sign[reg_num] = 0;
                    true_name = "MUL";
                    break;

        case (ADD): if (reg_sign[reg_num] == op2_sign)
                    {
                        r[reg_num] += op2;
                    }
                    else
                    if (reg_sign[reg_num] != op2_sign)
                    {
                        r[reg_num] = abs((int)(r[reg_num] - op2));
                        if (r[reg_num] < op2) reg_sign[reg_num] = op2_sign;
                    }
                    if (strcmp(true_name, "SUB") != 0) true_name = "ADD";   //for correct printing in function Info_Print()
                    else
                    {
                        if (op2_sign == 0) op2_sign = 1;
                        else op2_sign = 0;
                    }
                    break;

        case (SUB): opcode = ADD;
                    if (op2_sign == 0) op2_sign = 1;
                    else op2_sign = 0;
                    true_name = "SUB";
                    goto RE;
                    break;

        case (MOV): r[reg_num] = op2;
                    reg_sign[reg_num] = op2_sign;
                    true_name = "MOV";
                    break;

        case (DEC): if (r[reg_num] == 0)
                    {
                        r[reg_num] = 1;
                        reg_sign[reg_num] = 0;
                    }
                    else
                    {
                        if (reg_sign[reg_num] == 1) r[reg_num]--;
                                               else r[reg_num]++;
                    }
                    true_name = "DEC";
                    break;

        case (INC): if (r[reg_num] == 0)
                    {
                        r[reg_num] = 1;
                        reg_sign[reg_num] = 1;
                    }
                    else
                    {
                        if (reg_sign[reg_num] == 1) r[reg_num]++;
                                               else r[reg_num]--;
                    }
                    true_name = "INC";
                    break;

        case(SSGN): reg_sign[reg_num] = op1_sign;
                    true_name = "SSGN";
                    break;

        case(ISGN): if (reg_sign[reg_num] == 1) reg_sign[reg_num] = 0;
                    else reg_sign[reg_num] = 1;
                    true_name = "ISGN";
                    break;

        //Bitwise_logical_operations
        case (AND): r[reg_num] = op1 & op2;
                    if ((reg_sign[reg_num] == 1) && ( op2_sign == 1)) reg_sign[reg_num] = 1;
                                                                 else reg_sign[reg_num] = 0;
                    true_name = "AND";
                    break;

        case ( OR): r[reg_num] = op1 | op2;
                    if ((reg_sign[reg_num] == 0) && ( op2_sign == 0)) reg_sign[reg_num] = 0;
                                                                 else reg_sign[reg_num] = 1;
                    true_name = "OR";
                    break;

        case (XOR): r[reg_num] = op1 ^ op2;
                    if (reg_sign[reg_num] == op2_sign) reg_sign[reg_num] = 0;
                                                  else reg_sign[reg_num] = 1;
                    true_name = "XOR";
                    break;

        case (NOT): r[reg_num] = ~op1;
                    if (reg_sign[reg_num] == 0) reg_sign[reg_num] = 1;
                                           else reg_sign[reg_num] = 0;
                    true_name = "NOT";
                    break;
        //Unknown operation
        default: printf("Command %d not found\n", opcode);
                 true_name = "Unknown";
                 Unknown_Op = 1;
                 break;
    }
    return;
}


void Simmy:: Info_Print ()
{
    hostUInt8 c = (op2_sign == 0) ? '-' : ' ';
    if (((opcode >= AND) && (opcode <= XOR)) || ((opcode >= DIV) && (opcode <= MOV)))
    {
        if (op2_type == 0) printf("%s r%d r%d\n", true_name, reg_num, op2_num);
        else printf("%s r%d %c%d\n", true_name, reg_num, c, op2);
    }
    else
    {
        printf("%s r%d ", true_name, reg_num);
        if (opcode == SSGN) printf("%d\n", op1_sign);
        printf("\n");
    }
}


//==========================================================================================================


/**Instructions:
 *  1000 0000   128   DIV        Integer devision
 *  1000 0001   129   MUL        Integer multiplication
 *  1000 0010   130   ADD        Integer addition
 *  1000 0011   131   SUB        Integer subtraction
 *  1000 0100   132   MOV        Move a value into a register
 *  1100 0000   192   DEC        Integer decrement
 *  1100 0001   193   INC        Integer increment
 *  1100 0010   194   SSGN       Set a new sign
 *  1100 0011   195   ISGN       Sign inversion
 *  0000 0001     1   AND        Bitwise logical AND
 *  0000 0010     2   OR         Bitwise logical OR
 *  0000 0011     3   XOR        Bitwise exclusive OR
 *  0100 0100    68   NOT        Bitwise logical negation


 Start address                                                 Start address
     of the next instr                                               of the instr
            ↓                                                           ↓
           N+5         N+4         N+3         N+2         N+1          N
            ↓           ↓           ↓           ↓           ↓           ↓
    Next    │ MSB of op2│ LSB of op2│    op1    │  Control  │   Opcode  │  Previous
    instr   │ 0100 0000 │ 0100 1101 │ 0000 0011 │ 0000 0100 │ 0100 1101 │  instr
                                                       ││
                                          sign of op2 ―┘│
                                           type of op2 ―┘
*/

int main()
{
    hostUInt8 array[] = { 132, 12, 0,   6,    0,
                          132,  4,  1, 255, 217,
                           68,  0,  1,   1,   0,
                          131,  0,  0,   1,   0,
                          130, 12,  0,  17,   0,
                          130,  4,  0,  34,   0,
                          193,  2,  2,   0,   0,
                          130, 12, 40, 120,   0,
                          131, 12,  0, 200,   0,
                          192,  2,  0,   0,   0,
                          194,  1,  0,   0,   0,
                          195,  0,  1,  78,   0,
                          233, 12,  1, 123,   0 };
    Simmy My_simmy(array, 1);
    My_simmy.Execute( sizeof(array)/(5*sizeof(hostUInt8)) );
    return 0;
}
