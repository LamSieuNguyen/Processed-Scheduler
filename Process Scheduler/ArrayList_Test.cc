#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "List.h"
#include "ArrayList.h"
#include <iostream>
#include <string>

TEST_CASE("TESTING ArrayList Class"){

  ArrayList<int>* alists;
  ArrayList<string>* alists2;
  SECTION("Default Constructor")
    {
    alists = new ArrayList<int>();
    REQUIRE (alists->getSize() == 0);
    REQUIRE_FALSE(alists->getSize() != 0); //Check if false

    REQUIRE (alists->getCapacity() == 10);
    REQUIRE_FALSE(alists->getCapacity() != 10); //Check if false

    delete alists;

    
    alists2 = new ArrayList<string>();
    REQUIRE (alists2->getSize() == 0);
    REQUIRE_FALSE(alists2->getSize() != 0); //Check if false

    REQUIRE (alists2->getCapacity() == 10);
    REQUIRE_FALSE(alists2->getCapacity() != 10); //Check if false

    delete alists2;
    }
  
  SECTION("Capacity Constructor")
    {
    alists = new ArrayList<int>(5);
    REQUIRE (alists->getSize() == 0);
    REQUIRE_FALSE(alists->getSize() != 0); //Check if false

    REQUIRE (alists->getCapacity() == 10);
    REQUIRE_FALSE(alists->getCapacity() != 10); //Check if false

    delete alists;
    alists2 = new ArrayList<string>(5);
    REQUIRE (alists2->getSize() == 0);
    REQUIRE_FALSE(alists2->getSize() != 0); //Check if false

    REQUIRE (alists2->getCapacity() == 10);
    REQUIRE_FALSE(alists2->getCapacity() != 10); //Check if false

    delete alists2;
    }

  SECTION("Pushback Function")
    {

      alists = new ArrayList<int>();
      alists->pushBack(1);
      alists->pushBack(2);
      alists->pushBack(3);
      alists->pushBack(4);
      alists->pushBack(5);
      alists->pushBack(6);
      alists->pushBack(7);
      alists->pushBack(8);
      alists->pushBack(9);
      alists->pushBack(10);		
      alists->pushBack(11);
      alists->pushBack(12);


    REQUIRE(alists->getItem(11) == 12); //should be 11, is 49
    REQUIRE(alists->getCapacity() == 20);
    REQUIRE(alists->getSize() == 12); //should be 11

    delete alists;
    /*
    alists2 = new ArrayList<string>();
    alists2->pushBack("1");
    alists2->pushBack("2");
    alists2->pushBack("3");
    alists2->pushBack("4");
    alists2->pushBack("5");
    alists2->pushBack("6");
    alists2->pushBack("7");
    alists2->pushBack("8");
    alists2->pushBack("9");
    alists2->pushBack("10");		
    alists2->pushBack("11");
    alists2->pushBack("12");
    

    REQUIRE(alists2->getItem(11) == "12"); //should be 11, is 49
    REQUIRE(alists2->getCapacity() == 20);
    REQUIRE(alists2->getSize() == 12); //should be 11

    delete alists2;
    */
  }

  SECTION("Popback Function")
    {
      alists = new ArrayList<int>();
      alists->pushBack(5);
      alists->pushBack(6);
    REQUIRE(alists->getItem(0) == 5);
    REQUIRE_FALSE(alists->getItem(0) != 5); //Check if false
    REQUIRE(alists->getSize() == 2);
    REQUIRE_FALSE(alists->getSize() != 2); //Check if false
    REQUIRE(alists->getBack() == 6);


    alists->popBack();
    REQUIRE(alists->getSize() == 1);
    REQUIRE(alists->getBack() == 5);

    delete alists;
    
    alists2 = new ArrayList<string>();
    alists2->pushBack("5");
    alists2->pushBack("6");
    REQUIRE(alists2->getItem(0) == "5");
    REQUIRE_FALSE(alists2->getItem(0) != "5"); //Check if false
    REQUIRE(alists2->getSize() == 2);
    REQUIRE_FALSE(alists2->getSize() != 2); //Check if false
    REQUIRE(alists2->getBack() == "6");


    alists2->popBack();
    REQUIRE(alists2->getSize() == 1);
    REQUIRE(alists2->getBack() == "5");

    delete alists2;
    
    }
  SECTION("Pushfront Function")
    {
    alists= new ArrayList<int>();

    alists->pushFront(8);
    alists->pushFront(5);
    
    alists->pushFront(4);
    alists->pushFront(3);
    alists->pushFront(2);
    
    alists->pushFront(9);

    REQUIRE(alists->getFront() == 9);
    REQUIRE(alists->getBack() == 8);
    
    delete alists;
    
    alists2= new ArrayList<string>();

    alists2->pushFront("8");
    alists2->pushFront("5");
    
    alists2->pushFront("4");
    alists2->pushFront("3");
    alists2->pushFront("2");
    
    alists2->pushFront("9");

    REQUIRE(alists2->getFront() == "9");
    REQUIRE(alists2->getBack() == "8");
    
    delete alists2;
    }
  
  SECTION("Popfront Function")
    {
    alists = new ArrayList<int>();
    alists->pushFront(5);
    alists->pushFront(4);
    REQUIRE(alists->getFront() == 4);
    REQUIRE(alists->getSize() == 2);

    alists->popFront();
    REQUIRE(alists->getFront() == 5);
    REQUIRE(alists->getSize() == 1);

    delete alists;

    alists2 = new ArrayList<string>();
    alists2->pushFront("5");
    alists2->pushFront("4");
    REQUIRE(alists2->getFront() == "4");
    REQUIRE(alists2->getSize() == 2);

    alists2->popFront();
    REQUIRE(alists2->getFront() == "5");
    REQUIRE(alists2->getSize() == 1);

    delete alists2;
    }

  SECTION("SetItem Function")
    {
      alists= new ArrayList<int>();
      alists->pushFront(5);
      alists->pushFront(4);
      alists->pushFront(3);
      REQUIRE(alists->getSize() == 3);
      REQUIRE(alists->getItem(1) == 4);

      alists->setItem(1,6);
      REQUIRE(alists->getSize() == 3);
      REQUIRE(alists->getItem(1) == 6);

      delete alists;

      alists2= new ArrayList<string>();
      alists2->pushFront("5");
      alists2->pushFront("4");
      alists2->pushFront("3");
      REQUIRE(alists2->getSize() == 3);
      REQUIRE(alists2->getItem(1) =="4");

      alists2->setItem(1,"6");
      REQUIRE(alists2->getSize() == 3);
      REQUIRE(alists2->getItem(1) == "6");

      delete alists2;
    }
  
  SECTION("Insert Function")
    {
    alists = new ArrayList<int>();
    alists->pushFront(5);
    alists->pushFront(4);
    alists->pushFront(3);
    REQUIRE(alists->getSize() == 3);
    REQUIRE(alists->getItem(1) == 4);

    alists->insert(1,8);
    REQUIRE(alists->getSize() == 4);
    REQUIRE(alists->getItem(1) == 8);
    REQUIRE(alists->getFront() == 3);
    REQUIRE(alists->getBack() == 5);    

    delete alists;

    alists2 = new ArrayList<string>();
    alists2->pushFront("5");
    alists2->pushFront("4");
    alists2->pushFront("3");
    REQUIRE(alists2->getSize() == 3);
    REQUIRE(alists2->getItem(1) == "4");

    alists2->insert(1,"8");
    REQUIRE(alists2->getSize() == 4);
    REQUIRE(alists2->getItem(1)== "8");
    REQUIRE(alists2->getFront() == "3");
    REQUIRE(alists2->getBack() == "5");    

    delete alists2;
    }

  SECTION("Remove Function")
    {
    alists= new ArrayList<int>();
    alists->pushFront(5);
    alists->pushFront(4);
    alists->pushFront(3);
    REQUIRE(alists->getSize() == 3);
    REQUIRE(alists->getItem(1) == 4);

    alists->remove(1);
    REQUIRE(alists->getSize() == 2);
    REQUIRE(alists->getItem(1) == 5);

    delete alists;

    alists2= new ArrayList<string>();
    alists2->pushFront("5");
    alists2->pushFront("4");
    alists2->pushFront("3");
    REQUIRE(alists2->getSize() == 3);
    REQUIRE(alists2->getItem(1) == "4");

    alists2->remove(1);
    REQUIRE(alists2->getSize() == 2);
    REQUIRE(alists2->getItem(1) == "5");

    delete alists2;
    }

  SECTION("Remove Function")
    {
    alists = new ArrayList<int>();
    REQUIRE(alists->isEmpty() == 1);

    alists->pushFront(5);
    REQUIRE(alists->isEmpty() == 0);

    delete alists;
    }
    alists2 = new ArrayList<string>();
    REQUIRE(alists2->isEmpty() == 1);

    alists2->pushFront("5");
    REQUIRE(alists2->isEmpty() == 0);

    delete alists2;
  
}
