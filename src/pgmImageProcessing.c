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

// matrice de pixels, 1000 lignes et 1000 colonnes
int p[1000][1000];
int w, h;
 
// Fonctions sur les fichiers d'images
void load_image_from_file(char[]);
void save_image_to_file(char[]);
 
// Fonctions de traitement de l'image
void invert_colours();

int main() {
    // chargement et inversion d'une image :
    load_image_from_file("single_0.pgm");
    // invert_colours();
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
 
    // Open input image file
    printf("Opening input file %s\n", filename);
    f = fopen(filename, "r");
 
    // Read 4 header lines.
    // These will just be ignored, but we need to read
    // them to get down to the table of numbers further
    // down in the file.
    printf("Reading file header info\n");
    fscanf(f, "%[^\n]\n", line);
    // fscanf(f, "%[^\n]\n", line);
    fscanf(f, "%d %d\n", &w, &h);
    fscanf(f, "%[^\n]\n", line);
 
    // Read pixel data into 2-D array
    printf("Reading pixel data from file %s\n", filename);
    y = 0;
    while(y < h)
    {
        x = 0;
        while(x < w)
        {
            fscanf(f, "%d", &p[y][x]);
            x = x + 1;
        }
        y = y + 1;
    }
 
    // Close input file
    printf("Closing input file %s\n", filename);
    fclose(f);
}
 
void save_image_to_file(char filename[])
{
    // variables
    FILE *f;
    int x, y;
 
    // open output file
    printf("Opening output file %s\n", filename);
    f = fopen(filename, "w");
 
    // Print header info into file
    printf("Printing file header to file %s\n", filename);
    fprintf(f, "P2\n");
    fprintf(f, "# My PGM file\n");
    fprintf(f, "%d %d\n", w, h);
    fprintf(f, "255\n");
 
    // Print pixel data into file
    printf("Printing pixel data to file %s\n", filename);
    y = 0;
    while(y < h)
    {
        x = 0;
        while(x < w)
        {
            fprintf(f, "%d ", p[y][x]);
            x = x + 1;
        }
        fprintf(f, "\n");
        y = y + 1;
    }
 
    // Close file
    printf("Closing output file %s\n", filename);
    fclose(f);
}
void invert_colours(int threshold)
{
    // variables
    int x, y;
 
    // Modify all pixel values one at a time
    printf("Inverting colours...");
    y = 0;
    while(y < h)
    {
        x = 1;
        while(x < w)
        {
            p[y][x] = 255 - p[y][x];
            x = x + 1;
        }
        y = y + 1;
    }
    printf("OK\n");
}