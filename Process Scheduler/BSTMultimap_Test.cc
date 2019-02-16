#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "BSTNode.h"
#include "BSTMultimap.h"
#include <iostream>
#include <string>

TEST_CASE("TESTING BSTMultimap Class")
{

  BSTMultimap<double ,double>* bts;
  BSTMultimap<double ,double>* val;
  BSTForwardIterator<double ,double>* iter;
  BSTForwardIterator<double,double>* iter2;
  BSTNode<double,double>* node;
  BSTNode<double,double>* node2;
  BSTNode<double,double>* sentinel;
  SECTION("Constructor & Insert  & getsize & isEmpty & clear")
    {
      bts = new BSTMultimap<double,double>();
      
      bts->insert(1,2);
      bts->insert(4,5);
      bts->insert(10,11);
      REQUIRE(bts->getSize() == 3);
      bts->clear();
      REQUIRE (bts->getSize()==0);
      REQUIRE(bts->isEmpty());
    }
  
    SECTION("Contains")
    {

    bts = new BSTMultimap<double , double >;
    bts->insert(1,2);
    bts->insert(4,5);
    bts->insert(10,11);
    REQUIRE(bts->contains(1));
    
    }
    /*
    SECTION("getMin/Max")
    {

    bts = new BSTMultimap<double , double >;
    sentinel = 0;
    node = new BSTNode<double,double>(1,2);
    node2 = new BSTNode<double,double>(13,2);
    BSTForwardIterator<double ,double>* iter = new BSTForwardIterator<double,double>(node,sentinel);
    BSTForwardIterator<double ,double>* iter2 = new BSTForwardIterator<double,double>(node2,sentinel);
    bts->insert(node);
    bts->insert(node2);
    bts->insert(10,11);
    REQUIRE( bts->getMin() == iter);
    REQUIRE( bts->getMax()  == iter2);
    
    }
    
    SECTION("findFirst/Last")
    {

    bts = new BSTMultimap<double , double >;
    
    bts->insert(1,2);
    bts->insert(4,5);
    bts->insert(10,11);
    REQUIRE(bts->contains(1));
    
    }
    SECTION("remove")
    {

    bts = new BSTMultimap<double , double >;
    
    bts->insert(1,2);
    bts->insert(4,5);
    bts->insert(10,11);
    REQUIRE(bts->contains(1));
    
    }
    */
 
}


