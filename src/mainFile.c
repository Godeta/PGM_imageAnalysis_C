/** Fichier principal du programme
 * On regarde le diamètre intérieur 32 pixels et extérieur 64 pixels
 * idée tester toutes les lignes du cercle et on garde le maximum
 * */
#include "mainFile.h"

int main() {
    testCalcTime();
    return 0;
}

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