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
                                         0b01111111) ^ 0b10000000); //0b01111111
            else this->setByte( 0,  this->getByteVal( 0) & !FLAG_N_POSITION);
            break;
        case FLAG_ZERO:
            if ( value) this->setByte( 0, ( this->getByteVal( 0) & 
                                            0b10111111) ^ 0b01000000); //0b10111111
            else this->setByte( 0,  this->getByteVal( 0) & !( hostUInt8)64);
            break;
        case FLAG_CARRY:
            if ( value) this->setByte( 0, ( this->getByteVal( 0) & 
                                            0b11011111) ^ 0b00100000); //0b11011111 
            else this->setByte( 0,  this->getByteVal( 0) & 0b11011111);
            break;
        case FLAG_OVERFLOW:
            if ( value) this->setByte( 0, ( this->getByteVal( 0) & 
                                            0b11101111) ^ 0b00010000); //0b11101111
            else this->setByte( 0,  this->getByteVal( 0) & 0b11101111);
            break;
        default:
            cout << "Invalid flag register type\n";
            assert( 0);
    }
}
