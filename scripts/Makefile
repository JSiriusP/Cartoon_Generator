# Compiladores
CC = gcc
MPICC = mpicc

# Flags de compilacion
CFLAGS = -Wall -O3
# OpenMP para memoria compartida
OMPFLAGS = -fopenmp
# Enlace para la biblioteca de mates
LDFLAGS = -lm

# Directorio para binarios y ejecutables
OBJ_DIR = obj

# Nombres de los ejecutables (se guardan en obj)
EXEC_SEQ = $(OBJ_DIR)/cartoon_seq_exec
EXEC_SHARED = $(OBJ_DIR)/cartoon_shared
EXEC_MPI = $(OBJ_DIR)/MPIcartoon

# Por defecto, compila todos
all: $(EXEC_SEQ) $(EXEC_SHARED) $(EXEC_MPI)

# Creación del directorio si no existe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# ---- Compilación Sequential ----
$(OBJ_DIR)/cartoon_sequential.o: cartoon_sequential.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC_SEQ): $(OBJ_DIR)/cartoon_sequential.o | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# ---- Compilación Shared Memory (OpenMP) ----
$(OBJ_DIR)/cartoon_shared_memory.o: cartoon_shared_memory.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OMPFLAGS) -c $< -o $@

$(EXEC_SHARED): $(OBJ_DIR)/cartoon_shared_memory.o | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OMPFLAGS) $< -o $@ $(LDFLAGS)

# ---- Compilación MPI ----
$(OBJ_DIR)/MPIcartooon.o: MPIcartooon.c | $(OBJ_DIR)
	$(MPICC) $(CFLAGS) -c $< -o $@

$(EXEC_MPI): $(OBJ_DIR)/MPIcartooon.o | $(OBJ_DIR)
	$(MPICC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Limpiar los archivos generados (.o y ejecutables)
clean:
	rm -rf $(OBJ_DIR)

.PHONY: all clean
