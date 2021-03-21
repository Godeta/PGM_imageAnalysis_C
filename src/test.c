#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** Notre structure définissant une image
 * Elle contient le nombre de lignes, colonnes, valeur maximale de gris et une matrice
 * */
typedef struct{
    char version[2];
    int width, height, grayLevel;
    int **pixel;
} IMAGE;

// allouer de la mémoire pour la matrice
int **memoryAllocate(int w, int h){
    int **tmp, i;

    tmp = (int**)malloc(w * sizeof(int*));
    for(i = 0; i < w; i++)
        tmp[i] = (int*)malloc(h * sizeof(int));

    return tmp;
}

// libérer la mémoire
void freeMemory(int row, int **matrix){
    int i;

    for(i=0; i<row; i++)
		free(matrix[i]);
	free(matrix);
}

//lecture du fichier
void readFile(char *filename, IMAGE *img){
    int i,j;
    FILE *file;

    printf("\n[+]Opening input file -> ");
    printf("%s\n",filename);

    if ((file = fopen(filename, "rb")) == NULL){
       printf("Errör..!");
       exit(0);
    }

    fgets(&img->version,3,file); //printf("%s\n",&img->version);
    fscanf(file,"%d %d",&img->width,&img->height); //printf("%d ",img->width); printf("%d\n",img->height);
    fscanf(file,"%d",&img->grayLevel); //printf("%d\n",img->grayLevel);

    img->pixel = memoryAllocate(img->width,img->height);

    for (i=0; i<img->width; i++)
        for (j=0; j<img->height; j++){
            img->pixel[i][j] = fgetc(file);
            //printf("%d ",img->pixel[i][j]);
        }
    printf("   Rows %d - Columns %d \n",img->width,img->height);
    fclose(file);
    printf("[*]End of File Reading.!\n");
}

void writeFile(char *filename, IMAGE *img){
    FILE *f;
    int i, j;

    printf("\n[+]Opening output file : %s\n", filename);

    if ((f = fopen(filename, "wb")) == NULL){
       printf("Errör..!");
       exit(0);
    }

    fprintf(f,"%s\n",img->version);
    fprintf(f,"%d %d\n",img->width,img->height);
    fprintf(f,"%d\n",img->grayLevel);

    for (i=0; i<img->width; i++)
        for (j=0; j<img->height; j++){
             fputc(img->pixel[i][j],f);
            //printf("%d ",img->pixel[i][j]);
        }
    fclose(f);
    printf("[*]End of File Writing.\n");
}
// Plus d'infos : https://en.wikipedia.org/wiki/Sobel_operator 
void sobelFiltering(IMAGE *img){

    int **newPixel;

    int sobel_x[3][3] = { { 1,   0,  -1},
                          { 2,   0,  -2},
                          { 1,   0,  -1}};
    int sobel_y[3][3] = { { 1,   2,   1},
                          { 0,   0,   0},
                          {-1,  -2,  -1}};
    int x,y,i,j;
    int valX=0,valY=0;

    newPixel = memoryAllocate(img->width,img->height);
    for (x=0; x<img->width; x++)
        for (y=0; y<img->height; y++){
            newPixel[x][y] = 0;
        }

        // first solution
    for (i=1; i<img->width-1; i++)
        for (j=1; j<img->height-1; j++){
            valX=0; valY=0;
            for (x = -1; x <= 1; x++)
                 for (y = -1; y <= 1; y++){
                    valX = valX + img->pixel[i+x][j+y] * sobel_x[1+x][1+y];
                    valY = valY + img->pixel[i+x][j+y] * sobel_y[1+x][1+y];
                    }
            newPixel[i][j] = (int)( sqrt(valX*valX + valY*valY) );
            if (newPixel[i][j] < 0)
                newPixel[i][j] = 0;
            else if (newPixel[i][j] > 255)
                newPixel[i][j] = 255;
        }

     // second solution
     /*
    for (i=1; i<img->width-1; i++)
        for (j=1; j<img->height-1; j++){
            valX = (img->pixel[i-1][j+1]+2*img->pixel[i][j+1]+img->pixel[i+1][j+1]) -
                   (img->pixel[i-1][j-1]+2*img->pixel[i][j-1]+img->pixel[i+1][j-1]);
            valY = (img->pixel[i+1][j-1]+2*img->pixel[i+1][j]+img->pixel[i+1][j+1])-
                   (img->pixel[i-1][j-1]+2*img->pixel[i-1][j]+img->pixel[i-1][j+1]);
            newPixel[i][j] = (int)( sqrt(valX*valX + valY*valY) );
            //newPixel[i][j] = abs(valX) + abs(valY);
           }
    */

    for (x=0; x<img->width; x++)
        for (y=0; y<img->height; y++){
            img->pixel[x][y] = newPixel[x][y];
        }
    //freeMemory(img->width,&newPixel);

    writeFile("filtreSobel.pgm",img);
    printf("\n[*]End of Sobel.!");
}

// répartition des niveaux de gris
void histogramEqu(IMAGE *img, int grayLevel){

    int histogram[256] = {0};
    float cumulative[256] = {0.0};
    int totalPixel = img->width * img->height;
    int i,j;

    for (i=0; i<img->width; i++)
        for (j=0; j<img->height; j++){
            histogram[img->pixel[i][j]]++;
        }
    //for (i=0; i<256; i++)
        //printf("%d ",histogram[i]);

    cumulative[0] = (float)histogram[0] / (float)totalPixel;

    for (i=0; i<255; i++){
        cumulative[i+1] = cumulative[i] + (float)histogram[i+1] / (float)totalPixel;
        //printf("%f ",cumulative[i+1]);
    }

    for (i=0; i<256; i++){
        histogram[i] = (int)roundf(cumulative[i+1]) * grayLevel;
        //printf("%d ",histogram[i]);
    }

    for (i=1; i<img->width; i++)
        for (j=1; j<img->height; j++)
            img->pixel[i][j] = histogram[img->pixel[i][j]];

    writeFile("histogram.pgm",img);
    printf("\n[*]End of Histogram Equalization.!\n");
}

int main()
{
    IMAGE image;
    int grayLevel;
    char *filename;

    printf("Enter the filename : ");
    scanf("%s",&filename);

    readFile(&filename,&image);
    sobelFiltering(&image);

    printf("\n\nEnter new gray level : ");
    scanf("%d",&grayLevel);

    histogramEqu(&image,grayLevel);
    scanf('%s',NULL);

    return 0;
}