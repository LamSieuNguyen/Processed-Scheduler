#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Process.h"

TEST_CASE("TESTING CPUBoundProcess class")

{
  CPUBoundProcess *test;
  SECTION("Default Constructor")
    {
      test = new CPUBoundProcess(20);
      INFO("default constructor");
      CAPTURE(test->getID());
      REQUIRE(test->getID()==20);
      REQUIRE_FALSE(test->getID()!=20);
    }
  SECTION("CPUTIME")
    {
      test = new CPUBoundProcess(20);
      INFO("getting CPUtime");
      CAPTURE(test->getCPUTime());
      REQUIRE(test->getCPUTime()==0);
      REQUIRE_FALSE(test->getCPUTime()!=0);
    }
  
  SECTION("Waittime")
    {
      test = new CPUBoundProcess(13);
      INFO("getting wait time");
      CAPTURE(test->getWaitTime(16));
      REQUIRE(test->getWaitTime()==16);
      REQUIRE_FALSE(test->getWAitTime()!=16);
    }
   SECTION("Blocked Process")
    {
      test = new CPUBoundProcess(200);
      INFO("getting process");
      CAPTURE(test->isBlocked(18));
      REQUIRE(!test->isBlocked(18));
      REQUIRE_FALSE(test->getBlocked(18));
    }
  
  SECTION("Simulated Cycles")
    {
      test = new CPUBoundProcess(100);
      INFO("CPU cylces process");
      CAPTURE(test->simulate(15,18));
      REQUIRE(test->simulate(15,18) == 18);
      REQUIRE_FALSE(test->simulate(15,18) != 18);
    }
}
  
