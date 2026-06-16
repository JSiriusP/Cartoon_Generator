# Cartoon Image Generator (Sequential, OpenMP & MPI)

This repository contains a C-based image processing application that applies a "Cartoon" effect to images. The project includes three different implementations to demonstrate performance improvements through parallel computing: Sequential, Shared Memory (OpenMP), and Distributed Memory (MPI).

## Project Structure

```text
.
├── files/                      # Directory for input images and generated output images
├── includes/                   # Header files (e.g., stb_image libraries)
│   ├── stb_image.h
│   └── stb_image_write.h
├── obj/                        # Compiled object files and executables
├── Makefile                    # Build automation script
├── cartoon_sequential.c        # Standard sequential implementation
├── cartoon_shared_memory.c     # OpenMP parallelized implementation
└── MPIcartooon.c               # MPI distributed implementation
```

## Prerequisites

To compile and run this project, ensure you have the following installed on your system:

- **GCC** (GNU Compiler Collection)
- **Make**
- **OpenMPI** (For the distributed memory implementation)

## Compilation

The project includes a `Makefile` for easy compilation. Simply run the following command in the root directory:

```
make
```

This will compile all the source files and generate the respective executables (mostly located in the `obj/` directory).

## Usage

The program requires four arguments to run:

1. `<input_image_path>`: The path to the source image (e.g., `files/4601217.jpg`).
2. `<parameter>`: The intensity/radius parameter for the cartoon effect (1, 2).
3. `<posterizeRanges>`: The number of ranges for the posterization effect (1 -> 3, 2 -> 9).
4. `<output_name>`: The prefix for the generated output image (e.g., `mundo`).

## Sequential Execution

To run the standard sequential version, use the executable located in the `obj/` directory:

```
./obj/cartoon_seq_exec <input_image_path> <parameter> <posterizeRanges> <output_name>
```

## Shared Memory Execution (OpenMP)

To run the shared memory version (which automatically utilizes available CPU threads), execute:

```
./obj/cartoon_shared <input_image_path> <parameter> <posterizeRanges> <output_name> [num_hilos]
```

## Distributed Memory Execution (MPI)

To run the distributed version using MPI, use `mpirun`. You can specify the number of processes using the `-n` flag. If you are running more processes than physical cores, use the `--oversubscribe` flag:

```
mpirun -n <procces_number> --oversubscribe ./MPIcartoon <input_image_path> <parameter> <posterizeRanges> <output_name>
```

