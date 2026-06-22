# Resultados del Benchmark

## Imagen: 800x800

### Filtro: 3x3, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 0.042527 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 0.031362 | 1.36x | 0.68 |
| OpenMP | 4 hilos | 0.027727 | 1.53x | 0.38 |
| OpenMP | 8 hilos | 0.025433 | 1.67x | 0.21 |
| MPI | 3 procesos | 0.044951 | 0.95x | 0.32 |
| MPI | 5 procesos | 0.032854 | 1.29x | 0.26 |
| MPI | 8 procesos | 0.032832 | 1.30x | 0.16 |
| Híbrido | 3 procs x 2 hilos | 0.03452 | 1.23x | 0.21 |
| Híbrido | 3 procs x 4 hilos | 0.030153 | 1.41x | 0.12 |
| Híbrido | 5 procs x 2 hilos | 0.031019 | 1.37x | 0.14 |

### Filtro: 3x3, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 0.046782 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 0.034669 | 1.35x | 0.67 |
| OpenMP | 4 hilos | 0.031081 | 1.51x | 0.38 |
| OpenMP | 8 hilos | 0.031063 | 1.51x | 0.19 |
| MPI | 3 procesos | 0.047001 | 1.00x | 0.33 |
| MPI | 5 procesos | 0.041577 | 1.13x | 0.23 |
| MPI | 8 procesos | 0.038084 | 1.23x | 0.15 |
| Híbrido | 3 procs x 2 hilos | 0.038921 | 1.20x | 0.20 |
| Híbrido | 3 procs x 4 hilos | 0.036766 | 1.27x | 0.11 |
| Híbrido | 5 procs x 2 hilos | 0.033152 | 1.41x | 0.14 |

### Filtro: 5x5, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 0.071812 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 0.046894 | 1.53x | 0.77 |
| OpenMP | 4 hilos | 0.033098 | 2.17x | 0.54 |
| OpenMP | 8 hilos | 0.030576 | 2.35x | 0.29 |
| MPI | 3 procesos | 0.072535 | 0.99x | 0.33 |
| MPI | 5 procesos | 0.058333 | 1.23x | 0.25 |
| MPI | 8 procesos | 0.047599 | 1.51x | 0.19 |
| Híbrido | 3 procs x 2 hilos | 0.047248 | 1.52x | 0.25 |
| Híbrido | 3 procs x 4 hilos | 0.035982 | 2.00x | 0.17 |
| Híbrido | 5 procs x 2 hilos | 0.046585 | 1.54x | 0.15 |

### Filtro: 5x5, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 0.073413 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 0.045987 | 1.60x | 0.80 |
| OpenMP | 4 hilos | 0.034386 | 2.13x | 0.53 |
| OpenMP | 8 hilos | 0.033072 | 2.22x | 0.28 |
| MPI | 3 procesos | 0.074844 | 0.98x | 0.33 |
| MPI | 5 procesos | 0.047768 | 1.54x | 0.31 |
| MPI | 8 procesos | 0.048304 | 1.52x | 0.19 |
| Híbrido | 3 procs x 2 hilos | 0.048716 | 1.51x | 0.25 |
| Híbrido | 3 procs x 4 hilos | 0.037248 | 1.97x | 0.16 |
| Híbrido | 5 procs x 2 hilos | 0.043735 | 1.68x | 0.17 |

## Imagen: 2000x2000

### Filtro: 3x3, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 0.27777 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 0.205229 | 1.35x | 0.68 |
| OpenMP | 4 hilos | 0.184175 | 1.51x | 0.38 |
| OpenMP | 8 hilos | 0.18097 | 1.53x | 0.19 |
| MPI | 3 procesos | 0.280328 | 0.99x | 0.33 |
| MPI | 5 procesos | 0.212619 | 1.31x | 0.26 |
| MPI | 8 procesos | 0.221789 | 1.25x | 0.16 |
| Híbrido | 3 procs x 2 hilos | 0.218256 | 1.27x | 0.21 |
| Híbrido | 3 procs x 4 hilos | 0.197936 | 1.40x | 0.12 |
| Híbrido | 5 procs x 2 hilos | 0.222713 | 1.25x | 0.12 |

### Filtro: 3x3, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 0.301939 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 0.231656 | 1.30x | 0.65 |
| OpenMP | 4 hilos | 0.207734 | 1.45x | 0.36 |
| OpenMP | 8 hilos | 0.207351 | 1.46x | 0.18 |
| MPI | 3 procesos | 0.293474 | 1.03x | 0.34 |
| MPI | 5 procesos | 0.236697 | 1.28x | 0.26 |
| MPI | 8 procesos | 0.248046 | 1.22x | 0.15 |
| Híbrido | 3 procs x 2 hilos | 0.24652 | 1.22x | 0.20 |
| Híbrido | 3 procs x 4 hilos | 0.223492 | 1.35x | 0.11 |
| Híbrido | 5 procs x 2 hilos | 0.237793 | 1.27x | 0.13 |

