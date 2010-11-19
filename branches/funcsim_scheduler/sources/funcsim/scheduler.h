/**
 *Scheduler.h - header of Scheduler class
 * @author Vladimir Dubihin
 * Copyright 2009 MDSP team
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H


#include "core.h"


using namespace std;

class Scheduler
{
    public:
        //Scheduler();
        void init(int argc, char** argv);

        int steps_sim;//number of steps for funcsim
        hostUInt16 start_pc;//point counter for core
};

#endif /* SCHEDULER_H */
