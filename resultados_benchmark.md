# Resultados del Benchmark

## Imagen: 800x800

### Filtro: 3x3, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.054289 | 1.0 |
| OpenMP | 2 hilos | 0.033556 | 1.62x |
| OpenMP | 4 hilos | 0.026586 | 2.04x |
| OpenMP | 8 hilos | 0.029277 | 1.85x |
| MPI | 3 procesos | 0.043554 | 1.25x |
| MPI | 5 procesos | 0.038322 | 1.42x |
| MPI | 8 procesos | 0.034783 | 1.56x |
| Híbrido | 3 procs x 2 hilos | 0.035251 | 1.54x |
| Híbrido | 3 procs x 4 hilos | 0.03206 | 1.69x |
| Híbrido | 5 procs x 2 hilos | 0.031376 | 1.73x |

### Filtro: 3x3, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.046316 | 1.0 |
| OpenMP | 2 hilos | 0.035791 | 1.29x |
| OpenMP | 4 hilos | 0.031957 | 1.45x |
| OpenMP | 8 hilos | 0.031535 | 1.47x |
| MPI | 3 procesos | 0.050121 | 0.92x |
| MPI | 5 procesos | 0.043908 | 1.05x |
| MPI | 8 procesos | 0.038055 | 1.22x |
| Híbrido | 3 procs x 2 hilos | 0.041981 | 1.10x |
| Híbrido | 3 procs x 4 hilos | 0.038174 | 1.21x |
| Híbrido | 5 procs x 2 hilos | 0.037914 | 1.22x |

### Filtro: 5x5, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.079919 | 1.0 |
| OpenMP | 2 hilos | 0.045961 | 1.74x |
| OpenMP | 4 hilos | 0.038071 | 2.10x |
| OpenMP | 8 hilos | 0.031973 | 2.50x |
| MPI | 3 procesos | 0.075681 | 1.06x |
| MPI | 5 procesos | 0.051545 | 1.55x |
| MPI | 8 procesos | 0.049076 | 1.63x |
| Híbrido | 3 procs x 2 hilos | 0.04945 | 1.62x |
| Híbrido | 3 procs x 4 hilos | 0.03862 | 2.07x |
| Híbrido | 5 procs x 2 hilos | 0.040119 | 1.99x |

### Filtro: 5x5, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.074377 | 1.0 |
| OpenMP | 2 hilos | 0.046958 | 1.58x |
| OpenMP | 4 hilos | 0.035275 | 2.11x |
| OpenMP | 8 hilos | 0.037525 | 1.98x |
| MPI | 3 procesos | 0.077002 | 0.97x |
| MPI | 5 procesos | 0.057961 | 1.28x |
| MPI | 8 procesos | 0.056891 | 1.31x |
| Híbrido | 3 procs x 2 hilos | 0.051423 | 1.45x |
| Híbrido | 3 procs x 4 hilos | 0.039025 | 1.91x |
| Híbrido | 5 procs x 2 hilos | 0.0438 | 1.70x |

## Imagen: 2000x2000

### Filtro: 3x3, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.284814 | 1.0 |
| OpenMP | 2 hilos | 0.215849 | 1.32x |
| OpenMP | 4 hilos | 0.188211 | 1.51x |
| OpenMP | 8 hilos | 0.181637 | 1.57x |
| MPI | 3 procesos | 0.301682 | 0.94x |
| MPI | 5 procesos | 0.237813 | 1.20x |
| MPI | 8 procesos | 0.236057 | 1.21x |
| Híbrido | 3 procs x 2 hilos | 0.242795 | 1.17x |
| Híbrido | 3 procs x 4 hilos | 0.21601 | 1.32x |
| Híbrido | 5 procs x 2 hilos | 0.230042 | 1.24x |

### Filtro: 3x3, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.326423 | 1.0 |
| OpenMP | 2 hilos | 0.243269 | 1.34x |
| OpenMP | 4 hilos | 0.214906 | 1.52x |
| OpenMP | 8 hilos | 0.208322 | 1.57x |
| MPI | 3 procesos | 0.334602 | 0.98x |
| MPI | 5 procesos | 0.259402 | 1.26x |
| MPI | 8 procesos | 0.256452 | 1.27x |
| Híbrido | 3 procs x 2 hilos | 0.269841 | 1.21x |
| Híbrido | 3 procs x 4 hilos | 0.242898 | 1.34x |
| Híbrido | 5 procs x 2 hilos | 0.243364 | 1.34x |

