#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

// Sobel 3x3
const int SOBEL_3X3_X[3][3] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};
const int SOBEL_3X3_Y[3][3] = {
    {-1, -2, -1},
    { 0,  0,  0},
    { 1,  2,  1}
};

// Sobel 5x5 (Valores estándar de gradiente extendido)
const int SOBEL_5X5_X[5][5] = {
    {-1, -2, 0,  2, 1},
    {-2, -3, 0,  3, 2},
    {-3, -5, 0,  5, 3},
    {-2, -3, 0,  3, 2},
    {-1, -2, 0,  2, 1}
};

const int SOBEL_5X5_Y[5][5] = {
    {-1, -2, -3, -2, -1},
    {-2, -3, -5, -3, -2},
    { 0,  0,  0,  0,  0},
    { 2,  3,  5,  3,  2},
    { 1,  2,  3,  2,  1}
};

int blurMatriz3x3(Pixel **input, Pixel **output, int width, int height){
    int w = width - 1;
    int h = height - 1;
    // for para bordes 3x3
    int r = 0, g = 0, b= 0;
    // Bordes horizontales
    for(int i = 1; i < h; i++){
        // superior 
        for(int f = 0; f <= 1; f++){
            for(int c = i - 1; c <= i + 1; c++){
                Pixel neighbours = input[f][c];
                r += neighbours.r;
                g += neighbours.g;
                b += neighbours.b;
            }
        }
        output[i][0].r = (unsigned char)(r/6);
        output[i][0].g = (unsigned char)(g/6);
        output[i][0].b = (unsigned char)(b/6);
        
        // inferior
        r = 0; g = 0; b = 0;
        for(int f = h - 1; f <= h; f++){
            for(int c = i - 1; c <= i + 1; c++){
                Pixel neighbours = input[f][c];
                r += neighbours.r;
                g += neighbours.g;
                b += neighbours.b;
            }
        }
        output[i][h].r = (unsigned char)(r/6);
        output[i][h].g = (unsigned char)(g/6);
        output[i][h].b = (unsigned char)(b/6); 
    }
    
    //bordes laterales
    for(int i = 1; i < w; i++){
        int r = 0, g = 0, b= 0;

        // izquierdo 
        for(int f = i - 1; f <= i + 1; f++){
            for(int c = 0; c <= 1; c++){
                Pixel neighbours = input[f][c];
                r += neighbours.r;
                g += neighbours.g;
                b += neighbours.b;
            }
        }
        output[i][0].r = (unsigned char)(r/6);
        output[i][0].g = (unsigned char)(g/6);
        output[i][0].b = (unsigned char)(b/6);
        
        // derecho
        r = 0; g = 0; b = 0;
        for(int f = i - 1; f <= i + 1; f++){
            for(int c = w - 1; c <= w ; c++){
                Pixel neighbours = input[f][c];
                r += neighbours.r;
                g += neighbours.g;
                b += neighbours.b;
            }
        }
        output[i][w].r = (unsigned char)(r/6);
        output[i][w].g = (unsigned char)(g/6);
        output[i][w].b = (unsigned char)(b/6); 
    }

    // for para el centro
    for(int i = 1; i < w; i ++){
        for(int j = 1; j < h; j++){

            int r = 0, g = 0, b= 0;
            for(int f = i - 1; f <= i + 1; f++){
                for(int c = j - 1; c <= j + 1; c++){
                    Pixel neighbours = input[f][c];
                    r += neighbours.r;
                    g += neighbours.g;
                    b += neighbours.b;
                }
            }
            output[i][j].r = (unsigned char)(r/9);
            output[i][j].g = (unsigned char)(g/9);
            output[i][j].b = (unsigned char)(b/9); 
        }
    } 

    

    // esq sup izq to-do
    for(int i = 0; i < 1; i++){
        for(int j = 0; j < 0; j++){
        output[0][0].r = (unsigned char)(input[0][0].r + input[0][1].r + input[1][0].r + input[1][1].r) /4;
        output[0][0].g = (unsigned char)(input[0][0].g + input[0][1].g + input[1][0].g + input[1][1].g) /4;
        output[0][0].b = (unsigned char)(input[0][0].b + input[0][1].b + input[1][0].b + input[1][1].b) /4;
        }
    }
    // esq sup der 
    output[0][w].r = (unsigned char)(input[0][0].r + input[0][1].r + input[1][0].r + input[1][1].r) /4;
    output[0][w].g = (unsigned char)(input[0][0].g + input[0][1].g + input[1][0].g + input[1][1].g) /4;
    output[0][w].b = (unsigned char)(input[0][0].b + input[0][1].b + input[1][0].b + input[1][1].b) /4;

    output[0][0].r = (unsigned char)(input[0][0].r + input[0][1].r + input[1][0].r + input[1][1].r) /4;
    output[0][0].g = (unsigned char)(input[0][0].g + input[0][1].g + input[1][0].g + input[1][1].g) /4;
    output[0][0].b = (unsigned char)(input[0][0].b + input[0][1].b + input[1][0].b + input[1][1].b) /4;

    output[0][0].r = (unsigned char)(input[0][0].r + input[0][1].r + input[1][0].r + input[1][1].r) /4;
    output[0][0].g = (unsigned char)(input[0][0].g + input[0][1].g + input[1][0].g + input[1][1].g) /4;
    output[0][0].b = (unsigned char)(input[0][0].b + input[0][1].b + input[1][0].b + input[1][1].b) /4;
}

