/**
 * cout_wrapper.h - Header file for stdout wrapper
 * @author Alexander Potashev
 * Copyright 2010 MDSP team
 */

#ifndef COUT_WRAPPER_H
#define COUT_WRAPPER_H

#include <iostream>
#include <stdio.h>

/**
 * Switches "cout" to work with stdout
 */
void setStandardCoutHandler();

/**
 * Switches "cout" to work with internal buffer (for testing)
 */
void setTestingCoutHandler();

/**
 * Returns a string with the text collected in the buffer since the last
 * call to setTestingCoutHandler()
 */
string getTestingCoutBuffer();

#endif


/* Example:

    Operation *op = new Operation();
    setTestingCoutHandler();
    op->set(MOVE, BRR, NOP, NOP, 0, 0, 0, 0, 1, 0, 2);
    op->dump();
    setStandardCoutHandler();

    if (getTestingCoutBuffer() != string("brr 1, r2;"))
    {
        cout << "fail!" << endl;
        assert(0);
    }
    else
    {
        cout << "OK" << endl;
    }

*/
