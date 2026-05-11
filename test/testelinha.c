#include "../unity/unity.h"
#include "../include/linha.h"
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

void test_cria_linha_e_gets(void) {
    LINHA l = cria_linha(15, 10.5, 20.0, 50.5, 80.0, "vermelho");
    
    TEST_ASSERT_NOT_NULL(l);
    TEST_ASSERT_EQUAL_INT(15, getIdLinha(l));
    
    TEST_ASSERT_FLOAT_WITHIN(0.001, 10.5, getX1Linha(l));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 20.0, getY1Linha(l));
    
    TEST_ASSERT_FLOAT_WITHIN(0.001, 50.5, getX2Linha(l));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 80.0, getY2Linha(l));
    
    TEST_ASSERT_EQUAL_STRING("vermelho", getCorLinha(l));
    
    limparLinha(l);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_cria_linha_e_gets);
    return UNITY_END();
}