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

#include "mainFile.h"

// matrice de pixels, 1000 lignes et 1000 colonnes
int p[1000][1000];
int p2[1000][1000];
// largeur et hauteur initialisées dans la récupération de l'image
int maxWidth, maxHeight;
 
// Fonctions sur les fichiers d'images
void load_image_from_file(char[]);
void save_image_to_file(char[]);
 
// Fonctions de traitement de l'image
void invert_colours();
int conMatrixMult(int theImageArray[1000][1000], int myMatrix[3][3], int i, int j, int divisor, int subtractor);
void applyConvolutionProcessing(char effet);
void rotate(int degree);

int main() {
    // chargement et inversion d'une image :
    load_image_from_file("single_0.pgm");
    // invert_colours();
    // applyConvolutionProcessing('e');
    // rotate(180);
    save_image_to_file("resultat.pgm");
    return 0;
}

/** Fonction pour charger une image PGM
 * 
 * */
void load_image_from_file(char filename[])
{
   // Variables
    FILE *f;
    char line[200];
    int x, y;
 
    printf("Ouverture de l'image %s\n", filename);
    f = fopen(filename, "r");
 
    printf("Lecture des informations dans l'entete\n");
    fscanf(f, "%[^\n]\n", line);
    // fscanf(f, "%[^\n]\n", line);
    fscanf(f, "%d %d\n", &maxWidth, &maxHeight);
    fscanf(f, "%[^\n]\n", line);
 
    // On met chaque pixel dans notre matrice p
    printf("Lecture de chaque pixels de l'image %s\n", filename);
    y = 0;
    while(y < maxHeight)
    {
        x = 0;
        while(x < maxWidth)
        {
            // fscanf(f, "%d", &p[y][x]);
            p[y][x] = fgetc(f);
            x = x + 1;
        }
        y = y + 1;
    }
 
    // Close input file
    printf("Fermeture du fichier %s\n", filename);
    fclose(f);
}
 
void save_image_to_file(char filename[])
{
    // variables
    FILE *f;
    int x, y;
 
    printf("Ouverture du fichier pour enregistrer la nouvelle image %s\n", filename);
    f = fopen(filename, "w");
 
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
            fprintf(f, "%d ", p[y][x]);
            x = x + 1;
        }
        fprintf(f, "\n");
        y = y + 1;
    }
 
    printf("Fermeture du fichier en sortie %s\n", filename);
    fclose(f);
}

/**
 * Inversion très simple des couleurs, on donne simplement pour chaque pixels la valeur 255 - valeur originale
 * donc si il était noir 255-0 devient blanc et si il était blanc 255-255 =0 donc noir
 */
void invert_colours()
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
            p[y][x] = 255 - p[y][x];
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
void applyConvolutionProcessing(char effet) {
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
                p[y][x] = conMatrixMult(p,edgeDetect,y,x,15,0);
            }
            else if (effet == 's') {
                p[y][x] = conMatrixMult(p,sharpen,y,x,8,-50);
            }
            else if (effet == 'g') {
                p[y][x] = conMatrixMult(p,gaussian,y,x,16,0);
            }
            else {
                printf("\nCe charactère n'est pas pris en compte par la fonction applyConvolutionProcessing !");
                return ;
            }
            p[y][x] = 255 - p[y][x];
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