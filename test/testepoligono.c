#include "../unity/unity.h"
#include "../include/poligono.h"
#include <stdio.h>

void setUp(void) {
    
}


void tearDown(void) {
    
}

void test_cria_poligono(void) {
    POLIGONO p = cria_poligono();
    
    TEST_ASSERT_NOT_NULL(p);
}


/// @brief Testa as funções de Set e Get do ID
void test_get_set_id(void) {
    POLIGONO p = cria_poligono();
    
    setIdPoligono(&p, 105);
    
    int id_retornado = getIdPoligono(&p);
    
    TEST_ASSERT_EQUAL_INT(105, id_retornado);
}


/// @brief Testa a lógica da fila da inserção e remoção de coordenadas
void test_inserir_remover_coordenada(void) {
    POLIGONO p = cria_poligono();
    
    inserirCoordenada(&p, 10.5, 20.1); 
    inserirCoordenada(&p, 30.0, 40.8); 
    
    StrPonto p1 = removerCoordenada(&p);
    
    
    TEST_ASSERT_FLOAT_WITHIN(0.001, 10.5, p1.x);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 20.1, p1.y);
    
    StrPonto p2 = removerCoordenada(&p);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 30.0, p2.x);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 40.8, p2.y);
}


/// @brief Testa a criação da lista de selecionadas
void test_criar_lista_selecionadas(void) {
    ListaSelecionadas* lista = criarListaSelecionadas();
    TEST_ASSERT_NOT_NULL(lista);
}



int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_cria_poligono);
    RUN_TEST(test_get_set_id);
    RUN_TEST(test_inserir_remover_coordenada);
    RUN_TEST(test_criar_lista_selecionadas);
    
    return UNITY_END();
}