#include "../unity/unity.h"
#include "../include/poligono.h"
#include "lista.h" 
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
    limparPoligono(p);
}

/// @brief Testa as funções de Set e Get do ID
void test_get_set_id(void) {
    POLIGONO p = cria_poligono();
    setIdPoligono(p, 105);
    int id_retornado = getIdPoligono(p);
    TEST_ASSERT_EQUAL_INT(105, id_retornado);
    limparPoligono(p);
}

/// @brief Testa a lógica da fila da inserção e remoção de coordenadas
void test_inserir_remover_coordenada(void) {
    POLIGONO p = cria_poligono();
    
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

/// @brief Testa o algoritmo Scanline de geração de bordas e hachuras
void test_gerar_linhas(void) {
    POLIGONO p = cria_poligono();
    LISTA l = cria_lista(); // Lista falsa para receber as linhas geradas

    // Vamos criar um polígono simples (um quadrado de 10x10)
    inserirCoordenadaPoligono(p, 0.0, 0.0);
    inserirCoordenadaPoligono(p, 10.0, 0.0);
    inserirCoordenadaPoligono(p, 10.0, 10.0);
    inserirCoordenadaPoligono(p, 0.0, 10.0);

    // Manda gerar as linhas começando com ID 1, distância de hachura = 2.0
    int prox_id = gerarLinhas(p, l, 1, 2.0, "preto", "vermelho");

    // O quadrado tem 4 bordas. Então deve ter gerado 4 linhas de borda.
    // Mais as linhas de hachura no meio. O ID retornado com certeza será maior que 1.
    TEST_ASSERT_TRUE(prox_id > 1);

    // A lista principal não pode estar vazia (tem que ter as linhas dentro dela)
    TEST_ASSERT_TRUE(getTamanhoLista(l) > 0);

    limparPoligono(p);
    limparLista(l); // Não esqueça de limpar a lista falsa
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_cria_poligono);
    RUN_TEST(test_get_set_id);
    RUN_TEST(test_inserir_remover_coordenada);
    RUN_TEST(test_gerar_linhas); // ADICIONADO: Executa o novo teste
        
    return UNITY_END();
}