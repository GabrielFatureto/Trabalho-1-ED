#ifndef POLIGONO_H
#define POLIGONO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Um Polígono é... */

typedef void* Ponto;
typedef void* POLIGONO;


/*-------------------------------------------- ESTRUTURAS --------------------------------------------*/

/// @brief Estrutura que representa uma coordenada bidimensional
typedef struct {
    double x;
    double y;
} StrPonto;


/// @brief Estrutura que representa uma figura geométrica
typedef struct {
    int id;
    char tipo;
    StrPonto ancora;
    char* corb;
    char* corp;
} StrFigura;


/// @brief Nó da fila que armazena os vértices do polígono
typedef struct NoFila {
    StrPonto ponto;
    struct NoFila* prox;
} NoFila;


/// @brief Nó da lista que armazena as figuras selecionadas
typedef struct NoLista {
    StrFigura* figura; 
    struct NoLista* prox;
} NoLista;


/// @brief Estrutura para controle da fila de coordenadas do polígono
typedef struct {
    NoFila* inicio;
    NoFila* fim;
    int tamanho;
} StrFila;


/// @brief Estrutura da lista que guarda as figuras selecionadas
typedef struct {
    NoLista* inicio;
    int tamanho;
} ListaSelecionadas;


/// @brief Estrutura que guarda as informações do polígono
typedef struct {
    int id;
    StrFila* coordenadas;
} StrPoligono;


/*-------------------------------------------- FUNÇÕES --------------------------------------------*/


/// @brief Cria o poligono
/// @return Retorna o poligono já inicializado
POLIGONO cria_poligono();

/// @brief Função get do ID do polígono
/// @param p Polígono p
/// @return Retorna o ID do polígono
int getIdPoligono(POLIGONO* p);

/// @brief Altera o ID de um polígono existente
/// @param p Ponteiro para o polígono p
/// @param novoId Novo ID do polígono
void setIdPoligono(POLIGONO* p, int novoId);

/// @brief Insere uma nova coordenada na fila do polígono
/// @param p Ponteiro para o polígono p
/// @param x Coordenada x da âncora
/// @param y Coordenada y da âncora
void inserirCoordenada(POLIGONO* p, double x, double y);

/// @brief Remove a coordenada da fila mais antiga do polígono
/// @param p Ponteiro para o poligono p
/// @return Retorna a coordenada removida
StrPonto removerCoordenada(POLIGONO* p);

/// @brief Esvazia a fila de coordenadas do polígono
/// @param p Poligono p
void limparPoligono(POLIGONO p);

/// @brief Gera as linhas de borda e de preenchimento do polígono
/// @param p Ponteiro para o polígono p
/// @param id_inicio identificador inicial para as linhas criadas
/// @param d Distância entre as linhas de preenchimento do polígono
/// @param corb Cor da borda do polígono
/// @param corp Cor do preenchimento do polígono
void gerarLinhas(POLIGONO* p, int id_inicio, double d, char* corb, char* corp);

/// @brief Inicializa e aloca a estrutura da lista de figuras selecionadas
/// @return Retorna o ponteiro para a nova lista de formas selecionadas
ListaSelecionadas* criarListaSelecionadas();

/// @brief Seleciona as figuras contidas totalmente no retângulo especificado
/// @param lista Ponteiro para a lista de selecionadas
/// @param x Posição x do canto superior esquerdo da região de seleção (âncora)
/// @param y Posição y do canto superior esquerdo da região de seleção (âncora)
/// @param w Largura da região de seleção
/// @param h Altura da região de seleção
void sel_selecionarFiguras(ListaSelecionadas* lista, double x, double y, double w, double h);

/// @brief Exclui do sistema todas as figuras que estão atualmente selecionadas
/// @param lista Ponteiro para a lista de selecionadas
void dels_removerSelecionadas(ListaSelecionadas* lista);

/// @brief Modifica a posição e as cores das figuras selecionadas
/// @param lista Ponteiro para a lista de selecionadas
/// @param dx Valor de deslocamento no eixo x
/// @param dy Valor de deslocamento no eixo y
/// @param corb Nova cor da borda
/// @param corp Nova cor de preenchimento
void mcs_modificarSelecionadas(ListaSelecionadas* lista, double dx, double dy, char* corb, char* corp);


#endif