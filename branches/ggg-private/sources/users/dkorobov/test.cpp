/**
* test.cpp - The test for refister file model
* Copyright 2009 MDSP team
*/

#include "register_file.h"

int main()
{
    RegisterFileModel* rfm = new RegisterFileModel( 2, 1);
    RegVal* rv = new RegVal( 1);
    RegVal rv1( 1);
    rv->setByteVal( 0, 5);
    rv1.setByteVal( 0, 2);
    rfm->writeReg( 1, *rv);
    rfm->writeReg( 0, rv1);

    /* To watch how are errors handled when write to non-existent register */
    //rfm->writeReg( 2, rv1);

    /* To watch how are errors handled when read from non-existent register */
    //*rv = *rfm->readReg( 2);
    cout << ( int)rfm->readReg( 0)->getByteVal( 0) << " " <<
            ( int)rfm->readReg( 1)->getByteVal( 0) << "\n"; 
    delete rv;
    delete rfm;

    /* 
     * Memory test.
     * We run this program and then watch in task manager that
     * memory used by program is stable. It means that we allocate
     * and deallocate memory correctly.
     */
    for ( int i = 0; i < 1000000; i++)
    {
        RegisterFileModel r0( 5, 5);
        for ( int j = 0; j < 1000000; j++)
        {
            RegisterFileModel r2( 10, 10);
            for ( int k = 0; k < 1000000; k++)
            {
                RegisterFileModel r1( 5, 5);
            }
        }
    }
    
    return 0;
}

