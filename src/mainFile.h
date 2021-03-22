#include <time.h>
//on y trouve notamment les fonctions pour charger une image, la sauvegarder ou appliquer le filtre sobel...
#include "pgmImageProcessing.h"

//pour utiliser des booleans
typedef int bool;
enum { false, true };

//pour faire un test de calcul de temps en C
void testCalcTime();

//tests qui permettent de vérifier pour un anneau qu'il peut être conforme
void findCircle();
bool mandatoryTests(int i, int j);