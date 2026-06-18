# Resultados del Benchmark

## Imagen: 800x800

### Filtro: 3x3, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 0.430802 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 0.383252 | 1.12x | 0.56 |
| OpenMP | 4 hilos | 0.384256 | 1.12x | 0.28 |
| OpenMP | 8 hilos | 0.384426 | 1.12x | 0.14 |
| OpenMP | 16 hilos | 0.406671 | 1.06x | 0.07 |
| OpenMP | 32 hilos | 0.406234 | 1.06x | 0.03 |
| MPI | 3 procesos | 0.408984 | 1.05x | 0.35 |
| MPI | 8 procesos | 0.313341 | 1.37x | 0.17 |
| MPI | 16 procesos | 0.291762 | 1.48x | 0.09 |
| MPI | 32 procesos | 0.288532 | 1.49x | 0.05 |
| Híbrido | 3 procs x 2 hilos | 0.298572 | 1.44x | 0.24 |
| Híbrido | 3 procs x 4 hilos | 0.250563 | 1.72x | 0.14 |
| Híbrido | 3 procs x 8 hilos | 0.227238 | 1.90x | 0.08 |
| Híbrido | 4 procs x 8 hilos | 0.226574 | 1.90x | 0.06 |
| Híbrido | 8 procs x 4 hilos | 0.237488 | 1.81x | 0.06 |
| Híbrido | 16 procs x 2 hilos | 0.248326 | 1.73x | 0.05 |

### Filtro: 3x3, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 0.455256 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 0.428906 | 1.06x | 0.53 |
| OpenMP | 4 hilos | 0.417661 | 1.09x | 0.27 |
| OpenMP | 8 hilos | 0.430242 | 1.06x | 0.13 |
| OpenMP | 16 hilos | 0.438713 | 1.04x | 0.06 |
| OpenMP | 32 hilos | 0.428456 | 1.06x | 0.03 |
| MPI | 3 procesos | 0.419394 | 1.09x | 0.36 |
| MPI | 8 procesos | 0.313615 | 1.45x | 0.18 |
| MPI | 16 procesos | 0.310684 | 1.47x | 0.09 |
| MPI | 32 procesos | 0.349943 | 1.30x | 0.04 |
| Híbrido | 3 procs x 2 hilos | 0.274383 | 1.66x | 0.28 |
| Híbrido | 3 procs x 4 hilos | 0.255642 | 1.78x | 0.15 |
| Híbrido | 3 procs x 8 hilos | 0.266376 | 1.71x | 0.07 |
| Híbrido | 4 procs x 8 hilos | 0.271965 | 1.67x | 0.05 |
| Híbrido | 8 procs x 4 hilos | 0.28194 | 1.61x | 0.05 |
| Híbrido | 16 procs x 2 hilos | 0.263249 | 1.73x | 0.05 |

### Filtro: 5x5, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 0.632849 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 0.606827 | 1.04x | 0.52 |
| OpenMP | 4 hilos | 0.606744 | 1.04x | 0.26 |
| OpenMP | 8 hilos | 0.606565 | 1.04x | 0.13 |
| OpenMP | 16 hilos | 0.606671 | 1.04x | 0.07 |
| OpenMP | 32 hilos | 0.616207 | 1.03x | 0.03 |
| MPI | 3 procesos | 0.613548 | 1.03x | 0.34 |
| MPI | 8 procesos | 0.359315 | 1.76x | 0.22 |
| MPI | 16 procesos | 0.306038 | 2.07x | 0.13 |
| MPI | 32 procesos | 0.334849 | 1.89x | 0.06 |
| Híbrido | 3 procs x 2 hilos | 0.410035 | 1.54x | 0.26 |
| Híbrido | 3 procs x 4 hilos | 0.317972 | 1.99x | 0.17 |
| Híbrido | 3 procs x 8 hilos | 0.260705 | 2.43x | 0.10 |
| Híbrido | 4 procs x 8 hilos | 0.260952 | 2.43x | 0.08 |
| Híbrido | 8 procs x 4 hilos | 0.257681 | 2.46x | 0.08 |
| Híbrido | 16 procs x 2 hilos | 0.269513 | 2.35x | 0.07 |

