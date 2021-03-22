#include "../src/pgmImageProcessing.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(pgmImageProcessing);

TEST_SETUP(pgmImageProcessing)
{
  //This is run before EACH TEST
}

TEST_TEAR_DOWN(pgmImageProcessing)
{
}

TEST(pgmImageProcessing, load_image)
{
    int test [1000][1000];
    TEST_ASSERT_EQUAL(-1, load_image_from_file("a", test));
    TEST_ASSERT_EQUAL(0, load_image_from_file("../pgm_de_test/examen_0.pgm", test));
}

TEST(pgmImageProcessing, save_image)
{
    int test [1000][1000];
    TEST_ASSERT_EQUAL(-1, load_image_from_file("a", test));
    TEST_ASSERT_EQUAL(0, save_image_to_file("truc.pgm", test));
}
