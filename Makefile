# =========================================================
# Makefile - Projeto TED (Estrutura de Dados 1)
# =========================================================

# Compilador e Flags
CC = gcc
CFLAGS = -std=c99 -fstack-protector-all -Wall -Wextra -g -I./include -I./unity
LDFLAGS = -lm

# Diretórios baseados na sua imagem
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
TEST_DIR = test
UNITY_DIR = unity

# Nome do executável principal
EXEC = ted

# Coleta todos os arquivos .c do diretório src/
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Objeto do framework Unity
UNITY_SRC = $(UNITY_DIR)/unity.c
UNITY_OBJ = $(OBJ_DIR)/unity.o

# =========================================================
# TARGETS DO PROGRAMA PRINCIPAL
# =========================================================

all: cria_pastas $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

cria_pastas:
	@mkdir -p $(OBJ_DIR)

# =========================================================
# TARGETS DE TESTE UNITÁRIO
# =========================================================

$(UNITY_OBJ): $(UNITY_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

test_circulo: cria_pastas $(UNITY_OBJ) $(OBJ_DIR)/circulo.o
	$(CC) $(CFLAGS) $(TEST_DIR)/testecirculo.c $(OBJ_DIR)/circulo.o $(UNITY_OBJ) -o $(OBJ_DIR)/test_circulo $(LDFLAGS)
	./$(OBJ_DIR)/test_circulo

test_retangulo: cria_pastas $(UNITY_OBJ) $(OBJ_DIR)/retangulo.o
	$(CC) $(CFLAGS) $(TEST_DIR)/testeretangulo.c $(OBJ_DIR)/retangulo.o $(UNITY_OBJ) -o $(OBJ_DIR)/test_retangulo $(LDFLAGS)
	./$(OBJ_DIR)/test_retangulo

test_lista: cria_pastas $(UNITY_OBJ) $(OBJ_DIR)/lista.o
	$(CC) $(CFLAGS) $(TEST_DIR)/testelista.c $(OBJ_DIR)/lista.o $(UNITY_OBJ) -o $(OBJ_DIR)/test_lista $(LDFLAGS)
	./$(OBJ_DIR)/test_lista

test_fila: cria_pastas $(UNITY_OBJ) $(OBJ_DIR)/fila.o
	$(CC) $(CFLAGS) $(TEST_DIR)/testefila.c $(OBJ_DIR)/fila.o $(UNITY_OBJ) -o $(OBJ_DIR)/test_fila $(LDFLAGS)
	./$(OBJ_DIR)/test_fila

test_poligono: cria_pastas $(UNITY_OBJ) $(OBJ_DIR)/poligono.o
	$(CC) $(CFLAGS) $(TEST_DIR)/testepoligono.c $(OBJ_DIR)/poligono.o $(UNITY_OBJ) -o $(OBJ_DIR)/test_poligono $(LDFLAGS)
	./$(OBJ_DIR)/test_poligono

# Target para rodar todos
testes: test_circulo test_retangulo test_lista test_fila test_poligono

# =========================================================
# UTILITÁRIOS
# =========================================================

clean:
	rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/test_* $(EXEC)