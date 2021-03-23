#include <time.h>
//on y trouve notamment les fonctions pour charger une image, la sauvegarder ou appliquer le filtre sobel...
#include "pgmImageProcessing.h"

//pour utiliser des booleans
typedef int bool;
enum { false, true };

//pour faire un test de calcul de temps en C
void testCalcTime();


// matrices de pixels, 1000 lignes et 1000 colonnes
int p[1000][1000];
int p2[1000][1000];
int comp[1000][1000];
// largeur et hauteur initialisées dans la récupération de l'image
int maxWidth, maxHeight;

//tests qui permettent de vérifier pour un anneau qu'il peut être conforme
int findCircle();
bool mandatoryTests(int i, int j);
int comparerImages(int img [1000][1000], int img2 [1000][1000]);
void cutCircle(int i, int j);