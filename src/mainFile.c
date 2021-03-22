/** Fichier principal du programme
 * On regarde le diamètre intérieur 32 pixels et extérieur 64 pixels
 * idée tester toutes les lignes du cercle et on garde le maximum
 * */
#include "mainFile.h"

// matrice de pixels, 1000 lignes et 1000 colonnes
int p[1000][1000];
int p2[1000][1000];
int comp[1000][1000];
// largeur et hauteur initialisées dans la récupération de l'image
int maxWidth, maxHeight;

/**
 * Lorsque l'on exectue le programme il faut fournir le chemin de l'image en argument
 */ 
int main(int argc, char **argv) {
    // testCalcTime();
    
    // nom du fichier à ouvrir
    char * filename = "../dataset/conforme.pgm";
    //si on n'a pas fourni d'argument en appelant le programme
    if(argc<2) {
        printf("Pas de chemin pour le fichier fourni en argument, utilisation de '../dataset/conforme1.pgm' \n");
    }
    else {
        printf("Image : %s",filename);
        filename = argv[1];
    }
    // on charge l'image de référence
    load_image_from_file("../dataset/ref_anneau.pgm", comp);
    // sobelFiltering(comp,p2);
    // save_image_to_file("ref.pgm",comp);

    load_image_from_file(filename, p);
    printf(" de taille : %d %d\n", maxWidth, maxHeight);
    findCircle();
    // sobelFiltering(p,p2);
    // save_image_to_file("resultat.pgm",p2);
    return 0;
}
