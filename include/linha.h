#ifndef LINHA_H
#define LINHA_H


/**
 * @brief Ponteiro opaco que representa a entidade Linha.
 */
typedef void* LINHA;


/**
 * @brief Instancia e aloca na memória um novo elemento Linha.
 *
 * @param id  Identificador numérico único da linha.
 * @param x1  Coordenada X da primeira extremidade.
 * @param y1  Coordenada Y da primeira extremidade.
 * @param x2  Coordenada X da segunda extremidade.
 * @param y2  Coordenada Y da segunda extremidade.
 * @param cor String representando a cor da linha.
 * @return    Retorna o ponteiro (LINHA) para a estrutura recém-criada,
 * ou NULL em caso de falha na alocação.
 */
LINHA cria_linha(int id, double x1, double y1, double x2, double y2, char* cor);


/** @brief Recupera o ID da linha. */
int getIdLinha(LINHA l);

/** @brief Recupera a coordenada X da primeira extremidade. */
double getX1Linha(LINHA l);

/** @brief Recupera a coordenada Y da primeira extremidade. */
double getY1Linha(LINHA l);

/** @brief Recupera a coordenada X da segunda extremidade. */
double getX2Linha(LINHA l);

/** @brief Recupera a coordenada Y da segunda extremidade. */
double getY2Linha(LINHA l);

/** @brief Recupera a cor da linha. */
char* getCorLinha(LINHA l);


/**
 * @brief Libera toda a memória alocada para o elemento linha.
 * @param l Ponteiro para a linha que será destruída.
 */
void limparLinha(LINHA l);

#endif // LINHA_H