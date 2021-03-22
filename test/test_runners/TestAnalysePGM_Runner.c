#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(analysePGM)
{
  printf("\n- - - - - - - - - - - - - - - - - \n Tests détection d'anneaux sur la matrice  :\n- - - - - - - - - - - - - - - - - \n");
  RUN_TEST_CASE(analysePGM, findCircle);
  printf("\n- - - - - - - - - - - - - - - - - \n Tests conformité des anneaux :\n- - - - - - - - - - - - - - - - - \n");
  // RUN_TEST_CASE(analysePGM, scraping_getipAdress_connectToAdress);
}