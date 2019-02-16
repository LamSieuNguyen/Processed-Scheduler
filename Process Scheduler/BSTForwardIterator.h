
#ifndef BST_FORWARD_ITERATOR
#define BST_FORWARD_ITERATOR

#include "BSTNode.h"

template <class key_t, class val_t>
class BSTForwardIterator
{
  protected:
   //The node the iterator currently points to
   BSTNode<key_t, val_t>* current;
   //The value representing the non-node
   BSTNode<key_t, val_t>* sentinel;
   
  public:
   BSTForwardIterator(BSTNode<key_t, val_t>* node, BSTNode<key_t, val_t>* sentinel);


   virtual void next();


   virtual bool isPastEnd() const;

   //Returns the key of the current node
   virtual const key_t& getKey() const;

   //Returns the value of the current node
   virtual const val_t& getValue() const;
   
   //Sets the value of the current node
   virtual void setValue(const val_t& newVal);

   //Declares BSTMultimap as a friend class
   //(so it can access the protected member current)
   template <class k_t, class v_t> friend class BSTMultimap;

   //Declares RSTMultimap as a friend class
   //(so it can access the protected member current)
   template <class k_t, class v_t> friend class RBTMultimap;
};

////////////////////////////////////////////////////
//Implementation of BSTForwardIterator begins here//
////////////////////////////////////////////////////

template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t>::BSTForwardIterator(BSTNode<key_t, val_t>* node, BSTNode<key_t, val_t>* sentinel)
{
  current = node;
  this->sentinel = sentinel;
}

//Points the iterator at the successor of its
//current node (if current is the sentinel,
//does nothing).
template <class key_t, class val_t>
void BSTForwardIterator<key_t, val_t>::next()
{
  if (current != sentinel)
  {

    if (current->getRightChild() != sentinel)
    { 
      current = current->getRightChild();
      
      // find the most left node of the right subtree
      if (current != sentinel)
      {
	while (current->getLeftChild() != sentinel)
	{
	  current = current->getLeftChild();
	}
      }
    }

    else if (current->getKey() < current->getParent()->getKey())
    {
      current = current->getParent();
    }
 
    else if (current->getKey() >= current->getParent()->getKey())
    {
      // go up until find the first left child node 
      // or go all the way up to the root
      while (current->getParent() != sentinel and current->getKey() >= current->getParent()->getKey())
      {
	current = current->getParent();
      }
      // successor is the parent of the left child node 
      // or parent of the root - the sentinel, when current is the largest
      current = current->getParent();
    }
  }
}

//Returns true if the iterator has moved past
//the end of the container (if current is sentinel)
template <class key_t, class val_t>
bool BSTForwardIterator<key_t, val_t>::isPastEnd() const
{
  return (current == sentinel);
}

//Returns the key of the current node
template <class key_t, class val_t>
const key_t& BSTForwardIterator<key_t, val_t>::getKey() const
{
  return current->getKey();
}

//Returns the value of the current node
template <class key_t, class val_t>
const val_t& BSTForwardIterator<key_t, val_t>::getValue() const
{
  return current->getValue();
}

template <class key_t, class val_t>
//Sets the value of the current node
void BSTForwardIterator<key_t, val_t>::setValue(const val_t& newVal)
{
  current->setValue(newVal);
}

#endif
