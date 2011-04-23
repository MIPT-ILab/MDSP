/**
 * flags.cpp - Implementation of Flags class methods
 * Copyright 2009 MDSP team
 */

#include "flags.h"

/**
 * Default contructor - create 4 byte register (2*0x10-bit)
 * p_flags + s_flags
 *                  p_flags
 * p_N0 p_N1 p_N2 p_N3 p_Z0 p_Z1 p_Z2 p_Z3 p_C0 p_C1 p_C2 p_C3 p_O0 p_O1 p_O2 p_O3
 *                  s_flags
 * ****************Reserved*************** s_N0 s_N1 s_N2 s_N3 s_O0 s_O1 s_O2 s_O3
 */
Flags::Flags() : RegVal( 4)
{
   
}


/**
 * Get bit of flag register
 */
bool Flags::getFlag( FlagType flag)
{
    switch( flag)
    {
        case FLAG_NEG:
            return this->getByteVal( 0) & FLAG_N_POSITION;
        case FLAG_ZERO:
            return this->getByteVal( 0) & FLAG_Z_POSITION;
        case FLAG_CARRY:
            return this->getByteVal( 0) & FLAG_C_POSITION;
        case FLAG_OVERFLOW:
            return this->getByteVal( 0) & FLAG_O_POSITION;
        case p_N0:
            return this->getByteVal( 3) & 0x80;
        case p_N1:
            return this->getByteVal( 3) & 0x40;
        case p_N2:
            return this->getByteVal( 3) & 0x20;
        case p_N3:
            return this->getByteVal( 3) & 0x10;
        case p_Z0:
            return this->getByteVal( 3) & 0x08;
        case p_Z1:
            return this->getByteVal( 3) & 0x04;
        case p_Z2:
            return this->getByteVal( 3) & 0x02;
        case p_Z3:
            return this->getByteVal( 3) & 0x01;
        case p_C0:
            return this->getByteVal( 2) & 0x80;
        case p_C1:
            return this->getByteVal( 2) & 0x40;
        case p_C2:
            return this->getByteVal( 2) & 0x20;
        case p_C3:
            return this->getByteVal( 2) & 0x10;
        case p_O0:
            return this->getByteVal( 2) & 0x08;
        case p_O1:
            return this->getByteVal( 2) & 0x04;
        case p_O2:
            return this->getByteVal( 2) & 0x02;
        case p_O3:
            return this->getByteVal( 2) & 0x01;
        default:
            cout << "Invalid flag register type\n";
            assert( 0);
    }

    return false;
}

/**
 * Set bit of flag register
 */
void Flags::setFlag( FlagType flag, bool value)
{
    switch( flag)
    {
        case FLAG_NEG:
            if ( value) this->setByte( 0, ( this->getByteVal( 0) & 
                                            FLAG_N_POS_INVERSED) ^ FLAG_N_POSITION);
            else this->setByte( 0,  this->getByteVal( 0) & FLAG_N_POS_INVERSED);
            break;
        case FLAG_ZERO:
            if ( value) this->setByte( 0, ( this->getByteVal( 0) & 
                                            FLAG_Z_POS_INVERSED) ^ FLAG_Z_POSITION);
            else this->setByte( 0,  this->getByteVal( 0) & FLAG_Z_POS_INVERSED);
            break;
        case FLAG_CARRY:
            if ( value) this->setByte( 0, ( this->getByteVal( 0) & 
                                            FLAG_C_POS_INVERSED) ^ FLAG_C_POSITION);
            else this->setByte( 0,  this->getByteVal( 0) & FLAG_C_POS_INVERSED);
            break;
        case FLAG_OVERFLOW:
            if ( value) this->setByte( 0, ( this->getByteVal( 0) & 
                                            FLAG_O_POS_INVERSED) ^ FLAG_O_POSITION);
            else this->setByte( 0,  this->getByteVal( 0) & FLAG_O_POS_INVERSED);
            break;
        case p_N0:
            if ( value) this->setByte( 3,  this->getByteVal( 3) & ~0x80 | 0x80);
            else this->setByte( 3,  this->getByteVal( 3) & ~0x80);
            break;
        case p_N1:
            if ( value) this->setByte( 3,  this->getByteVal( 3) & ~0x40 | 0x40);
            else this->setByte( 3,  this->getByteVal( 3) & ~0x40);
            break;
        case p_N2:
            if ( value) this->setByte( 3,  this->getByteVal( 3) & ~0x20 | 0x20);
            else this->setByte( 3,  this->getByteVal( 3) & ~0x20);
            break;
        case p_N3:
            if ( value) this->setByte( 3,  this->getByteVal( 3) & ~0x10 | 0x10);
            else this->setByte( 3,  this->getByteVal( 3) & ~0x10);
            break;
        case p_Z0:
            if ( value) this->setByte( 3,  this->getByteVal( 3) & ~0x08 | 0x08);
            else this->setByte( 3,  this->getByteVal( 3) & ~0x08);
            break;
        case p_Z1:
            if ( value) this->setByte( 3,  this->getByteVal( 3) & ~0x04 | 0x04);
            else this->setByte( 3,  this->getByteVal( 3) & ~0x04);
            break;
        case p_Z2:
            if ( value) this->setByte( 3,  this->getByteVal( 3) & ~0x02 | 0x02);
            else this->setByte( 3,  this->getByteVal( 3) & ~0x02);
            break;
        case p_Z3:
            if ( value) this->setByte( 3,  this->getByteVal( 3) & ~0x01 | 0x01);
            else this->setByte( 3,  this->getByteVal( 3) & ~0x01);
            break;
        case p_C0:
            if ( value) this->setByte( 2,  this->getByteVal( 2) & ~0x80 | 0x80);
            else this->setByte( 2,  this->getByteVal( 2) & ~0x80);
            break;
        case p_C1:
            if ( value) this->setByte( 2,  this->getByteVal( 2) & ~0x40 | 0x40);
            else this->setByte( 2,  this->getByteVal( 2) & ~0x40);
            break;
        case p_C2:
            if ( value) this->setByte( 2,   this->getByteVal( 2) & ~0x20 | 0x20);
            else this->setByte( 2,  this->getByteVal( 2) & ~0x20);
            break;
        case p_C3:
            if ( value) this->setByte( 2,   this->getByteVal( 2) & ~0x10 | 0x10);
            else this->setByte( 2,  this->getByteVal( 2) & ~0x10);
            break;
        case p_O0:
            if ( value) this->setByte( 2,   this->getByteVal( 2) & ~0x08 | 0x08);
            else this->setByte( 2,  this->getByteVal( 2) & ~0x08);
            break;
        case p_O1:
            if ( value) this->setByte( 2,   this->getByteVal( 2) & ~0x04 | 0x04);
            else this->setByte( 2,  this->getByteVal( 2) & ~0x04);
            break;
        case p_O2:
            if ( value) this->setByte( 2,   this->getByteVal( 2) & ~0x02 | 0x02);
            else this->setByte( 2,  this->getByteVal( 2) & ~0x02);
            break;
        case p_O3:
            if ( value) this->setByte( 2,   this->getByteVal( 2) & ~0x01  | 0x01);
            else this->setByte( 2,  this->getByteVal( 2) & ~0x01);
            break;
        default:
            cout << "Invalid flag register type\n";
            assert( 0);
    }

}
