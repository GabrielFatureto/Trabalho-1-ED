#ifndef TEXTO_H
#define TEXTO_H


/**
 * @brief Ponteiro opaco que representa a entidade Texto.
 * A estrutura interna (struct) está propositalmente oculta no arquivo .c
 * para impedir o acesso direto e garantir o encapsulamento.
 */
typedef void* TEXTO;


/**
 * @brief Instancia e aloca na memória um novo elemento de Texto.
 *
 * @param id   Identificador numérico único do texto.
 * @param x    Coordenada X (posição horizontal) no plano cartesiano.
 * @param y    Coordenada Y (posição vertical) no plano cartesiano.
 * @param corb String representando a cor da borda (stroke).
 * @param corp String representando a cor de preenchimento (fill).
 * @param a    Caractere de âncora ('i' = início, 'm' = meio, 'f' = fim).
 * @param txto String dinâmica contendo a mensagem do texto.
 * * @return     Retorna o ponteiro (TEXTO) para a estrutura recém-criada,
 * ou NULL em caso de falha na alocação de memória.
 */
TEXTO cria_texto(int id, double x, double y, char* corb, char* corp, char a, char* txto);



/** @brief Recupera o ID do texto. */
int getIdTexto(TEXTO t);

/** @brief Recupera a coordenada X da âncora do texto. */
double getXTexto(TEXTO t);

/** @brief Recupera a coordenada Y da âncora do texto. */
double getYTexto(TEXTO t);

/** @brief Recupera a cor da borda do texto. */
char* getCorbTexto(TEXTO t);

/** @brief Recupera a cor de preenchimento do texto. */
char* getCorpTexto(TEXTO t);

/** @brief Recupera o tipo de âncora do texto ('i', 'm' ou 'f'). */
char getAncoraTexto(TEXTO t);

/** @brief Recupera a string com o conteúdo textual. */
char* getStringTexto(TEXTO t);



/**
 * @brief Libera toda a memória alocada para o elemento de texto.
 * Deve ser chamado ao final do ciclo de vida da figura para evitar 
 * vazamento de memória (Memory Leak), limpando a string interna e a struct.
 *
 * @param t Ponteiro para o texto que será destruído.
 */
void limparTexto(TEXTO t);

#endif // TEXTO_H