### Filtro: 5x5, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 0.634402 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 0.606882 | 1.05x | 0.52 |
| OpenMP | 4 hilos | 0.606762 | 1.05x | 0.26 |
| OpenMP | 8 hilos | 0.606344 | 1.05x | 0.13 |
| OpenMP | 16 hilos | 0.606689 | 1.05x | 0.07 |
| OpenMP | 32 hilos | 0.617468 | 1.03x | 0.03 |
| MPI | 3 procesos | 0.60781 | 1.04x | 0.35 |
| MPI | 8 procesos | 0.294855 | 2.15x | 0.27 |
| MPI | 16 procesos | 0.299176 | 2.12x | 0.13 |
| MPI | 32 procesos | 0.265659 | 2.39x | 0.07 |
| Híbrido | 3 procs x 2 hilos | 0.418993 | 1.51x | 0.25 |
| Híbrido | 3 procs x 4 hilos | 0.317704 | 2.00x | 0.17 |
| Híbrido | 3 procs x 8 hilos | 0.262825 | 2.41x | 0.10 |
| Híbrido | 4 procs x 8 hilos | 0.261001 | 2.43x | 0.08 |
| Híbrido | 8 procs x 4 hilos | 0.280055 | 2.27x | 0.07 |
| Híbrido | 16 procs x 2 hilos | 0.254328 | 2.49x | 0.08 |

## Imagen: 2000x2000

### Filtro: 3x3, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 2.419022 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 1.812776 | 1.33x | 0.67 |
| OpenMP | 4 hilos | 2.281576 | 1.06x | 0.27 |
| OpenMP | 8 hilos | 1.655634 | 1.46x | 0.18 |
| OpenMP | 16 hilos | 2.11751 | 1.14x | 0.07 |
| OpenMP | 32 hilos | 2.279819 | 1.06x | 0.03 |
| MPI | 3 procesos | 2.111498 | 1.15x | 0.38 |
| MPI | 8 procesos | 1.464386 | 1.65x | 0.21 |
| MPI | 16 procesos | 1.147487 | 2.11x | 0.13 |
| MPI | 32 procesos | 1.020436 | 2.37x | 0.07 |
| Híbrido | 3 procs x 2 hilos | 1.229697 | 1.97x | 0.33 |
| Híbrido | 3 procs x 4 hilos | 1.09315 | 2.21x | 0.18 |
| Híbrido | 3 procs x 8 hilos | 1.045679 | 2.31x | 0.10 |
| Híbrido | 4 procs x 8 hilos | 1.046472 | 2.31x | 0.07 |
| Híbrido | 8 procs x 4 hilos | 1.083029 | 2.23x | 0.07 |
| Híbrido | 16 procs x 2 hilos | 1.109717 | 2.18x | 0.07 |

### Filtro: 3x3, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 2.232247 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 1.745877 | 1.28x | 0.64 |
| OpenMP | 4 hilos | 2.271765 | 0.98x | 0.25 |
| OpenMP | 8 hilos | 1.767468 | 1.26x | 0.16 |
| OpenMP | 16 hilos | 1.749348 | 1.28x | 0.08 |
| OpenMP | 32 hilos | 1.67247 | 1.33x | 0.04 |
| MPI | 3 procesos | 1.69177 | 1.32x | 0.44 |
| MPI | 8 procesos | 1.490853 | 1.50x | 0.19 |
| MPI | 16 procesos | 1.237368 | 1.80x | 0.11 |
| MPI | 32 procesos | 1.187998 | 1.88x | 0.06 |
| Híbrido | 3 procs x 2 hilos | 1.718347 | 1.30x | 0.22 |
| Híbrido | 3 procs x 4 hilos | 1.474846 | 1.51x | 0.13 |
| Híbrido | 3 procs x 8 hilos | 1.066875 | 2.09x | 0.09 |
| Híbrido | 4 procs x 8 hilos | 1.032429 | 2.16x | 0.07 |
| Híbrido | 8 procs x 4 hilos | 1.20344 | 1.85x | 0.06 |
| Híbrido | 16 procs x 2 hilos | 1.271783 | 1.76x | 0.05 |

