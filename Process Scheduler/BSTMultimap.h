

#ifndef BSTMULTIMAP_H
#define BSTMULTIMAP_H

#include <iostream>
#include <cstdlib>
#include <queue>
#include "BSTNode.h"
#include "BSTForwardIterator.h"

using namespace std;

template <class key_t, class val_t>
class BSTMultimap
{
 protected:
  BSTNode<key_t, val_t>* root;
  BSTNode<key_t, val_t>* sentinel;
  int numItems;

  virtual void insertNode(BSTNode<key_t, val_t>* newNode);

 public:
  BSTMultimap();
  virtual ~BSTMultimap();
  virtual void insert(const key_t& key, const val_t& value);
  
  virtual int getSize();
  virtual bool isEmpty();
  virtual void printTree();

  virtual bool contains(const key_t& key) const;
  virtual void clear();


  virtual BSTForwardIterator<key_t, val_t> getMin() const;
  virtual BSTForwardIterator<key_t, val_t> getMax() const;

  virtual BSTForwardIterator<key_t, val_t> findFirst(const key_t& key) const;
  virtual BSTForwardIterator<key_t, val_t> findLast(const key_t& key) const;
  virtual void transplant(BSTNode<key_t, val_t>* nodeToReplace, BSTNode<key_t, val_t>* replacementNode);
  virtual BSTForwardIterator<key_t, val_t> remove(const BSTForwardIterator<key_t, val_t>& pos);
};

///////////////////////////////////////
// Implementation of BSTMultimap Class
///////////////////////////////////////


// Constructor
template <class key_t, class val_t>
BSTMultimap<key_t, val_t>::BSTMultimap()
{
  root = 0;
  sentinel = 0;
  numItems = 0;
}
  
template <class key_t, class val_t>
  BSTMultimap<key_t, val_t>::~BSTMultimap()
{
  clear();
}
// helper methode insertNode
template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::insertNode(BSTNode<key_t, val_t>* newNode)
{
  BSTNode<key_t, val_t>* node = root;
  
  BSTNode<key_t, val_t>* parent = root; 
  // to keep track of the parent of new node
  
  bool left; 
  // to keep track whether the new node is a left or right child

  // Find the right position for new node
  while (node != sentinel)
  {
    parent = node;
    if (newNode->getKey() < node->getKey())
    {
      node = node->getLeftChild();
      left = true;
    }
    // Note: if the key of new node == parent's key, 
    // new node will be inserted in the right subtree
    else
    {
      node = node->getRightChild();
      left = false;
    }
  }

  // If the tree is currently empty
  if (numItems == 0)
  {
    root = newNode;
    root->setParent(sentinel);
    root->setLeftChild(sentinel);
    root->setRightChild(sentinel);
  }
  else
  {
    if (left)
    {
      parent->setLeftChild(newNode);
    }
    else
    {
      parent->setRightChild(newNode);
    }
    newNode->setParent(parent);
    newNode->setLeftChild(sentinel);
    newNode->setRightChild(sentinel);
  }
  numItems ++;
}

// insert
template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::insert(const key_t& key, const val_t& value)
{
  BSTNode<key_t, val_t>* newNode = new BSTNode<key_t, val_t>(key, value);
  insertNode(newNode);
}
  
// getSize
template <class key_t, class val_t>
int BSTMultimap<key_t, val_t>::getSize()
{
  return numItems;
}

// isEmpty
template <class key_t, class val_t>
bool BSTMultimap<key_t, val_t>::isEmpty()
{
  return (numItems == 0);
}

// printTree
template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::printTree()
{
  if (numItems > 0)
  {
    queue< BSTNode<key_t, val_t>* > a;
    a.push(root);
    while (not a.empty())
    {
      BSTNode<key_t, val_t>* curNode = a.front();
      a.pop();
      cout << curNode->getKey() << " " << curNode->getValue() << endl;
      
      if (curNode->getLeftChild() != sentinel)
      {
	a.push(curNode->getLeftChild());
      }
      if (curNode->getRightChild() != sentinel)
      {
	a.push(curNode->getRightChild());
      }
    }
  }
}

// contains
template <class key_t, class val_t>
bool BSTMultimap<key_t, val_t>::contains(const key_t& key) const
{
  BSTNode<key_t, val_t>* curNode = root;

  while (curNode != sentinel and curNode->getKey() != key)
  {
   if (curNode->getKey() > key)
   {
     curNode = curNode->getLeftChild();
   }
   else
   {
     curNode = curNode->getRightChild();
   }
  }
  
  if (curNode == sentinel)
  {
    return false;
  }
  else
  {
    return true;
  }
}

