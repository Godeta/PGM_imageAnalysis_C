#include "usefulFunctions.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(usefulFunctions);


/* These should be ignored because they are commented out in various ways:
#include "whatever.h"
*/
//#include "somethingelse.h"

TEST_SETUP(usefulFunctions)
{
}

TEST_TEAR_DOWN(usefulFunctions)
{
}

TEST(usefulFunctions, IgnoredTest)
{
    TEST_IGNORE_MESSAGE("This Test Was Ignored On Purpose");
}

TEST(usefulFunctions, AnotherIgnoredTest)
{
    TEST_IGNORE_MESSAGE("These Can Be Useful For Leaving Yourself Notes On What You Need To Do Yet");
}

TEST(usefulFunctions, ThisFunctionHasNotBeenTested_NeedsToBeImplemented)
{
    TEST_IGNORE(); //Like This
}
