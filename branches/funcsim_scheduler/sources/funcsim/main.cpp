/**
 * main.cpp - Entry point of functional simulator (funcsim)
 * Copyright 2009 MDSP team
 */

#include <fstream>
#include <iostream>

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
    if(argc>=3)
    {
        scheduler.steps_sim = atoi(argv[2]);
        scheduler.start_pc = 0x0000;
        scheduler.init( argc, argv);
    } else
    {
        cout<<"wrong input"<<endl;

    }
    return 0;
}
