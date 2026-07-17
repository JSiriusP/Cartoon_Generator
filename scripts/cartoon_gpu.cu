#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <sys/time.h>

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 1024
#endif

#ifndef TILE_SIZE
#define TILE_SIZE 16
#endif

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "includes/stb_image.h"
#include "includes/stb_image_write.h"

#define SATURATE(v) ((v) > 255 ? 255 : ((v) < 0 ? 0 : (v)))

typedef struct{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

// Sobel 3x3
__constant__ int SOBEL_3X3_X[3][3] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};
__constant__ int SOBEL_3X3_Y[3][3] = {
    {-1, -2, -1},
    {0, 0, 0},
    {1, 2, 1}
};

// Sobel 5x5 (Valores estándar de gradiente extendido)
__constant__ int SOBEL_5X5_X[5][5] = {
    {-1, -2, 0, 2, 1},
    {-2, -3, 0, 3, 2},
    {-3, -5, 0, 5, 3},
    {-2, -3, 0, 3, 2},
    {-1, -2, 0, 2, 1}
};

__constant__ int SOBEL_5X5_Y[5][5] = {
    {-1, -2, -3, -2, -1},
    {-2, -3, -5, -3, -2},
    {0, 0, 0, 0, 0},
    {2, 3, 5, 3, 2},
    {1, 2, 3, 2, 1}
};


template <int radio>
__device__ void blurKernel(Pixel *input, Pixel *output, int width, int height){

    __shared__ Pixel tile[(TILE_SIZE + 2 * radio) * (TILE_SIZE + 2 * radio)];

    // Mapping 1D to 2D
    int tx = threadIdx.x % TILE_SIZE;
    int ty = threadIdx.x / TILE_SIZE;
    
    // Grilla 1D -> Reconstrucción 2D
    int blocksPerRow = (width + TILE_SIZE - 1) / TILE_SIZE;
    int blockIdx_x = blockIdx.x % blocksPerRow;
    int blockIdx_y = blockIdx.x / blocksPerRow;
    
    int col = blockIdx_x * TILE_SIZE + tx;
    int row = blockIdx_y * TILE_SIZE + ty;

    int sharedWidth = TILE_SIZE + 2 * radio;

    for (int i = -radio; i <= radio; i++){
        for (int j = -radio; j <= radio; j++){
            int currentRow = row + i;
            int currentCol = col + j;

            int index = (ty + radio + i) * sharedWidth + (tx + radio + j);

            if (currentRow >= 0 && currentRow < height && currentCol >= 0 && currentCol < width){
                tile[index] = input[currentRow * width + currentCol];
            } else{
                tile[index] = {0, 0, 0};
            }
        }
    }

    __syncthreads();

    if (row < height && col < width){
        int r = 0, g = 0, b = 0;
        int cantPixel = (2 * radio + 1) * (2 * radio + 1);

        for (int i = -radio; i <= radio; i++){
            for (int j = -radio; j <= radio; j++){
                int index = (ty + radio + i) * sharedWidth + (tx + radio + j);
                Pixel p = tile[index];
                r += p.r;
                g += p.g;
                b += p.b;
            }
        }

        int out_idx = row * width + col;
        output[out_idx].r = (unsigned char)(r / cantPixel);
        output[out_idx].g = (unsigned char)(g / cantPixel);
        output[out_idx].b = (unsigned char)(b / cantPixel);
    }
}

template <int radio>
__device__ void highlightKernel(Pixel *input, Pixel *output, int width, int height){

    __shared__ Pixel tile[(TILE_SIZE + 2 * radio) * (TILE_SIZE + 2 * radio)];

    // Mapping 1D to 2D
    int tx = threadIdx.x % TILE_SIZE;
    int ty = threadIdx.x / TILE_SIZE;
    
    // Grilla 1D -> Reconstrucción 2D
    int blocksPerRow = (width + TILE_SIZE - 1) / TILE_SIZE;
    int blockIdx_x = blockIdx.x % blocksPerRow;
    int blockIdx_y = blockIdx.x / blocksPerRow;
    
    int col = blockIdx_x * TILE_SIZE + tx;
    int row = blockIdx_y * TILE_SIZE + ty;

    int sharedWidth = TILE_SIZE + 2 * radio;

    for (int i = -radio; i <= radio; i++) {
        for (int j = -radio; j <= radio; j++) {
            int currentRow = row + i;
            int currentCol = col + j;

            int index = (ty + radio + i) * sharedWidth + (tx + radio + j);

            if (currentRow >= 0 && currentRow < height && currentCol >= 0 && currentCol < width)
            {
                tile[index] = input[currentRow * width + currentCol];
            }
            else
            {
                tile[index] = {0, 0, 0};
            }
        }
    }

    __syncthreads();

    if (row < height && col < width)
    {
        int gx = 0;
        int gy = 0;

        for (int i = -radio; i <= radio; i++){
            for (int j = -radio; j <= radio; j++){   
                int index = (ty + radio + i) * sharedWidth + (tx + radio + j);

                unsigned char valorGris = (unsigned char)(0.299f * tile[index].r +
                                                          0.587f * tile[index].g +
                                                          0.114f * tile[index].b);

                if (radio == 1)
                {
                    gx += valorGris * SOBEL_3X3_X[i + radio][j + radio];
                    gy += valorGris * SOBEL_3X3_Y[i + radio][j + radio];
                }
                else
                {
                    gx += valorGris * SOBEL_5X5_X[i + radio][j + radio];
                    gy += valorGris * SOBEL_5X5_Y[i + radio][j + radio];
                }
            }
        }
        int out_idx = row * width + col;

        // UMBRALIZE
        float magnitude = (abs(gx) + abs(gy));
        unsigned char umbralize = (magnitude > 255 / 2)? 255 : 0;
        output[out_idx].r = umbralize;
        output[out_idx].g = umbralize;
        output[out_idx].b = umbralize;
    }
}

