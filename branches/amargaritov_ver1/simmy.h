/*
 * simmy.h
 *
 *  Created on: 16.12.2011
 *      Author: art
 */

#ifndef SIMMY_H_
#define SIMMY_H_

#include <iostream>
#include "types.h"
#include <vector>

class Register;
class Operation;

/*List of commands*/
enum
	{
        cmdNOP    = 0,    cmdAND   = 1,	    cmdOR  = 2,	     cmdXOR  = 3,
        cmdADD    = 130,  cmdSUB   = 131,	cmdMUL = 129,    cmdDIV  = 128,
        cmdMOV    = 132,
        cmdNOT    = 68,
        cmdDEC    = 192,  cmdINC = 193,     cmdSSGN = 194,   cmdISGN = 195,
        cmdHLT    = -1
    };

class Simmy
{
	std::vector<Register> reg_;
	hostUInt8* instrPointer_;
	void decodeInstr   ( Operation* curOp);
	void execCurCmd    ( Operation* curOp);
	void write         ( hostSInt32 res, hostUInt8 numreg);
public:
	Simmy              ( hostUInt8* data, hostUInt32 length);
	hostSInt32 execute ( hostUInt32 numInstr);
};

class Register
{
public:
	bool sign_;
	hostUInt16 value_;
};

class Operation
{
public:
	hostUInt8 opcode_;
	hostUInt8 control_;
	hostUInt8 op1_;
	hostUInt8 lop2_;
	hostUInt8 mop2_;
	bool typeop2_;
	bool signop2_;
};

#endif /* SIMMY_H_ */
