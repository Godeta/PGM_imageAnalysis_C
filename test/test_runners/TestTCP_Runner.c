#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(TCP)
{
  printf("\n- - - - - - - - - - - - - - - - - \n Tests send back error if wrong port :\n- - - - - - - - - - - - - - - - - \n");
  RUN_TEST_CASE(TCP, ServerWrongPort);
  RUN_TEST_CASE(TCP, ClientWrongPort);
  printf("\n- - - - - - - - - - - - - - - - - \n Tests connecting to a distant server and scrap it like google.com :\n- - - - - - - - - - - - - - - - - \n");
  RUN_TEST_CASE(TCP, scraping_getipAdress_connectToAdress);
}