/**
 * flags.cpp - Implementation of Flags class methods
 * Copyright 2009 MDSP team
 */

#include "flags.h"

/**
 * Default contructor - create single byte register
 */
Flags::Flags() : RegVal( 1)
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
            break;
        case FLAG_ZERO:
            return this->getByteVal( 0) & FLAG_Z_POSITION;
            break;
        case FLAG_CARRY:
            return this->getByteVal( 0) & FLAG_C_POSITION;
            break;
        case FLAG_OVERFLOW:
            return this->getByteVal( 0) & FLAG_O_POSITION;
            break;
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
        default:
            cout << "Invalid flag register type\n";
            assert( 0);
    }
}