### Filtro: 5x5, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 2.396958 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 2.542161 | 0.94x | 0.47 |
| OpenMP | 4 hilos | 2.517534 | 0.95x | 0.24 |
| OpenMP | 8 hilos | 3.42779 | 0.70x | 0.09 |
| OpenMP | 16 hilos | 2.469947 | 0.97x | 0.06 |
| OpenMP | 32 hilos | 2.49067 | 0.96x | 0.03 |
| MPI | 3 procesos | 3.870985 | 0.62x | 0.21 |
| MPI | 8 procesos | 1.207734 | 1.98x | 0.25 |
| MPI | 16 procesos | 1.192099 | 2.01x | 0.13 |
| MPI | 32 procesos | 1.08585 | 2.21x | 0.07 |
| Híbrido | 3 procs x 2 hilos | 1.832 | 1.31x | 0.22 |
| Híbrido | 3 procs x 4 hilos | 1.23861 | 1.94x | 0.16 |
| Híbrido | 3 procs x 8 hilos | 1.182372 | 2.03x | 0.08 |
| Híbrido | 4 procs x 8 hilos | 1.063828 | 2.25x | 0.07 |
| Híbrido | 8 procs x 4 hilos | 1.002213 | 2.39x | 0.07 |
| Híbrido | 16 procs x 2 hilos | 0.959063 | 2.50x | 0.08 |

### Filtro: 5x5, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 2.45529 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 2.385205 | 1.03x | 0.51 |
| OpenMP | 4 hilos | 3.513056 | 0.70x | 0.17 |
| OpenMP | 8 hilos | 3.656725 | 0.67x | 0.08 |
| OpenMP | 16 hilos | 2.534647 | 0.97x | 0.06 |
| OpenMP | 32 hilos | 2.424945 | 1.01x | 0.03 |
| MPI | 3 procesos | 3.480968 | 0.71x | 0.24 |
| MPI | 8 procesos | 1.861991 | 1.32x | 0.16 |
| MPI | 16 procesos | 1.407904 | 1.74x | 0.11 |
| MPI | 32 procesos | 1.154735 | 2.13x | 0.07 |
| Híbrido | 3 procs x 2 hilos | 1.697507 | 1.45x | 0.24 |
| Híbrido | 3 procs x 4 hilos | 1.482336 | 1.66x | 0.14 |
| Híbrido | 3 procs x 8 hilos | 1.449658 | 1.69x | 0.07 |
| Híbrido | 4 procs x 8 hilos | 0.993733 | 2.47x | 0.08 |
| Híbrido | 8 procs x 4 hilos | 1.247153 | 1.97x | 0.06 |
| Híbrido | 16 procs x 2 hilos | 1.24057 | 1.98x | 0.06 |

## Imagen: 5000x5000

### Filtro: 3x3, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 14.883381 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 8.978545 | 1.66x | 0.83 |
| OpenMP | 4 hilos | 14.274831 | 1.04x | 0.26 |
| OpenMP | 8 hilos | 13.881187 | 1.07x | 0.13 |
| OpenMP | 16 hilos | 8.964486 | 1.66x | 0.10 |
| OpenMP | 32 hilos | 14.236292 | 1.05x | 0.03 |
| MPI | 3 procesos | 11.259051 | 1.32x | 0.44 |
| MPI | 8 procesos | 9.189132 | 1.62x | 0.20 |
| MPI | 16 procesos | 4.673244 | 3.18x | 0.20 |
| MPI | 32 procesos | 5.819466 | 2.56x | 0.08 |
| Híbrido | 3 procs x 2 hilos | 9.639211 | 1.54x | 0.26 |
| Híbrido | 3 procs x 4 hilos | 7.652803 | 1.94x | 0.16 |
| Híbrido | 3 procs x 8 hilos | 4.728533 | 3.15x | 0.13 |
| Híbrido | 4 procs x 8 hilos | 7.230167 | 2.06x | 0.06 |
| Híbrido | 8 procs x 4 hilos | 4.57626 | 3.25x | 0.10 |
| Híbrido | 16 procs x 2 hilos | 4.691959 | 3.17x | 0.10 |

