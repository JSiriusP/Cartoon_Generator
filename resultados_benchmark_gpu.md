# Resultados del Benchmark: Secuencial vs GPU

Este documento compara el tiempo de ejecución y el *speedup* de la versión GPU en diferentes configuraciones de hilos frente a la versión secuencial.

## Imagen: 800x800

### Filtro: 3x3, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.022458 | 1.00x |
| GPU (Tile 8) | 64 hilos | 0.000806 | 27.86x |
| GPU (Tile 16) | 256 hilos | 0.000749 | 29.98x |
| GPU (Tile 24) | 576 hilos | 0.000885 | 25.36x |
| GPU (Tile 32) | 1024 hilos | 0.000778 | 28.86x |

### Filtro: 3x3, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.022597 | 1.00x |
| GPU (Tile 8) | 64 hilos | 0.000803 | 28.12x |
| GPU (Tile 16) | 256 hilos | 0.000772 | 29.26x |
| GPU (Tile 24) | 576 hilos | 0.000902 | 25.07x |
| GPU (Tile 32) | 1024 hilos | 0.000777 | 29.09x |

### Filtro: 5x5, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.054859 | 1.00x |
| GPU (Tile 8) | 64 hilos | 0.002279 | 24.07x |
| GPU (Tile 16) | 256 hilos | 0.001580 | 34.71x |
| GPU (Tile 24) | 576 hilos | 0.001696 | 32.35x |
| GPU (Tile 32) | 1024 hilos | 0.001505 | 36.46x |

### Filtro: 5x5, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.055305 | 1.00x |
| GPU (Tile 8) | 64 hilos | 0.002243 | 24.66x |
| GPU (Tile 16) | 256 hilos | 0.001570 | 35.23x |
| GPU (Tile 24) | 576 hilos | 0.001669 | 33.13x |
| GPU (Tile 32) | 1024 hilos | 0.001500 | 36.87x |

## Imagen: 2000x2000

### Filtro: 3x3, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.138506 | 1.00x |
| GPU (Tile 8) | 64 hilos | 0.004862 | 28.49x |
| GPU (Tile 16) | 256 hilos | 0.004366 | 31.73x |
| GPU (Tile 24) | 576 hilos | 0.005789 | 23.93x |
| GPU (Tile 32) | 1024 hilos | 0.003963 | 34.95x |

### Filtro: 3x3, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.139167 | 1.00x |
| GPU (Tile 8) | 64 hilos | 0.004920 | 28.28x |
| GPU (Tile 16) | 256 hilos | 0.003849 | 36.15x |
| GPU (Tile 24) | 576 hilos | 0.004844 | 28.73x |
| GPU (Tile 32) | 1024 hilos | 0.003961 | 35.13x |

### Filtro: 5x5, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.348351 | 1.00x |
| GPU (Tile 8) | 64 hilos | 0.016063 | 21.69x |
| GPU (Tile 16) | 256 hilos | 0.009996 | 34.85x |
| GPU (Tile 24) | 576 hilos | 0.010129 | 34.39x |
| GPU (Tile 32) | 1024 hilos | 0.009128 | 38.16x |

### Filtro: 5x5, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.342613 | 1.00x |
| GPU (Tile 8) | 64 hilos | 0.016041 | 21.36x |
| GPU (Tile 16) | 256 hilos | 0.009830 | 34.86x |
| GPU (Tile 24) | 576 hilos | 0.010162 | 33.72x |
| GPU (Tile 32) | 1024 hilos | 0.008968 | 38.20x |

## Imagen: 5000x5000

### Filtro: 3x3, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.877222 | 1.00x |
| GPU (Tile 8) | 64 hilos | 0.027111 | 32.36x |
| GPU (Tile 16) | 256 hilos | 0.025208 | 34.80x |
| GPU (Tile 24) | 576 hilos | 0.031109 | 28.20x |
| GPU (Tile 32) | 1024 hilos | 0.024545 | 35.74x |

### Filtro: 3x3, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 0.899776 | 1.00x |
| GPU (Tile 8) | 64 hilos | 0.027079 | 33.23x |
| GPU (Tile 16) | 256 hilos | 0.024286 | 37.05x |
| GPU (Tile 24) | 576 hilos | 0.030964 | 29.06x |
| GPU (Tile 32) | 1024 hilos | 0.025088 | 35.87x |

### Filtro: 5x5, Posterizado: 3 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 2.154183 | 1.00x |
| GPU (Tile 8) | 64 hilos | 0.091003 | 23.67x |
| GPU (Tile 16) | 256 hilos | 0.057529 | 37.45x |
| GPU (Tile 24) | 576 hilos | 0.066418 | 32.43x |
| GPU (Tile 32) | 1024 hilos | 0.053219 | 40.48x |

### Filtro: 5x5, Posterizado: 9 rangos

| Implementación | Configuración | Tiempo (s) | Speedup |
|---|---|---|---|
| Secuencial | N/A | 2.146076 | 1.00x |
| GPU (Tile 8) | 64 hilos | 0.090005 | 23.84x |
| GPU (Tile 16) | 256 hilos | 0.057761 | 37.15x |
| GPU (Tile 24) | 576 hilos | 0.066201 | 32.42x |
| GPU (Tile 32) | 1024 hilos | 0.053592 | 40.05x |

