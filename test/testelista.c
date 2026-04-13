#include "../unity/unity.h"
#include "../include/lista.h"

void setUp(void) {}

void tearDown(void) {}

/// @brief Testa a criação de uma lista vazia
void test_cria_lista(void) {
    LISTA l = cria_lista();
    
    TEST_ASSERT_NOT_NULL(l);
    TEST_ASSERT_EQUAL_INT(0, getTamanhoLista(l));
    
    limparLista(l);
}

/// @brief Testa a inserção de elementos e a iteração pela lista
void test_inserir_e_iterar_lista(void) {
    LISTA l = cria_lista();
    StrFigura fig1 = {1, 'c', {0,0}, NULL, NULL, NULL};
    StrFigura fig2 = {2, 'r', {10,10}, NULL, NULL, NULL};
    
    inserirLista(l, &fig1);
    inserirLista(l, &fig2);
    
    TEST_ASSERT_EQUAL_INT(2, getTamanhoLista(l));

    StrFigura* primeira = getPrimeiroLista(l);
    TEST_ASSERT_NOT_NULL(primeira);
    TEST_ASSERT_EQUAL_INT(1, primeira->id);

    StrFigura* segunda = getProximoLista(l, primeira);
    TEST_ASSERT_NOT_NULL(segunda);
    TEST_ASSERT_EQUAL_INT(2, segunda->id);

    limparLista(l);
}

/// @brief Testa a remoção de um elemento específico da lista
void test_remover_lista(void) {
    LISTA l = cria_lista();
    StrFigura fig1 = {1, 'c', {0,0}, NULL, NULL, NULL};
    StrFigura fig2 = {2, 'r', {10,10}, NULL, NULL, NULL};
    
    inserirLista(l, &fig1);
    inserirLista(l, &fig2);

    StrFigura* removida = removerFiguraLista(l, 1);
    
    TEST_ASSERT_NOT_NULL(removida);
    TEST_ASSERT_EQUAL_INT(1, removida->id);
    TEST_ASSERT_EQUAL_INT(1, getTamanhoLista(l));

    limparLista(l);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_cria_lista);
    RUN_TEST(test_inserir_e_iterar_lista);
    RUN_TEST(test_remover_lista);
    
    return UNITY_END();
}