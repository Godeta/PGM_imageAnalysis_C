#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(mainFile)
{
  printf("\n- - - - - - - - - - - - - - - - - \n Tests détection d'anneaux sur la matrice  :\n- - - - - - - - - - - - - - - - - \n");
  RUN_TEST_CASE(mainFile, findCircle);
  printf("\n- - - - - - - - - - - - - - - - - \n Tests conformité des anneaux :\n- - - - - - - - - - - - - - - - - \n");
  // RUN_TEST_CASE(mainFile, scraping_getipAdress_connectToAdress);
}