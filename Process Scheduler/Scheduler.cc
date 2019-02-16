
#include <cstdlib>
#include <iostream>
#include "Scheduler.h"
#include "List.h"
#include "ArrayList.h"
#include "LinkedList.h"
#include "BSTNode.h"
#include "BSTMultimap.h"
#include "BSTForwardIterator.h"
#include "Process.h"
#include "RBTMultimap.h"
using namespace std;


RoundRobin::RoundRobin()
{
  procQueue = new ArrayList<Process*>();
}

RoundRobin::~RoundRobin()
{
  delete procQueue;
}
void RoundRobin::addProcess(Process* proc)
{
  procQueue->pushBack(proc); 
}

Process* RoundRobin:: popNext(int curCycle)
{
  bool go = true;
  int acc = 0;
  while (procQueue->getFront()->isBlocked(curCycle) && go == true)
    {
      Process *p = procQueue-> getFront();
      procQueue->pushBack(p);
      procQueue->popFront();
      acc ++;
      if (acc == procQueue ->getSize())
	{
	  go = false;
	}
     
	    
    }
  if (go == false)
    {
      Process *p = procQueue->getFront();
      return p;
    }
  else 
    {
      return 0;
    }
   
}
FastRoundRobin::FastRoundRobin()
{
  delete procQueue;
  procQueue = new LinkedList<Process*>;
}
  
CompletelyFair::CompletelyFair()
{
  procTree = new BSTMultimap< int, Process*>;
}

CompletelyFair::~CompletelyFair()
{
  delete procTree;
}

void CompletelyFair::addProcess(Process *proc)
{
  procTree->insert(proc->getCPUTime(), proc);
}

Process *CompletelyFair:: popNext(int curCycle)
{
  BSTForwardIterator<int , Process* >  iter = procTree->getMin();
  
  while (!iter.isPastEnd())
    {
      Process *p = iter.getValue();
      if (!p->isBlocked(curCycle))
	{
	  iter.next();
	}
      else
	{
	  procTree->remove(iter);
	  return p;
	}
    }
  return 0;
}


FastCompletelyFair::FastCompletelyFair()
{
  
  delete procTree;
  procTree = new RBTMultimap<int, Process*>;
}
