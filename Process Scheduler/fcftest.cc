#include "Scheduler.h"

#include <iostream>
#include <vector>

using namespace std;

class BlockedProcess : public Process
{
  public:
   BlockedProcess(int id) : Process(id) {}
   virtual bool isBlocked(int curCycleNum) const {return true;}
   virtual int simulate(int curCyclenum, int sliceSize) {return 0;}
};

int main(int argc, char**argv)
{
   Scheduler* s = new FastCompletelyFair();
   vector<Process*> procs;
   for(int i = 0; i < 5; i++)
   {
      Process* p = new IOBoundProcess(i);
      s->addProcess(p);
      procs.push_back(p);
   }
   Process* c = new CPUBoundProcess(5);
   s->addProcess(c);
   procs.push_back(c);
   int idOrder[] = {0, 1, 2, 3, 4, 5, 0, 1, 2, 5, 5, 5, 5, 5, 3};
   int curCycle = 0;
   bool problem = false;
   for(int i = 0; i < 15; i++)
   {
      Process* p = s->popNext(curCycle);
      if(p->getID() != idOrder[i])
      {
	 cout << "- " << i << "th process had ID " << p->getID() << " (was expecting " << idOrder[i] << ")" << endl << endl;
	 problem = true;
      }
      curCycle += p->simulate(curCycle, 10);
      s->addProcess(p);
   }

   Process* b = new BlockedProcess(6);
   Scheduler* t = new CompletelyFair();
   t->addProcess(b);
   Process* p = t->popNext(0);
   if(p != 0)
   {
      problem = true;
      cout << "- All processes are blocked but popNext returned ID " << p->getID() << " rather than null pointer" << endl << endl;
   }
   delete b;
   delete t;
   
   for(int i = 0; i < 6; i++)
   {
      delete procs[i];
   }
   delete s;

   if(problem)
   {
      return 1;
   }
}
