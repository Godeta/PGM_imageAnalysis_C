#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(usefulFunctions)
{
  RUN_TEST_CASE(usefulFunctions, IgnoredTest);
  RUN_TEST_CASE(usefulFunctions, AnotherIgnoredTest);
  RUN_TEST_CASE(usefulFunctions, ThisFunctionHasNotBeenTested_NeedsToBeImplemented);
}