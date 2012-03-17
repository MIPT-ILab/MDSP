/**
 * executor.cpp
 *
 * Simmy Executor
 *
 * @author Pavel Kryukov
 * Copyright 2012 MDSP team
*/

#include "./executor.h"

namespace Simmy 
{

void Executor::f_and()
{
    Register r1 = this->readop( p1);
    Register r2 = this->readop( p2);
    r1.sign  &=  r2.sign;
    r1.value &=  r2.value;
    this->writeop( p1, r1);
}

void Executor::f_or()
{
    Register r1 = this->readop( p1);
    Register r2 = this->readop( p2);
    r1.sign  |=  r2.sign;
    r1.value |=  r2.value;
    this->writeop( p1, r1);
}

void Executor::f_xor()
{
    Register r1 = this->readop( p1);
    Register r2 = this->readop( p2);
    r1.sign  ^= r2.sign;
    r1.value ^= r2.value;
    this->writeop( p1, r1);
}

void Executor::f_add()
{
    SDWORD sdword1 = this->readop( p1).sdword();
    SDWORD sdword2 = this->readop( p2).sdword();
    this->writeop( p1, Register( sdword1 + sdword2));
}

void Executor::f_sub()
{
    SDWORD sdword1 = this->readop( p1).sdword();
    SDWORD sdword2 = this->readop( p2).sdword();
    this->writeop( p1, Register( sdword1 - sdword2));
}

void Executor::f_mul()
{
    SDWORD sdword1 = this->readop( p1).sdword();
    SDWORD sdword2 = this->readop( p2).sdword();
    this->writeop( p1, Register( sdword1 * sdword2));
}

void Executor::f_div()
{
    SDWORD sdword1 = this->readop( p1).sdword();
    SDWORD sdword2 = this->readop( p2).sdword();
    this->writeop( p1, Register( sdword1 / sdword2));
}

void Executor::f_mov()
{
    this->writeop( p1, this->readop( p2));
}

void Executor::f_not()
{
    Register r1 = this->readop( p1);
    r1.sign  = !r1.sign;
    r1.value = ~r1.value;
    this->writeop( p1, r1);
}

void Executor::f_dec()
{
    Register r1 = this->readop( p1);
    if ( r1.value == 0x00)
    {
        r1.value = 0x01;
        r1.sign  = 0;
    }
    else
    {
        if ( r1.sign)
        {
            --( r1.value);
        }
        else
        {
            ++( r1.value);
        }
    }
    this->writeop( p1, r1);
}

void Executor::f_inc()
{
    Register r1 = this->readop( p1);
    if ( r1.value == 0x00)
    {
        r1.value = 0x01;
        r1.sign  = 1;
    }
    else
    {
        if ( r1.sign)
        {
            ++( r1.value);
        }
        else
        {
            --( r1.value);
        }
    }
    this->writeop( p1, r1);
}

void Executor::f_isgn()
{
    Register r1 = this->readop( p1);
    r1.sign  = !r1.sign;
    this->writeop( p1, r1);
}

void Executor::f_ssgn()
{
    Register r1 = this->readop( p1);
    r1.sign  = this->readop( p2).sign;
    this->writeop( p1, r1);
}

}  // namespace Simmy
