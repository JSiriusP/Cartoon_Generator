# Resultados del Benchmark

## Imagen: 800x800

### Filtro: 3x3, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 0.301987 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 0.267195 | 1.13x | 0.57 |
| OpenMP | 4 hilos | 0.261739 | 1.15x | 0.29 |
| OpenMP | 8 hilos | 0.261934 | 1.15x | 0.14 |
| OpenMP | 16 hilos | 0.262042 | 1.15x | 0.07 |
| OpenMP | 32 hilos | 0.272949 | 1.11x | 0.03 |
| MPI | 3 procesos | 0.25624 | 1.18x | 0.39 |
| MPI | 8 procesos | 0.224576 | 1.34x | 0.17 |
| MPI | 16 procesos | 0.198748 | 1.52x | 0.09 |
| MPI | 32 procesos | 0.193907 | 1.56x | 0.05 |
| Híbrido | 3 procs x 2 hilos | 0.203023 | 1.49x | 0.25 |
| Híbrido | 3 procs x 4 hilos | 0.179971 | 1.68x | 0.14 |
| Híbrido | 3 procs x 8 hilos | 0.164229 | 1.84x | 0.08 |
| Híbrido | 4 procs x 8 hilos | 0.167661 | 1.80x | 0.06 |
| Híbrido | 8 procs x 4 hilos | 0.19117 | 1.58x | 0.05 |
| Híbrido | 16 procs x 2 hilos | 0.181443 | 1.66x | 0.05 |

### Filtro: 3x3, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 0.297789 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 0.328266 | 0.91x | 0.45 |
| OpenMP | 4 hilos | 0.283672 | 1.05x | 0.26 |
| OpenMP | 8 hilos | 0.285086 | 1.04x | 0.13 |
| OpenMP | 16 hilos | 0.283647 | 1.05x | 0.07 |
| OpenMP | 32 hilos | 0.272317 | 1.09x | 0.03 |
| MPI | 3 procesos | 0.281498 | 1.06x | 0.35 |
| MPI | 8 procesos | 0.247162 | 1.20x | 0.15 |
| MPI | 16 procesos | 0.225037 | 1.32x | 0.08 |
| MPI | 32 procesos | 0.217489 | 1.37x | 0.04 |
| Híbrido | 3 procs x 2 hilos | 0.219274 | 1.36x | 0.23 |
| Híbrido | 3 procs x 4 hilos | 0.191644 | 1.55x | 0.13 |
| Híbrido | 3 procs x 8 hilos | 0.175611 | 1.70x | 0.07 |
| Híbrido | 4 procs x 8 hilos | 0.179215 | 1.66x | 0.05 |
| Híbrido | 8 procs x 4 hilos | 0.202462 | 1.47x | 0.05 |
| Híbrido | 16 procs x 2 hilos | 0.165188 | 1.80x | 0.06 |

### Filtro: 5x5, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 0.397814 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 0.394848 | 1.01x | 0.50 |
| OpenMP | 4 hilos | 0.394964 | 1.01x | 0.25 |
| OpenMP | 8 hilos | 0.406005 | 0.98x | 0.12 |
| OpenMP | 16 hilos | 0.383862 | 1.04x | 0.06 |
| OpenMP | 32 hilos | 0.405811 | 0.98x | 0.03 |
| MPI | 3 procesos | 0.404002 | 0.98x | 0.33 |
| MPI | 8 procesos | 0.280972 | 1.42x | 0.18 |
| MPI | 16 procesos | 0.224629 | 1.77x | 0.11 |
| MPI | 32 procesos | 0.232128 | 1.71x | 0.05 |
| Híbrido | 3 procs x 2 hilos | 0.276062 | 1.44x | 0.24 |
| Híbrido | 3 procs x 4 hilos | 0.213121 | 1.87x | 0.16 |
| Híbrido | 3 procs x 8 hilos | 0.191535 | 2.08x | 0.09 |
| Híbrido | 4 procs x 8 hilos | 0.201373 | 1.98x | 0.06 |
| Híbrido | 8 procs x 4 hilos | 0.2148 | 1.85x | 0.06 |
| Híbrido | 16 procs x 2 hilos | 0.215335 | 1.85x | 0.06 |