// clear
template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::clear()
{
  if (numItems > 0)
  {
    queue< BSTNode<key_t, val_t>* > a;
    a.push(root);
    while (not a.empty())
    {
      BSTNode<key_t, val_t>* curNode = a.front();
      a.pop();

      if (curNode->getLeftChild() != sentinel)
      {
	a.push(curNode->getLeftChild());
      }
      if (curNode->getRightChild() != sentinel)
      {
	a.push(curNode->getRightChild());
      }

      delete curNode;
    }
    root = 0;
    numItems = 0;
  }
}

// getMin
template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::getMin() const
{
  BSTNode<key_t, val_t>* minNode = root;
  BSTForwardIterator<key_t, val_t> iterator(minNode, sentinel);
  if (numItems > 0)
  { 
    while (minNode->getLeftChild() != sentinel)
    {
      minNode = minNode->getLeftChild();
    }

    return iterator;
  }
  return iterator;
} 

// getMax
template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::getMax() const
{
  BSTNode<key_t, val_t>* maxNode = root;
  BSTForwardIterator<key_t, val_t> iterator(maxNode, sentinel);
  if (numItems > 0)
  {

    
    while (maxNode->getRightChild() != sentinel)
    {
      maxNode = maxNode->getRightChild();
    }
  
    return iterator;
  }
  return iterator;
}

// findFirst
template <class key_t, class val_t>
  BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::findFirst(const key_t& key) const
{
  BSTNode<key_t, val_t>* node = root;
  BSTForwardIterator<key_t, val_t> iterator(node, sentinel);
  if (numItems > 0)
    {
  
      while (node != sentinel and node->getKey() != key)
	{
	  if (node->getKey() > key)
	    {
	      node = node->getLeftChild();
	    }
	  else
	    {
	      node = node->getRightChild();
	    }
	}
      return iterator;
    }
  return iterator;
}

template <class key_t, class val_t>
  BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::findLast(const key_t& key) const
{
  BSTNode<key_t, val_t>* node = root;
  BSTNode<key_t, val_t>* thenode;
  BSTForwardIterator<key_t,val_t> temp (node,sentinel);


  while (thenode!=node)
    {
 
      if (node->getKey() < key)
	{
	  node = node->getLeftChild();
	}
      else if (node->getKey() >key)
	{
	  node = node->getRightChild();
	}
      else if (node->getKey() == key && node->getRightChild()!=sentinel)
	{
	  thenode= node;
	  node = node->getRightChild();

	}
      else
	{
	  node = thenode;
	}
      
    }
  
  BSTForwardIterator<key_t, val_t> iterator(thenode, sentinel);
  return iterator; 
}
 // transplant
template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::transplant(BSTNode<key_t, val_t>* nodeToReplace, BSTNode<key_t, val_t>* replacementNode)
{
  BSTNode<key_t, val_t>* parent = nodeToReplace->getParent();

  if (this->root == nodeToReplace)
  {
    this->root = replacementNode;
  }
  else
  {
    if (nodeToReplace == parent->getLeftChild())
    {
      parent->setLeftChild(replacementNode);
    }
    else
    {
      parent->setRightChild(replacementNode);
    }
  }
  replacementNode->setParent(parent);
}
// remove
template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::remove(const BSTForwardIterator<key_t, val_t>& pos)
{
  BSTForwardIterator<key_t, val_t> iter = pos;
  BSTNode<key_t, val_t>* node = pos.current;
   
  BSTNode<key_t, val_t>* deletedNode = node;
  BSTNode<key_t, val_t>* replaceNode;

  if (deletedNode->getLeftChild() == this->sentinel)
  {
    replaceNode = node->getRightChild();
    transplant(deletedNode, replaceNode);
    delete deletedNode;
    delete replaceNode;
  }
  else if (deletedNode->getRightChild() == this->sentinel)
  {
    replaceNode = node->getLeftChild();
    transplant(deletedNode, replaceNode);
    delete deletedNode;
    delete replaceNode;
  }
  else
  {
    iter.next();
    deletedNode = iter.current;
    replaceNode = deletedNode->getRightChild();
    if (deletedNode->getParent()!= node)
      {
	transplant(deletedNode,replaceNode);
	deletedNode->setRightChild(node->getRightChild());
	deletedNode->getRightChild()->setParent(deletedNode);
      }
    transplant(node, deletedNode);
    deletedNode->setLeftChild(node->getLeftChild());
    deletedNode->getLeftChild()->setParent(deletedNode);
    delete deletedNode;
    delete replaceNode;
  }

  delete node;
  this->numItems --;
  return iter;
}


#endif
