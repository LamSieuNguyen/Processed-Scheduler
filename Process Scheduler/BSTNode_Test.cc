#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "BSTNode.h"
#include <iostream>
#include <string>

TEST_CASE("TESTING BSTNode Class")
{

  BSTNode<int ,int>* bts;
  BSTNode<int ,int>* val;
    
  SECTION("Constructor")
    {
      bts = new BSTNode<int,int>(1,1);
      REQUIRE (bts->getParent() == 0);
      REQUIRE (bts->getLeftChild() == 0);
      REQUIRE (bts->getRightChild() == 0);

    }


    SECTION("GET KEY AND SET KEY FUNCTION")
    {

    bts = new BSTNode<int ,int >(1,1);
    bts->setKey(1);
    REQUIRE(bts->getKey() == 1);
    
    }
    
  SECTION(" GET VALUE AND SET VALUE FUNCTION")
    {
      bts = new BSTNode<int,int>(1,1);
      bts->setValue(2);
      REQUIRE(bts->getValue() == 2);
    
    }

  SECTION("GET & SET LEFT CHILD")
    {
      bts = new BSTNode<int,int>(1,1);
      val = new BSTNode<int,int>(2,2);
      bts->setLeftChild(val);
      REQUIRE(bts->getLeftChild() == val);

    
    }
  
  SECTION("GET & SET RIGHT CHILD")
    {
      bts = new BSTNode<int,int>(1,1);
      val = new BSTNode<int,int>(2,2);
      bts->setRightChild(val);
      REQUIRE(bts->getRightChild() == val);

    }

  SECTION("GET & SET PARENT")
    {
      bts = new BSTNode<int,int>(1,1);

      val = new BSTNode<int,int>(2,2);
      bts->setParent(val);
      REQUIRE(bts->getParent() == val);
  
  
    
    }
  
}