### Filtro: 5x5, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 0.410248 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 0.38424 | 1.07x | 0.53 |
| OpenMP | 4 hilos | 0.384144 | 1.07x | 0.27 |
| OpenMP | 8 hilos | 0.384267 | 1.07x | 0.13 |
| OpenMP | 16 hilos | 0.406055 | 1.01x | 0.06 |
| OpenMP | 32 hilos | 0.395164 | 1.04x | 0.03 |
| MPI | 3 procesos | 0.393659 | 1.04x | 0.35 |
| MPI | 8 procesos | 0.282207 | 1.45x | 0.18 |
| MPI | 16 procesos | 0.22702 | 1.81x | 0.11 |
| MPI | 32 procesos | 0.232201 | 1.77x | 0.06 |
| Híbrido | 3 procs x 2 hilos | 0.285681 | 1.44x | 0.24 |
| Híbrido | 3 procs x 4 hilos | 0.21365 | 1.92x | 0.16 |
| Híbrido | 3 procs x 8 hilos | 0.203314 | 2.02x | 0.08 |
| Híbrido | 4 procs x 8 hilos | 0.202746 | 2.02x | 0.06 |
| Híbrido | 8 procs x 4 hilos | 0.202464 | 2.03x | 0.06 |
| Híbrido | 16 procs x 2 hilos | 0.198703 | 2.06x | 0.06 |

## Imagen: 2000x2000

### Filtro: 3x3, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 1.441434 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 1.339598 | 1.08x | 0.54 |
| OpenMP | 4 hilos | 1.340394 | 1.08x | 0.27 |
| OpenMP | 8 hilos | 1.339804 | 1.08x | 0.13 |
| OpenMP | 16 hilos | 1.339719 | 1.08x | 0.07 |
| OpenMP | 32 hilos | 1.338476 | 1.08x | 0.03 |
| MPI | 3 procesos | 1.358742 | 1.06x | 0.35 |
| MPI | 8 procesos | 0.923318 | 1.56x | 0.20 |
| MPI | 16 procesos | 0.828499 | 1.74x | 0.11 |
| MPI | 32 procesos | 1.00376 | 1.44x | 0.04 |
| Híbrido | 3 procs x 2 hilos | 1.03479 | 1.39x | 0.23 |
| Híbrido | 3 procs x 4 hilos | 0.847219 | 1.70x | 0.14 |
| Híbrido | 3 procs x 8 hilos | 0.752591 | 1.92x | 0.08 |
| Híbrido | 4 procs x 8 hilos | 0.812051 | 1.78x | 0.06 |
| Híbrido | 8 procs x 4 hilos | 0.778828 | 1.85x | 0.06 |
| Híbrido | 16 procs x 2 hilos | 0.778815 | 1.85x | 0.06 |

### Filtro: 3x3, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 1.510772 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 1.406297 | 1.07x | 0.54 |
| OpenMP | 4 hilos | 1.405874 | 1.07x | 0.27 |
| OpenMP | 8 hilos | 1.406725 | 1.07x | 0.13 |
| OpenMP | 16 hilos | 1.418437 | 1.07x | 0.07 |
| OpenMP | 32 hilos | 1.417058 | 1.07x | 0.03 |
| MPI | 3 procesos | 1.439318 | 1.05x | 0.35 |
| MPI | 8 procesos | 0.992044 | 1.52x | 0.19 |
| MPI | 16 procesos | 0.894943 | 1.69x | 0.11 |
| MPI | 32 procesos | 1.114817 | 1.36x | 0.04 |
| Híbrido | 3 procs x 2 hilos | 1.100019 | 1.37x | 0.23 |
| Híbrido | 3 procs x 4 hilos | 0.915643 | 1.65x | 0.14 |
| Híbrido | 3 procs x 8 hilos | 0.824828 | 1.83x | 0.08 |
| Híbrido | 4 procs x 8 hilos | 0.857177 | 1.76x | 0.06 |
| Híbrido | 8 procs x 4 hilos | 0.825466 | 1.83x | 0.06 |
| Híbrido | 16 procs x 2 hilos | 0.841704 | 1.79x | 0.06 |

