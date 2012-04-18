/*
 * simmy.cpp
 *
 *  Created on: 16.12.2011
 *      Author: Artemy Margaritov
 */

#include "./simmy.h"
#include <cmath>

using namespace std;

Simmy::Simmy ( hostUInt8* data, hostUInt32 length)
{
	reg_.reserve ( 16);
	instrPointer_ = data;
}

hostSInt32 Simmy::execute ( hostUInt32 numInstr)
{
	while ( numInstr)
	{
		Operation curOp;
		decodeInstr ( &curOp);
		execCurCmd  ( &curOp);
		numInstr--;
	}
	return  ( reg_[0].sign_ ?
            ( hostSInt32) reg_[0].value_ : ( hostSInt32)reg_[0].value_ * ( -1));
}

void Simmy::decodeInstr  ( Operation* curOp)
{
	curOp->opcode_  = *instrPointer_; instrPointer_++;
	curOp->control_ = *instrPointer_; instrPointer_++;
	curOp->op1_     = *instrPointer_; instrPointer_++;
	curOp->lop2_    = *instrPointer_; instrPointer_++;
	curOp->mop2_    = *instrPointer_; instrPointer_++;
	curOp->typeop2_ = curOp->control_ & 4;
	curOp->signop2_ = curOp->control_ & 8;
	return;
}

void Simmy::write ( hostSInt32 res, hostUInt8 numreg)
{
	reg_[numreg].value_ = (hostUInt16) fabs( res);
	reg_[numreg].sign_ = res > 0;
	return;
}

void Simmy::execCurCmd ( Operation* curOp)
{
	hostSInt32 op1 = 0;
	hostSInt32 op2 = 0;

    /* Op1 is always register number. */
    op1 = reg_[curOp->op1_].value_;
    if ( !reg_[curOp->op1_].sign_)
    {
        op1 *= -1;
    }
	if ( curOp->typeop2_)
	{
        /* Op2 is value. */
		op2 = ( curOp->mop2_ << 8) + curOp->lop2_;
		if ( !curOp->signop2_)
		{
			op2 *= -1;
		}
	} else
	{
        /* Op2 is register number. */
		op2 = reg_[curOp->lop2_].value_;
		if ( !reg_[curOp->lop2_].sign_)
		{
			op2 *= -1;
		}
	}

	switch ( curOp->opcode_)
	{
	case ( cmdAND) :
		if ( curOp->typeop2_)
		{
			reg_[curOp->op1_].value_ = reg_[curOp->op1_].value_ &
			                           (( curOp->mop2_ << 8) + curOp->lop2_);
			reg_[curOp->op1_].sign_ =  reg_[curOp->op1_].sign_  &
									   curOp->signop2_;
		} else
		{
			reg_[curOp->op1_].value_ = reg_[curOp->op1_].value_ &
									   reg_[curOp->lop2_].value_;
			reg_[curOp->op1_].sign_  = reg_[curOp->op1_].sign_  &
									   reg_[curOp->lop2_].sign_;
		}
		break;
	case ( cmdOR ) :
		if ( curOp->typeop2_)
		{
			reg_[curOp->op1_].value_ = reg_[curOp->op1_].value_ |
									   (( curOp->mop2_ << 8) + curOp->lop2_);
			reg_[curOp->op1_].sign_ =  reg_[curOp->op1_].sign_  |
								       curOp->signop2_;
		} else
		{
			reg_[curOp->op1_].value_ = reg_[curOp->op1_].value_ |
									   reg_[curOp->lop2_].value_;
			reg_[curOp->op1_].sign_  = reg_[curOp->op1_].sign_  |
									   reg_[curOp->lop2_].sign_;
		}
		break;
	case ( cmdXOR) :
		if ( curOp->typeop2_)
		{
			reg_[curOp->op1_].value_ = reg_[curOp->op1_].value_ ^
									   (( curOp->mop2_ << 8) + curOp->lop2_);
			reg_[curOp->op1_].sign_ =  reg_[curOp->op1_].sign_  ^
								       curOp->signop2_;
		} else
		{
			reg_[curOp->op1_].value_ = reg_[curOp->op1_].value_ ^
									   reg_[curOp->lop2_].value_;
			reg_[curOp->op1_].sign_  = reg_[curOp->op1_].sign_  ^
									   reg_[curOp->lop2_].sign_;
		}
		break;
	case ( cmdADD) :
		write ( op1 + op2, curOp->op1_);
		break;
	case ( cmdSUB) :
		write ( op1 - op2, curOp->op1_);
		break;
	case ( cmdMUL) :
		write ( op1 * op2, curOp->op1_);
		break;
	case ( cmdDIV) :
		write ( op1 / op2, curOp->op1_);
		break;
	case ( cmdMOV) :
		write ( op2, curOp->op1_);
		break;
	case ( cmdNOT) :
		reg_[curOp->op1_].value_ = ~reg_[curOp->op1_].value_;
		reg_[curOp->op1_].sign_  = ~reg_[curOp->op1_].sign_;
		break;
	case ( cmdDEC) :
		write ( ++op1, curOp->op1_);
		break;
	case ( cmdINC) :
		write ( --op2, curOp->op1_);
		break;
	case ( cmdSSGN):
		if ( reg_[curOp->op1_].value_ == 1)
		{
			write ( fabs( op2), curOp->lop2_);
		} else
		{
			write ( (-1) * fabs( op2), curOp->lop2_);
		}
		break;
	case ( cmdISGN):
		write ( (-1) * op1, curOp->op1_);
		break;
	}
	return;
}


