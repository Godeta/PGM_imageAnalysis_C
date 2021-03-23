#include <stdlib.h>
#include <stdio.h>
#include <math.h>
// penser à compiler avec l'argument -lm quand on utilise math.h
 
// Fonctions sur les fichiers d'images
int load_image_from_file(char[], int matrix[1000][1000]);
int save_image_to_file(char[],int matrix[1000][1000]);
 
// Fonctions de traitement de l'image
void invert_colours(int matrix[1000][1000]);
int conMatrixMult(int theImageArray[1000][1000], int myMatrix[3][3], int i, int j, int divisor, int subtractor);
void applyConvolutionProcessing(char effet, int matrix[1000][1000]);
void rotate(int degree);
void sobelFiltering(int matrix[1000][1000], int temp[1000][1000]);
void threshold(int matrix[1000][1000], int val);
