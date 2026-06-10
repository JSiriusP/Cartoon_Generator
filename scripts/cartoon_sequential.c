#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <sys/time.h>
#include "stb_image.h"
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#define SATURATE(v) ((v) > 255 ? 255 : ((v) < 0 ? 0 : (v)))
#define POSTURIZERANGES 12

typedef struct{
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
    {0, 0, 0},
    {1, 2, 1}
};

// Sobel 5x5 (Valores estándar de gradiente extendido)
const int SOBEL_5X5_X[5][5] = {
    {-1, -2, 0, 2, 1},
    {-2, -3, 0, 3, 2},
    {-3, -5, 0, 5, 3},
    {-2, -3, 0, 3, 2},
    {-1, -2, 0, 2, 1}
};

const int SOBEL_5X5_Y[5][5] = {
    {-1, -2, -3, -2, -1},
    {-2, -3, -5, -3, -2},
    {0, 0, 0, 0, 0},
    {2, 3, 5, 3, 2},
    {1, 2, 3, 2, 1}
};

Pixel **padding(Pixel **input, int height, int width, int radio){

    int newHeight = height + (2 * radio);
    int newWidth = width + (2 * radio);

    Pixel **output = (Pixel **)malloc(newHeight * sizeof(Pixel *));
    Pixel *pool = (Pixel *)malloc(newHeight * newWidth * sizeof(Pixel));

    for (int i = 0; i < newHeight; i++)
    {
        output[i] = &pool[i * newWidth];
    }

    memset(pool, 0, newHeight * newWidth * sizeof(Pixel));

    for (int f = 0; f < height; f++)
    {
        int row = f + radio;
        memcpy(&output[row][radio], input[f], width * sizeof(Pixel));
    }
   return output;
}

Pixel **initAuxMatriz(int height, int width){
    Pixel **aux = (Pixel **)malloc(height * sizeof(Pixel *));
    for (int i = 0; i < height; i++)
    {
        aux[i] = (Pixel *)malloc(width * sizeof(Pixel));
    }
    return aux;
}

Pixel **initMainMatriz(Pixel *pixelCast, int height, int width) {
    Pixel **matriz = (Pixel **)malloc(height * sizeof(Pixel *));
    
    if (matriz == NULL) {
        return NULL;
    }

    for (int i = 0; i < height; i++) {
        matriz[i] = &pixelCast[i * width];
    }

    return matriz;
}

    int umbralize(float magnitud)
{
    if (magnitud > 255 / 2)
    {
        return 255;
    }
    else
    {
        return 0;
    }
}

Pixel **blurMatriz(Pixel **input, int width, int height, int radio){
    int newHeight = height + (2 * radio);
    int newWidth = width + (2 * radio);
    Pixel **output = initAuxMatriz(newHeight, newWidth);
    int r = 0, g = 0, b = 0;
    int cantPixel = (2 * radio + 1) * (2 * radio + 1);

    for (int i = 0; i < newHeight; i++) {
        for (int j = 0; j < newWidth; j++) {
            output[i][j].r = 0; output[i][j].g = 0; output[i][j].b = 0;
        }
    }

    for (int i = radio; i < (height + radio); i++)
    {
        for (int j = radio; j < (width + radio); j++)
        {
            r = 0, g = 0, b = 0;
            for (int f = i - radio; f <= i + radio; f++)
            {
                for (int c = j - radio; c <= j + radio; c++)
                {
                    Pixel neighbours = input[f][c];
                    r += neighbours.r;
                    g += neighbours.g;
                    b += neighbours.b;
                }
            }
            output[i][j].r = (unsigned char)(r / cantPixel);
            output[i][j].g = (unsigned char)(g / cantPixel);
            output[i][j].b = (unsigned char)(b / cantPixel);
        }
    }
    return output;
}

/**
 * Detects and highlights image edges using the Sobel operator.
 *
 * The image is first converted to grayscale for gradient computation.
 * Horizontal and vertical gradients are calculated using either a 3x3
 * or 5x5 Sobel kernel depending on the specified radius. The resulting
 * gradient magnitude is then thresholded to produce an edge-highlighted
 * output image.
 *
 * @param input   Image pixel matrix (modified in place).
 * @param width   Width of the image in pixels.
 * @param height  Height of the image in pixels.
 * @param radio   Radius of the Sobel kernel (1 for 3x3, 2 for 5x5).
 *
 * @return A newly allocated image containing the detected edges.
 */
Pixel** highlightedMatriz(Pixel **input, int width, int height, int radio){
    int newHeight = height + (2 * radio);
    int newWidth = width + (2 * radio);
    Pixel **output = initAuxMatriz(newHeight, newWidth);
    int r = 0, g = 0, b = 0;
    int cantPixel = (2 * radio + 1) * (2 * radio + 1);
    float gx, gy;
    float magnitude;
    int umbralizeValue;

    for (int i = 0; i < newHeight; i++) {
        for (int j = 0; j < newWidth; j++) {
            output[i][j].r = 0; output[i][j].g = 0; output[i][j].b = 0;
        }
    }

    for (int i = radio; i < (height + radio); i++)
    {
        for (int j = radio; j < (width + radio); j++)
        {
            gx = 0;
            gy = 0;
            int r = 0, g = 0, b = 0;
            for (int f = -radio; f <= radio; f++)
            {
                for (int c = -radio; c <= radio; c++)
                {
                    unsigned char valorGris = (unsigned char)(0.299f * input[i + f][j + c].r +
                                                              0.587f * input[i + f][j + c].g +
                                                              0.114f * input[i + f][j + c].b);

                    if (radio == 1)
                    {
                        gx += valorGris * SOBEL_3X3_X[f + radio][c + radio];
                        gy += valorGris * SOBEL_3X3_Y[f + radio][c + radio];
                    }
                    else
                    {
                        gx += valorGris * SOBEL_5X5_X[f + radio][c + radio];
                        gy += valorGris * SOBEL_5X5_Y[f + radio][c + radio];
                    }
                }
            }
            // criterio de magnitud (aproximado)
            umbralizeValue = umbralize(abs(gx) + abs(gy));
            output[i][j].r = (unsigned char)umbralizeValue;
            output[i][j].g = (unsigned char)umbralizeValue;
            output[i][j].b = (unsigned char)umbralizeValue;
        }
    }
    return output;
}

