#ifndef POLIGONO_H
#define POLIGONO_H

#include "fila.h"  // Inclui a fila para reconhecer a StrPonto
#include "lista.h" // ADICIONADO: Necessário para a função gerarLinhas conhecer a LISTA

/* Um Polígono é uma forma geométrica construída dinamicamente através de uma fila de coordenadas (seus vértices). Neste sistema, 
ele funciona como um gerador: armazena sequencialmente os pontos de ancoragem de outras figuras e, ao ser processado,
produz um conjunto de novas linhas que formam a sua borda fechada e o seu preenchimento (hachuras). */


/*-------------------------------------------- TIPOS DE DADOS --------------------------------------------*/

typedef void* POLIGONO;

// ATENÇÃO: A struct StrPoligono foi removida daqui! 
// Ela DEVE ser declarada apenas dentro do src/poligono.c para garantir o encapsulamento.


/*-------------------------------------------- CONSTRUTOR --------------------------------------------*/

/// @brief Cria o poligono
/// @return Retorna o poligono já inicializado
POLIGONO cria_poligono();


/*-------------------------------------------- FUNÇÕES GET E SET --------------------------------------------*/

/// @brief Função get do ID do polígono
/// @param p Polígono p
/// @return Retorna o ID do polígono
int getIdPoligono(POLIGONO p);

/// @brief Altera o ID de um polígono existente
/// @param p Polígono p
/// @param novoId Novo ID do polígono
void setIdPoligono(POLIGONO p, int novoId);


/*-------------------------------------------- OPERAÇÕES DO POLÍGONO --------------------------------------------*/

/// @brief Insere uma nova coordenada na fila do polígono
/// @param p Polígono p
/// @param x Coordenada x da âncora
/// @param y Coordenada y da âncora
void inserirCoordenadaPoligono(POLIGONO p, double x, double y);

/// @brief Remove a coordenada da fila mais antiga do polígono
/// @param p Polígono p
/// @return Retorna a coordenada removida
StrPonto removerCoordenadaPoligono(POLIGONO p);

/// @brief Gera as linhas de borda e de preenchimento do polígono e as insere na lista
/// @param p Polígono p
/// @param l Lista principal do sistema onde as linhas geradas serão armazenadas
/// @param id_inicio identificador inicial para as linhas criadas
/// @param d Distância entre as linhas de preenchimento do polígono
/// @param corb Cor da borda do polígono
/// @param corp Cor do preenchimento do polígono
/// @return Retorna o próximo ID livre após a criação de todas as linhas
int gerarLinhas(POLIGONO p, LISTA l, int id_inicio, double d, char* corb, char* corp);


/*-------------------------------------------- DESTRUTOR --------------------------------------------*/

/// @brief Esvazia a fila de coordenadas do polígono e desaloca sua memória
/// @param p Poligono p
void limparPoligono(POLIGONO p);

#endif