/** Ce fichier sert à comprendre comment on peut traiter une image PGM en C
 * petits tutos intéressant sur le traitement d'images en C
https://batchloaf.wordpress.com/2011/11/21/pgm-image-processing-example/ 
-> ouvre une image PGM et propose des modifications comme inverser les couleurs, compter le nombre de pixels blancs, detecter le bord horizontal

https://fractalcoding.blogspot.com/2019/10/image-processing-in-c.html
-> détails avec vidéo sur différentes transformations applicable à une image pgm (changement luminausité,flou...)

https://ugurkoltuk.wordpress.com/2010/03/04/an-extreme-simple-pgm-io-api/ 
-> un exemple très simple de chargement et d'écriture d'une image PGM, bien expliqué

https://github.com/th3gundy/pgm-image-processing/blob/master/image_processing.c 
-> du code pour ouvrir une image PGM et écrire en sortie une autre avec des niveaux de gris différents
*/

#include "mainFile.h"

/** Notre structure définissant une image
 * Elle contient le nombre de lignes, colonnes, valeur maximale de gris et une matrice
 * */
typedef struct _IMG {
    int row;
    int col;
    int max_gray;
    int **matrix;
} IMG;

int main() {
    return 0;
}