/** 
* Applies a posterization effect to an image by reducing the number of
* available color intensity levels.
* For grayscale images (channels = 1), each pixel is converted to a
* luminance value and then quantized into a limited set of ranges.
* For RGB images (channels = 3), each color channel is quantized
* independently.
* @param input    Image pixel matrix (modified in place).
* @param width    Image width in pixels.
* @param height   Image height in pixels.
* @param channels Number of channels (1 = grayscale, 3 = RGB). 
*/
void posterize(Pixel **input, int width, int height, int channels){
    int step = 256 / POSTURIZERANGES; // tamaño de cada intervalito

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (channels == 1)
            {
                // caso escala de grises - convierte a gris y reduce
                int valor = (int) (0.299f * input[i][j].r +
                                                      0.587f * input[i][j].g +
                                                      0.114f * input[i][j].b);

                int rango = valor / step;            // a que intervalito pertenece -- indice
                int valorPosterizado = rango * step; // valor representativo

                input[i][j].r = (unsigned char)valorPosterizado;
                input[i][j].g = (unsigned char)valorPosterizado;
                input[i][j].b = (unsigned char)valorPosterizado;
            }
            else if (channels == 3)
            {
                int rposter = (input[i][j].r / step) * step; // se reduce el canal por separado - igual a valor / step
                int gposter = (input[i][j].g / step) * step;
                int bposter = (input[i][j].b / step) * step;

                input[i][j].r = (unsigned char) rposter;
                input[i][j].g = (unsigned char) gposter;
                input[i][j].b = (unsigned char) bposter;
                
            }
            else 
            {
                int rposter = (input[i][j].r / step) * step;
                int gposter = (input[i][j].g / step) * step;
                int bposter = (input[i][j].b / step) * step;

                input[i][j].r = (unsigned char) rposter;
                input[i][j].g = (unsigned char) gposter;
                input[i][j].b = (unsigned char) bposter;
            }
        }
    }
}

void sum(Pixel **originalMatriz, Pixel **paddingMatriz, int height, int width, int radio){
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalMatriz[i][j].r = (unsigned char)SATURATE(originalMatriz[i][j].r + paddingMatriz[i + radio][j + radio].r);
            originalMatriz[i][j].g = (unsigned char)SATURATE(originalMatriz[i][j].g + paddingMatriz[i + radio][j + radio].g);
            originalMatriz[i][j].b = (unsigned char)SATURATE(originalMatriz[i][j].b + paddingMatriz[i + radio][j + radio].b);
        }
    }
}

void main(int argc, char **argv){
    if (argc < 4) {
        printf("Uso: %s <imagen> <radio> <nombre_salida>\n", argv[0]);
        exit(1);
    }
    char *path = argv[1];
    int radio = atoi(argv[2]);
    char *out_name = argv[3];
    int width, height, channels;

    printf("0\n");
    unsigned char *data = stbi_load(path, &width, &height, &channels, 3);

    if (data == NULL)
    {
        printf("Error al cargar la imagen. \n");
    }
    else
    {
        // cast de puntero data a pixel
        Pixel *pixelCast = (Pixel *)data;
        
        struct timeval start, end;
        gettimeofday(&start, NULL);

        Pixel **matriz = initMainMatriz(pixelCast, height, width);

        Pixel **paddingMatriz = padding(matriz, height, width, radio);

        Pixel **blurOutput = blurMatriz(paddingMatriz, width, height, radio);
        
        Pixel **highlightOutput = highlightedMatriz(blurOutput, width, height, radio);

        posterize(matriz, width, height, channels);
        
        sum(matriz, highlightOutput, height, width, radio);

        int bytePerFile = width * 3;
        
        char out_path[256];
        snprintf(out_path, sizeof(out_path), "files/%s%s", out_name, strstr(out_name, ".png") ? "" : ".png");
        
        int result = stbi_write_png(out_path, width, height, 3, matriz[0], bytePerFile);

        gettimeofday(&end, NULL);
        double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

        if (result == 0)
        {
            printf("Error al guardar la imagen final.\n");
        }
        else
        {
            printf("¡Imagen de tipo Cartoon generada con éxito en %f segundos!\n", time_taken);
        }

        free(matriz);
        free(paddingMatriz[0]);
        free(paddingMatriz);
        
        for (int i = 0; i < height + 2 * radio; i++) {
            free(blurOutput[i]);
            free(highlightOutput[i]);
        }
        free(blurOutput);
        free(highlightOutput);

        stbi_image_free(data);
    }
}
