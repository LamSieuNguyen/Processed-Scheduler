#ifndef RBT_MULTIMAP
#define RBT_MULTIMAP

#include "BSTMultimap.h"
#include "RBTNode.h"

#include <string>
#include <fstream>
#include <queue>
#include <iostream>
#include <map>

using namespace std;

template <class key_t, class val_t>
class RBTMultimap : public BSTMultimap<key_t, val_t>
{
  protected:
   //Performs the rotate left operation
   //(assumes node has a right child)
   virtual void rotateLeft(BSTNode<key_t, val_t>* node);

   //Performs the rotate right operation
   //(assumes node has a left child)
   virtual void rotateRight(BSTNode<key_t, val_t>* node);

   //Fix up the tree after an insert
   //(assumes insertedNode is red)
   virtual void insertFixup(RBTNode<key_t, val_t>* insertedNode);

   //Fix up the tree after deleting a node
   //ReplaceNode is the node that replaced the deleted node
   //(possibly the sentinel)
   virtual void deleteFixup(RBTNode<key_t, val_t>* replaceNode);

   //Puts replacementNode in nodeToReplace's position in the tree
   //(replacementNode takes its children along with it)
   //Assumes nodeToReplace is a real node (not the sentinel)
   virtual void transplant(BSTNode<key_t, val_t>* nodeToReplace, BSTNode<key_t, val_t>* replacementNode);

  public:
   //Creates an empty red-black tree
   RBTMultimap();
   virtual ~RBTMultimap();
 
   //Inserts (key, value) into the multimap
   virtual void insert(const key_t& key, const val_t& value);

   //Removes the key/value pair pointed to by pos
   //(if pos is off the end, does nothing)
   //Returns an iterator pointing to the next node after the
   //deleted node
   virtual BSTForwardIterator<key_t, val_t> remove(const BSTForwardIterator<key_t, val_t>& pos);

   //Prints the tree in the "dot" format for visualization
   //using graphviz
   //NOTE: Requires that keys are streamable (values are not printed)
   virtual void printDOT(std::string filename);
};

//////////////////////////////////////////
//RBTMultimap implementation begins here//
//////////////////////////////////////////

// constructor
template <class key_t, class val_t>
RBTMultimap<key_t, val_t>::RBTMultimap()
{
  key_t key;
  val_t value;
  this->sentinel = new RBTNode<key_t, val_t>(key, value, false);
  this->root = this->sentinel;
}

// destructor (problem?)
template <class key_t, class val_t>
RBTMultimap<key_t, val_t>::~RBTMultimap()
{
  this->clear();
  delete this->sentinel;
}
// insert
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::insert(const key_t& key, const val_t& value)
{
  RBTNode<key_t, val_t>* newNode = new RBTNode<key_t, val_t>(key, value, true);
  this->insertNode(newNode);
  newNode ->setLeftChild(this->sentinel);
  newNode ->setRightChild(this->sentinel);
  newNode ->setColor(this->sentinel);
  this->insertFixup(newNode);
}

// rotate left
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::rotateLeft(BSTNode<key_t, val_t>* node)
{
  RBTNode<key_t, val_t>* rightChild = dynamic_cast<RBTNode<key_t,val_t>*>(node->getRightChild());

  node->setRightChild(rightChild->getLeftChild());
  if (rightChild->getLeftChild() != this->sentinel)
  {
    rightChild->getLeftChild()->setParent(node);
  }

  rightChild->setParent(node->getParent());
  
  // If 'node' was the root, change its right child to the root
  if (this->sentinel == node->getParent())
  {
    this->root = rightChild;
  }
  else if (node == node->getParent()->getLeftChild()) // node used to be the left child
  {
    node->getParent()->setLeftChild(rightChild);
  }
  else // node used to be the right child
  {
    node->getParent()->setRightChild(rightChild);
  }

  rightChild->setLeftChild(node);
  node->setParent(rightChild);
}

