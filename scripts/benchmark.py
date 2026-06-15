import os
import subprocess
import re

images = {
    '800x800': 'files/800.jpeg',
    '2000x2000': 'files/2000.jpeg',
    '5000x5000': 'files/5000.jpg'
}

radios = [1, 2] # 3x3, 5x5
posterizes = [1, 2] # 3, 9

# Configs for parallel execution
omp_threads = [2, 4, 8]
mpi_procs = [3, 5, 8]
# hybrid configs (procs, threads_per_proc)
hybrid_configs = [(3, 2), (3, 4), (5, 2)]

def extract_time(output):
    match = re.search(r'en ([0-9.]+) segundos', output)
    if match:
        return float(match.group(1))
    return None

def run_cmd(cmd):
    try:
        # Some outputs might go to stderr or stdout, combine them
        res = subprocess.run(cmd, shell=True, capture_output=True, text=True)
        t = extract_time(res.stdout)
        if t is None:
            print(f"Failed to extract time from: {cmd}")
            print("STDOUT:", res.stdout)
            print("STDERR:", res.stderr)
        return t
    except Exception as e:
        print(f"Error executing {cmd}: {e}")
        return None

with open('../resultados_benchmark.md', 'w') as f:
    f.write("# Resultados del Benchmark\n\n")
    
    for img_name, img_path in images.items():
        f.write(f"## Imagen: {img_name}\n\n")
        
        for radio in radios:
            for posterize in posterizes:
                f.write(f"### Filtro: {'3x3' if radio==1 else '5x5'}, Posterizado: {'3 rangos' if posterize==1 else '9 rangos'}\n\n")
                
                f.write("| Implementación | Configuración | Tiempo (s) | Speedup |\n")
                f.write("|---|---|---|---|\n")
                
                # Sequential
                cmd_seq = f"./obj/cartoon_seq_exec {img_path} {radio} {posterize} out_seq"
                t_seq = run_cmd(cmd_seq)
                f.write(f"| Secuencial | N/A | {t_seq if t_seq else 'Error'} | 1.0 |\n")
                
                if not t_seq:
                    continue
                    
                # OpenMP
                for th in omp_threads:
                    cmd_omp = f"./obj/cartoon_shared {img_path} {radio} {posterize} out_omp {th}"
                    t_omp = run_cmd(cmd_omp)
                    speedup = f"{t_seq/t_omp:.2f}x" if t_omp else "Error"
                    f.write(f"| OpenMP | {th} hilos | {t_omp if t_omp else 'Error'} | {speedup} |\n")
                
                # MPI
                for pr in mpi_procs:
                    cmd_mpi = f"mpirun -n {pr} --oversubscribe ./obj/MPIcartoon {img_path} {radio} {posterize} out_mpi"
                    t_mpi = run_cmd(cmd_mpi)
                    speedup = f"{t_seq/t_mpi:.2f}x" if t_mpi else "Error"
                    f.write(f"| MPI | {pr} procesos | {t_mpi if t_mpi else 'Error'} | {speedup} |\n")
                
                # Hybrid
                for pr, th in hybrid_configs:
                    cmd_hyb = f"mpirun -n {pr} --oversubscribe ./obj/cartoon_hybrid {img_path} {radio} {posterize} out_hyb {th}"
                    t_hyb = run_cmd(cmd_hyb)
                    speedup = f"{t_seq/t_hyb:.2f}x" if t_hyb else "Error"
                    f.write(f"| Híbrido | {pr} procs x {th} hilos | {t_hyb if t_hyb else 'Error'} | {speedup} |\n")
                
                f.write("\n")
                f.flush()
