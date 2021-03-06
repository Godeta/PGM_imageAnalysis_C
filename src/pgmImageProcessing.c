/** Ce fichier sert à comprendre comment on peut traiter une image PGM en C
 * petits tutos intéressant sur le traitement d'images en C
https://batchloaf.wordpress.com/2011/11/21/pgm-image-processing-example/ 
-> ouvre une image PGM et propose des modifications comme inverser les couleurs, compter le nombre de pixels blancs, detecter le bord horizontal

https://fractalcoding.blogspot.com/2019/10/image-processing-in-c.html
-> détails avec vidéo sur différentes transformations applicable à une image pgm (changement luminausité,flou...)

https://ugurkoltuk.wordpress.com/2010/03/04/an-extreme-simple-pgm-io-api/ 
-> un exemple très simple de chargement et d'écriture d'une image PGM, bien expliqué

https://github.com/th3gundy/pgm-image-processing/blob/master/image_processing.c 
-> du code pour ouvrir une image PGM et écrire en sortie une autre avec des niveaux de gris différents, histogramme
*/

#include "pgmImageProcessing.h"

// matrice de pixels, 1000 lignes et 1000 colonnes
int p[1000][1000];
int p2[1000][1000];
// largeur et hauteur initialisées dans la récupération de l'image
int maxWidth, maxHeight;

/*
int main() {
    // chargement d'une image :
    load_image_from_file("single_0.pgm",p);
    // invert_colours();
    // applyConvolutionProcessing('e');
    // rotate(180);
    sobelFiltering();
    save_image_to_file("resultat.pgm");
    return 0;
}
*/

/**
 *  Fonction pour charger une image PGM, initialise au passage les valeurs de maxwidth et maxheight
 * retourne 0 en cas de réussite
 * */
int load_image_from_file(char filename[], int matrix[1000][1000])
{
   // Variables
    FILE *f;
    char line[200];
    int x, y;
 
    // printf("Ouverture de l'image %s\n", filename);
    f = fopen(filename, "r");
    if(f == NULL) {
        return -1;
    }
 
    // printf("Lecture des informations dans l'entete\n");
    fscanf(f, "%[^\n]\n", line);
    // fscanf(f, "%[^\n]\n", line);
    fscanf(f, "%d %d\n", &maxWidth, &maxHeight);
    fscanf(f, "%[^\n]\n", line);
 
    // On met chaque pixel dans notre matrice p
    // printf("Lecture de chaque pixels de l'image %s\n", filename);
    y = 0;
    while(y < maxHeight)
    {
        x = 0;
        while(x < maxWidth)
        {
            // fscanf(f, "%d", &p[y][x]);
            matrix[y][x] = fgetc(f);
            x = x + 1;
        }
        y = y + 1;
    }
 
    // Close input file
    // printf("Fermeture du fichier %s\n", filename);
    fclose(f);
    return 0;
}
 
/**
 * Enregistrer notre matrice p en une image PGM
 * Retourne 0 en cas de réussite
 */ 
int save_image_to_file(char filename[], int matrix[1000][1000])
{
    // variables
    FILE *f;
    int x, y;
 
    printf("\nOuverture du fichier pour enregistrer la nouvelle image %s\n", filename);
    f = fopen(filename, "w");
    if(f == NULL) {
        return -1;
    }
 
    printf("Ecriture de l'entête %s\n", filename);
    fprintf(f, "P2\n");
    // met un commentaire dans le fichier, sachant qu'en temps normal un fichier pgm à 3 lignes d'entêtes 
    // si on en rajoute une cela perturbe la récupération des données du fichier
    // fprintf(f, "# Mon fichier PGM <3\n");
    fprintf(f, "%d %d\n", maxWidth, maxHeight);
    fprintf(f, "255\n");
 
    printf("Ecriture de chaque pixels de notre matrice %s\n", filename);
    y = 0;
    while(y < maxHeight)
    {
        x = 0;
        while(x < maxWidth)
        {
            fprintf(f, "%d ", matrix[y][x]);
            x = x + 1;
        }
        fprintf(f, "\n");
        y = y + 1;
    }
 
    printf("Fermeture du fichier en sortie %s\n", filename);
    fclose(f);
    return 0;
}

/**
 * Inversion très simple des couleurs, on donne simplement pour chaque pixels la valeur 255 - valeur originale
 * donc si il était noir 255-0 devient blanc et si il était blanc 255-255 =0 donc noir
 */
void invert_colours(int matrix[1000][1000])
{
    // variables
    int x, y;

    printf("Inversion des couleurs ! ");
    y = 0;
    while(y < maxHeight)
    {
        x = 1;
        while(x < maxWidth)
        {
            matrix[y][x] = 255 - matrix[y][x];
            x = x + 1;
        }
        y = y + 1;
    }
    printf("OK\n");
}

/**
 * Application d'un produit de convolution, pour plus d'explications : https://en.wikipedia.org/wiki/Kernel_(image_processing)
 * Les arguments divisor et substractor sont là pour ramener la valeur entre 0 et 255 tout en conservant l'effet attendu
 * Ainsi si on trouve que l'image est trop sombre on peut diminuer un peu le diviseur appliqué ou changer la soustraction
 */ 
