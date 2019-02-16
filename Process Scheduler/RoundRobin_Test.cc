#define CATCH_CONFIG_MAIN //This will make our main for us :)
#include "catch.hpp"

/*More info on Catch
Git-Page: https://github.com/philsquared/Catch
*/

//What are we testing today?
#include "Scheduler.h"
#include "List.h"
#include "Process.h"
#include "ArrayList.h"

TEST_CASE("TESTING RoundRobin Class")
{
  RoundRobin *test_roundrobin;

  SECTION("addProcesses & popNext")
    {
      test_roundrobin  =  new RoundRobin();
      CPUBoundProcess* p = new CPUBoundProcess(1);
      IOBoundProcess* p2 = new IOBoundProcess(2);
      CPUBoundProcess* p3 = new CPUBoundProcess(3);
      // tests the add function
      test_roundrobin -> addProcess(p);
      // checks if the pop
      REQUIRE (test_roundrobin->popNext(1) == p);
      
      test_roundrobin -> addProcess(p2);
      test_roundrobin -> addProcess(p3);
	    
      REQUIRE (test_roundrobin->popNext(3) == p3);
      delete test_roundrobin;
      
    } 
  
}
