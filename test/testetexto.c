#include "../unity/unity.h"
#include "../include/texto.h"
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

void test_cria_texto_e_gets(void) {
    char* conteudo = "Exemplo de Texto do Projeto";
    TEXTO t = cria_texto(50, 100.5, 200.5, "preto", "azul", 'm', conteudo);
    
    TEST_ASSERT_NOT_NULL(t);
    TEST_ASSERT_EQUAL_INT(50, getIdTexto(t));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 100.5, getXTexto(t));
    TEST_ASSERT_EQUAL_STRING("preto", getCorbTexto(t));
    TEST_ASSERT_EQUAL_INT('m', getAncoraTexto(t));
    
    // Verifica se a string foi copiada corretamente
    TEST_ASSERT_EQUAL_STRING(conteudo, getStringTexto(t));
    
    limparTexto(t);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_cria_texto_e_gets);
    return UNITY_END();
}