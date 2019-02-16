
#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include<iostream>
#include<cstdlib>
#include "List.h"

using namespace std; 

template <class item_t>
class ArrayList: public List <item_t>
{
 protected: 
  int capacity;
  int size;
  item_t* items;

 public:
  ArrayList();
  ArrayList(int capacity);
  virtual ~ArrayList();

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
  virtual int getCapacity() const;
  // HELPER method to double the size of the list
  virtual void doubleCapacity();
  virtual void printList() const;
};

/////////////////////////////////////
// Implementation of ArrayList class
/////////////////////////////////////

//Constructor, makes the capacity to size.
template <class item_t>
ArrayList<item_t>::ArrayList()
{
  items = new item_t[10];
  capacity = 10;
  size = 0;
}

//Initializes the array list with the given capacity and length 0
template <class item_t>
ArrayList<item_t>::ArrayList(int capacity)
{
  capacity = 10;
  items = new item_t[capacity];

  size = 0;
}

//Destructor
template <class item_t>
ArrayList<item_t>::~ArrayList()
{
  delete[] items;
}

//Adds item to the end of the list
template <class item_t>
void ArrayList<item_t>::pushBack(const item_t& item)
{
  if (size == capacity)
  {
    doubleCapacity();
  }

  items[size] = item;
  size ++;
}

//Removes the last element
template <class item_t>
void ArrayList<item_t>::popBack()
{
  if (size > 0)
  {
    size --;
  }
}

//Returns the last element
template <class item_t>
const item_t& ArrayList<item_t>::getBack() const
{
  return items[size-1];
}

// adds item to front of the list
template <class item_t>
void ArrayList<item_t>::pushFront(const item_t& item)
{
  if (size == capacity)
  {
    // increases the size of the list
    doubleCapacity();
  }

  for (int i = size -1; i>=0; i--)
  {
    items[i+1] = items[i];
  }
  items[0] = item;
  size ++;
}

//Removes the first element
template <class item_t>
void ArrayList<item_t>::popFront()
{
  if (size > 0)
  {
    for (int i = 0; i < size-1; i++)
    {
      items[i] = items[i+1];
    }
    size --;
  }
}

//Returns the first element
template <class item_t>
const item_t& ArrayList<item_t>::getFront() const
{
  return items[0];
}

//Returns the item at the index
template <class item_t>
const item_t& ArrayList<item_t>::getItem(int index) const
{ 
  return items[index];
}

//Sets the item at the index
template <class item_t>
void ArrayList<item_t>::setItem(int index, const item_t& item)
{
  items[index] = item;
}
  
//inserts an item into the list by moving everything after it.
template <class item_t>
void ArrayList<item_t>::insert(int index, const item_t& item)
{
  if (size == capacity)
  {
    doubleCapacity();
  }

  for (int i = size-1; i >= index; i--)
  {
    items[i+1] = items[i];
  }
  items[index] = item;
  size ++;
}

// removes the item at the index
template <class item_t>
void ArrayList<item_t>::remove(int index)
{
  if (size > 0)
  {
    for (int i = index; i < size-1; i++)
    {
      items[i] = items[i+1];
    }
    size --;
  }
}

//Returns the number of elements in the list.
template <class item_t>
int ArrayList<item_t>::getSize() const
{
  return size;
}
// returns the capacity
template <class item_t>
int ArrayList<item_t>::getCapacity() const
{
  return capacity;
}
// checks if list is empty
template <class item_t>
bool ArrayList<item_t>::isEmpty() const
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

//Increases the capacity of the list
template <class item_t>
void ArrayList<item_t>::doubleCapacity()
{
  capacity *= 2;
  item_t* bigList = new item_t[capacity];
  for (int i = 0; i < size; i++)
  {
    bigList[i] = items[i];
  }
  items= bigList;
}

//Print all elements in the list
template <class item_t>
void ArrayList<item_t>::printList() const
{
  for (int i = 0; i < size; i++)
  {
    cout << items[i] << " ";
  }
}

#endif
