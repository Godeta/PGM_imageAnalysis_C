/** Fichier principal du programme
 * On regarde le diamètre intérieur 32 pixels et extérieur 64 pixels
 * idée tester toutes les lignes du cercle et on garde le maximum
 * */
#include "mainFile.h"

// matrice de pixels, 1000 lignes et 1000 colonnes
int p[1000][1000];
int p2[1000][1000];
// largeur et hauteur initialisées dans la récupération de l'image
int maxWidth, maxHeight;

int main() {
    // testCalcTime();
    load_image_from_file("../dataset/conforme1.pgm");
    printf("Taille : %d %d\n", maxWidth, maxHeight);
    findCircle();
    // save_image_to_file("resultat.pgm");
    return 0;
}

/**
 * Un exemple de calcul de temps en C avec le calcul du temps réel passé et 
 * du temps que l'ordinateur a pris pour effectuer la fonction
 */ 
void testCalcTime() {
    // Calculate the time taken by fun() 
    clock_t t; 
    time_t begin = time(NULL);
    t = clock(); 
    printf("Debut calcul du temps, appuie sur entrer pour arreter \n"); 
    while(1) 
    { 
        if (getchar()) 
            break; 
    } 
    printf("fin \n");
    t = clock() - t; 
    time_t end = time(NULL);
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
  
    printf("Il y a %d secondes qui se sont passees et le système a pris %f secondes a executer l'operation \n", (end - begin),time_taken); 
}

/**
 * Trouve les anneaux puis execute les tests obligatoires
 */ 
void findCircle() {
    for (int i=0; i<maxHeight; i++) {
        for(int j=0; j<maxWidth; j++) {
            //si le pixel est noir
            if(p[i][j]<60) {
                mandatoryTests(i,j);
                return ;
            }
        }
    }
    printf("Pas d'anneau trouvé sur l'image !\n");
}

/**
 * paramètres i et j coordonnées du premier pixel noir 
 * on part du premier pixel noir et à partir de celui ci :
 * on vérifie que 31 et 63 pixels plus bas on à un pixel noir 
 * entre les pixels 32 et 49 ce n'est pas noir 
 * entre 49 et 64 c'est noir
 */ 
bool mandatoryTests(int i, int j) {
    
    // for (int a =0; a<10; a++) {
    //     printf("pixel : %d %d val : %d\n",a+320,a+370,p[370+a][320+a]);
    // }
    printf("Premier pixel noir : %d %d\n", i, j);
    //entre i+0, i+16 et i+49, i+63 pixels noirs
    for(int x =1; x<17; x++) {
        if(p[i+x][j] > 65) {
            printf("Anneau non conforme, pixel non noir entre 0 et 17 ! Pixel : %d %d Valeur :%d\n",i+x,j,p[i+x][j]);
            return false;
        }
        else if (p[i+x+48][j] > 65) {
            printf("Anneau non conforme, pixel non noir entre 49 et 64 ! Pixel : %d %d Valeur :%d\n",i+x+48,j,p[i+x+48][j]);
            return false;  
        }
        else if (p[i+x+64][j] < 65) {
            printf("Anneau non conforme (trop large), pixel noir après 64 ! Pixel : %d %d Valeur :%d\n",i+x+48,j,p[i+x+48][j]);
            return false; 
        }
    }

    printf("\nL'anneau est conforme !\n");
    return true;
}