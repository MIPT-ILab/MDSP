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
bool isWrapperUsed = true;

void setStandardCoutHandler()
{
    if ( isWrapperUsed)
    {
        coutStreambuf = cout.rdbuf( coutBuffer.rdbuf());
        isWrapperUsed = false;
    }
}

void setTestingCoutHandler()
{
    if ( !isWrapperUsed)
    {
        coutBuffer.clear();
        cout.rdbuf( coutStreambuf);
        isWrapperUsed = true;
    }
}

string getTestingCoutBuffer()
{
    return coutBuffer.str();
}

