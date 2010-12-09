/**
 *Scheduler.h - Implementation of Scheduler class
 * @author Vladimir Dubihin
 * Copyright 2010 MDSP team
 */

#include "scheduler.h"
#include "main_functions.h"

#include <iostream>
#include <cstdlib>

using namespace std;

void Scheduler::init(Config* handler)
{
    /* opening stream of input file */
    /* ifstream is used to handle binary input file */
    ifstream in_bin;
    if ( handler->getInputType())
    {
        openBinaryInputFile ( in_bin, handler->getBinaryFilename().c_str());
    }
    else
    {
        cout << "No ELF support provided\n";
        exit(0);
    }
    
    /* parsing number of steps */
    if ( handler->getNumSteps() != -1)
    {
        this->steps_sim = handler->getNumSteps();
    }
    else
    {
        this->steps_sim = MAXINT;
    }

    Core* core = new Core();
    core->init( this->start_pc);
    core->loadBinary( in_bin);
    core->setDisasmPrint( handler->getDisassembler());

    closeBinaryInputFile ( in_bin, handler->getBinaryFilename().c_str());

    core->warning("Simulation started.");
    core->run(this->steps_sim);
    core->warning("Simulation finished.");
}

