#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(pgmImageProcessing)
{
    printf("\n- - - - - - - - - - - - - - - - - \n Tests chargement et traitement des images :\n- - - - - - - - - - - - - - - - - \n");
  RUN_TEST_CASE(pgmImageProcessing, load_image);
  RUN_TEST_CASE(pgmImageProcessing, save_image);
}