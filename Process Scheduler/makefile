OPTS = -Wall -g
c11 = -std=c++11 

Process.o: Process.cc Process.h
	g++ ${OPTS} ${c11} -c Process.cc

BSTNode: BSTNode_Test.cc BSTNode.h
	g++ ${OPTS}  ${c11} -o BSTNode BSTNode_Test.cc
Scheduler.o: Scheduler.cc Scheduler.h 
	g++ ${OPTS} ${c11}  -c  Scheduler.cc
simulate.o: simulate.cc simulate.h Process.o Scheduler.o
	g++ ${OPTS} ${c11}  -c  simulate.cc Process.o Scheduler.o
arraylist:  ArrayList_Test.cc ArrayList.h
	g++ ${OPTS} ${c11}  -o arraylist ArrayList_Test.cc 
RoundRobin: RoundRobin_Test.cc ArrayList.h Process.o Scheduler.o
	g++ ${OPTS} ${c11}  -o  RoundRobin_Test  RoundRobin_Test.cc Process.o Scheduler.o
FastRoundRobin: FastRoundRobin_Test.cc ArrayList.h Scheduler.h Process.h
	g++ ${OPTS} ${c11}  -o  FastRoundRobin_Test  FastRoundRobin_Test.cc Process.o

CompletelyFair: CompletelyFair_Test.cc BSTMultimap.h Scheduler.o Process.o 	
	g++ ${OPTS} ${c11}  -o CompletelyFair_Test CompletelyFair_Test.cc Scheduler.o Process.o
FastCompletelyFair: FastCompletelyFair_Test.cc BSTMultimap.h RBTMultimap.h Scheduler.h	Process.o Scheduler.o
	g++ ${OPTS} ${c11}  -o FastCompletelyFair_Test FastCompletelyFair_Test.cc Process.o Scheduler.o
linkedlist: LinkedList_Test.cc  LinkedList.h Process.o Scheduler.o
	g++ ${OPTS}  ${c11} -o linkedlist LinkedList_Test.cc Process.o Scheduler.o
BSTMultimap: BSTMultimap_Test.cc BSTMultimap.h BSTForwardIterator.h BSTNode.h
	g++ ${OPTS} ${c11}  -o BSTMultiMap BSTMultimap_Test.cc
BSTForwardIterator: BSTForwardIterator_Test.cc BSTMultimap.h BSTForwardIterator.h BSTNode.h
	g++ ${OPTS}  ${c11} -o BSTForwardIterator BSTForwardIterator_Test.cc
schedulesim: schedulesim.cc Process.o Scheduler.o  simulate.o
	g++ ${OPTS} ${c11} -o schedulesim schedulesim.cc Process.o Scheduler.o	 simulate.o
RBTNode: RBTNode_Test.cc RBTNode.h BSTNode.h 
	g++ ${OPTS}  ${c11} -o RBTNode RBTNode_Test.cc
RBTMultimap: RBTMultimap_Test.cc RBTMultimap.h RBTNode.h
	g++ ${OPTS} ${c11} -o RBTMultimap RBTMultimap_Test.cc		

clean:
	rm *.o
	rm BSTNode BSTMultiMap BSTForwardIterator RBTNode RBTMultimap FastCompletelyFair CompletelyFair schedulesim

cleanemacs:
	rm *~
