#include "poligono.h"

/* --- CRIAÇÃO --- */

POLIGONO cria_poligono() {
    StrPoligono* p = (StrPoligono*) malloc(sizeof(StrPoligono));
    
    // Verifica se a memória foi alocada corretamente
    if (p != NULL) {
        p->id = -1; // Valor padrão para indicar que ainda não tem ID definido
        p->coordenadas = cria_fila(); // Inicializa a fila usando a função do fila.h
    }
    
    return p;
}


/* --- FUNÇÕES GET E SET --- */

int getIdPoligono(POLIGONO p) {
    if (p == NULL) return -1;
    StrPoligono* p_int = (StrPoligono*)p;
    return p_int->id;
}

void setIdPoligono(POLIGONO p, int novoId) {
    if (p == NULL) return;
    StrPoligono* p_int = (StrPoligono*)p;
    p_int->id = novoId;
}


/* --- OPERAÇÕES DO POLÍGONO --- */

void inserirCoordenadaPoligono(POLIGONO p, double x, double y) {
    if (p == NULL) return;
    StrPoligono* p_int = (StrPoligono*)p;
    
    // Repassa a responsabilidade de inserção para o módulo de fila
    inserirFila(p_int->coordenadas, x, y);
}

StrPonto removerCoordenadaPoligono(POLIGONO p) {
    StrPonto pontoVazio = {0.0, 0.0};
    if (p == NULL) return pontoVazio;
    
    StrPoligono* p_int = (StrPoligono*)p;
    
    // Repassa a responsabilidade de remoção para o módulo de fila
    return removerFila(p_int->coordenadas);
}

void gerarLinhas(POLIGONO p, int id_inicio, double d, char* corb, char* corp) {
    if (p == NULL) return;
    StrPoligono* p_int = (StrPoligono*)p;
    

    printf("-> Gerando bordas e hachuras para Poligono ID: %d\n", p_int->id);
    printf("   Distancia (d): %.2f | Cor Borda: %s | Cor Preenchimento: %s\n", d, corb, corp);
}


/* --- DESTRUTOR --- */

void limparPoligono(POLIGONO p) {
    if (p != NULL) {
        StrPoligono* p_int = (StrPoligono*)p;
        limparFila(p_int->coordenadas); 
        free(p_int);
    }
}