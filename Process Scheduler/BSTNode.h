
#ifndef BSTNODE_H
#define BSTNODE_H

#include <iostream>
#include <cstdlib>

using namespace std;

template <class key_t, class val_t>	
class BSTNode
{
 protected:
  key_t key;
  val_t value;
  BSTNode* leftChild;
  BSTNode* rightChild;
  BSTNode* parent;

 public:
  BSTNode(const key_t& key, const val_t& value);
  virtual ~BSTNode();
  virtual const key_t& getKey() const;
  virtual void setKey(const key_t& newKey);

  virtual const val_t& getValue() const;
  virtual void setValue(const val_t& newValue);

  virtual BSTNode* getLeftChild() const;
  virtual void setLeftChild(BSTNode* newLeftChild);

  virtual BSTNode* getRightChild() const;
  virtual void setRightChild(BSTNode* newRightChild);

  virtual BSTNode* getParent() const;
  virtual void setParent(BSTNode* newParent);
};

///////////////////////////////////
// Implementation of BSTNode class
///////////////////////////////////

template <class key_t, class val_t>
BSTNode<key_t, val_t>::BSTNode(const key_t& key, const val_t& value)
{
  this->key = key;
  this->value = value;
  leftChild = 0;
  rightChild = 0;
  parent = 0;
}


template <class key_t, class val_t>
  BSTNode<key_t, val_t>::~BSTNode()
{
}
template <class key_t, class val_t>
const key_t& BSTNode<key_t, val_t>::getKey() const
{
  return key;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setKey(const key_t& newKey)
{
  key = newKey;
}

template <class key_t, class val_t>
const val_t& BSTNode<key_t, val_t>::getValue() const
{
  return value;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setValue(const val_t& newValue)
{
  value = newValue;
}

template <class key_t, class val_t>
BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getLeftChild() const
{
  return leftChild;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setLeftChild(BSTNode* newLeftChild)
{
  leftChild = newLeftChild;
}

template <class key_t, class val_t>
BSTNode<key_t, val_t>* BSTNode<key_t, val_t>:: getRightChild() const
{
  return rightChild;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setRightChild(BSTNode* newRightChild)
{
  rightChild = newRightChild;
}

template <class key_t, class val_t>
BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getParent() const
{
  return parent;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setParent(BSTNode* newParent)
{
  parent = newParent;
}

#endif
