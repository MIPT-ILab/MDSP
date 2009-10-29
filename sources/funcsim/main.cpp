/**
 * main.cpp - Entry point of functional simulator (funcsim)
 * Copyright 2009 MDSP team
 */

#include "operation.h"
#include "test.h"
#include "core.h"
#include "register_file.h"

int main()
{
    Core* core = new Core();
    core->init( 0x0000);
    core->run();

    RegisterFileModel* rfm = new RegisterFileModel( 2, 1);
    RegVal* rv = new RegVal( 1);
    RegVal rv1( 1);
    Byte* b1 = new Byte( 5);
    Byte* b2 = new Byte( 2);
    rv->setByte( 0, *b1);
    rv1.setByte( 0, *b2);
    rfm->writeReg( 1, *rv);
    rfm->writeReg( 0, rv1);

    cout << ( int)rfm->readReg( 0)->getByte( 0).getByteVal() << " " <<
            ( int)rfm->readReg( 1)->getByte( 0).getByteVal() << "\n"; 
    delete b1;
    delete b2;
    delete rv;
    delete rfm;

    //test();

    return 0;
}
