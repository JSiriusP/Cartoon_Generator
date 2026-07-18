import os
import subprocess
import re

images = {
    '800x800': 'files/800x800.jpg',
    '2000x2000': 'files/2000x2000.jpg',
    '5000x5000': 'files/5000x5000.jpg'
}

radios = [1, 2] # 3x3, 5x5
posterizes = [1, 2] # 3, 9

gpu_configs = [
    (8, 64),
    (16, 256),
    (24, 576),
    (32, 1024)
]

def extract_time(output, is_gpu=False):
    if is_gpu:
        match = re.search(r'en ([0-9.]+) milisegundos', output)
        if match:
            return float(match.group(1)) / 1000.0
    else:
        match = re.search(r'en ([0-9.]+) segundos', output)
        if match:
            return float(match.group(1))
    return None

def run_cmd(cmd, is_gpu=False):
    try:
        res = subprocess.run(cmd, shell=True, capture_output=True, text=True)
        t = extract_time(res.stdout, is_gpu)
        if t is None:
            print(f"Failed to extract time from: {cmd}")
            print("STDOUT:", res.stdout)
            print("STDERR:", res.stderr)
        return t
    except Exception as e:
        print(f"Error executing {cmd}: {e}")
        return None

def compile_gpu(tile, block):
    cmd = f"nvcc -O3 -DTILE_SIZE={tile} -DBLOCK_SIZE={block} cartoon_gpu.cu -o obj/cartoon_gpu -lm"
    res = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    if res.returncode != 0:
        print(f"Failed to compile GPU with TILE_SIZE={tile}, BLOCK_SIZE={block}")
        print("STDERR:", res.stderr)
        return False
    return True

output_path = '../resultados_benchmark_gpu.md'

with open(output_path, 'w') as f:
    f.write("# Resultados del Benchmark: Secuencial vs GPU\n\n")
    f.write("Este documento compara el tiempo de ejecución y el *speedup* de la versión GPU en diferentes configuraciones de hilos frente a la versión secuencial.\n\n")
    
    for img_name, img_path in images.items():
        f.write(f"## Imagen: {img_name}\n\n")
        
        for radio in radios:
            for posterize in posterizes:
                f.write(f"### Filtro: {'3x3' if radio==1 else '5x5'}, Posterizado: {'3 rangos' if posterize==1 else '9 rangos'}\n\n")
                f.write("| Implementación | Configuración | Tiempo (s) | Speedup |\n")
                f.write("|---|---|---|---|\n")
                
                # Sequential
                cmd_seq = f"./obj/cartoon_seq_exec {img_path} {radio} {posterize} out_seq"
                t_seq = run_cmd(cmd_seq, is_gpu=False)
                f.write(f"| Secuencial | N/A | {t_seq:.6f} | 1.00x |\n" if t_seq else "| Secuencial | N/A | Error | Error |\n")
                
                if not t_seq:
                    continue
                
                # GPU for each config
                for tile, block in gpu_configs:
                    if not compile_gpu(tile, block):
                        f.write(f"| GPU (Tile {tile}) | {block} hilos | Error de Compilación | Error |\n")
                        continue
                        
                    cmd_gpu = f"./obj/cartoon_gpu {img_path} {radio} {posterize} out_gpu"
                    t_gpu = run_cmd(cmd_gpu, is_gpu=True)
                    
                    if t_gpu:
                        speedup = t_seq / t_gpu
                        f.write(f"| GPU (Tile {tile}) | {block} hilos | {t_gpu:.6f} | {speedup:.2f}x |\n")
                    else:
                        f.write(f"| GPU (Tile {tile}) | {block} hilos | Error de Ejecución | Error |\n")
                
                f.write("\n")
                f.flush()

print(f"Benchmark completado. Resultados guardados en: {output_path}")