void highlightedMatriz(Pixel **input, Pixel **output, int width, int height){
    
    int w = width - 1;
    int h = height - 1;
    // for para bordes 3x3
    int r = 0, g = 0, b= 0;

    float gx = 0;
    float gy = 0;
    // Bordes horizontales
    for(int i = 1; i < h; i++){
        // superior 
        for(int f = 0; f <= 1; f++){
            for(int c = i - 1; c <= i + 1; c++){
               unsigned char valorGris = (unsigned char)(0.299f * input[f][c].r + 
                                          0.587f * input[f][c].g + 
                                          0.114f * input[f][c].b);

                

                gx += valorGris * SOBEL_3X3_X[f][c];
                gy += valorGris * 
            }
        }
        
        // inferior
        r = 0; g = 0; b = 0;
        for(int f = h - 1; f <= h; f++){
            for(int c = i - 1; c <= i + 1; c++){
                Pixel neighbours = input[f][c];
                r += neighbours.r;
                g += neighbours.g;
                b += neighbours.b;
            }
        }
        output[i][h].r = (unsigned char)(r/6);
        output[i][h].g = (unsigned char)(g/6);
        output[i][h].b = (unsigned char)(b/6); 
    }
    
    //bordes laterales
    for(int i = 1; i < w; i++){
        int r = 0, g = 0, b= 0;

        // izquierdo 
        for(int f = i - 1; f <= i + 1; f++){
            for(int c = 0; c <= 1; c++){
                Pixel neighbours = input[f][c];
                r += neighbours.r;
                g += neighbours.g;
                b += neighbours.b;
            }
        }
        output[i][0].r = (unsigned char)(r/6);
        output[i][0].g = (unsigned char)(g/6);
        output[i][0].b = (unsigned char)(b/6);
        
        // derecho
        r = 0; g = 0; b = 0;
        for(int f = i - 1; f <= i + 1; f++){
            for(int c = w - 1; c <= w ; c++){
                Pixel neighbours = input[f][c];
                r += neighbours.r;
                g += neighbours.g;
                b += neighbours.b;
            }
        }
        output[i][w].r = (unsigned char)(r/6);
        output[i][w].g = (unsigned char)(g/6);
        output[i][w].b = (unsigned char)(b/6); 
    }

    // for para el centro
    for(int i = 1; i < w; i ++){
        for(int j = 1; j < h; j++){

            int r = 0, g = 0, b= 0;
            for(int f = i - 1; f <= i + 1; f++){
                for(int c = j - 1; c <= j + 1; c++){
                    Pixel neighbours = input[f][c];
                    r += neighbours.r;
                    g += neighbours.g;
                    b += neighbours.b;
                }
            }
            output[i][j].r = (unsigned char)(r/9);
            output[i][j].g = (unsigned char)(g/9);
            output[i][j].b = (unsigned char)(b/9); 
        }
    } 

}


void main(int argc, char **argv){

    char *path = argv[1];
    int width, height, channels;

    unsigned char *data = stbi_load(path, &width, &height, &channels, 3);

    if(data == NULL){
        printf("Error al cargar la imagen. \n");
    }
    else{
        // cast de puntero data a pixel
        Pixel* pixelCast = (Pixel*)data;
        // asignacion de memoria para height 
        Pixel **matriz = (Pixel **)malloc(height * sizeof(Pixel *));

        if (matriz == NULL) {
            stbi_image_free(data);
            return;
        }

        for (int i = 0; i < height; i++) {
            matriz[i] = &pixelCast[i * width];
        }        
        
        free(matriz);
        stbi_image_free(data);
    }
}