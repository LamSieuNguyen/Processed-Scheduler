

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<iostream>
#include<cstdlib>
#include "List.h"
#include "LinkedListNode.h"

using namespace std;

template <class item_t>
class LinkedList: public List <item_t>
{
 protected:
  LinkedListNode<item_t>* head;
  LinkedListNode<item_t>* tail;
  int size;

 public:
  LinkedList();
  virtual ~LinkedList();

  virtual void pushBack(const item_t& item);
  virtual void popBack();
  virtual const item_t& getBack() const;
   
  virtual void pushFront(const item_t& item);
  virtual void popFront();
  virtual const item_t& getFront() const;

  virtual const item_t& getItem(int index) const;
  virtual void setItem(int index, const item_t& item);
  
  virtual void insert(int index, const item_t& item);
  virtual void remove(int index);

  virtual int getSize() const;
  virtual bool isEmpty() const;

  virtual void printList() const;
  // a helper function to get a value at an index
  virtual LinkedListNode<item_t>* getNode(int index) const;
};

///////////////////////////////////////
// Implementation of LinkedList class
///////////////////////////////////////

// the Constructor
template <class item_t>
LinkedList<item_t>::LinkedList()
{
  head = 0;
  tail = 0;
  size = 0;
}

//Deletes all nodes of the linked list
template <class item_t>
LinkedList<item_t>::~LinkedList()
{
  LinkedListNode<item_t>* tempNode = head;
  while (head != 0)
  {
    head = head->getNext();
    delete tempNode;
    tempNode = head;
  }
}

//Adds item to the end of the list
template <class item_t>
void LinkedList<item_t>::pushBack(const item_t& item)
{
  LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(0, item);
  if (size == 0)
  {
    head = newNode;
    tail = newNode;
  }
  else
  {
    tail->setNext(newNode);
    tail = newNode;
  }
  size ++;
}

//Removes, but does not return, the last element of the list
template <class item_t>
void LinkedList<item_t>::popBack()
{
  if (size == 1)
  {
    delete head;
    head = 0;
    tail = 0;
    size = 0;
  }
  else if (size > 1)
  {
    // sets a temp node to be prior to the ones you want to popback. the set the last node to be after it
    LinkedListNode<item_t>* temp = getNode(size-2);
    LinkedListNode<item_t>* lastNode = temp->getNext();
    
    temp->setNext(0);
    delete lastNode;
    size --;
  }
}

//Returns, but does not remove, the last element of the list
template <class item_t>
const item_t& LinkedList<item_t>::getBack() const
{
  return tail->getItem();
}

//Adds item to the front of the list
template <class item_t>
void LinkedList<item_t>::pushFront(const item_t& item)
{
  // makes a new node 
  LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(head, item);
  if (size == 0)
  {
    head = newNode;
    tail = newNode;
  }
  // set head to new node then increment the size
  else
  {
    head = newNode;
  }
  size ++;
}

// removes the item at the front
template <class item_t>
void LinkedList<item_t>::popFront()
{
  if (size == 1)
  {
    delete head;
    head = 0;
    tail = 0;
    size = 0;
  }
  else if (size > 1)
  {
    // sets temp node to be equal to head, set head to get next. delete the temp.
    LinkedListNode<item_t>* tempNode = head;
    head = head->getNext();
    delete tempNode;
    size --;
  }
}

//returns the first item
template <class item_t>
const item_t& LinkedList<item_t>::getFront() const
{
  return head->getItem();
}

//Returns the item the index
template <class item_t>
const item_t& LinkedList<item_t>::getItem(int index) const
{ 
  // makes a temp node then returns the value at that temp
  LinkedListNode<item_t>* tempNode = getNode(index);
  return tempNode->getItem();
}

//Sets the item at the index
template <class item_t>
void LinkedList<item_t>::setItem(int index, const item_t& item)
{
  LinkedListNode<item_t>* tempNode = getNode(index);
  tempNode->setItem(item);
}
  
// inserts item to the index
template <class item_t>
void LinkedList<item_t>::insert(int index, const item_t& item)
{
  if (index == 0)
  {
    pushFront(item);
  }
  else if (index > 0 and index < size)
  {
    // sets 2 nodes to be equal to the prev node and next node .
    LinkedListNode<item_t>* prevNode = getNode(index-1);
    LinkedListNode<item_t>* nextNode = prevNode->getNext();
    
    LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(nextNode, item);
    prevNode->setNext(newNode);
    size ++;
  }
}

// removes item at index.
template <class item_t>
void LinkedList<item_t>::remove(int index)
{
  if (index == 0)
  {
    popFront();
  }
  else if (index == size - 1)
  {
    popBack();
  }
  else if (index > 0 and index < size - 1)
  {
    LinkedListNode<item_t>* preNode = getNode(index-1);
    LinkedListNode<item_t>* deleteNode = preNode->getNext();
    LinkedListNode<item_t>* nextNode = deleteNode->getNext();
    
    preNode->setNext(nextNode);
    delete deleteNode;
    size --;
  }
}

//Returns the number of elements in the list.
template <class item_t>
int LinkedList<item_t>::getSize() const
{
  return size;
}

//checks if the list is empty
template <class item_t>
bool LinkedList<item_t>::isEmpty() const
{
  if (size == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//Print all elements in the list
template <class item_t>
void LinkedList<item_t>::printList() const
{
  LinkedListNode<item_t>* tempNode = head;
  while (tempNode != 0)
  {
    cout << tempNode->getItem() << " ";
    tempNode = tempNode->getNext();
  }
  cout << endl;
}

// Return the pointer to the node at the given index
template <class item_t>
LinkedListNode<item_t>* LinkedList<item_t>::getNode(int index) const
{
  LinkedListNode<item_t>* tempNode = head;
  int pos = 0;
  while (pos != index)
  {
    tempNode = tempNode->getNext();
    pos ++;
  }
  return tempNode;
}

#endif
