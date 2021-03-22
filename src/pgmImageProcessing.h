#include <stdlib.h>
#include <stdio.h>
#include <math.h>
// penser à compiler avec l'argument -lm quand on utilise math.h
 
// Fonctions sur les fichiers d'images
void load_image_from_file(char[]);
void save_image_to_file(char[]);
 
// Fonctions de traitement de l'image
void invert_colours();
int conMatrixMult(int theImageArray[1000][1000], int myMatrix[3][3], int i, int j, int divisor, int subtractor);
void applyConvolutionProcessing(char effet);
void rotate(int degree);
void sobelFiltering();
