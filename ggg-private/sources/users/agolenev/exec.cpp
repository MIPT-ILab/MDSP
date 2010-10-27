/**
 * exec.cpp implementation of instructions
 * Main execution component
 * Copyright 2009 MDSP team
 */

#include "operation.h"

void Operation::execute()
{
    switch( type)
{
    case NO_TYPE :
    cout << "ERROR: NO_TYPE Operation type\n"
    assert( 0);
        
    case MOVE :
    
    switch( opcode0) 
{
    case
}
    break;
        
    case ALU :
    break;

    case MAC :
    cout << "MAC instructions not implemented yet\n";
    break;

    case DMAC :
    cout << "DMAC instructions not implemented yet\n";
    break;

    case P_FLOW:
    break;

    default:
    cout << "ERROR: unknown operation code\n";
    assert( 0)

}
}
