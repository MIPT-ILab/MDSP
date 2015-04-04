/**
 * cout_wrapper.cpp - Implementation of stdout wrapper
 * @author Alexander Potashev
 * Copyright 2010 MDSP team
 */

#include <iostream>
#include <sstream>

using namespace std;

ostringstream coutBuffer;
streambuf *coutStreambuf;
bool isWrapperUsed = false;

void setTestingCoutHandler()
{
    if ( !isWrapperUsed)
    {
        // coutBuffer.clear() doesn't reset buffer!!!
        coutBuffer.str("");
        coutStreambuf = cout.rdbuf( coutBuffer.rdbuf());
        isWrapperUsed = true;

    }
}

void setStandardCoutHandler()
{
    if ( isWrapperUsed)
    {
        cout.rdbuf( coutStreambuf);
        isWrapperUsed = false;
    }
}

string getTestingCoutBuffer()
{
    return coutBuffer.str();
}

