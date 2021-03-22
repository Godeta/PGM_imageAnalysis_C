#include "../src/mainFile.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(mainFile);

TEST_SETUP(mainFile)
{
  //This is run before EACH TEST
}

TEST_TEAR_DOWN(mainFile)
{
}

TEST(mainFile, findCircle)
{
  //All of these should pass
  TEST_ASSERT_EQUAL(-1, findCircle());
}