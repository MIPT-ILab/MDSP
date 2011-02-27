/**
 * flags.cpp - Implementation of Flags class methods
 * Copyright 2009 MDSP team
 */

#include "flags.h"

/*
 * Default contructor - create single byte register
 */
Flags::Flags() : RegVal( 1)
{
    
}


/*
 * Get bit of flag register
 */
bool Flags::getFlag( FlagType flag)
{
    switch( flag)
    {
        case N:
            return this->getByteVal( 0) & 0b10000000;
            break;
        case Z:
            return this->getByteVal( 0) & 0b01000000;
            break;
        case C:
            return this->getByteVal( 0) & 0b00100000;
            break;
        case O:
            return this->getByteVal( 0) & 0b00010000;
            break;
        default:
            cout << "Invalid flag register type\n";
            assert( 0);
    }

    return false;
}

/*
 * Set bit of flag register
 */
void Flags::setFlag( FlagType flag, bool value)
{
    switch( flag)
    {
        case N:
            if ( value) this->setByte( 0, ( this->getByteVal( 0) & 0b01111111) + 0b10000000);
            else this->setByte( 0,  this->getByteVal( 0) & 0b01111111);
            break;
        case Z:
            if ( value) this->setByte( 0, ( this->getByteVal( 0) & 0b10111111) + 0b01000000);
            else this->setByte( 0,  this->getByteVal( 0) & 0b10111111);
            break;
        case C:
            if ( value) this->setByte( 0, ( this->getByteVal( 0) & 0b11011111) + 0b00100000);
            else this->setByte( 0,  this->getByteVal( 0) & 0b11011111);
            break;
        case O:
            if ( value) this->setByte( 0, ( this->getByteVal( 0) & 0b11101111) + 0b00010000);
            else this->setByte( 0,  this->getByteVal( 0) & 0b11101111);
            break;
        default:
            cout << "Invalid flag register type\n";
            assert( 0);
    }
}
