# Cartoon Image Generator (Sequential, OpenMP, MPI & Hybrid)

This repository contains a C-based image processing application that applies a "Cartoon" effect to images. The project includes four different implementations to demonstrate performance improvements through parallel computing: Sequential, Shared Memory (OpenMP), Distributed Memory (MPI), and a Hybrid approach (MPI + OpenMP).

## Project Structure

```text
.
├── scripts/                    # Directory containing source code and build files
│   ├── files/                  # Directory for input images and generated output images
│   ├── includes/               # Header files (e.g., stb_image libraries)
│   ├── obj/                    # Compiled object files and executables
│   ├── Makefile                # Build automation script
│   ├── cartoon_sequential.c    # Standard sequential implementation
│   ├── cartoon_shared_memory.c # OpenMP parallelized implementation
│   ├── MPIcartooon.c           # MPI distributed implementation
│   └── hibrido.c               # Hybrid (MPI + OpenMP) implementation
├── benchmark/                  # Benchmark scripts and results
├── latexReport/                # LaTeX source for the project report
├── machinefile                 # Configuration for MPI execution
└── README.md                   # This documentation file
```

## Prerequisites

To compile and run this project, ensure you have the following installed on your system:

- **GCC** (GNU Compiler Collection)
- **Make**
- **OpenMPI** (For the distributed memory and hybrid implementations)

## Compilation

The project includes a `Makefile` for easy compilation inside the `scripts` directory. Simply navigate to the directory and run the following command:

```bash
cd scripts
make
```

This will compile all the source files and generate the respective executables located in the `scripts/obj/` directory.

## Usage

The program requires four arguments to run. **Note**: Make sure to run the executables from the `scripts` directory.

1. `<input_image_path>`: The path to the source image (e.g., `files/4601217.jpg`).
2. `<parameter>`: The intensity/radius parameter for the cartoon effect (1, 2).
3. `<posterizeRanges>`: The number of ranges for the posterization effect (1 -> 3, 2 -> 9).
4. `<output_name>`: The prefix for the generated output image (e.g., `mundo`).

## Sequential Execution

To run the standard sequential version, use the executable located in the `obj/` directory:

```bash
./obj/cartoon_seq_exec <input_image_path> <parameter> <posterizeRanges> <output_name>
```

## Shared Memory Execution (OpenMP)

To run the shared memory version (which automatically utilizes available CPU threads), execute:

```bash
./obj/cartoon_shared <input_image_path> <parameter> <posterizeRanges> <output_name> [num_hilos]
```

## Distributed Memory Execution (MPI)

To run the distributed version using MPI, use `mpirun`. You can specify the number of processes using the `-n` flag. If you are running more processes than physical cores, use the `--oversubscribe` flag:

```bash
mpirun -n <process_number> --oversubscribe ./obj/MPIcartoon <input_image_path> <parameter> <posterizeRanges> <output_name>
```

## Hybrid Execution (MPI + OpenMP)

To run the hybrid version, you can specify both the number of MPI processes and the number of OpenMP threads per process by adding the thread count as the final argument:

```bash
mpirun -n <process_number> --oversubscribe ./obj/cartoon_hybrid <input_image_path> <parameter> <posterizeRanges> <output_name> <num_hilos>
```
