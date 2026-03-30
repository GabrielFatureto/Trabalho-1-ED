#ifndef CIRCULO_H
#define CIRCULO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Um Círculo é uma forma geométrica básica definida por uma coordenada central (âncora) e um raio. 
Neste sistema, ele armazena suas propriedades e fornece operações diretas para consulta e 
modificação de seus dados, como posição e cores (borda e preenchimento). */

typedef void* CIRCULO;


/*-------------------------------------------- ESTRUTURAS --------------------------------------------*/

/// @brief Estrutura que guarda as informações do círculo
typedef struct {
    int id;
    double x; // Coordenada X do centro (âncora)
    double y; // Coordenada Y do centro (âncora)
    double r; // Raio do círculo
    char* corb; // Cor da borda
    char* corp; // Cor do preenchimento
} StrCirculo;


/*-------------------------------------------- FUNÇÕES --------------------------------------------*/

/// @brief Cria o círculo alocando-o dinamicamente na memória
/// @param id Identificador único do círculo
/// @param x Posição x do centro do círculo
/// @param y Posição y do centro do círculo
/// @param r Raio do círculo
/// @param corb String com a cor da borda do círculo
/// @param corp String com a cor do preenchimento do círculo
/// @return Retorna o ponteiro (void*) para o círculo inicializado
CIRCULO cria_circulo(int id, double x, double y, double r, char* corb, char* corp);


/* --- FUNÇÕES GET --- */

/// @brief Função get do ID do círculo
/// @param c Círculo c
/// @return Retorna o ID do círculo
int getIdCirculo(CIRCULO c);

/// @brief Função get da coordenada X do círculo
/// @param c Círculo c
/// @return Retorna a coordenada X do centro do círculo
double getXCirculo(CIRCULO c);

/// @brief Função get da coordenada Y do círculo
/// @param c Círculo c
/// @return Retorna a coordenada Y do centro do círculo
double getYCirculo(CIRCULO c);

/// @brief Função get do raio do círculo
/// @param c Círculo c
/// @return Retorna o valor do raio do círculo
double getRaioCirculo(CIRCULO c);

/// @brief Função get da cor da borda do círculo
/// @param c Círculo c
/// @return Retorna a string contendo a cor da borda
char* getCorbCirculo(CIRCULO c);

/// @brief Função get da cor do preenchimento do círculo
/// @param c Círculo c
/// @return Retorna a string contendo a cor do preenchimento
char* getCorpCirculo(CIRCULO c);


/* --- FUNÇÕES SET --- */

/// @brief Altera o ID de um círculo existente
/// @param c Círculo c
/// @param novoId Novo ID do círculo
void setIdCirculo(CIRCULO c, int novoId);

/// @brief Altera a coordenada X do centro do círculo
/// @param c Círculo c
/// @param x Nova coordenada X
void setXCirculo(CIRCULO c, double x);

/// @brief Altera a coordenada Y do centro do círculo
/// @param c Círculo c
/// @param y Nova coordenada Y
void setYCirculo(CIRCULO c, double y);

/// @brief Altera o raio do círculo
/// @param c Círculo c
/// @param r Novo valor do raio
void setRaioCirculo(CIRCULO c, double r);

/// @brief Altera a cor da borda do círculo
/// @param c Círculo c
/// @param corb String com a nova cor da borda
void setCorbCirculo(CIRCULO c, char* corb);

/// @brief Altera a cor do preenchimento do círculo
/// @param c Círculo c
/// @param corp String com a nova cor de preenchimento
void setCorpCirculo(CIRCULO c, char* corp);


/* --- DESTRUTOR --- */

/// @brief Desaloca a memória do círculo e de suas strings internas
/// @param c Círculo c
void limparCirculo(CIRCULO c);

#endif