__device__ Pixel device_posterizeSum_pixel(Pixel p, Pixel hl, int channels, int step) {
    Pixel result;
    if (channels == 1) {
        // Convertir a escala de grises
        int valor = (int)(0.299f * p.r + 0.587f * p.g + 0.114f * p.b);
        int valorPosterizado = (valor / step) * step;
        p.r = p.g = p.b = (unsigned char)valorPosterizado;

    } else {
        // RGB o estándar
        p.r = (unsigned char)((p.r / step) * step);
        p.g = (unsigned char)((p.g / step) * step);
        p.b = (unsigned char)((p.b / step) * step);
    }

    result.r = (unsigned char)SATURATE(p.r - hl.r);
    result.g = (unsigned char)SATURATE(p.g - hl.g);
    result.b = (unsigned char)SATURATE(p.b - hl.b);

    return result;
}

__device__ void posterizeSumKernel(Pixel *input, Pixel *highlight, Pixel *output, int width, int height, int channels, int posterizeRanges){
    int step = 256 / posterizeRanges;

    // Grilla 1D -> Reconstrucción 2D
    int tx = threadIdx.x % TILE_SIZE;
    int ty = threadIdx.x / TILE_SIZE;
    int blocksPerRow = (width + TILE_SIZE - 1) / TILE_SIZE;
    int blockIdx_x = blockIdx.x % blocksPerRow;
    int blockIdx_y = blockIdx.x / blocksPerRow;
    
    int col = blockIdx_x * TILE_SIZE + tx;
    int row = blockIdx_y * TILE_SIZE + ty;

    if (row < height && col < width){
        int tid = row * width + col;
        Pixel copyInput = input[tid];
        Pixel hl = highlight[tid];

        output[tid] = device_posterizeSum_pixel(copyInput, hl, channels, step);
    }
}

template <int radio>
__global__ void manager(Pixel *input, Pixel *blur, Pixel *highlight, Pixel *output, int width, int height, int channels, int posterizeRanges){
    blurKernel<radio>(input, blur, width, height);

    __syncthreads();

    highlightKernel<radio>(blur, highlight, width, height);

    __syncthreads();

    posterizeSumKernel(input, highlight, output, width, height, channels, posterizeRanges);
}

int main(int argc, char **argv){
    if (argc < 5){
        printf("Uso: %s <imagen> <radio> <posterizeRanges> <nombre_salida>\n", argv[0]);
        exit(1);
    }
    char *path = argv[1];
    int radio = atoi(argv[2]);
    if (radio != 1 && radio != 2){
        printf("Radio debe ser 1 o 2.\n");
        exit(1);
    }
    int posterizeArg = atoi(argv[3]);
    if (posterizeArg != 1 && posterizeArg != 2){
        printf("Rango del posterizado debe ser 1 o 2.\n");
        exit(1);
    }
    int posterizeRanges = (posterizeArg == 1) ? 3 : 9;
    char *out_name = argv[4];
    int width, height, channels;

    unsigned char *data = stbi_load(path, &width, &height, &channels, 3);

    if (data == NULL){
        printf("Error al cargar la imagen. \n");
        return 1;
    }
    
    // cast de puntero data a pixel -- host
    Pixel *h_pixelCast = (Pixel *)data;
    Pixel *d_input, *d_blur, *d_highlight, *d_output;

    cudaMalloc((void **)&d_input, width * height * sizeof(Pixel));
    cudaMalloc((void **)&d_blur, width * height * sizeof(Pixel));
    cudaMalloc((void **)&d_highlight, width * height * sizeof(Pixel));
    cudaMalloc((void **)&d_output, width * height * sizeof(Pixel));

    cudaMemcpy(d_input, h_pixelCast, width * height * sizeof(Pixel), cudaMemcpyHostToDevice);

    // ------------ TIMERS ----------- //
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    // ------------------------------- //

    cudaEventRecord(start, 0);

    // grilla 1D basada en tiles de 16x16
    int blocksPerRow = (width + TILE_SIZE - 1) / TILE_SIZE;
    int blocksPerCol = (height + TILE_SIZE - 1) / TILE_SIZE;
    int totalBlocks = blocksPerRow * blocksPerCol;
    
    dim3 blockSize(BLOCK_SIZE); // 256 hilos
    dim3 gridSize(totalBlocks); // Grilla 1D

    if (radio == 1) {
        manager<1><<<gridSize, blockSize>>>(d_input, d_blur, d_highlight, d_output, width, height, channels, posterizeRanges);
    } else {
        manager<2><<<gridSize, blockSize>>>(d_input, d_blur, d_highlight, d_output, width, height, channels, posterizeRanges);
    }

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    int bytePerFile = width * 3;

    char out_path[256];
    snprintf(out_path, sizeof(out_path), "files/%s%s", out_name, strstr(out_name, ".png") ? "" : ".png");

    cudaMemcpy(h_pixelCast, d_output, width * height * sizeof(Pixel), cudaMemcpyDeviceToHost);

    int result = stbi_write_png(out_path, width, height, 3, h_pixelCast, bytePerFile);

    if (result == 0){
        printf("Error al guardar la imagen final.\n");
    }
    else{
        printf("¡Imagen de tipo Cartoon generada con éxito en %f milisegundos!\n", milliseconds);
    }

    cudaFree(d_input);
    cudaFree(d_blur);
    cudaFree(d_highlight);
    cudaFree(d_output);

    stbi_image_free(data);
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    
    return 0;
}
