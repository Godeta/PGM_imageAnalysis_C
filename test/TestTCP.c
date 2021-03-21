#include "../src/TCP.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(TCP);

//sometimes you may want to get at local data in a module.
//for example: If you plan to pass by reference, this could be useful
//however, it should often be avoided
extern int Counter;

TEST_SETUP(TCP)
{
  //This is run before EACH TEST
}

TEST_TEAR_DOWN(TCP)
{
}

TEST(TCP, ServerWrongPort)
{
  //All of these should pass
  TEST_ASSERT_EQUAL(-1, TCPserver(20));
  TEST_ASSERT_EQUAL(-1, TCPserver(14));
}

TEST(TCP, ClientWrongPort)
{
  //All of these should pass
  TEST_ASSERT_EQUAL(-1, TCPclient(-1));
  TEST_ASSERT_EQUAL(-1, TCPclient(20));
}

TEST(TCP, scraping_getipAdress_connectToAdress)
{
  //All of these should pass
  char truc[100];
  TEST_ASSERT_EQUAL(-1, getIpAddress("aaa",truc));
  TEST_ASSERT_EQUAL(0, getIpAddress("google.com",truc));
  TEST_ASSERT_EQUAL(-1,connectToAddress("a1d"));
  TEST_ASSERT_EQUAL(-1,connectToAddress("google.com"));
  TEST_ASSERT_EQUAL(0,connectToAddress("216.58.201.238"));
  // TEST_ASSERT_EQUAL(0,TCPscraping("google.com"));
  TEST_ASSERT_EQUAL(-1,TCPscraping("yes"));
}