// rotate right
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::rotateRight(BSTNode<key_t, val_t>* node)
{
  RBTNode<key_t, val_t>* leftChild = dynamic_cast<RBTNode<key_t,val_t>*>(node->getLeftChild());

  node->setLeftChild(leftChild->getRightChild());
  if (leftChild->getRightChild() != this->sentinel)
  {
    leftChild->getRightChild()->setParent(node);
  }

  leftChild->setParent(node->getParent());
  
  if (this->sentinel == node->getParent())
  {
    this->root = leftChild;
  }
  else if (node == node->getParent()->getRightChild()) 
  {
    node->getParent()->setRightChild(leftChild);
  }
  else // node used to be the right child
  {
    node->getParent()->setLeftChild(leftChild);
  }

  leftChild->setRightChild(node);
  node->setParent(leftChild);
}

// insertFixup
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::insertFixup(RBTNode<key_t, val_t>* insertedNode)
{

  while (insertedNode->getParent()->getColor())
  {
    RBTNode<key_t, val_t>* parent = insertedNode->getParent();
    RBTNode<key_t, val_t>* uncle;
    RBTNode<key_t, val_t>* grandParent = parent->getParent();
    if (parent == grandParent->getLeftChild())
    {
      uncle = grandParent->getRightChild();
      
      if (uncle->getColor())
      {
        parent->setColor(false);
	uncle->setColor(false);
	grandParent->setColor(true);
	insertedNode = grandParent;
      }
      else
      {
	if (insertedNode == parent->getRightChild())
	{
	  insertedNode = parent;
	  rotateLeft(insertedNode);
	}
	insertedNode->getParent()->setColor(false);
	insertedNode->getParent()->getParent()->setColor(true);
	rotateRight(insertedNode->getParent()->getParent());
      }
    }
    else
    {
      uncle = grandParent->getLeftChild();
      if (uncle->getColor())
      {
        parent->setColor(false);
	uncle->setColor(false);
	grandParent->setColor(true);
	insertedNode = grandParent;
      }

      else
      {
	if (insertedNode == parent->getLeftChild())
	{
	  insertedNode = parent;
	  rotateRight(insertedNode);
	}
	insertedNode->getParent()->setColor(false);
	insertedNode->getParent()->getParent()->setColor(true);
	rotateLeft(insertedNode->getParent()->getParent());
      }
    }
  }
  // Make sure the color of the root is black
  RBTNode<key_t, val_t>* root = dynamic_cast<RBTNode<key_t, val_t>*>(this->root);
  root->setColor(false);
}

// transplant
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::transplant(BSTNode<key_t, val_t>* nodeToReplace, BSTNode<key_t, val_t>* replacementNode)
{
  BSTNode<key_t, val_t>* parent = nodeToReplace->getParent();

  if (this->root == nodeToReplace)
  {
    this->root = replacementNode;
  }
  else
  {
    // left child
    if (nodeToReplace == parent->getLeftChild())
    {
      parent->setLeftChild(replacementNode);
    }
    // right child
    else
    {
      parent->setRightChild(replacementNode);
    }
  }
  replacementNode->setParent(parent);
}

// remove
template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> RBTMultimap<key_t, val_t>::remove(const BSTForwardIterator<key_t, val_t>& pos)
{
  BSTForwardIterator<key_t, val_t> iter = pos;
  RBTNode<key_t, val_t>* node = dynamic_cast<RBTNode<key_t, val_t>*>(pos.current);
   
  RBTNode<key_t, val_t>* deletedNode = node;
  // keep track of color of the node being deleted or moved
  bool originalColor = deletedNode->getColor(); 
  RBTNode<key_t, val_t>* replaceNode;

  // deleteNode has no child or only one child
  if (deletedNode->getLeftChild() == this->sentinel)
  {
    replaceNode = node->getRightChild();
    transplant(deletedNode, replaceNode);
  }
  else if (deletedNode->getRightChild() == this->sentinel)
  {
    replaceNode = node->getLeftChild();
    transplant(deletedNode, replaceNode);
  }

  // deleteNode has two children
  else
  {
    iter.next();
    deletedNode = dynamic_cast<RBTNode<key_t, val_t>*>(iter.current);
    originalColor = deletedNode->getColor();
    replaceNode = deletedNode->getRightChild();
    if (deletedNode->getParent() == node)
    {
      // set replaceNode's parent, even if replaceNode is sentinel
      replaceNode->setParent(deletedNode);
    }
    // If deletedNode is not the right child of node
    else
    {
      transplant(deletedNode, replaceNode);
      deletedNode->setRightChild(node->getRightChild());
      deletedNode->getRightChild()->setParent(deletedNode);
    }
    // replace node by deletedNode (its successor);
    transplant(node, deletedNode);
    deletedNode->setLeftChild(node->getLeftChild());
    deletedNode->getLeftChild()->setParent(deletedNode);
    deletedNode->setColor(node->getColor());
  }
  if (not originalColor)
  {
    deleteFixup(replaceNode);
  }
  delete node;
  this->numItems --;
  return iter;
}

