#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "BSTNode.h"
#include "BSTMultimap.h"
#include <iostream>
#include <string>

TEST_CASE("TESTING BSTMultimap Class")
{

  BSTForwardIterator<int ,int>* bts;
  BSTForwardIterator<int ,int>* val;
  BSTNode<int,int>* node;
  BSTNode<int,int>* node2;

  BSTNode<int,int>* node3;
    
  BSTNode<int,int>* sentinel;
  SECTION("Constructor & getKey & getValue & setValue ")
    {
      node = new BSTNode<int,int>(1,3);
      sentinel = 0;
      bts = new BSTForwardIterator<int,int>(node,sentinel);
      REQUIRE(bts->getKey() == 1);
      REQUIRE (bts->getValue() == 3);
      bts->setValue(5);
      REQUIRE (bts->getValue() == 5);
      delete bts;
      
    }
  
  /*SECTION(" next")
    {
      node = new BSTNode<int,int>(1,3);
      node2 = new BSTNode<int,int>(4,5);
      node3 = new BSTNode<int,int>(1,6);
      sentinel = 0;
      bts = new BSTForwardIterator<int,int>(node,sentinel);
      bts->next();
      delete bts;
      

    }
  */
    SECTION("ISPastend")
    {
      node = new BSTNode<int,int>(1,3);
      sentinel = 0;
      bts = new BSTForwardIterator<int,int>(node,sentinel);
      bool check = bts->isPastEnd();
      REQUIRE(check == false);
      node = sentinel;
      val = new BSTForwardIterator<int,int>(node,sentinel);
      bool check2 = val->isPastEnd();
      REQUIRE(check == false);
      delete bts;
	    
    }
  
}


