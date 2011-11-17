/**
 *Scheduler.h - header of Scheduler class
 * @author Vladimir Dubihin
 * Copyright 2010 MDSP team
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#define MAXINT 0-1

#include "core.h"


using namespace std;

class Scheduler
{
    public:
        //Scheduler();
        void init(int argc, char** argv);

        hostUInt64 steps_sim;//number of steps for funcsim
        hostUInt16 start_pc;//point counter for core
};

#endif /* SCHEDULER_H */
