/**
 * @file:main.cpp 
 * The demonstation of the Simmy class usage.
 * @author Andrey Pushkar
 */
/*
 * Copyright 2011 MDSP team
 */

#include <iostream>
#include "Simmy.h"


hostSInt32 main ( hostSInt32 argc, const hostSInt8 * argv[])
{
    hostUInt8 bytes[ 20] = 
    {
        132, //10000100
        12, //0000001100
        4, //00000100
        42, //00101010
        0, //00000000
        
        132, //10000100
        12, //0000001100
        5, //00000101
        20, //00010100
        0, //00000000
        
        130, //10000010
        0, //00000000
        5, //00000101
        4, //00000100
        0, //00000000
        
        132, //10000100
        0, //00000000
        0, //00000000
        5, //00000101
        0, //00000000

    
    };
    
    Simmy sim( bytes, 20);
    cout << sim.Execute( 4);
    return 0;
}
