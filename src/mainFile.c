/** Fichier principal du programme
 * On regarde le diamètre intérieur 32 pixels et extérieur 64 pixels
 * idée tester toutes les lignes du cercle et on garde le maximum
 * */
#include "mainFile.h"

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
        filename = argv[1];
        printf("Image : %s",filename);
    }
    // on charge l'image de référence
    load_image_from_file("dataset/ref_anneau.pgm", comp);
    // sobelFiltering(comp,p2);
    // save_image_to_file("ref.pgm",comp);

    load_image_from_file(filename, p);
    printf(" de taille : %d %d\n", maxWidth, maxHeight);
    // calcul du temps
    clock_t t; 
    time_t begin = time(NULL);
    t = clock(); 
    findCircle();
    t = clock() - t; 
    time_t end = time(NULL);
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf(" Fin de l'analyse de l'image, %d secondes passée et %f secondes a executer l'operation \n\n",(end - begin),time_taken);
    // sobelFiltering(p,p2);
    // save_image_to_file("resultat.pgm",p2);
    return 0;
}