### Filtro: 5x5, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 0.479544 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 0.339489 | 1.41x | 0.71 |
| OpenMP | 4 hilos | 0.234109 | 2.05x | 0.51 |
| OpenMP | 8 hilos | 0.212295 | 2.26x | 0.28 |
| MPI | 3 procesos | 0.480418 | 1.00x | 0.33 |
| MPI | 5 procesos | 0.314962 | 1.52x | 0.30 |
| MPI | 8 procesos | 0.302863 | 1.58x | 0.20 |
| Híbrido | 3 procs x 2 hilos | 0.317815 | 1.51x | 0.25 |
| Híbrido | 3 procs x 4 hilos | 0.237288 | 2.02x | 0.17 |
| Híbrido | 5 procs x 2 hilos | 0.297681 | 1.61x | 0.16 |

### Filtro: 5x5, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 0.49963 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 0.313003 | 1.60x | 0.80 |
| OpenMP | 4 hilos | 0.238354 | 2.10x | 0.52 |
| OpenMP | 8 hilos | 0.216019 | 2.31x | 0.29 |
| MPI | 3 procesos | 0.480294 | 1.04x | 0.35 |
| MPI | 5 procesos | 0.327332 | 1.53x | 0.31 |
| MPI | 8 procesos | 0.323347 | 1.55x | 0.19 |
| Híbrido | 3 procs x 2 hilos | 0.32135 | 1.55x | 0.26 |
| Híbrido | 3 procs x 4 hilos | 0.246585 | 2.03x | 0.17 |
| Híbrido | 5 procs x 2 hilos | 0.285254 | 1.75x | 0.18 |

## Imagen: 5000x5000

### Filtro: 3x3, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 1.76925 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 1.319163 | 1.34x | 0.67 |
| OpenMP | 4 hilos | 1.167855 | 1.51x | 0.38 |
| OpenMP | 8 hilos | 1.135942 | 1.56x | 0.19 |
| MPI | 3 procesos | 1.806589 | 0.98x | 0.33 |
| MPI | 5 procesos | 1.437784 | 1.23x | 0.25 |
| MPI | 8 procesos | 1.40116 | 1.26x | 0.16 |
| Híbrido | 3 procs x 2 hilos | 1.477695 | 1.20x | 0.20 |
| Híbrido | 3 procs x 4 hilos | 1.281903 | 1.38x | 0.12 |
| Híbrido | 5 procs x 2 hilos | 1.30222 | 1.36x | 0.14 |

### Filtro: 3x3, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 2.112818 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 1.66797 | 1.27x | 0.63 |
| OpenMP | 4 hilos | 1.551476 | 1.36x | 0.34 |
| OpenMP | 8 hilos | 1.516416 | 1.39x | 0.17 |
| MPI | 3 procesos | 2.212137 | 0.96x | 0.32 |
| MPI | 5 procesos | 1.787184 | 1.18x | 0.24 |
| MPI | 8 procesos | 1.848007 | 1.14x | 0.14 |
| Híbrido | 3 procs x 2 hilos | 1.861072 | 1.14x | 0.19 |
| Híbrido | 3 procs x 4 hilos | 1.67768 | 1.26x | 0.10 |
| Híbrido | 5 procs x 2 hilos | 1.720934 | 1.23x | 0.12 |

### Filtro: 5x5, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 2.93404 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 1.865455 | 1.57x | 0.79 |
| OpenMP | 4 hilos | 1.374766 | 2.13x | 0.53 |
| OpenMP | 8 hilos | 1.272795 | 2.31x | 0.29 |
| MPI | 3 procesos | 2.973555 | 0.99x | 0.33 |
| MPI | 5 procesos | 1.940531 | 1.51x | 0.30 |
| MPI | 8 procesos | 1.641788 | 1.79x | 0.22 |
| Híbrido | 3 procs x 2 hilos | 1.981681 | 1.48x | 0.25 |
| Híbrido | 3 procs x 4 hilos | 1.479992 | 1.98x | 0.17 |
| Híbrido | 5 procs x 2 hilos | 1.666687 | 1.76x | 0.18 |

### Filtro: 5x5, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 3.190601 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 2.076153 | 1.54x | 0.77 |
| OpenMP | 4 hilos | 1.56375 | 2.04x | 0.51 |
| OpenMP | 8 hilos | 1.47489 | 2.16x | 0.27 |
| MPI | 3 procesos | 3.16021 | 1.01x | 0.34 |
| MPI | 5 procesos | 2.113526 | 1.51x | 0.30 |
| MPI | 8 procesos | 2.410893 | 1.32x | 0.17 |
| Híbrido | 3 procs x 2 hilos | 2.167753 | 1.47x | 0.25 |
| Híbrido | 3 procs x 4 hilos | 1.649706 | 1.93x | 0.16 |
| Híbrido | 5 procs x 2 hilos | 1.856617 | 1.72x | 0.17 |

