#include "../unity/unity.h"
#include "../include/poligono.h"
#include <stdio.h>

void setUp(void) {
    // Pode deixar vazio se não precisar inicializar nada globalmente antes de cada teste
}

void tearDown(void) {
    // Pode deixar vazio se não precisar limpar nada globalmente após cada teste
}

void test_cria_poligono(void) {
    POLIGONO p = cria_poligono();
    
    TEST_ASSERT_NOT_NULL(p);
    
    limparPoligono(p); // Importante liberar a memória ao fim do teste
}

/// @brief Testa as funções de Set e Get do ID
void test_get_set_id(void) {
    POLIGONO p = cria_poligono();
    
    // CORREÇÃO: Passando 'p' direto em vez de '&p'
    setIdPoligono(p, 105);
    
    int id_retornado = getIdPoligono(p);
    
    TEST_ASSERT_EQUAL_INT(105, id_retornado);
    
    limparPoligono(p);
}

/// @brief Testa a lógica da fila da inserção e remoção de coordenadas
void test_inserir_remover_coordenada(void) {
    POLIGONO p = cria_poligono();
    
    // CORREÇÃO: Nomes atualizados das funções e passando 'p' sem o '&'
    inserirCoordenadaPoligono(p, 10.5, 20.1); 
    inserirCoordenadaPoligono(p, 30.0, 40.8); 
    
    StrPonto p1 = removerCoordenadaPoligono(p);
    
    TEST_ASSERT_FLOAT_WITHIN(0.001, 10.5, p1.x);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 20.1, p1.y);
    
    StrPonto p2 = removerCoordenadaPoligono(p);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 30.0, p2.x);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 40.8, p2.y);
    
    limparPoligono(p);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_cria_poligono);
    RUN_TEST(test_get_set_id);
    RUN_TEST(test_inserir_remover_coordenada);
        
    return UNITY_END();
}