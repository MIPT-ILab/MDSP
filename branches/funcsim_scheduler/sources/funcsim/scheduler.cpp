/**
 *Scheduler.h - Implementation of Scheduler class
 * @author Vladimir Dubihin
 * Copyright 2010 MDSP team
 */

#include "scheduler.h"
#include <iostream>
#include "main_functions.h"


using namespace std;

void Scheduler::init(int argc, char** argv)
{


    /* ifstream is used to handle binary input file */
    ifstream in_bin;
    openBinaryInputFile ( in_bin, argv[1]);

    Core* core = new Core();
    core->init( this->start_pc);
    core->loadBinary( in_bin);

    closeBinaryInputFile ( in_bin, argv[1]);

    core->warning(1);
    core->run(this->steps_sim);
    core->warning(2);
}

