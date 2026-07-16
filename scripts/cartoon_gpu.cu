#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define BLOCK_SIZE 256
#define GRID_SIZE (BLOCK_SIZE + N - 1) / BLOCK_SIZE
#define TILE_SIZE 16
#define MAX_RADIO 2
#define SHARED_SIZE ((TILE_SIZE + 2 * MAX_RADIO) * (TILE_SIZE + 2 * MAX_RADIO))

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "includes/stb_image.h"
#include "includes/stb_image_write.h"

#define SATURATE(v) ((v) > 255 ? 255 : ((v) < 0 ? 0 : (v)))

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} Pixel;

// Sobel 3x3
__constant__ int SOBEL_3X3_X[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
__constant__ int SOBEL_3X3_Y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

// Sobel 5x5 (Valores estándar de gradiente extendido)
__constant__ int SOBEL_5X5_X[5][5] = {{-1, -2, 0, 2, 1},
                                      {-2, -3, 0, 3, 2},
                                      {-3, -5, 0, 5, 3},
                                      {-2, -3, 0, 3, 2},
                                      {-1, -2, 0, 2, 1}};

__constant__ int SOBEL_5X5_Y[5][5] = {{-1, -2, -3, -2, -1},
                                      {-2, -3, -5, -3, -2},
                                      {0, 0, 0, 0, 0},
                                      {2, 3, 5, 3, 2},
                                      {1, 2, 3, 2, 1}};

__device__ void *blurKernel(Pixel *input, Pixel *output, int width, int height,
                            int radio) {

  __shared__ Pixel tile[SHARED_SIZE];

  // Mapping 1D to 2D
  int tx = threadIdx.x % TILE_SIZE;
  int ty = threadIdx.x / TILE_SIZE;
  int col = blockIdx.x * TILE_SIZE + tx;
  int row = blockIdx.y * TILE_SIZE + ty;

  int sharedWidth = TILE_SIZE + 2 * radio;

  for (int i = -radio; i <= radio; i++) {
    for (int j = -radio; j <= radio; j++) {
      int currentRow = row + i;
      int currentCol = col + j;

      int index = (ty + radio + i) * sharedWidth + (tx + radio + j);

      if (currentRow >= 0 && currentRow < height && currentCol >= 0 &&
          currentCol < width) {
        tile[index] = input[currentRow * width + currentCol];
      } else {
        tile[index] = {0, 0, 0};
      }
    }
  }

  __syncthreads();

  if (row < height && col < width) {
    int r = 0, g = 0, b = 0;
    int cantPixel = (2 * radio + 1) * (2 * radio + 1);

    for (int i = -radio; i <= radio; i++) {
      for (int j = -radio; j <= radio; j++) {
        int index = (ty + radio + i) * sharedWidth + (tx + radio + j);
        Pixel p = tile[index];
        r += p.r;
        g += p.g;
        b += p.b;
      }
    }

    int out_idx = row * width + col; // warning
    output[out_idx].r = (unsigned char)(r / cantPixel);
    output[out_idx].g = (unsigned char)(g / cantPixel);
    output[out_idx].b = (unsigned char)(b / cantPixel);
  }
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
__device__ void highlightKernel(Pixel *input, Pixel *output, int width,
                                int height, int radio) {

  __shared__ Pixel tile[SHARED_SIZE];

  // Mapping 1D to 2D
  int tx = threadIdx.x % TILE_SIZE;
  int ty = threadIdx.x / TILE_SIZE;
  int col = blockIdx.x * TILE_SIZE + tx;
  int row = blockIdx.y * TILE_SIZE + ty;

  int sharedWidth = TILE_SIZE + 2 * radio;

  for (int i = -radio; i <= radio; i++) {
    for (int j = -radio; j <= radio; j++) {
      int currentRow = row + i;
      int currentCol = col + j;

      int index = (ty + radio + i) * sharedWidth + (tx + radio + j);

      if (currentRow >= 0 && currentRow < height && currentCol >= 0 &&
          currentCol < width) {
        tile[index] = input[currentRow * width + currentCol];
      } else {
        tile[index] = {0, 0, 0};
      }
    }
  }

  __syncthreads();

  if (row < height && col < width) {
    int r = 0, g = 0, b = 0;

    int gx = 0;
    int gy = 0;
    int cantPixel = (2 * radio + 1) * (2 * radio + 1);

    for (int i = -radio; i <= radio; i++) {
      for (int j = -radio; j <= radio; j++) {
        int index = (ty + radio + i) * sharedWidth + (tx + radio + j);

        unsigned char valorGris =
            (unsigned char)(0.299f * tile[index].r + 0.587f * tile[index].g +
                            0.114f * tile[index].b);

        if (radio == 1) {
          gx += valorGris * SOBEL_3X3_X[i + radio][j + radio];
          gy += valorGris * SOBEL_3X3_Y[i + radio][j + radio];
        } else {
          gx += valorGris * SOBEL_5X5_X[i + radio][j + radio];
          gy += valorGris * SOBEL_5X5_Y[i + radio][j + radio];
        }
      }
    }
    // criterio de magnitud (aproximado)
    int out_idx = row * width + col; // warning

    // UMBRALIZE
    float magnitude = (abs(gx) + abs(gy));
    unsigned char umbralize = (magnitude > 255 / 2) ? 255 : 0;
    output[out_idx].r = umbralize;
    output[out_idx].g = umbralize;
    output[out_idx].b = umbralize;
  }
}

__device__ Pixel device_posterizeSum_pixel(Pixel p, Pixel hl, int channels,
                                           int step) {
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
__device__ void posterizeSumKernel(Pixel *input, Pixel *highlight,
                                   Pixel *output, int width, int height,
                                   int channels, int posterizeRanges) {
  int step = 256 / posterizeRanges; // tamaño de cada intervalito

  int tid = blockIdx.x * blockDim.x + threadIdx.x;
  int totalPixels = width * height;

  if (tid < totalPixels) {
    Pixel copyInput = input[tid];
    Pixel hl = highlight[tid];

    output[tid] = device_posterizeSum_pixel(copyInput, hl, channels, step);
  }
}

__global__ void manager(Pixel *input, Pixel *output) {
  Pixel *d_input, *d_blur, *d_highlight, *d_output;

  cudaMalloc((void **)&d_input, width * height * sizeof(Pixel));
  cudaMalloc((void **)&d_blur, width * height * sizeof(Pixel));
  cudaMalloc((void **)&d_highlight, width * height * sizeof(Pixel));
  cudaMalloc((void **)&d_output, width * height * sizeof(Pixel));

  cudaMemcpy(d_input, h_pixelCast, width * height * sizeof(Pixel),
             cudaMemcpyHostToDevice);

  // ------------ TIMERS ----------- //
  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);
  // ------------------------------- //

  cudaEventRecord(start, 0);

  dim3 blockSize(BLOCK_SIZE);
  dim3 griSize();
}

int main(int argc, char **argv) {
  if (argc < 5) {
    printf("Uso: %s <imagen> <radio> <posterizeRanges> <nombre_salida>\n",
           argv[0]);
    exit(1);
  }
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

  unsigned char *data = stbi_load(path, &width, &height, &channels, 3);

  if (data == NULL) {
    printf("Error al cargar la imagen. \n");
  } else {
    // cast de puntero data a pixel -- host
    Pixel *h_pixelCast = (Pixel *)data;

    manager();

    blurKernel(paddingMatriz, width, height, radio);

    highlightKernel(blurOutput, width, height, radio);

    posterizeSumKernel(matriz, width, height, channels, posterizeRanges);

    cudaEventRecord(stop, 0);
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    int bytePerFile = width * 3;

    char out_path[256];
    snprintf(out_path, sizeof(out_path), "files/%s%s", out_name,
             strstr(out_name, ".png") ? "" : ".png");

    cudaMemcpy(h_pixelCast, d_output, width * height * sizeof(Pixel),
               cudaMemcpyDeviceToHost);

    int result =
        stbi_write_png(out_path, width, height, 3, matriz[0], bytePerFile);

    if (result == 0) {
      printf("Error al guardar la imagen final.\n");
    } else {
      printf("¡Imagen de tipo Cartoon generada con éxito en %f segundos!\n",
             milliseconds);
    }

    cudaFree(d_input);
    cudaFree(d_blur);
    cudaFree(d_highlight);
    cudaFree(d_output);

    stbi_image_free(data);
    return 0;
  }
}
