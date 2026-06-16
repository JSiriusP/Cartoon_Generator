#!/bin/bash

# Este script se debe ejecutar desde la carpeta "scripts"
# chmod +x benchmark_cluster.sh
# ./benchmark_cluster.sh

IMAGES=("files/800.jpeg" "files/2000.jpeg" "files/5000.jpg")
RADIOS=(1 2)
POSTERIZES=(1 2)

# Configuraciones expandidas para aprovechar el clúster
# 4 nodos x 32 cores = 128 cores en total
OMP_THREADS=(2 4 8 16 32 64 128)
MPI_PROCS=(4 8 16 32 64 128)

# Configuraciones híbridas: "procesos hilos_por_proceso"
HYBRID_CONFIGS=(
    "4 8"
    "4 16"
    "4 32"
    "8 8"
    "8 16"
)

OUT_FILE="../resultados_benchmark_cluster.md"

echo "# Resultados del Benchmark en Cluster" > $OUT_FILE
echo "" >> $OUT_FILE

extract_time() {
    # Busca la expresión "en X.XXX segundos" en la salida estándar/error combinada
    echo "$1" | grep -oP 'en \K[0-9.]+(?= segundos)' | head -1
}

for img in "${IMAGES[@]}"; do
    echo "## Imagen: $img" >> $OUT_FILE
    echo "" >> $OUT_FILE

    for r in "${RADIOS[@]}"; do
        for p in "${POSTERIZES[@]}"; do
            filter_name=$([ "$r" -eq 1 ] && echo "3x3" || echo "5x5")
            post_name=$([ "$p" -eq 1 ] && echo "3 rangos" || echo "9 rangos")

            echo "### Filtro: $filter_name, Posterizado: $post_name" >> $OUT_FILE
            echo "" >> $OUT_FILE
            echo "| Implementación | Configuración | Tiempo (s) | Speedup | Eficiencia |" >> $OUT_FILE
            echo "|---|---|---|---|---|" >> $OUT_FILE

            # Secuencial
            echo "Ejecutando Secuencial $img radio=$r post=$p"
            out_seq=$(./obj/cartoon_seq_exec $img $r $p out_seq 2>&1)
            t_seq=$(extract_time "$out_seq")
            
            if [ -z "$t_seq" ]; then
                echo "| Secuencial | N/A | Error | 1.00x | 1.00 |" >> $OUT_FILE
                continue
            fi
            
            echo "| Secuencial | N/A | $t_seq | 1.00x | 1.00 |" >> $OUT_FILE

            # OpenMP
            for th in "${OMP_THREADS[@]}"; do
                echo "Ejecutando OpenMP $th hilos $img radio=$r post=$p"
                out_omp=$(./obj/cartoon_shared $img $r $p out_omp $th 2>&1)
                t_omp=$(extract_time "$out_omp")
                
                if [ -n "$t_omp" ]; then
                    speedup=$(awk "BEGIN {printf \"%.2f\", $t_seq / $t_omp}")
                    efficiency=$(awk "BEGIN {printf \"%.2f\", $speedup / $th}")
                    echo "| OpenMP | $th hilos | $t_omp | ${speedup}x | $efficiency |" >> $OUT_FILE
                else
                    echo "| OpenMP | $th hilos | Error | Error | Error |" >> $OUT_FILE
                fi
            done

            # MPI
            for pr in "${MPI_PROCS[@]}"; do
                echo "Ejecutando MPI $pr procesos $img radio=$r post=$p"
                # Usamos el machinefile de la raíz del proyecto
                out_mpi=$(mpirun -n $pr -machinefile ../machinefile ./obj/MPIcartoon $img $r $p out_mpi 2>&1)
                t_mpi=$(extract_time "$out_mpi")
                
                if [ -n "$t_mpi" ]; then
                    speedup=$(awk "BEGIN {printf \"%.2f\", $t_seq / $t_mpi}")
                    efficiency=$(awk "BEGIN {printf \"%.2f\", $speedup / $pr}")
                    echo "| MPI | $pr procesos | $t_mpi | ${speedup}x | $efficiency |" >> $OUT_FILE
                else
                    echo "| MPI | $pr procesos | Error | Error | Error |" >> $OUT_FILE
                fi
            done

            # Híbrido
            for config in "${HYBRID_CONFIGS[@]}"; do
                read pr th <<< "$config"
                echo "Ejecutando Híbrido $pr procs x $th hilos $img radio=$r post=$p"
                out_hyb=$(mpirun -n $pr -machinefile ../machinefile ./obj/cartoon_hybrid $img $r $p out_hyb $th 2>&1)
                t_hyb=$(extract_time "$out_hyb")
                
                if [ -n "$t_hyb" ]; then
                    speedup=$(awk "BEGIN {printf \"%.2f\", $t_seq / $t_hyb}")
                    total_cores=$(($pr * $th))
                    efficiency=$(awk "BEGIN {printf \"%.2f\", $speedup / $total_cores}")
                    echo "| Híbrido | $pr procs x $th hilos | $t_hyb | ${speedup}x | $efficiency |" >> $OUT_FILE
                else
                    echo "| Híbrido | $pr procs x $th hilos | Error | Error | Error |" >> $OUT_FILE
                fi
            done
            echo "" >> $OUT_FILE
        done
    done
done
echo "¡Benchmark en cluster finalizado! Resultados guardados en $OUT_FILE"
