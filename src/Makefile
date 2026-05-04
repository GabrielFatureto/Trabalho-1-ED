# =========================================================
# Makefile - Projeto TED (Estrutura de Dados 1)
# =========================================================

CC = gcc

CFLAGS = -std=c99 -fstack-protector-all -Wall -Wextra -g -I./include
LDFLAGS = -lm

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
TEST_DIR = test
UNITY_DIR = unity

EXEC = ted

# Coleta TODOS os arquivos de src (incluindo main.c e svg.c)
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Transforma a lista de .c em .o na pasta obj
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Configuração específica para o Unity (usado apenas nos testes)
UNITY_SRC = $(UNITY_DIR)/unity.c
UNITY_OBJ = $(OBJ_DIR)/unity.o
CFLAGS_TEST = $(CFLAGS) -I./unity

# =========================================================
# TARGETS DO PROGRAMA PRINCIPAL
# =========================================================

# O "all" agora garante que as pastas existam e compila o ted
all: cria_pastas $(EXEC)

# Linkagem final do executável principal
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Regra genérica para compilar qualquer .c de src/ para .o em obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

cria_pastas:
	@mkdir -p $(OBJ_DIR)

# =========================================================
# TARGETS DE TESTE UNITÁRIO
# =========================================================

# Compila o framework Unity
$(UNITY_OBJ): $(UNITY_SRC)
	$(CC) $(CFLAGS_TEST) -c $< -o $@

# Regras de testes (Note que elas NÃO usam o $(OBJS) completo, 
# para não incluir o main.o e dar conflito)

test_circulo: cria_pastas $(UNITY_OBJ) $(OBJ_DIR)/circulo.o
	$(CC) $(CFLAGS_TEST) $(TEST_DIR)/testecirculo.c $(OBJ_DIR)/circulo.o $(UNITY_OBJ) -o $(OBJ_DIR)/test_circulo $(LDFLAGS)
	./$(OBJ_DIR)/test_circulo

test_retangulo: cria_pastas $(UNITY_OBJ) $(OBJ_DIR)/retangulo.o
	$(CC) $(CFLAGS_TEST) $(TEST_DIR)/testeretangulo.c $(OBJ_DIR)/retangulo.o $(UNITY_OBJ) -o $(OBJ_DIR)/test_retangulo $(LDFLAGS)
	./$(OBJ_DIR)/test_retangulo

test_lista: cria_pastas $(UNITY_OBJ) $(OBJ_DIR)/lista.o $(OBJ_DIR)/fila.o
	$(CC) $(CFLAGS_TEST) $(TEST_DIR)/testelista.c $(OBJ_DIR)/lista.o $(OBJ_DIR)/fila.o $(UNITY_OBJ) -o $(OBJ_DIR)/test_lista $(LDFLAGS)
	./$(OBJ_DIR)/test_lista

test_fila: cria_pastas $(UNITY_OBJ) $(OBJ_DIR)/fila.o
	$(CC) $(CFLAGS_TEST) $(TEST_DIR)/testefila.c $(OBJ_DIR)/fila.o $(UNITY_OBJ) -o $(OBJ_DIR)/test_fila $(LDFLAGS)
	./$(OBJ_DIR)/test_fila

test_poligono: cria_pastas $(UNITY_OBJ) $(OBJ_DIR)/poligono.o $(OBJ_DIR)/fila.o $(OBJ_DIR)/lista.o $(OBJ_DIR)/linha.o
	$(CC) $(CFLAGS_TEST) $(TEST_DIR)/testepoligono.c $(OBJ_DIR)/poligono.o $(OBJ_DIR)/fila.o $(OBJ_DIR)/lista.o $(OBJ_DIR)/linha.o $(UNITY_OBJ) -o $(OBJ_DIR)/test_poligono $(LDFLAGS)
	./$(OBJ_DIR)/test_poligono

test_texto: cria_pastas $(UNITY_OBJ) $(OBJ_DIR)/texto.o
	$(CC) $(CFLAGS_TEST) $(TEST_DIR)/testetexto.c $(OBJ_DIR)/texto.o $(UNITY_OBJ) -o $(OBJ_DIR)/test_texto $(LDFLAGS)
	./$(OBJ_DIR)/test_texto

test_linha: cria_pastas $(UNITY_OBJ) $(OBJ_DIR)/linha.o
	$(CC) $(CFLAGS_TEST) $(TEST_DIR)/testelinha.c $(OBJ_DIR)/linha.o $(UNITY_OBJ) -o $(OBJ_DIR)/test_linha $(LDFLAGS)
	./$(OBJ_DIR)/test_linha

testes: test_circulo test_retangulo test_lista test_fila test_poligono test_texto test_linha

# =========================================================
# UTILITÁRIOS
# =========================================================

clean:
	rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/test_* $(EXEC)