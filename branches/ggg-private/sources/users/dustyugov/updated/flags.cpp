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
            break;
        case Z:
            break;
        case C:
            break;
        case O:
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
            break;
        case Z:
            break;
        case C:
            break;
        case O:
            break;
        default:
            cout << "Invalid flag register type\n";
            assert( 0);
    }
}