// deleteFixup
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::deleteFixup(RBTNode<key_t, val_t>* replaceNode)
{
  RBTNode<key_t, val_t>* sib; // sibling of replaceNode
  RBTNode<key_t, val_t>* root = dynamic_cast<RBTNode<key_t, val_t>*>(this->root);

  // until replaceNode is black
  while (replaceNode != root and replaceNode->getColor() == false)
  {
    // if replaceNode is the left child
    if (replaceNode == replaceNode->getParent()->getLeftChild())
    {
      sib = replaceNode->getParent()->getRightChild();
      if (sib->getColor())
      {
	// change sibling's color to black, parent's color to red
	sib->setColor(false);
	replaceNode->getParent()->setColor(true);
	// rotate left parent
	rotateLeft(replaceNode->getParent());
	// find new sibling (Note: this new sibling is black for sure)
	sib = replaceNode->getParent()->getRightChild();
      }
      if (sib->getLeftChild()->getColor() == false and sib->getRightChild()->getColor() == false)
      {
	// change sibling's color to red
	sib->setColor(true);
	// node that needs fixing is replaceNode's parent
	replaceNode = replaceNode->getParent();
      }
      
      else 
      {
	if (sib->getRightChild()->getColor() == false)
	{
	  sib->getLeftChild()->setColor(false);
	  sib->setColor(true);
	  // rotate right sibling
	  rotateRight(sib);
	  // find new sibling
	  sib = replaceNode->getParent()->getRightChild();
	}
	sib->setColor(replaceNode->getParent()->getColor());
	replaceNode->getParent()->setColor(false);
	// set sibling's right child's color to black
	sib->getRightChild()->setColor(false);
	// rotate left parent
	rotateLeft(replaceNode->getParent());
	
	// set replaceNode to root to terminate the while-loop
	replaceNode = root;
      }
    }
    
    // if replaceNode is the right child
    else
    {
      sib = replaceNode->getParent()->getLeftChild();

      // if sibling is red
      if (sib->getColor())
      {
	sib->setColor(false);
	replaceNode->getParent()->setColor(true);
	rotateRight(replaceNode->getParent());
	sib = replaceNode->getParent()->getLeftChild();
      }


      if (sib->getLeftChild()->getColor() == false and sib->getRightChild()->getColor() == false)
      {
	sib->setColor(true);
	replaceNode = replaceNode->getParent();
      }
      
      else 
      {
   	if (sib->getLeftChild()->getColor() == false)
	{
	  sib->getRightChild()->setColor(false);
	  sib->setColor(true);
	  rotateLeft(sib);
	  sib = replaceNode->getParent()->getLeftChild();
	}
	
	sib->setColor(replaceNode->getParent()->getColor());
	replaceNode->getParent()->setColor(false);
	sib->getLeftChild()->setColor(false);
	rotateRight(replaceNode->getParent());

	replaceNode = root;
      }
    }
  }
  replaceNode->setColor(false);
}

