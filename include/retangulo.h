#ifndef RETANGULO_H
#define RETANGULO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Um Retângulo é uma forma geométrica básica definida por uma coordenada de âncora 
(nesse caso o canto superior esquerdo), uma largura (w) e uma altura (h). 
Este arquivo define sua estrutura e as operações para encapsular, acessar 
e modificar seus dados e propriedades visuais de forma segura. */

typedef void* RETANGULO;


/*-------------------------------------------- ESTRUTURAS --------------------------------------------*/

/// @brief Estrutura que guarda as informações do retângulo
typedef struct {
    int id;
    double x; // Coordenada X da âncora (canto superior esquerdo)
    double y; // Coordenada Y da âncora (canto superior esquerdo)
    double w; // Largura (width) do retângulo
    double h; // Altura (height) do retângulo
    char* corb; // Cor da borda
    char* corp; // Cor do preenchimento
} StrRetangulo;


/*-------------------------------------------- FUNÇÕES --------------------------------------------*/

/// @brief Cria o retângulo alocando-o dinamicamente na memória
/// @param id Identificador único do retângulo
/// @param x Posição x da âncora do retângulo
/// @param y Posição y da âncora do retângulo
/// @param w Largura do retângulo
/// @param h Altura do retângulo
/// @param corb String com a cor da borda do retângulo
/// @param corp String com a cor do preenchimento do retângulo
/// @return Retorna o ponteiro (void*) para o retângulo inicializado
RETANGULO cria_retangulo(int id, double x, double y, double w, double h, char* corb, char* corp);


/* --- FUNÇÕES GET --- */

/// @brief Função get do ID do retângulo
/// @param r Retângulo r
/// @return Retorna o ID do retângulo
int getIdRetangulo(RETANGULO r);

/// @brief Função get da coordenada X da âncora do retângulo
/// @param r Retângulo r
/// @return Retorna a coordenada X do retângulo
double getXRetangulo(RETANGULO r);

/// @brief Função get da coordenada Y da âncora do retângulo
/// @param r Retângulo r
/// @return Retorna a coordenada Y do retângulo
double getYRetangulo(RETANGULO r);

/// @brief Função get da largura do retângulo
/// @param r Retângulo r
/// @return Retorna a largura (w) do retângulo
double getWRetangulo(RETANGULO r);

/// @brief Função get da altura do retângulo
/// @param r Retângulo r
/// @return Retorna a altura (h) do retângulo
double getHRetangulo(RETANGULO r);

/// @brief Função get da cor da borda do retângulo
/// @param r Retângulo r
/// @return Retorna a string contendo a cor da borda
char* getCorbRetangulo(RETANGULO r);

/// @brief Função get da cor do preenchimento do retângulo
/// @param r Retângulo r
/// @return Retorna a string contendo a cor do preenchimento
char* getCorpRetangulo(RETANGULO r);


/* --- FUNÇÕES SET --- */

/// @brief Altera o ID do retângulo
/// @param r Retângulo r
/// @param novoId Novo ID do retângulo
void setIdRetangulo(RETANGULO r, int novoId);

/// @brief Altera a coordenada X da âncora do retângulo
/// @param r Retângulo r
/// @param x Nova coordenada X
void setXRetangulo(RETANGULO r, double x);

/// @brief Altera a coordenada Y da âncora do retângulo
/// @param r Retângulo r
/// @param y Nova coordenada Y
void setYRetangulo(RETANGULO r, double y);

/// @brief Altera a largura do retângulo
/// @param r Retângulo r
/// @param w Nova largura
void setWRetangulo(RETANGULO r, double w);

/// @brief Altera a altura do retângulo
/// @param r Retângulo r
/// @param h Nova altura
void setHRetangulo(RETANGULO r, double h);

/// @brief Altera a cor da borda do retângulo
/// @param r Retângulo r
/// @param corb String com a nova cor da borda
void setCorbRetangulo(RETANGULO r, char* corb);

/// @brief Altera a cor do preenchimento do retângulo
/// @param r Retângulo r
/// @param corp String com a nova cor de preenchimento
void setCorpRetangulo(RETANGULO r, char* corp);


/* --- DESTRUTOR --- */

/// @brief Desaloca a memória do retângulo e de suas strings internas
/// @param r Retângulo r
void limparRetangulo(RETANGULO r);

#endif