### Filtro: 3x3, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 16.489305 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 16.115032 | 1.02x | 0.51 |
| OpenMP | 4 hilos | 16.096768 | 1.02x | 0.26 |
| OpenMP | 8 hilos | 16.056923 | 1.03x | 0.13 |
| OpenMP | 16 hilos | 15.670084 | 1.05x | 0.07 |
| OpenMP | 32 hilos | 16.082516 | 1.03x | 0.03 |
| MPI | 3 procesos | 9.667662 | 1.71x | 0.57 |
| MPI | 8 procesos | 10.565694 | 1.56x | 0.20 |
| MPI | 16 procesos | 5.741539 | 2.87x | 0.18 |
| MPI | 32 procesos | 6.893844 | 2.39x | 0.07 |
| Híbrido | 3 procs x 2 hilos | 11.530493 | 1.43x | 0.24 |
| Híbrido | 3 procs x 4 hilos | 6.480733 | 2.54x | 0.21 |
| Híbrido | 3 procs x 8 hilos | 9.133044 | 1.81x | 0.08 |
| Híbrido | 4 procs x 8 hilos | 6.177563 | 2.67x | 0.08 |
| Híbrido | 8 procs x 4 hilos | 5.481496 | 3.01x | 0.09 |
| Híbrido | 16 procs x 2 hilos | 5.96771 | 2.76x | 0.09 |

### Filtro: 5x5, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 23.177882 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 22.243366 | 1.04x | 0.52 |
| OpenMP | 4 hilos | 13.172055 | 1.76x | 0.44 |
| OpenMP | 8 hilos | 22.037473 | 1.05x | 0.13 |
| OpenMP | 16 hilos | 22.112685 | 1.05x | 0.07 |
| OpenMP | 32 hilos | 22.179474 | 1.05x | 0.03 |
| MPI | 3 procesos | 15.02468 | 1.54x | 0.51 |
| MPI | 8 procesos | 11.428418 | 2.03x | 0.25 |
| MPI | 16 procesos | 5.001359 | 4.63x | 0.29 |
| MPI | 32 procesos | 5.756974 | 4.03x | 0.13 |
| Híbrido | 3 procs x 2 hilos | 9.576669 | 2.42x | 0.40 |
| Híbrido | 3 procs x 4 hilos | 9.18554 | 2.52x | 0.21 |
| Híbrido | 3 procs x 8 hilos | 7.241312 | 3.20x | 0.13 |
| Híbrido | 4 procs x 8 hilos | 5.563688 | 4.17x | 0.13 |
| Híbrido | 8 procs x 4 hilos | 5.268925 | 4.40x | 0.14 |
| Híbrido | 16 procs x 2 hilos | 4.894796 | 4.74x | 0.15 |

### Filtro: 5x5, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 23.900001 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 22.955603 | 1.04x | 0.52 |
| OpenMP | 4 hilos | 22.878844 | 1.04x | 0.26 |
| OpenMP | 8 hilos | 14.471456 | 1.65x | 0.21 |
| OpenMP | 16 hilos | 22.595232 | 1.06x | 0.07 |
| OpenMP | 32 hilos | 22.884747 | 1.04x | 0.03 |
| MPI | 3 procesos | 13.822971 | 1.73x | 0.58 |
| MPI | 8 procesos | 12.14125 | 1.97x | 0.25 |
| MPI | 16 procesos | 5.481604 | 4.36x | 0.27 |
| MPI | 32 procesos | 6.383668 | 3.74x | 0.12 |
| Híbrido | 3 procs x 2 hilos | 12.390989 | 1.93x | 0.32 |
| Híbrido | 3 procs x 4 hilos | 7.138523 | 3.35x | 0.28 |
| Híbrido | 3 procs x 8 hilos | 7.877891 | 3.03x | 0.13 |
| Híbrido | 4 procs x 8 hilos | 6.300642 | 3.79x | 0.12 |
| Híbrido | 8 procs x 4 hilos | 7.259891 | 3.29x | 0.10 |
| Híbrido | 16 procs x 2 hilos | 5.283977 | 4.52x | 0.14 |