### Filtro: 5x5, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 2.243352 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 2.196568 | 1.02x | 0.51 |
| OpenMP | 4 hilos | 2.195392 | 1.02x | 0.26 |
| OpenMP | 8 hilos | 2.196494 | 1.02x | 0.13 |
| OpenMP | 16 hilos | 2.195356 | 1.02x | 0.06 |
| OpenMP | 32 hilos | 2.195179 | 1.02x | 0.03 |
| MPI | 3 procesos | 2.187214 | 1.03x | 0.34 |
| MPI | 8 procesos | 1.158203 | 1.94x | 0.24 |
| MPI | 16 procesos | 0.92544 | 2.42x | 0.15 |
| MPI | 32 procesos | 1.067723 | 2.10x | 0.07 |
| Híbrido | 3 procs x 2 hilos | 1.419027 | 1.58x | 0.26 |
| Híbrido | 3 procs x 4 hilos | 1.037532 | 2.16x | 0.18 |
| Híbrido | 3 procs x 8 hilos | 0.853267 | 2.63x | 0.11 |
| Híbrido | 4 procs x 8 hilos | 0.855539 | 2.62x | 0.08 |
| Híbrido | 8 procs x 4 hilos | 0.800778 | 2.80x | 0.09 |
| Híbrido | 16 procs x 2 hilos | 0.909793 | 2.47x | 0.08 |

### Filtro: 5x5, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 2.253848 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 2.207473 | 1.02x | 0.51 |
| OpenMP | 4 hilos | 2.206545 | 1.02x | 0.26 |
| OpenMP | 8 hilos | 2.285057 | 0.99x | 0.12 |
| OpenMP | 16 hilos | 2.162358 | 1.04x | 0.07 |
| OpenMP | 32 hilos | 2.21655 | 1.02x | 0.03 |
| MPI | 3 procesos | 2.172716 | 1.04x | 0.35 |
| MPI | 8 procesos | 1.234167 | 1.83x | 0.23 |
| MPI | 16 procesos | 0.951437 | 2.37x | 0.15 |
| MPI | 32 procesos | 1.038206 | 2.17x | 0.07 |
| Híbrido | 3 procs x 2 hilos | 1.425874 | 1.58x | 0.26 |
| Híbrido | 3 procs x 4 hilos | 1.046614 | 2.15x | 0.18 |
| Híbrido | 3 procs x 8 hilos | 0.888088 | 2.54x | 0.11 |
| Híbrido | 4 procs x 8 hilos | 0.889328 | 2.53x | 0.08 |
| Híbrido | 8 procs x 4 hilos | 0.858714 | 2.62x | 0.08 |
| Híbrido | 16 procs x 2 hilos | 0.879349 | 2.56x | 0.08 |

## Imagen: 5000x5000

### Filtro: 3x3, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 9.110487 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 8.181822 | 1.11x | 0.56 |
| OpenMP | 4 hilos | 8.173508 | 1.11x | 0.28 |
| OpenMP | 8 hilos | 8.602096 | 1.06x | 0.13 |
| OpenMP | 16 hilos | 8.874222 | 1.03x | 0.06 |
| OpenMP | 32 hilos | 8.673202 | 1.05x | 0.03 |
| MPI | 3 procesos | 8.143475 | 1.12x | 0.37 |
| MPI | 8 procesos | 5.236314 | 1.74x | 0.22 |
| MPI | 16 procesos | 4.571317 | 1.99x | 0.12 |
| MPI | 32 procesos | 5.801641 | 1.57x | 0.05 |
| Híbrido | 3 procs x 2 hilos | 6.138483 | 1.48x | 0.25 |
| Híbrido | 3 procs x 4 hilos | 4.972677 | 1.83x | 0.15 |
| Híbrido | 3 procs x 8 hilos | 4.42153 | 2.06x | 0.09 |
| Híbrido | 4 procs x 8 hilos | 4.442218 | 2.05x | 0.06 |
| Híbrido | 8 procs x 4 hilos | 4.233731 | 2.15x | 0.07 |
| Híbrido | 16 procs x 2 hilos | 4.315193 | 2.11x | 0.07 |

