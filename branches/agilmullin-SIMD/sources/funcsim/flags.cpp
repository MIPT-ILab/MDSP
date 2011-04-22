/**
 * flags.cpp - Implementation of Flags class methods
 * Copyright 2009 MDSP team
 */

#include "flags.h"

/**
 * Default contructor - create 4 byte register (2*16-bit)
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
            return this->getByteVal( 4) & 128;
        case p_N1:
            return this->getByteVal( 4) & 64;
        case p_N2:
            return this->getByteVal( 4) & 32;
        case p_N3:
            return this->getByteVal( 4) & 16;
        case p_Z0:
            return this->getByteVal( 3) & 8;
        case p_Z1:
            return this->getByteVal( 3) & 4;
        case p_Z2:
            return this->getByteVal( 3) & 2;
        case p_Z3:
            return this->getByteVal( 3) & 1;
        case p_C0:
            return this->getByteVal( 2) & 128;
        case p_C1:
            return this->getByteVal( 2) & 64;
        case p_C2:
            return this->getByteVal( 2) & 32;
        case p_C3:
            return this->getByteVal( 2) & 16;
        case p_O0:
            return this->getByteVal( 2) & 8;
        case p_O1:
            return this->getByteVal( 2) & 4;
        case p_O2:
            return this->getByteVal( 2) & 2;
        case p_O3:
            return this->getByteVal( 2) & 1;
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
            if ( value) this->setByte( 3, ( this->getByteVal( 3) & !128) ^ 128);
            else this->setByte( 3,  this->getByteVal( 3) & !128);
            break;
        case p_N1:
            if ( value) this->setByte( 3, ( this->getByteVal( 3) & !64) ^ 64);
            else this->setByte( 3,  this->getByteVal( 3) & !64);
            break;
        case p_N2:
            if ( value) this->setByte( 3, ( this->getByteVal( 3) & !32) ^ 32);
            else this->setByte( 3,  this->getByteVal( 3) & !32);
            break;
        case p_N3:
            if ( value) this->setByte( 3, ( this->getByteVal( 3) & !16) ^ 16);
            else this->setByte( 3,  this->getByteVal( 3) & !16);
            break;
        case p_Z0:
            if ( value) this->setByte( 3, ( this->getByteVal( 3) & !8) ^ 8);
            else this->setByte( 3,  this->getByteVal( 3) & !8);
            break;
        case p_Z1:
            if ( value) this->setByte( 3, ( this->getByteVal( 3) & !4) ^ 4);
            else this->setByte( 3,  this->getByteVal( 3) & !4);
            break;
        case p_Z2:
            if ( value) this->setByte( 3, ( this->getByteVal( 3) & !2) ^ 2);
            else this->setByte( 3,  this->getByteVal( 3) & !2);
            break;
        case p_Z3:
            if ( value) this->setByte( 3, ( this->getByteVal( 3) & !1) ^ 1);
            else this->setByte( 3,  this->getByteVal( 3) & !1);
            break;
        case p_C0:
            if ( value) this->setByte( 2, ( this->getByteVal( 2) & !128) ^ 128);
            else this->setByte( 2,  this->getByteVal( 2) & !128);
            break;
        case p_C1:
            if ( value) this->setByte( 2, ( this->getByteVal( 2) & !64) ^ 64);
            else this->setByte( 2,  this->getByteVal( 2) & !64);
            break;
        case p_C2:
            if ( value) this->setByte( 2, ( this->getByteVal( 2) & !32) ^ 32);
            else this->setByte( 2,  this->getByteVal( 2) & !32);
            break;
        case p_C3:
            if ( value) this->setByte( 2, ( this->getByteVal( 2) & !16) ^ 16);
            else this->setByte( 2,  this->getByteVal( 2) & !16);
            break;
        case p_O0:
            if ( value) this->setByte( 2, ( this->getByteVal( 2) & !8) ^ 8);
            else this->setByte( 2,  this->getByteVal( 2) & !8);
            break;
        case p_O1:
            if ( value) this->setByte( 2, ( this->getByteVal( 2) & !4) ^ 4);
            else this->setByte( 2,  this->getByteVal( 2) & !4);
            break;
        case p_O2:
            if ( value) this->setByte( 2, ( this->getByteVal( 2) & !2) ^ 2);
            else this->setByte( 2,  this->getByteVal( 2) & !2);
            break;
        case p_O3:
            if ( value) this->setByte( 2, ( this->getByteVal( 2) & !1) ^ 1);
            else this->setByte( 2,  this->getByteVal( 2) & !1);
            break;
        default:
            cout << "Invalid flag register type\n";
            assert( 0);
    }

}