int conMatrixMult(int theImageArray[1000][1000], int myMatrix[3][3], int i, int j, int divisor, int subtractor){
     return (theImageArray[i+1][j+1]*myMatrix[0][0] + theImageArray[i][j+1]*myMatrix[0][1]+ 
     theImageArray[i-1][j+1]*myMatrix[0][2]+theImageArray[i+1][j]*myMatrix[1][0]+theImageArray[i][j]*myMatrix[1][1]+
     theImageArray[i-1][j]*myMatrix[1][2]+theImageArray[i+1][j-1]*myMatrix[2][0]+theImageArray[i][j+1]*myMatrix[2][1]+
     theImageArray[i-1][j-1]*myMatrix[2][2])/divisor - subtractor;
}
//matrices à utiliser avec les produits de convolution
    int edgeDetect[3][3] = {
        {-1, -1, -1},
        {-1,  5, -1},
        {-1, -1, -1}
    };

    int sharpen[3][3] = {
        {0, -1,  0},
        {-1, 5, -1},
        {0, -1,  0}
    };

    int gaussian[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };

/**
 * Fonction qui permet de modifier l'image en appliquant divers effets comme flouter, détecter les angles...
 * Le principe est de manipuler un pixel selon les pixels qui l'entourent avec un produit de convolution 
 * entre notre matrice de pixels et une matrice définie selon l'effet attendu
 * Prend en paramètre un charactère selon l'effet a effectuer :
 * -> 'e' pour edge detection
 * -> 's' pour sharpen
 * -> 'g' pour flou gaussien
 */
void applyConvolutionProcessing(char effet, int matrix[1000][1000]) {
    // Parcours de la matrice p
    int x, y;

    printf("Application de l'effet : %c",effet);
    y = 1;
    while(y < maxHeight)
    {
        x = 1;
        while(x < maxWidth)
        {
            // les effets à appliquer sur les pixels selon notre choix
            if(effet == 'e') {
                matrix[y][x] = conMatrixMult(matrix,edgeDetect,y,x,20,-20);
            }
            else if (effet == 's') {
                matrix[y][x] = conMatrixMult(matrix,sharpen,y,x,8,-50);
            }
            else if (effet == 'g') {
                matrix[y][x] = conMatrixMult(matrix,gaussian,y,x,16,0);
            }
            else {
                printf("\nCe charactère n'est pas pris en compte par la fonction applyConvolutionProcessing !");
                return ;
            }
            matrix[y][x] = 255 - matrix[y][x];
            x = x + 1;
        }
        y = y + 1;
    }

} 

/**
 * Permet de tourner l'image à 90, 180 ou 270 degrès
 */ 
void rotate(int degree) {
    printf("\nRotation de %d degres",degree);
    // on change les valeurs de chaque pixels que l'on stocke dans une matrice p2
    for(int i =0; i<maxWidth;i++) {
        for (int j =0; j<maxHeight; j++) {
            if(degree == 90) {
                p2[i][j] = p[j][i];
            }
            else if (degree == 180) {
                p2[i][j] = p[maxWidth - i][maxHeight - j];
            }
            else if (degree == 270) {
                p2[i][j] = p[maxHeight - j][i];
            }
            else {
                printf("Cette valeur de degrés de rotation n'est pas pris en compte par la fonction rotate !");
                return;
            }
        }
    }
    // notre matrice p reprend les valeurs de la matrice p2
    for(int i =0; i<maxWidth;i++) {
        for (int j =0; j<maxHeight; j++) {
            p [i][j] = p2[i][j];
        }
    }
}

/**
 * Application du filtre sobel pour la détection des bords
 *  Plus d'infos : https://en.wikipedia.org/wiki/Sobel_operator 
 * Arguments : la matrice sur laquelle on veut effectuer l'opération et une matrice temporaire
 */
 void sobelFiltering(int matrix[1000][1000], int temp[1000][1000]){
     printf("\nDebut du filtre sobel");

    // approximation de la dérivée horizontale (voir wikipedia la formulation en français)
    int sobel_x[3][3] = { { -1,   0,  1},
                          { -2,   0,  2},
                          { -1,   0,  1}};
    // approximation de la dérivée verticale
    int sobel_y[3][3] = { {-1,  -2,  -1},
                          { 0,   0,   0},
                          { 1,   2,   1}};
    int valX=0,valY=0;

    // parcours de toute la matrice sur lequel on applique le filtre sobel sur chaque pixels et que l'on écris dans p2
    for (int i=1; i<maxWidth-1; i++){
        for (int j=1; j<maxHeight-1; j++){
            valX=0; valY=0;
            // avec les 8 points autour de notre point on calcule le gradient
            for (int x = -1; x <= 1; x++){
                 for (int y = -1; y <= 1; y++){
                    valX += matrix[i+x][j+y] * sobel_x[1+x][1+y];
                    valY += matrix[i+x][j+y] * sobel_y[1+x][1+y];
                    }
            }
            temp[i][j] = (int)( sqrt(valX*valX + valY*valY) );
            // on remet les valeurs entre 0 et 255
            if (temp[i][j] < 0)
                temp[i][j] = 0;
            else if (temp[i][j] > 255)
                temp[i][j] = 255;
        }
    }
    // on remet les valeurs de notre matrice temporaire dans notree matrice p
    for (int x=0; x<maxWidth; x++)
        for (int y=0; y<maxHeight; y++){
            matrix[x][y] = temp[x][y];
        }

    printf("\nFin de l'application du filtre Sobel !");
}

/**
 * Seuillage d'images : https://fr.wikipedia.org/wiki/Seuillage_d%27image
 * On prend une matrice de pixels en paramètre et on transforme tous les pixels inférieurs au seuil en noir et les autres en blanc
 */
void threshold(int matrix[1000][1000], int val) {
    for (int x=0; x<maxWidth; x++){
        for (int y=0; y<maxHeight; y++){
            if(matrix[x][y]<val) {
                matrix[x][y] =0;
            }
            else {
                matrix[x][y] = 255;
            }
        }
    }
}