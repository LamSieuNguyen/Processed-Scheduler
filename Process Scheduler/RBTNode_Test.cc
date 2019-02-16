#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "BSTNode.h"
#include "BSTMultimap.h"
#include "RBTNode.h"
#include <iostream>
#include <string>

TEST_CASE("TESTING RBTNode class")
{

  RBTNode<int,int>* RBT;
  RBTNode<int,int>* parent;
  RBTNode<int,int>* l;
  RBTNode<int,int>* r;
  SECTION("Constructor & getColor & setColor")
    {
      RBT = new RBTNode<int,int>(1,1,true);
      REQUIRE(RBT->getColor() == true);
      RBT->setColor(false);
      REQUIRE(RBT->getColor() == false);

      
    }
  
  SECTION(" getparent ")
    {
      RBT = new RBTNode<int,int>(1,1,true);
      parent = new RBTNode<int,int>(2,3,true);
      RBT->setParent(parent);
      REQUIRE(RBT->getParent()== parent);
      
    }
  
    SECTION("getleftchild & get rightchild")
    {
      RBT = new RBTNode<int,int>(1,1,true);
      l  = new RBTNode<int,int>(3,4,true);
      r  = new RBTNode<int,int>(4,5,true);
      RBT->setLeftChild(l);
      RBT->setRightChild(r);
      REQUIRE(RBT->getRightChild()== r);
      REQUIRE(RBT->getLeftChild()== l);
	    
    }
  
}


