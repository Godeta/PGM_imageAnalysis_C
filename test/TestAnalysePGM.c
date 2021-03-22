#include "../src/mainFile.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(analysePGM);

TEST_SETUP(analysePGM)
{
  //This is run before EACH TEST
}

TEST_TEAR_DOWN(analysePGM)
{
}

TEST(analysePGM, findCircle)
{
  //All of these should pass
  TEST_ASSERT_EQUAL(0, findCircle());
}