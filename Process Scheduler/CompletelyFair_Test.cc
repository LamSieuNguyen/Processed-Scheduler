#define CATCH_CONFIG_MAIN //This will make our main for us :)
#include "catch.hpp"

/*More info on Catch
Git-Page: https://github.com/philsquared/Catch
*/

//What are we testing today?
#include "Scheduler.h"
#include "List.h"
#include "Process.h"
#include "BSTMultimap.h"


TEST_CASE("TESTING CompletelyFair Class")
{
  CompletelyFair *test;

  SECTION("addProcesses & popNext")
    {
      test = new CompletelyFair;
      CPUBoundProcess* p = new CPUBoundProcess(1);
      IOBoundProcess* p2 = new IOBoundProcess(2);
      CPUBoundProcess* p3 = new CPUBoundProcess(3);
      // tests the add function
      test->addProcess(p);
      // checks  the pop
      REQUIRE (test->popNext(1) == p);
      
      test->addProcess(p2);
      test->addProcess(p3);
	    
      REQUIRE (test->popNext(3) == p3);
      delete test;
      
    } 
  
}
