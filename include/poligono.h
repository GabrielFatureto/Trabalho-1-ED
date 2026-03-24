#ifndef POLIGONO_H
#define POLIGONO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Um Polígono é... */

typedef void* Ponto;
typedef void* POLIGONO;


typedef struct {
    double x;
    double y;
} StrPonto;


/// @brief 
typedef struct {
    int id;
    StrPonto ancora;
    char* corb;
    char* corp;
} StrFigura;


/// @brief 
typedef struct NoFila {
    StrPonto ponto;
    struct NoFila* prox;
} NoFila;


/// @brief 
typedef struct NoLista {
    StrFigura* figura; 
    struct NoLista* prox;
} NoLista;


/// @brief 
typedef struct {
    NoFila* inicio;
    NoFila* fim;
    int tamanho;
} StrFila;


/// @brief 
typedef struct {
    NoLista* inicio;
    int tamanho;
} ListaSelecionadas;


/// @brief 
typedef struct {
    int id;
    StrFila* coordenadas;
} StrPoligono;




/// @brief Cria o poligono
/// @return Retorna o poligono já inicializado
POLIGONO cria_poligono();


int getIdPoligono(POLIGONO* p);


void setIdPoligono(POLIGONO* p, int novoId);


void inserirCoordenada(POLIGONO* p, double x, double y);


StrPonto removerCoordenada(POLIGONO* p);


void limparPoligono(POLIGONO p);


void gerarLinhas(POLIGONO* p, int id_inicio, double d, char* corb, char* corp);


ListaSelecionadas* criarListaSelecionadas();


void sel_selecionarFiguras(ListaSelecionadas* lista, double x, double y, double w, double h);


void dels_removerSelecionadas(ListaSelecionadas* lista);


void mcs_modificarSelecionadas(ListaSelecionadas* lista, double dx, double dy, char* corb, char* corp);


#endif