#include "../unity/unity.h"
#include "../include/fila.h"

void setUp(void) {}

void tearDown(void) {}

/// @brief Testa a criação de uma fila vazia
void test_cria_fila(void) {
    FILA f = cria_fila();
    
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_INT(0, getTamanhoFila(f));
    
    limparFila(f);
}

/// @brief Testa o comportamento FIFO (First-In, First-Out) da Fila
void test_insercao_e_remocao_fila(void) {
    FILA f = cria_fila();

    // Inserindo elementos
    inserirFila(f, 10.0, 20.0); // Primeiro a entrar
    inserirFila(f, 30.0, 40.0); // Segundo a entrar
    
    TEST_ASSERT_EQUAL_INT(2, getTamanhoFila(f));
    
    // Verificando se o primeiro elemento está correto (sem remover)
    StrPonto p_primeiro = getPrimeiroFila(f);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 10.0, p_primeiro.x);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 20.0, p_primeiro.y);

    // Removendo elementos (FIFO: o primeiro a entrar deve ser o primeiro a sair)
    StrPonto p_removido1 = removerFila(f);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 10.0, p_removido1.x);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 20.0, p_removido1.y);
    TEST_ASSERT_EQUAL_INT(1, getTamanhoFila(f));

    StrPonto p_removido2 = removerFila(f);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 30.0, p_removido2.x);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 40.0, p_removido2.y);
    TEST_ASSERT_EQUAL_INT(0, getTamanhoFila(f));

    limparFila(f);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_cria_fila);
    RUN_TEST(test_insercao_e_remocao_fila);
    
    return UNITY_END();
}