### Filtro: 3x3, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 10.223752 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 9.303469 | 1.10x | 0.55 |
| OpenMP | 4 hilos | 9.294117 | 1.10x | 0.28 |
| OpenMP | 8 hilos | 9.626707 | 1.06x | 0.13 |
| OpenMP | 16 hilos | 9.684011 | 1.06x | 0.07 |
| OpenMP | 32 hilos | 9.727609 | 1.05x | 0.03 |
| MPI | 3 procesos | 9.683798 | 1.06x | 0.35 |
| MPI | 8 procesos | 6.361911 | 1.61x | 0.20 |
| MPI | 16 procesos | 5.776943 | 1.77x | 0.11 |
| MPI | 32 procesos | 7.042836 | 1.45x | 0.05 |
| Híbrido | 3 procs x 2 hilos | 7.296152 | 1.40x | 0.23 |
| Híbrido | 3 procs x 4 hilos | 6.054184 | 1.69x | 0.14 |
| Híbrido | 3 procs x 8 hilos | 5.496362 | 1.86x | 0.08 |
| Híbrido | 4 procs x 8 hilos | 5.56596 | 1.84x | 0.06 |
| Híbrido | 8 procs x 4 hilos | 5.312799 | 1.92x | 0.06 |
| Híbrido | 16 procs x 2 hilos | 5.491643 | 1.86x | 0.06 |

### Filtro: 5x5, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 13.798248 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 13.194396 | 1.05x | 0.52 |
| OpenMP | 4 hilos | 13.206031 | 1.04x | 0.26 |
| OpenMP | 8 hilos | 13.163794 | 1.05x | 0.13 |
| OpenMP | 16 hilos | 13.225977 | 1.04x | 0.07 |
| OpenMP | 32 hilos | 13.18571 | 1.05x | 0.03 |
| MPI | 3 procesos | 13.212348 | 1.04x | 0.35 |
| MPI | 8 procesos | 6.513229 | 2.12x | 0.26 |
| MPI | 16 procesos | 4.926443 | 2.80x | 0.18 |
| MPI | 32 procesos | 5.740116 | 2.40x | 0.08 |
| Híbrido | 3 procs x 2 hilos | 8.742038 | 1.58x | 0.26 |
| Híbrido | 3 procs x 4 hilos | 5.855753 | 2.36x | 0.20 |
| Híbrido | 3 procs x 8 hilos | 4.702978 | 2.93x | 0.12 |
| Híbrido | 4 procs x 8 hilos | 4.748632 | 2.91x | 0.09 |
| Híbrido | 8 procs x 4 hilos | 4.315156 | 3.20x | 0.10 |
| Híbrido | 16 procs x 2 hilos | 4.433721 | 3.11x | 0.10 |

### Filtro: 5x5, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |
|---|---|---|---|---|
| Secuencial | N/A | 14.26659 | 1.00x | 1.00 |
| OpenMP | 2 hilos | 13.716864 | 1.04x | 0.52 |
| OpenMP | 4 hilos | 13.680017 | 1.04x | 0.26 |
| OpenMP | 8 hilos | 13.649838 | 1.05x | 0.13 |
| OpenMP | 16 hilos | 13.708043 | 1.04x | 0.07 |
| OpenMP | 32 hilos | 13.240722 | 1.08x | 0.03 |
| MPI | 3 procesos | 13.635578 | 1.05x | 0.35 |
| MPI | 8 procesos | 7.022422 | 2.03x | 0.25 |
| MPI | 16 procesos | 5.418419 | 2.63x | 0.16 |
| MPI | 32 procesos | 6.153388 | 2.32x | 0.07 |
| Híbrido | 3 procs x 2 hilos | 9.113853 | 1.57x | 0.26 |
| Híbrido | 3 procs x 4 hilos | 6.323517 | 2.26x | 0.19 |
| Híbrido | 3 procs x 8 hilos | 5.127736 | 2.78x | 0.12 |
| Híbrido | 4 procs x 8 hilos | 5.165777 | 2.76x | 0.09 |
| Híbrido | 8 procs x 4 hilos | 4.812774 | 2.96x | 0.09 |
| Híbrido | 16 procs x 2 hilos | 4.841827 | 2.95x | 0.09 |

