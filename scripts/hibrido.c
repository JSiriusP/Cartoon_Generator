#include <mpi.h>
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

// Sobel 5x5
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

    for (int i = 0; i < newHeight; i++) {
        output[i] = &pool[i * newWidth];
    }

    memset(pool, 0, newHeight * newWidth * sizeof(Pixel));

    for (int f = 0; f < height; f++) {
        int row = f + radio;
        memcpy(&output[row][radio], input[f], width * sizeof(Pixel));
    }
   return output;
}

Pixel **initAuxMatriz(int height, int width){
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

int umbralize(float magnitud) {
    if (magnitud > 255 / 2) {
        return 255;
    } else {
        return 0;
    }
}

Pixel **blurMatriz(Pixel **input, int width, int height, int radio){
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

    #pragma omp parallel for collapse(2) schedule(guided)
    for (int i = radio; i < (height + radio); i++) {
        for (int j = radio; j < (width + radio); j++) {
            int r = 0, g = 0, b = 0;
            for (int f = i - radio; f <= i + radio; f++) {
                for (int c = j - radio; c <= j + radio; c++) {
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

Pixel** highlightedMatriz(Pixel **input, int width, int height, int radio){
    int newHeight = height + (2 * radio);
    int newWidth = width + (2 * radio);
    Pixel **output = initAuxMatriz(newHeight, newWidth);
    float gx, gy;
    int umbralizeValue;

    #pragma omp parallel for schedule (static)
    for (int i = 0; i < newHeight; i++) {
        for (int j = 0; j < newWidth; j++) {
            output[i][j].r = 0; output[i][j].g = 0; output[i][j].b = 0;
        }
    }

    #pragma omp parallel for collapse(2) schedule(guided)
    for (int i = radio; i < (height + radio); i++) {
        for (int j = radio; j < (width + radio); j++) {
            gx = 0;
            gy = 0;
            for (int f = -radio; f <= radio; f++) {
                for (int c = -radio; c <= radio; c++) {
                    unsigned char valorGris = (unsigned char)(0.299f * input[i + f][j + c].r +
                                                              0.587f * input[i + f][j + c].g +
                                                              0.114f * input[i + f][j + c].b);

                    if (radio == 1) {
                        gx += valorGris * SOBEL_3X3_X[f + radio][c + radio];
                        gy += valorGris * SOBEL_3X3_Y[f + radio][c + radio];
                    } else {
                        gx += valorGris * SOBEL_5X5_X[f + radio][c + radio];
                        gy += valorGris * SOBEL_5X5_Y[f + radio][c + radio];
                    }
                }
            }
            umbralizeValue = umbralize(abs(gx) + abs(gy));
            output[i][j].r = (unsigned char)umbralizeValue;
            output[i][j].g = (unsigned char)umbralizeValue;
            output[i][j].b = (unsigned char)umbralizeValue;
        }
    }
    return output;
}

void posterize(Pixel **input, int width, int height, int channels, int posterizeRanges){
    int step = 256 / posterizeRanges;

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (channels == 1) {
                int valor = (int) (0.299f * input[i][j].r +
                                   0.587f * input[i][j].g +
                                   0.114f * input[i][j].b);

                int rango = valor / step;
                int valorPosterizado = rango * step;

                input[i][j].r = (unsigned char)valorPosterizado;
                input[i][j].g = (unsigned char)valorPosterizado;
                input[i][j].b = (unsigned char)valorPosterizado;
            } else {
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

// Modificado para no requerir que highlightMatriz este con padding
void sum(Pixel **originalMatriz, Pixel **highlightMatriz, int height, int width){
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            originalMatriz[i][j].r = (unsigned char)SATURATE(originalMatriz[i][j].r - highlightMatriz[i][j].r);
            originalMatriz[i][j].g = (unsigned char)SATURATE(originalMatriz[i][j].g - highlightMatriz[i][j].g);
            originalMatriz[i][j].b = (unsigned char)SATURATE(originalMatriz[i][j].b - highlightMatriz[i][j].b);
        }
    }
}

int main(int argc, char **argv){
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 3) {
        if (rank == 0) printf("Se requieren al menos 3 procesos (1 Maestro, >= 1 Blur/Highlight, >= 1 Posterize)\n");
        MPI_Finalize();
        return 1;
    }

    int width = 0, height = 0, channels = 0, radio = 0, nthreads = 1, posterizeRanges = 9;
    unsigned char *data = NULL;
    Pixel *pixelCast = NULL;

    if (rank == 0) {
        if (argc < 6) {
            printf("Uso: mpirun -np X %s <imagen> <radio> <posterizeRanges> <nombre_salida> <num_hilos>\n", argv[0]);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        char *path = argv[1];
        radio = atoi(argv[2]);
        if(radio != 1 && radio != 2) {
            printf("Radio debe ser 1 o 2.\n");
            MPI_Finalize();
            return 1;
        }

        int posterizeArg = atoi(argv[3]);
        if(posterizeArg != 1 && posterizeArg != 2) {
            printf("Rango del posterizado debe ser 1 o 2.\n");
            MPI_Finalize();
            return 1;
        }
        posterizeRanges = (posterizeArg == 1) ? 3 : 9;

        nthreads = atoi(argv[5]);

        data = stbi_load(path, &width, &height, &channels, 3);
        if (data == NULL) {
            printf("Error al cargar la imagen.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        pixelCast = (Pixel *)data;
    }

    int metadata[6] = {width, height, channels, radio, nthreads, posterizeRanges};
    MPI_Bcast(metadata, 6, MPI_INT, 0, MPI_COMM_WORLD);
    width = metadata[0];
    height = metadata[1];
    channels = metadata[2];
    radio = metadata[3];
    nthreads = metadata[4];
    posterizeRanges = metadata[5];

    omp_set_num_threads(nthreads);
    
    int numWorkers = size - 1;
    int numBH = numWorkers / 2; // Cantidad de procesos que se le asignan a Blur & Highlight
    int numP = numWorkers - numBH; // Cantidad de procesos que se le asignan a Posterize

    if (rank == 0) {
        double start_time = MPI_Wtime();

        // Envio tareas Blur + Highlight
        int rowsPerBH = height / numBH;
        int remainderBH = height % numBH; //resto para dividir la imagen
        int currentRow = 0;

        for (int i = 0; i < numBH; i++) {
            int start = currentRow;
            int end = start + rowsPerBH + (i < remainderBH ? 1 : 0);
            
            int validStart = start - 2 * radio;
            if (validStart < 0) validStart = 0;
            
            int validEnd = end + 2 * radio - 1;
            if (validEnd >= height) validEnd = height - 1;
            
            int hRecv = validEnd - validStart + 1;
            int targetOffset = start - validStart;
            int numberOfTargetRows = end - start;  
            int destRank = i + 1;
            
            int info[3] = {hRecv, targetOffset, numberOfTargetRows};
            MPI_Send(info, 3, MPI_INT, destRank, 0, MPI_COMM_WORLD);
            MPI_Send(&pixelCast[validStart * width], hRecv * width * sizeof(Pixel), MPI_BYTE, destRank, 1, MPI_COMM_WORLD);
            currentRow = end;
        }

        // Envio tareas Posterize
        int rowsPerP = height / numP;
        int remainderP = height % numP;
        currentRow = 0;

        for (int i = 0; i < numP; i++) {
            int start = currentRow;
            int end = start + rowsPerP + (i < remainderP ? 1 : 0);
            int numberOfTargetRows = end - start;
            int destRank = numBH + i + 1;
            
            MPI_Send(&numberOfTargetRows, 1, MPI_INT, destRank, 0, MPI_COMM_WORLD);
            MPI_Send(&pixelCast[start * width], numberOfTargetRows * width * sizeof(Pixel), MPI_BYTE, destRank, 1, MPI_COMM_WORLD);
            
            currentRow = end;
        }

        Pixel *highlight_pixels = (Pixel *)malloc(height * width * sizeof(Pixel));
        Pixel *posterize_pixels = (Pixel *)malloc(height * width * sizeof(Pixel));

        // Recibir resultados de Blur + Highlight
        currentRow = 0;
        for (int i = 0; i < numBH; i++) {
            int start = currentRow;
            int end = start + rowsPerBH + (i < remainderBH ? 1 : 0);
            int numberOfTargetRows = end - start;
            int destRank = i + 1;
            
            MPI_Recv(&highlight_pixels[start * width], numberOfTargetRows * width * sizeof(Pixel), MPI_BYTE, destRank, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            currentRow = end;
        }

        // Recibir resultados de Posterize
        currentRow = 0;
        for (int i = 0; i < numP; i++) {
            int start = currentRow;
            int end = start + rowsPerP + (i < remainderP ? 1 : 0);
            int numberOfTargetRows = end - start;
            int destRank = numBH + i + 1;
            
            MPI_Recv(&posterize_pixels[start * width], numberOfTargetRows * width * sizeof(Pixel), MPI_BYTE, destRank, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            currentRow = end;
        }

        Pixel **matriz = initMainMatriz(posterize_pixels, height, width);
        Pixel **highlightOutput = initMainMatriz(highlight_pixels, height, width);

        // Suma final
        sum(matriz, highlightOutput, height, width);

        int bytePerFile = width * 3;
        
        char out_path[256];
        char *out_name = argv[4];
        snprintf(out_path, sizeof(out_path), "files/%s%s", out_name, strstr(out_name, ".png") ? "" : ".png");
        
        int result = stbi_write_png(out_path, width, height, 3, matriz[0], bytePerFile);

        double end_time = MPI_Wtime();
        if (result == 0) {
            printf("Error al guardar la imagen final.\n");
        } else {
            printf("¡Imagen generada con éxito con MPI en %f segundos!\nSe utilizaron %d threads en esta ejecución\n", end_time - start_time, size);
        }

        free(matriz);
        free(highlightOutput);
        free(highlight_pixels);
        free(posterize_pixels);
        stbi_image_free(data);

    } else if (rank <= numBH) {
        // Trabajador de Blur + Highlight
        int info[3];
        MPI_Recv(info, 3, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int hRecv = info[0];
        int targetOffset = info[1];
        int numberOfTargetRows = info[2];
        
        Pixel *localData = (Pixel *)malloc(hRecv * width * sizeof(Pixel));
        MPI_Recv(localData, hRecv * width * sizeof(Pixel), MPI_BYTE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        Pixel **matriz = initMainMatriz(localData, hRecv, width);
        Pixel **paddingMatriz = padding(matriz, hRecv, width, radio);
        Pixel **blurOutput = blurMatriz(paddingMatriz, width, hRecv, radio);
        Pixel **highlightOutput = highlightedMatriz(blurOutput, width, hRecv, radio);
        
        Pixel *send_buf = (Pixel *)malloc(numberOfTargetRows * width * sizeof(Pixel));
        for (int r = 0; r < numberOfTargetRows; r++) {
            memcpy(&send_buf[r * width], &highlightOutput[targetOffset + radio + r][radio], width * sizeof(Pixel));
        }
        
        MPI_Send(send_buf, numberOfTargetRows * width * sizeof(Pixel), MPI_BYTE, 0, 2, MPI_COMM_WORLD);
        
        free(send_buf);
        free(matriz);
        free(paddingMatriz[0]); 
        free(paddingMatriz);
        free(blurOutput[0]); 
        free(blurOutput);    

        free(highlightOutput[0]);
        free(highlightOutput);
        free(localData);
    } else {
        // Trabajador de Posterize
        int numberOfTargetRows;
        MPI_Recv(&numberOfTargetRows, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        Pixel *localData = (Pixel *)malloc(numberOfTargetRows * width * sizeof(Pixel));
        MPI_Recv(localData, numberOfTargetRows * width * sizeof(Pixel), MPI_BYTE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        Pixel **matriz = initMainMatriz(localData, numberOfTargetRows, width);
        posterize(matriz, width, numberOfTargetRows, channels, posterizeRanges);
        
        MPI_Send(localData, numberOfTargetRows * width * sizeof(Pixel), MPI_BYTE, 0, 2, MPI_COMM_WORLD);
        
        free(matriz);
        free(localData);
    }

    MPI_Finalize();
    return 0;
}
