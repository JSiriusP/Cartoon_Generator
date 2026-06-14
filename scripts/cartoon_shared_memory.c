#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#define STB_IMAGE_IMPLEMENTATION
#include "includes/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "includes/stb_image_write.h"
#include <omp.h>

#define SATURATE(v) ((v) > 255 ? 255 : ((v) < 0 ? 0 : (v)))

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

Pixel **initAuxMatriz(int height, int width) {
    Pixel **aux = (Pixel **)malloc(height * sizeof(Pixel *));
    if (aux == NULL) return NULL;

    Pixel *pool = (Pixel *)malloc(height * width * sizeof(Pixel));
    if (pool == NULL) {
        free(aux);
        return NULL;
    }

    for (int i = 0; i < height; i++) {
        aux[i] = &pool[i * width];
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

Pixel **blurMatriz(Pixel **input, int width, int height, int radio)
{
    int newHeight = height + (2 * radio);
    int newWidth = width + (2 * radio);
    Pixel **output = initAuxMatriz(newHeight, newWidth);
    int cantPixel = (2 * radio + 1) * (2 * radio + 1);

    #pragma omp parallel for schedule (static)
    for (int i = 0; i < newHeight; i++) {
        for (int j = 0; j < newWidth; j++) {
            output[i][j].r = 0; output[i][j].g = 0; output[i][j].b = 0;
        }    
    }
    //barrier implicito

    #pragma omp parallel for collapse(2) schedule(guided)
    for (int i = radio; i < (height + radio); i++)
    {
        for (int j = radio; j < (width + radio); j++)
        {
            int r = 0, g = 0, b = 0;
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
Pixel** highlightedMatriz(Pixel **input, int width, int height, int radio)
{
    int newHeight = height + (2 * radio);
    int newWidth = width + (2 * radio);
    Pixel **output = initAuxMatriz(newHeight, newWidth);

    #pragma omp parallel for schedule (static)
    for (int i = 0; i < newHeight; i++) {
        for (int j = 0; j < newWidth; j++) {
            output[i][j].r = 0; output[i][j].g = 0; output[i][j].b = 0;
        }
    }

    #pragma omp parallel for collapse(2) schedule(guided)
    for (int i = radio; i < (height + radio); i++)
    {
        for (int j = radio; j < (width + radio); j++)
        {
            float gx = 0;
            float gy = 0;
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
            int umbralizeValue = umbralize(abs(gx) + abs(gy));
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
void posterize(Pixel **input, int width, int height, int channels, int posterizeRanges)
{
    int step = 256 / posterizeRanges; // tamaño de cada intervalito

    #pragma omp parallel for schedule(static)
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

void sum(Pixel **originalMatriz, Pixel **paddingMatriz, int height, int width, int radio)
{
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalMatriz[i][j].r = (unsigned char)SATURATE(originalMatriz[i][j].r - paddingMatriz[i + radio][j + radio].r);
            originalMatriz[i][j].g = (unsigned char)SATURATE(originalMatriz[i][j].g - paddingMatriz[i + radio][j + radio].g);
            originalMatriz[i][j].b = (unsigned char)SATURATE(originalMatriz[i][j].b - paddingMatriz[i + radio][j + radio].b);
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 5) {
        printf("Uso: %s <imagen> <radio> <posterizeRanges> <nombre_salida> [num_hilos]\n", argv[0]);
        exit(1);
    }
    int nthreads;
    char *path = argv[1];
    int radio = atoi(argv[2]);
    if (radio != 1 && radio != 2) {
        printf("Radio debe ser 1 o 2.\n");
        exit(1);
    }
    int posterizeArg = atoi(argv[3]);
    if (posterizeArg != 1 && posterizeArg != 2) {
        printf("Rango del posterizado debe ser 1 o 2.\n");
        exit(1);
    }
    int posterizeRanges = (posterizeArg == 1) ? 3 : 9;
    char *out_name = argv[4];
    int width, height, channels;
    nthreads = (argc >= 6) ? atoi(argv[5]) : omp_get_max_threads();

    omp_set_num_threads(nthreads);
    omp_set_max_active_levels(2); // habilita paralelismo para las sections

    unsigned char *data = stbi_load(path, &width, &height, &channels, 3);

    if (data == NULL)
    {
        printf("Error al cargar la imagen. \n");
    }
    else
    {
        // cast de puntero data a pixel
        Pixel *pixelCast = (Pixel *)data;
        
        double start_time = omp_get_wtime();

        Pixel **matriz = initMainMatriz(pixelCast, height, width);

        Pixel **paddingMatriz = padding(matriz, height, width, radio);

        Pixel **blurOutput = NULL;
        Pixel **highlightOutput = NULL;

        #pragma omp parallel sections num_threads(2)
        {
            #pragma omp section

            blurOutput = blurMatriz(paddingMatriz, width, height, radio);
            highlightOutput = highlightedMatriz(blurOutput, width, height, radio);

            #pragma omp section
            
            posterize(matriz, width, height, channels, posterizeRanges);
        }
        

        sum(matriz, highlightOutput, height, width, radio);

        int bytePerFile = width * 3;
        
        char out_path[256];
        snprintf(out_path, sizeof(out_path), "files/%s%s", out_name, strstr(out_name, ".png") ? "" : ".png");
        
        int result = stbi_write_png(out_path, width, height, 3, matriz[0], bytePerFile);

        double end_time = omp_get_wtime();
        double time_taken = end_time - start_time;

        if (result == 0)
        {
            printf("Error al guardar la imagen final.\n");
        }
        else
        {
            printf("¡Imagen generada con éxito en %f segundos!\n Se utilizaron %d threads en esta ejecución\n", time_taken, nthreads);
        }

        free(matriz);
        free(paddingMatriz[0]);
        free(paddingMatriz);
        
        free(blurOutput[0]); 
        free(blurOutput);    

        free(highlightOutput[0]);
        free(highlightOutput);

        stbi_image_free(data);
    }
}
