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
    r1.sign  |= r2.sign;
    r1.value |= r2.value;
    this->writeop( p1, r1);
}

void Executor::f_xor()
{
    Register r1 = this->readop( p1);
    Register r2 = this->readop( p2);
    r1.sign  ^= r2.sign;
    r1.value ^=  r2.value;
    this->writeop( p1, r1);
}

void Executor::f_add()
{
    Register r1 = this->readop( p1);
    Register r2 = this->readop( p2);
    SDWORD sdword1 = r1.sign ? r1.value : -r1.value;
    SDWORD sdword2 = r2.sign ? r2.value : -r2.value;
    SDWORD sdwordres = sdword1 + sdword2;
    bool signres  = sdwordres >= 0;
    WORD valueres = signres ? (WORD)sdwordres : (WORD)( -sdwordres);
    Register result( signres, valueres);
    this->writeop( p1, result);
}

void Executor::f_sub()
{
    Register r1 = this->readop( p1);
    Register r2 = this->readop( p2);
    SDWORD sdword1 = r1.sign ? r1.value : -r1.value;
    SDWORD sdword2 = r2.sign ? r2.value : -r2.value;
    SDWORD sdwordres = sdword1 - sdword2;
    bool signres  = sdwordres >= 0;
    WORD valueres = signres ? (WORD)sdwordres : (WORD)( -sdwordres);
    Register result( signres, valueres);
    this->writeop( p1, result);
}

void Executor::f_mul()
{
    Register r1 = this->readop( p1);
    Register r2 = this->readop( p2);
    SDWORD sdword1 = r1.sign ? r1.value : -r1.value;
    SDWORD sdword2 = r2.sign ? r2.value : -r2.value;
    SDWORD sdwordres = sdword1 * sdword2;
    bool signres  = sdwordres >= 0;
    WORD valueres = signres ? (WORD)sdwordres : (WORD)( -sdwordres);
    Register result( signres, valueres);
    this->writeop( p1, result);
}

void Executor::f_div()
{
    Register r1 = this->readop( p1);
    Register r2 = this->readop( p2);
    SDWORD sdword1 = r1.sign ? r1.value : -r1.value;
    SDWORD sdword2 = r2.sign ? r2.value : -r2.value;
    SDWORD sdwordres = sdword1 / sdword2;
    bool signres  = sdwordres >= 0;
    WORD valueres = signres ? (WORD)sdwordres : (WORD)(-sdwordres);
    Register result( signres, valueres);
    this->writeop( p1, result);
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
    --( r1.value);
    this->writeop( p1, r1);
}

void Executor::f_inc()
{
    Register r1 = this->readop( p1);
    ++( r1.value);
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
