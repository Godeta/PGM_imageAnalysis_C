#include "mainFile.h"

/**
 * Un exemple de calcul de temps en C avec le calcul du temps réel passé et 
 * du temps que l'ordinateur a pris pour effectuer la fonction
 */ 
void testCalcTime() {
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
    double time_taken = ((double)t)/CLOCKS_PER_SEC; 
  
    printf("Il y a %d secondes qui se sont passees et le système a pris %f secondes a executer l'operation \n", (end - begin),time_taken); 
}

/**
 * Trouve les anneaux puis execute les tests obligatoires
 * Retourne -1 si aucun anneau trouvé, 0 si un anneau est trouvé
 */ 
int findCircle() {
    int nbAnneauxConf =0;
    for (int i=0; i<maxHeight; i++) {
        for(int j=0; j<maxWidth; j++) {
            //si le pixel est noir
            if(p[i][j]==0) {
                bool correct = mandatoryTests(i,j);
                cutCircle(i,j-32);
                if(correct == true) {
                int diff = comparerImages(p2,comp);
                if(diff <10) {
                    // printf("L'anneau est conforme selon la comparaison d'images !");
                    nbAnneauxConf+=1;
                }
                else {
                    // printf("L'anneau n'est pas conforme selon la comparaison d'images !");
                }
                // printf("\nComparaison %d\n",diff);
                }
            }
        }
    }
    printf(" Nombre d'anneaux conformes : %d ,",nbAnneauxConf );
    if(nbAnneauxConf>0) {
        return 0;
    }
    // printf(" Pas d'anneau conforme trouvé sur l'image,");
    return -1;
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
    // printf("Premier pixel noir : %d %d\n", i, j);
    //entre i+0, i+16 et i+49, i+63 pixels noirs
    for(int x =1; x<17; x++) {
        if(p[i+x][j] ==255) {
            // printf("Anneau non conforme (d >32), pixel non noir entre 0 et 17 ! Pixel : %d %d Valeur :%d\n",i+x,j,p[i+x][j]);
            printf("Anneau non conforme (d >32) ");
            return false;
        }
        else if (p[i+x+48][j] ==255) {
            // printf("Anneau non conforme (d <32), pixel non noir entre 49 et 64 ! Pixel : %d %d Valeur :%d\n",i+x+48,j,p[i+x+48][j]);
            printf("Anneau non conforme (d <32) ");
            return false;  
        }
        else if (p[i+x+64][j] ==0) {
            // printf("Anneau non conforme (trop large), pixel noir après 64 ! Pixel : %d %d Valeur :%d\n",i+x+48,j,p[i+x+48][j]);
            printf("Anneau non conforme (trop large) ");
            return false; 
        }
    }

    // printf("L'anneau semble conforme !\n");
    return true;
}

/**
 * Pour comparer la proximité entre deux images
 * Retourne la somme des différences entre chaque pixels
 */
int comparerImages(int img [1000][1000], int img2 [1000][1000]) {
    int diff = 0;
    for (int i =0; i<65; i++) {
        for (int j=0; j<65; j++) {
            int val = abs(img[i][j] - img2[i][j]);
            if(val!=0){
                diff+= 1;
            }
        }
    }
    return diff;
}

/**
 * On coupe un carré de 65*65 pixels de l'image pour le mettre dans p2 
 * et comparer ensuite l'image de l'anneau avec une image modèle d'un anneau conforme
 */ 
void cutCircle(int i, int j) {
    int centreX = i +32, centreY = j+32, diametre=64; 
    //on prend un carré de 65*65
                for(int x=0; x<65;x++){
                    for(int y=0; y<65;y++){
                        int disX = centreX-(i+x);
                        int disY = centreY-(j+y);
                        //si on est dans le cercle de centre : centreX,centreY et de diametre 64
                        if(sqrt(disX*disX + disY*disY)<diametre/2+1) {
                            p2[x][y] = p[i+x][j+y];
                            // on met le pixel blanc car on a traité l'anneau et ainsi on ne repassera pas dessus
                            p[i+x][j+y] = 255;
                        }
                        else {
                            p2[x][y] = 255;
                            // p[i+x][j+y] = 100; //mettre en gris, pratique pour visualiser ce qui se passe et debugguer
                        }
                    }
                }
}