
#include<iostream>
#include<cstdlib>

#include "RBTMultimap.h"
#include "Process.h"
#include "Scheduler.h"
#include "simulate.h"

using namespace std;

int main(int argc, char** argv)
{

int numCPUBound = atoi(argv[1]);
int numIOBound = atoi(argv[2]);
int numCycles = atoi(argv[3]);

Scheduler* rr = new RoundRobin();
Scheduler* rr2 = new FastRoundRobin();
Scheduler* cf = new CompletelyFair();
Scheduler* cf2 = new FastCompletelyFair();

double* rrsched = simulate(rr,numCPUBound,numIOBound,numCycles);

cout << "The number of actual seconds per process: " << rrsched[0] << endl;
cout << "The average CPU time of all CPU-bound processes: " << rrsched[1] << endl;
cout << "The average wait time of all CPU-bound processes: " <<rrsched[2]  << endl;
cout << "The average CPU time of all I/O-bound processes: " << rrsched[3] << endl;
cout << "The average wait time of all I/O-bound processes: " << rrsched[4]  << endl;

delete[] rrsched;

double*  rr2sched = simulate(rr2,numCPUBound,numIOBound,numCycles);
cout << "The number of actual seconds per process: " << rr2sched[0] << endl;
cout << "The average CPU time of all CPU-bound processes: " << rr2sched[1] << endl;
cout << "The average wait time of all CPU-bound processes: " <<rr2sched[2]  << endl;
cout << "The average CPU time of all I/O-bound processes: " << rr2sched[3] << endl;
cout << "The average wait time of all I/O-bound processes: " << rr2sched[4]  << endl;


delete[] rr2sched;

double*  cfsched = simulate(cf,numCPUBound,numIOBound,numCycles);
cout << "The number of actual seconds per process: " << cfsched[0] << endl;
cout << "The average CPU time of all CPU-bound processes: " << cfsched[1] << endl;
cout << "The average wait time of all CPU-bound processes: " <<cfsched[2]  << endl;
cout << "The average CPU time of all I/O-bound processes: " << cfsched[3] << endl;
cout << "The average wait time of all I/O-bound processes: " << cfsched[4]  << endl;

delete[] cfsched;
double*  cf2sched = simulate(cf2,numCPUBound,numIOBound,numCycles);
cout << "The number of actual seconds per process: " << cf2sched[0] << endl;
cout << "The average CPU time of all CPU-bound processes: " << cf2sched[1] << endl;
cout << "The average wait time of all CPU-bound processes: " <<cf2sched[2]  << endl;
cout << "The average CPU time of all I/O-bound processes: " << cf2sched[3] << endl;
cout << "The average wait time of all I/O-bound processes: " << cf2sched[4]  << endl;

delete[] cf2sched;
return 0;
}
