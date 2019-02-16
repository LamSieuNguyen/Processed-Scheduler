
#include "Scheduler.h"
#include "Process.h"

#include <iostream>
#include <chrono>

using namespace std;

double* simulate(Scheduler* sched, int numCPUBound, int numIOBound, int numCycles)
{
  ArrayList<Process*> cpuProcs; // makes a new process
  for(int i = 0; i < numCPUBound; i++) // loops through the numCPUBound
   {
     cpuProcs.pushBack(new CPUBoundProcess(i)); //adds the CPUBoundprocess at that index to the end of the process
     sched->addProcess(cpuProcs.getBack()); // adds the scheduler the back of the process
   }
   
  ArrayList<Process*> ioProcs; // makes a new process
   for(int i = 0; i < numIOBound; i++)
   {
     ioProcs.pushBack(new IOBoundProcess(i+numCPUBound)); // adds to the process the IOBOund index at the correct index
     sched->addProcess(ioProcs.getBack()); // the scheduler then adds the back of the process to it
   }

   auto start = chrono::system_clock::now(); // starts a clock timer.
   int numSchedules = 0; // sets number of Schedules to 0
   int curCycle = 0; // sets number of Cycles to 0

   while(curCycle < numCycles)
   {
     Process* p = sched->popNext(curCycle); // makes a process to be equal to the curCycle index of the sched
     numSchedules++; // increments the size of the schedule
      if(p != 0)
      {
	curCycle += p->simulate(curCycle, 10); // accumaltes the curCycle by recursion 
	sched->addProcess(p); // adds  the process p to the schedule
      }
      else
      {
	curCycle += 10; // adds 10 to curCylcle every time
      }
   }

   auto end = chrono::system_clock::now(); // sets and end time
   auto dur = end - start; // measures the total duration 
   auto durNS = chrono::duration_cast<chrono::nanoseconds>(dur); // 

   double cpuCPUTime = 0; // initializes the CPU time
   double cpuWaitTime = 0; // initializes the wait time
   for(int i = 0; i < cpuProcs.getSize(); i++)
   {
     Process* p = cpuProcs.getItem(i); // makes the process p to be getItem.
     cpuCPUTime += p->getCPUTime(); // accumalates the CPU time 
     cpuWaitTime += p->getWaitTime(curCycle);//accumulates the wait time 
     delete p; // deletes the p
   }

   double ioCPUTime = 0; // initializes the ioCPu time.
   double ioWaitTime = 0; //  initializes the io wait time. 
   for(int i = 0; i < ioProcs.getSize(); i++)
   {
     Process* p = ioProcs.getItem(i); // sets a new proccess to be the item at current index
     ioCPUTime += p->getCPUTime(); // adds the process to the cpu time 
     ioWaitTime += p->getWaitTime(curCycle); // adds proccess wait time to wait time.
     delete p; // deletes the process.
   }

   double* results = new double[5];
   results[0] = double(durNS.count())/numSchedules;
   results[1] = cpuCPUTime/numCPUBound;
   results[2] = cpuWaitTime/numCPUBound;
   results[3] = ioCPUTime/numIOBound;
   results[4] = ioWaitTime/numIOBound;
   return results;
}