// printDot
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::printDOT(std::string filename)
{
   using namespace std;
   ofstream fout(filename.c_str());

   long long counter = 1;
   map<RBTNode<key_t, val_t>*, long long> nodeToCounter;
   nodeToCounter[dynamic_cast<RBTNode<key_t, val_t>* >(this->sentinel)] = counter;
   counter++;

   fout << "digraph RBTMultimap {" << endl;

   fout << "\t node" << nodeToCounter[dynamic_cast<RBTNode<key_t, val_t>* >(this->sentinel)] << " [label=\"nil\", style=filled, color=grey, fontcolor=white];" << endl;

   if(this->root != this->sentinel)
   {
      RBTNode<key_t, val_t>* rt = dynamic_cast<RBTNode<key_t, val_t>* >(this->root);
      if(!nodeToCounter[rt])
      {
	 nodeToCounter[rt] = counter;
	 counter++;
      }
      if(!nodeToCounter[rt->getParent()])
      {
	 nodeToCounter[rt->getParent()] = counter;
	 counter++;
      }
      fout << "\t node" << nodeToCounter[rt] << " -> node" << nodeToCounter[rt->getParent()] << " [constraint=false, tailport=n, headport=s";
      if(rt->getParent() == this->sentinel)
      {
	 fout << ", color=grey];" << endl;
      }
      else
      {
	 //The root's parent is something weird!! Make the arrow orange so it sticks out
	 fout << ", color=orange];" << endl;
      }

      map<RBTNode<key_t, val_t>*, bool> printed;
   
      queue<RBTNode<key_t, val_t>* > q;
      q.push(rt);
      while(!q.empty())
      {
	 RBTNode<key_t, val_t>* node = q.front();
	 q.pop();

	 printed[node] = true;
      
	 //Set up node's appearance
	 if(!nodeToCounter[node])
	 {
	    nodeToCounter[node] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " [label=\"k: " << node->getKey() << "\", style=filled, color=";
	 if(node->getColor())
	 {
	    fout << "red";
	 }
	 else
	 {
	    fout << "black, fontcolor=white";
	 }
	 fout << "];" << endl;

	 //Set up child links
	 //First the left node
	 if(!nodeToCounter[node->getLeftChild()])
	 {
	    nodeToCounter[node->getLeftChild()] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " -> node" << nodeToCounter[node->getLeftChild()] << " [tailport=sw";    
	 if(node->getLeftChild() == this->sentinel)
	 {
	    fout << ", color=grey";
	 }
	 else if(printed[node->getLeftChild()])
	 {
	    fout << ", color=orange";
	 }
	 else
	 {
	    q.push(node->getLeftChild());
	 }

	 if(node->getLeftChild() != this->sentinel)
	 {
	    if(node->getLeftChild()->getParent() == node)
	    {
	       //The child's parent pointer points right back,
	       //so draw the second arrow
	       fout << ", dir=both];" << endl;
	    }
	    else
	    {
	       //The child node's parent pointer is not correct!
	       //Draw it in orange so it sticks out
	       fout << "];" << endl;
	       if(!nodeToCounter[node->getLeftChild()->getParent()])
	       {
		  nodeToCounter[node->getLeftChild()->getParent()] = counter;
		  counter++;
	       }
	       fout << "\t node" << nodeToCounter[node->getLeftChild()] << " -> node" << nodeToCounter[node->getLeftChild()->getParent()] << " [tailport=n, color=orange];" << endl;
	    }
	 }
	 else
	 {
	    fout << "];" << endl;
	 }

	 //Now the right node
	 if(!nodeToCounter[node->getRightChild()])
	 {
	    nodeToCounter[node->getRightChild()] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " -> node" << nodeToCounter[node->getRightChild()] << " [tailport=se";    
	 if(node->getRightChild() == this->sentinel)
	 {
	    fout << ", color=grey";
	 }
	 else if(printed[node->getRightChild()])
	 {
	    fout << ", color=orange";
	 }
	 else
	 {
	    q.push(node->getRightChild());
	 }

	 if(node->getRightChild() != this->sentinel)
	 {
	    if(node->getRightChild()->getParent() == node)
	    {
	       //The child's parent pointer points right back,
	       //so draw the second arrow
	       fout << ", dir=both];" << endl;
	    }
	    else
	    {
	       //The child node's parent pointer is not correct!
	       //Draw it in orange so it sticks out
	       fout << "];" << endl;
	       if(!nodeToCounter[node->getRightChild()->getParent()])
	       {
		  nodeToCounter[node->getRightChild()->getParent()] = counter;
		  counter++;
	       }
	       fout << "\t node" << nodeToCounter[node->getRightChild()] << " -> node" << nodeToCounter[node->getRightChild()->getParent()] << " [tailport=n, color=orange];" << endl;
	    }
	 }
	 else
	 {
	    fout << "];" << endl;
	 }
      }
   }
   fout << "}" << endl;
}

#endif
