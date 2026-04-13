#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include "fila.h" 

/* Uma Lista é uma estrutura de dados linear e dinâmica. 
Neste sistema, ela funciona para armazenar o conjunto de figuras geométricas 
criadas ou selecionadas, permitindo iteração e manipulação em massa. */

typedef void* LISTA;
typedef void* ITEM; // Usado para representar qualquer forma geométrica (CIRCULO, RETANGULO, etc.)


/*-------------------------------------------- ESTRUTURAS --------------------------------------------*/

/// @brief Estrutura unificada que representa uma figura geométrica no sistema
typedef struct {
    int id;
    char tipo; // Ex: 'c' para círculo, 'r' para retângulo, 'p' para polígono
    StrPonto ancora; // Posição base da figura
    char* corb;
    char* corp;
    ITEM forma; // Ponteiro genérico para a estrutura real (CIRCULO, RETANGULO, etc.)
} StrFigura;

/// @brief Nó interno da lista
typedef struct NoLista {
    StrFigura* figura; 
    struct NoLista* prox;
} NoLista;

/// @brief Estrutura de controle da lista
typedef struct {
    NoLista* inicio;
    NoLista* fim; // Adicionado 'fim' para otimizar inserções no final (opcional, mas recomendado)
    int tamanho;
} StrLista;


/*-------------------------------------------- FUNÇÕES --------------------------------------------*/

/// @brief Inicializa e aloca a estrutura da lista
/// @return Retorna o ponteiro (void*) para a nova lista
LISTA cria_lista();


/* --- FUNÇÕES GET  --- */

/// @brief Retorna a quantidade de figuras armazenadas na lista
/// @param l Lista l
/// @return Inteiro representando o tamanho
int getTamanhoLista(LISTA l);

/// @brief Retorna o primeiro nó da lista para iniciar uma iteração
/// @param l Lista l
/// @return Ponteiro para a primeira StrFigura armazenada
StrFigura* getPrimeiroLista(LISTA l);

/// @brief Retorna o próximo elemento da lista a partir de um elemento atual
/// @param l Lista l
/// @param atual Ponteiro para a figura atual na iteração
/// @return Ponteiro para a próxima StrFigura, ou NULL se for o fim da lista
StrFigura* getProximoLista(LISTA l, StrFigura* atual);


/* --- FUNÇÕES SET --- */

/// @brief Insere uma nova figura na lista
/// @param l Lista l
/// @param figura Ponteiro para a estrutura StrFigura pré-alocada
void inserirLista(LISTA l, StrFigura* figura);

/// @brief Remove uma figura específica da lista (pelo seu ID)
/// @param l Lista l
/// @param id Identificador da figura a ser removida
/// @return Retorna o ponteiro da figura removida (para que você possa desalocá-la depois)
StrFigura* removerFiguraLista(LISTA l, int id);


/* --- DESTRUTOR --- */

/// @brief Esvazia a lista, removendo os nós (não desaloca as figuras em si, apenas os nós da lista)
/// @param l Lista l
void limparLista(LISTA l);

#endif