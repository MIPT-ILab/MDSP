/**
 * executor.h
 *
 * Simmy Executor
 *
 * @author Pavel Kryukov
 * Copyright 2012 MDSP team
*/

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <cassert>

#include "./types.h"
#include "./register.h"

namespace Simmy 
{

class Executor
{
protected:
    // Registers
    RegisterFile reg;

    // Operands
    struct Operand 
    {
        DWORD index;
        Register constant;
        enum 
        {
            CONSTANT,
            REGISTER,
        } type;
    };

    inline Register readop( const Operand& p) const
    {
        switch ( p.type)
        {
            case Operand::CONSTANT:
                return p.constant;
            case Operand::REGISTER:
                return reg.readreg( p.index);
            default:
                return p.constant;
                assert( 0);
        }
    }

    inline void printOp( const Operand& p, char* buf) const
    {
        switch (p.type)
        {
            case Operand::CONSTANT:
                p.constant.print( buf);
                return;
            case Operand::REGISTER:
                reg.printreg( p.index, buf);
                return;
            default:
                assert( 0);
                return;
        }
    }

    inline void writeop( const Operand& p, Register data)
    {
        switch ( p.type)
        {
            case Operand::REGISTER:
                reg.writereg( p.index, data);
                return;                
            case Operand::CONSTANT:
            default:
                assert( 0);
        }
    }

    Operand p1, p2;

    // ISA
    friend class ISA;
    void f_and();
    void f_or();
    void f_xor();
    void f_add();
    void f_sub();
    void f_mul();
    void f_div();
    void f_mov();
    void f_not();
    void f_dec();
    void f_inc();
    void f_ssgn();
    void f_isgn();

    // Constructor
    inline Executor() {}
};
}

#endif
