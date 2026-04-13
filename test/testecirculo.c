#include "../unity/unity.h"
#include "../include/circulo.h" 
#include <stdio.h>
#include <string.h>

void setUp(void) {
}

void tearDown(void) {
}

/// @brief Testa a criação do círculo e as funções de Get
void test_cria_circulo_e_gets(void) {
    CIRCULO c = cria_circulo(1, 10.5, 20.0, 5.0, "preto", "branco");
    
    TEST_ASSERT_NOT_NULL(c);
    
    // Testes de Get
    TEST_ASSERT_EQUAL_INT(1, getIdCirculo(c));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 10.5, getXCirculo(c));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 20.0, getYCirculo(c));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 5.0, getRaioCirculo(c));
    TEST_ASSERT_EQUAL_STRING("preto", getCorbCirculo(c));
    TEST_ASSERT_EQUAL_STRING("branco", getCorpCirculo(c));
    
    limparCirculo(c);
}

/// @brief Testa as funções de Set do círculo
void test_sets_circulo(void) {
    CIRCULO c = cria_circulo(1, 10.5, 20.0, 5.0, "preto", "branco");
    
    setIdCirculo(c, 2);
    setXCirculo(c, 15.0);
    setCorbCirculo(c, "vermelho");
    
    TEST_ASSERT_EQUAL_INT(2, getIdCirculo(c));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 15.0, getXCirculo(c));
    TEST_ASSERT_EQUAL_STRING("vermelho", getCorbCirculo(c));
    
    limparCirculo(c);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_cria_circulo_e_gets);
    RUN_TEST(test_sets_circulo);
    
    return UNITY_END();
}