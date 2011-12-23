#include <iostream>
#include "types.h"
#include <string.h>
#include <memory.h>

const int NUMBER_OF_REG    = 16;

const int EXIT_SUCCESS     = 0;
const int DEVIDED_BY_NULL  = 2;
const int NOT_SUPPORT      = 3;




class Simmy
{
    hostUInt8* cur_instr;				        // address current instruction
    hostUInt16 reg      [ NUMBER_OF_REG];		// array of register of Simmy
    bool       sign_reg [ NUMBER_OF_REG];		// array of sign register of Simmy
    hostUInt8  opcode; 	    // opcode command
    hostUInt16 op1;         // It is always a register number and reg[op1] = result operation 
    hostUInt16 op2;         // if op2 is a value then saved unsigned part value 2 else op2 is a register number    	
    bool       sign_op1;    // sign of operand1
    bool       sign_op2;    // sign of operand2
    bool       type_op2;
    bool       sign_bit;    // using only if operations with single operand
    hostUInt8  number_reg1; // number register1
    hostUInt8  number_reg2; // number register2
	
	void initAllParams ();
	
	void funcNop   ();
	void funcAnd   ();
	void funcOr    ();
	void funcXor   ();
	void funcAdd   ();
	void funcSub   ();
	void funcMul   ();
	int  funcDiv   ();
	void funcMov   ();
	void funcNot   ();
	void funcDec   ();
	void funcInc   ();
	void funcSsgn  ();
	void funcIsgn  ();
	
	hostSInt32  readInstr ();
	hostSInt32  execInstr ();

public:
    Simmy ( hostUInt8* bytes, hostUInt32 length);
    int execute ( hostUInt32 numInstr);
};
