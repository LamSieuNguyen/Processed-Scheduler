#include "RBTMultimap.h"

#include <string>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

template <class k, class v>
class TestRBT : public RBTMultimap<k, v>
{
  public:
   TestRBT();
   TestRBT(const vector<RBTNode<k, v>*>& nodes, RBTNode<k, v>* sentinel, int size, int sentIdx = 0);
   void init(const vector<RBTNode<k, v>*>& nodes, int& index, int sentIdx);

   void rotateLeftTest(BSTNode<k, v>* n);
   void rotateRightTest(BSTNode<k, v>* n);

   void insertFixupTest(RBTNode<k, v>* nodeToFix);
   void deleteFixupTest(RBTNode<k, v>* nodeToFix);

   void insertFixup(RBTNode<k, v>* nodeToFix);
   void deleteFixup(RBTNode<k, v>* nodeToFix);
};

template <class k, class v>
TestRBT<k, v>::TestRBT() : RBTMultimap<k, v>()
{
}

template <class k, class v>
void TestRBT<k, v>::init(const vector<RBTNode<k, v>*>& nodes, int& index, int sentIdx)
{
   //Assumes "nodes" is a pre-order traversal, with NULLs marking the edges of the tree
   RBTNode<k, v>* n = nodes[index];
   index++;
   if(nodes[index]) //left child
   {
      n->setLeftChild(nodes[index]);
      nodes[index]->setParent(n);
      init(nodes, index, sentIdx);
   }
   else
   {
      n->setLeftChild(this->sentinel);
      if(index == sentIdx)
      {
	 this->sentinel->setParent(n);
      }
   }

   index++;
   if(nodes[index]) //right child
   {
      n->setRightChild(nodes[index]);
      nodes[index]->setParent(n);
      init(nodes, index, sentIdx);
   }
   else
   {
      n->setRightChild(this->sentinel);
      if(index == sentIdx)
      {
	 this->sentinel->setParent(n);
      }
   }
}

template <class k, class v>
TestRBT<k, v>::TestRBT(const vector<RBTNode<k, v>*>& nodes, RBTNode<k, v>* sentinel, int size, int sentIdx) : RBTMultimap<k, v>()
{
   this->numItems = size;
   delete this->sentinel;
   this->sentinel = sentinel;
   //For an empty tree, "nodes" should have one element: NULL
   if(nodes[0])
   {
      this->root = nodes[0];
      this->root->setParent(sentinel);
      int idx = 0;
      init(nodes, idx, sentIdx);
   }
   else
   {
      this->root = sentinel;
   }
}

template <class k, class v>
void TestRBT<k, v>::rotateLeftTest(BSTNode<k, v>* n)
{
   this->rotateLeft(n);
}

template <class k, class v>
void TestRBT<k, v>::rotateRightTest(BSTNode<k, v>* n)
{
   this->rotateRight(n);
}

template <class k, class v>
void TestRBT<k, v>::insertFixupTest(RBTNode<k, v>* nodeToFix)
{
   this->RBTMultimap<k, v>::insertFixup(nodeToFix);
}

template <class k, class v>
void TestRBT<k, v>::deleteFixupTest(RBTNode<k, v>* nodeToFix)
{
   this->RBTMultimap<k, v>::deleteFixup(nodeToFix);
}

template <class k, class v>
void TestRBT<k, v>::insertFixup(RBTNode<k, v>* nodeToFix)
{
}

template <class k, class v>
void TestRBT<k, v>::deleteFixup(RBTNode<k, v>* nodeToFix)
{
}

template <>
void TestRBT<int, int>::insertFixup(RBTNode<int, int>* nodeToFix)
{
   if(nodeToFix == this->sentinel)
   {
      cout << "key: NIL ";
   }
   else
   {
      cout << "key: " << nodeToFix->getKey() << " ";
   }
}

template <>
void TestRBT<int, int>::deleteFixup(RBTNode<int, int>* nodeToFix)
{
   if(nodeToFix == this->sentinel)
   {
      cout << "key: NIL" ;
   }
   else
   {
      cout << "key: " << nodeToFix->getKey();
   }
   cout << " parent: " << nodeToFix->getParent()->getKey() << " ";
}

template <class k, class v>
void printIt(BSTForwardIterator<k, v> it)
{
   if(it.isPastEnd())
   {
      cout << "NIL";
   }
   else
   {
      cout << it.getKey() << " " << it.getValue();
   }
}

