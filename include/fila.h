#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>

/* Uma Fila é uma estrutura de dados FIFO (First In, First Out). 
Neste sistema, ela é especializada em armazenar dinamicamente 
uma sequência de coordenadas bidimensionais (StrPonto). */

typedef void* FILA;


/*-------------------------------------------- ESTRUTURAS --------------------------------------------*/

/// @brief Estrutura que representa uma coordenada bidimensional
typedef struct {
    double x;
    double y;
} StrPonto;

/// @brief Nó interno da fila (exposto aqui caso precise de acesso direto, mas o ideal é uso opaco)
typedef struct NoFila {
    StrPonto ponto;
    struct NoFila* prox;
} NoFila;

/// @brief Estrutura de controle da fila
typedef struct {
    NoFila* inicio;
    NoFila* fim;
    int tamanho;
} StrFila;


/*-------------------------------------------- FUNÇÕES --------------------------------------------*/

/// @brief Inicializa e aloca a estrutura da fila
/// @return Retorna o ponteiro (void*) para a fila recém-criada
FILA cria_fila();


/* --- FUNÇÕES GET (CONSULTAS) --- */

/// @brief Retorna a quantidade de coordenadas atualmente na fila
/// @param f Fila f
/// @return Inteiro representando o tamanho da fila
int getTamanhoFila(FILA f);

/// @brief Consulta o primeiro ponto da fila sem removê-lo
/// @param f Fila f
/// @return Cópia da primeira coordenada (StrPonto)
StrPonto getPrimeiroFila(FILA f);


/* --- FUNÇÕES SET (MODIFICADORES) --- */

/// @brief Insere uma nova coordenada no final da fila
/// @param f Fila f
/// @param x Coordenada X
/// @param y Coordenada Y
void inserirFila(FILA f, double x, double y);

/// @brief Remove e retorna a coordenada do início da fila (mais antiga)
/// @param f Fila f
/// @return Estrutura StrPonto contendo a coordenada removida
StrPonto removerFila(FILA f);


/* --- DESTRUTOR --- */

/// @brief Esvazia a fila e desaloca todos os nós da memória
/// @param f Fila f
void limparFila(FILA f);

#endif