#include "../unity/unity.h"
#include "../include/retangulo.h"
#include <string.h>

void setUp(void) {
    // Inicializações globais para os testes de retângulo, se necessário
}

void tearDown(void) {
    // Limpeza global pós-testes, se necessário
}

/// @brief Testa a criação do retângulo e as funções de Get
void test_cria_retangulo_e_gets(void) {
    RETANGULO r = cria_retangulo(10, 0.0, 0.0, 100.0, 50.0, "azul", "verde");
    
    TEST_ASSERT_NOT_NULL(r);
    TEST_ASSERT_EQUAL_INT(10, getIdRetangulo(r));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 100.0, getWRetangulo(r));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 50.0, getHRetangulo(r));
    TEST_ASSERT_EQUAL_STRING("azul", getCorbRetangulo(r));
    
    limparRetangulo(r);
}

/// @brief Testa as funções de Set do retângulo
void test_sets_retangulo(void) {
    RETANGULO r = cria_retangulo(10, 0.0, 0.0, 100.0, 50.0, "azul", "verde");
    
    setWRetangulo(r, 200.0);
    setCorpRetangulo(r, "amarelo");

    TEST_ASSERT_FLOAT_WITHIN(0.001, 200.0, getWRetangulo(r));
    TEST_ASSERT_EQUAL_STRING("amarelo", getCorpRetangulo(r));

    limparRetangulo(r);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_cria_retangulo_e_gets);
    RUN_TEST(test_sets_retangulo);
    
    return UNITY_END();
}