int main(int argc, char** argv)
{
   map<string, int> mode;
   mode["default constructor"] = 0;
   mode["insert"] = 1;
   mode["remove"] = 2;
   mode["rotateLeft"] = 2;
   mode["rotateRight"] = 2;
   mode["insertFixup"] = 2;
   mode["deleteFixup"] = 2;

   if(argc <= 1)
   {
      cout << "No operation specified." << endl;
      exit(1);
   }

   string op = argv[1];

   if(mode.find(op) == mode.end())
   {
      cout << "Operation " << op << " not recognized. Possibilities are: ";
      for(map<string, int>::iterator it = mode.begin(); it != mode.end(); it++)
      {
	 cout << it->first << " ";
      }
      cout << endl;
      exit(1);      
   }
   
   if(mode[op] == 0) //Default constructor
   {
      if(argc <= 2)
      {
	 cout << "Argument required: output file." << endl;
	 exit(1);
      }
      string outfile = argv[2];
      
      TestRBT<int, int> t;
      cout << "size: " << t.getSize();
      t.printDOT(outfile);
      TestRBT<string, string> s; //If this does not compile, RBT is not generic enough

   }
   else
   {
      if(argc <= 2)
      {
	 cout << "No input tree provided. Must take the form of a pre-order traversal including sentinel nodes, preceded by the number of nodes in the traversal. Each node is represented by two items a number to serve as both the key and value and 0/1 for color (NIL for sentinel). For example, to input a tree with one black node: 3 1 0 NIL NIL NIL NIL. One root and one right child: 5 1 0 NIL NIL 3 1 NIL NIL NIL NIL." << endl;
	 exit(1);
      }
      int size = atoi(argv[2]);

      if(argc < 3+2*size)
      {
	 cout << "Not enough nodes for given size (" << size << "). Must take the form of a pre-order traversal including sentinel nodes, preceded by the number of nodes in the traversal. Each node is represented by two items a number to serve as both the key and value and 0/1 for color (NIL for sentinel). For example, to input a tree with one black node: 3 1 0 NIL NIL NIL NIL. One root and one right child: 5 1 0 NIL NIL 3 1 NIL NIL NIL NIL." << endl;
	 exit(1);	 
      }
      
      vector<RBTNode<int, int>*> n;
      vector<RBTNode<string, string>*> sn;

      int realSize = 0;
      for(int i = 0; i < size; i++)
      {
	 int idx = 3+2*i;
	 if(string(argv[idx]) != "NIL")
	 {
	    n.push_back(new RBTNode<int, int>(atoi(argv[idx]), atoi(argv[idx]), atoi(argv[idx+1])));
	    sn.push_back(new RBTNode<string, string>(argv[idx], argv[idx], atoi(argv[idx+1])));
	    realSize++;
	 }
	 else
	 {
	    n.push_back(0);
	    sn.push_back(0);
	 }
      }

      int argIdx = 3+2*size;
      
      if(argc <= argIdx+1)
      {
	 cout << "Argument error. Either tree is incomplete or missing arguments: output filename, original tree filename." << endl;
	 exit(1);
      }
      string outfile = argv[argIdx];
      string outfile2 = argv[argIdx+1];
      int idx = 0;
      if(mode[op] > 1)
      {
	 if(argc <= argIdx+2)
	 {
	    cout << "Argument error. Either tree is incomplete or missing arguments: output filename, original tree filename, node index." << endl;
	    exit(1);
	 }
	 idx = atoi(argv[argIdx+2]);
      }
      
      RBTNode<int, int>* sent = new RBTNode<int, int>(0, 0, false);
      TestRBT<int, int> t(n, sent, realSize, idx);
      t.printDOT(outfile2);
      
      RBTNode<string, string>* sentS = new RBTNode<string, string>("", "", false);
      TestRBT<string, string> s(sn, sentS, realSize, idx);

      if(op == "insert") //insert
      {
	 int k = atoi(argv[argIdx+2]);
	 t.insert(k, k);
	 cout << "size: " << t.getSize();
	 t.printDOT(outfile);

	 string sk = argv[argIdx+1];
	 s.insert(sk, sk);
      }
      else if(op == "remove") //remove
      {
	 BSTForwardIterator<int, int> it(n[idx], sent);
	 BSTForwardIterator<int, int> succ = t.remove(it);
	 cout << "next: ";
	 printIt(succ);
	 cout << " size: " << t.getSize();
	 t.printDOT(outfile);

	 BSTForwardIterator<string, string> its(sn[idx], sentS);
	 s.remove(its);
      }
      else if(op == "rotateLeft") //rotateLeft
      {
	 t.rotateLeftTest(n[idx]);
	 t.printDOT(outfile);

	 s.rotateLeftTest(sn[idx]);
      }
      else if(op == "rotateRight") //rotateRight
      {
	 t.rotateRightTest(n[idx]);
	 t.printDOT(outfile);

	 s.rotateRightTest(sn[idx]);
      }
      else if(op == "insertFixup") //insertFixup
      {
	 t.insertFixupTest(n[idx]);
	 t.printDOT(outfile);

	 s.insertFixupTest(sn[idx]);
      }
      else if(op == "deleteFixup") //deleteFixup
      {
	 RBTNode<int, int>* node = n[idx];
	 RBTNode<string, string>* snode = sn[idx];
	 if(node == 0)
	 {
	    node = sent;
	    snode = sentS;
	 }
	 t.deleteFixupTest(node);
	 t.printDOT(outfile);

	 s.deleteFixupTest(snode);
      }     
   }
}