### Filtro: 5x5, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.491696 | 1.0 |
| OpenMP | 2 hilos | 0.334638 | 1.47x |
| OpenMP | 4 hilos | 0.243819 | 2.02x |
| OpenMP | 8 hilos | 0.233533 | 2.11x |
| MPI | 3 procesos | 0.523379 | 0.94x |
| MPI | 5 procesos | 0.364256 | 1.35x |
| MPI | 8 procesos | 0.384831 | 1.28x |
| Híbrido | 3 procs x 2 hilos | 0.358059 | 1.37x |
| Híbrido | 3 procs x 4 hilos | 0.26687 | 1.84x |
| Híbrido | 5 procs x 2 hilos | 0.30215 | 1.63x |

### Filtro: 5x5, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.489304 | 1.0 |
| OpenMP | 2 hilos | 0.329085 | 1.49x |
| OpenMP | 4 hilos | 0.249309 | 1.96x |
| OpenMP | 8 hilos | 0.231196 | 2.12x |
| MPI | 3 procesos | 0.516048 | 0.95x |
| MPI | 5 procesos | 0.348145 | 1.41x |
| MPI | 8 procesos | 0.346519 | 1.41x |
| Híbrido | 3 procs x 2 hilos | 0.372018 | 1.32x |
| Híbrido | 3 procs x 4 hilos | 0.277287 | 1.76x |
| Híbrido | 5 procs x 2 hilos | 0.307949 | 1.59x |

## Imagen: 5000x5000

### Filtro: 3x3, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 1.834665 | 1.0 |
| OpenMP | 2 hilos | 1.398105 | 1.31x |
| OpenMP | 4 hilos | 1.205045 | 1.52x |
| OpenMP | 8 hilos | 1.176139 | 1.56x |
| MPI | 3 procesos | 1.928666 | 0.95x |
| MPI | 5 procesos | 1.497794 | 1.22x |
| MPI | 8 procesos | 1.388397 | 1.32x |
| Híbrido | 3 procs x 2 hilos | 1.617702 | 1.13x |
| Híbrido | 3 procs x 4 hilos | 1.386392 | 1.32x |
| Híbrido | 5 procs x 2 hilos | 1.401919 | 1.31x |

### Filtro: 3x3, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 2.203701 | 1.0 |
| OpenMP | 2 hilos | 1.73266 | 1.27x |
| OpenMP | 4 hilos | 1.565604 | 1.41x |
| OpenMP | 8 hilos | 1.516434 | 1.45x |
| MPI | 3 procesos | 2.267583 | 0.97x |
| MPI | 5 procesos | 1.865874 | 1.18x |
| MPI | 8 procesos | 1.847066 | 1.19x |
| Híbrido | 3 procs x 2 hilos | 1.91157 | 1.15x |
| Híbrido | 3 procs x 4 hilos | 1.766196 | 1.25x |
| Híbrido | 5 procs x 2 hilos | 1.796769 | 1.23x |

### Filtro: 5x5, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 3.087318 | 1.0 |
| OpenMP | 2 hilos | 1.952649 | 1.58x |
| OpenMP | 4 hilos | 1.411642 | 2.19x |
| OpenMP | 8 hilos | 1.295445 | 2.38x |
| MPI | 3 procesos | 3.148946 | 0.98x |
| MPI | 5 procesos | 2.188853 | 1.41x |
| MPI | 8 procesos | 2.025268 | 1.52x |
| Híbrido | 3 procs x 2 hilos | 2.161752 | 1.43x |
| Híbrido | 3 procs x 4 hilos | 1.618131 | 1.91x |
| Híbrido | 5 procs x 2 hilos | 1.800573 | 1.71x |

### Filtro: 5x5, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 3.147885 | 1.0 |
| OpenMP | 2 hilos | 2.049599 | 1.54x |
| OpenMP | 4 hilos | 1.563944 | 2.01x |
| OpenMP | 8 hilos | 1.463538 | 2.15x |
| MPI | 3 procesos | 3.223402 | 0.98x |
| MPI | 5 procesos | 2.218345 | 1.42x |
| MPI | 8 procesos | 2.128488 | 1.48x |
| Híbrido | 3 procs x 2 hilos | 2.22642 | 1.41x |
| Híbrido | 3 procs x 4 hilos | 1.722915 | 1.83x |
| Híbrido | 5 procs x 2 hilos | 2.022566 | 1.56x |

