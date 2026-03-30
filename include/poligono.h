#ifndef POLIGONO_H
#define POLIGONO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h" // Inclui a fila para reconhecer a estrutura FILA e a StrPonto

/* Um Polígono é uma forma geométrica construída dinamicamente através de uma fila de coordenadas (seus vértices). Neste sistema, 
ele funciona como um gerador: armazena sequencialmente os pontos de ancoragem de outras figuras e, ao ser processado,
produz um conjunto de novas linhas que formam a sua borda fechada e o seu preenchimento (hachuras). */

typedef void* POLIGONO;


/*-------------------------------------------- ESTRUTURAS --------------------------------------------*/

/// @brief Estrutura que guarda as informações do polígono
typedef struct {
    int id;
    FILA coordenadas; // O Polígono agora usa o tipo genérico FILA importado do fila.h
} StrPoligono;


/*-------------------------------------------- FUNÇÕES --------------------------------------------*/

/// @brief Cria o poligono
/// @return Retorna o poligono já inicializado
POLIGONO cria_poligono();


/* --- FUNÇÕES GET --- */

/// @brief Função get do ID do polígono
/// @param p Polígono p
/// @return Retorna o ID do polígono
int getIdPoligono(POLIGONO p);


/* --- FUNÇÕES SET --- */

/// @brief Altera o ID de um polígono existente
/// @param p Polígono p
/// @param novoId Novo ID do polígono
void setIdPoligono(POLIGONO p, int novoId);


/* --- OPERAÇÕES DO POLÍGONO --- */

/// @brief Insere uma nova coordenada na fila do polígono
/// @param p Polígono p
/// @param x Coordenada x da âncora
/// @param y Coordenada y da âncora
void inserirCoordenadaPoligono(POLIGONO p, double x, double y);

/// @brief Remove a coordenada da fila mais antiga do polígono
/// @param p Polígono p
/// @return Retorna a coordenada removida
StrPonto removerCoordenadaPoligono(POLIGONO p);

/// @brief Gera as linhas de borda e de preenchimento do polígono
/// @param p Polígono p
/// @param id_inicio identificador inicial para as linhas criadas
/// @param d Distância entre as linhas de preenchimento do polígono
/// @param corb Cor da borda do polígono
/// @param corp Cor do preenchimento do polígono
void gerarLinhas(POLIGONO p, int id_inicio, double d, char* corb, char* corp);


/* --- DESTRUTOR --- */

/// @brief Esvazia a fila de coordenadas do polígono e desaloca sua memória
/// @param p Poligono p
void limparPoligono(POLIGONO p);

#endif