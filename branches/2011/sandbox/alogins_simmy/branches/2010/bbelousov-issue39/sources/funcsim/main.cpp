/**
 * main.cpp - Entry point of functional simulator (funcsim)
 * Copyright 2009 MDSP team
 */

#include <fstream>
#include <iostream>

#ifdef WIN32 
/* Gross Hack Alert */ 
#if _MSC_VER < 1300 
#define strtoll(p, e, b) ((*(e) = (char*)(p) + (((b) == 10) ? strspn((p), "0123456789") : 0)), _atoi64(p)) 
#else 
#define strtoll(p, e, b) _strtoi64(p, e, b) 
#endif 
#endif

#include <stdlib.h>
#include "scheduler.h"
#include "main_functions.h"
#include "config.h"

using namespace std;

int main(int argc, char** argv)
{
    Config handler;


    //handler.handleArgs( argc, argv);

    /* Check arguments number */
    //checkArguments( argc);


    Scheduler scheduler;

    //simple input check
    //to be ommited later
    if(argc>=3)
    {
        if (!(scheduler.steps_sim = strtoll ( argv[2], NULL, 10)) )
            scheduler.steps_sim = MAXINT;
    } else
    {
        scheduler.steps_sim = MAXINT;
    }

    //ignition
    scheduler.start_pc = 0x0000;
    scheduler.init( argc, argv);

    return 0;
}
