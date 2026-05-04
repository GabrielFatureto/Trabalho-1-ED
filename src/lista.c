#include "lista.h"

/// @brief Nó interno da lista
typedef struct NoLista {
    StrFigura* figura; 
    struct NoLista* prox;
} NoLista;

/// @brief Estrutura de controle da lista
typedef struct {
    NoLista* inicio;
    NoLista* fim; 
    int tamanho;
} StrLista;

LISTA cria_lista() {
    StrLista* l = (StrLista*) malloc(sizeof(StrLista));
    if (l != NULL) {
        l->inicio = NULL;
        l->fim = NULL;
        l->tamanho = 0;
    }
    return l;
}

int getTamanhoLista(LISTA l) {
    return ((StrLista*)l)->tamanho;
}

StrFigura* getPrimeiroLista(LISTA l) {
    StrLista* l_int = (StrLista*)l;
    if (l_int->inicio != NULL) {
        return l_int->inicio->figura;
    }
    return NULL;
}

StrFigura* getProximoLista(LISTA l, StrFigura* atual) {
    StrLista* l_int = (StrLista*)l;
    NoLista* aux = l_int->inicio;
    
    while (aux != NULL) {
        if (aux->figura == atual) {
            if (aux->prox != NULL) return aux->prox->figura;
            return NULL;
        }
        aux = aux->prox;
    }
    return NULL;
}

void inserirLista(LISTA l, StrFigura* figura) {
    StrLista* l_int = (StrLista*)l;
    NoLista* novo = (NoLista*) malloc(sizeof(NoLista));
    novo->figura = figura;
    novo->prox = NULL;

    if (l_int->inicio == NULL) {
        l_int->inicio = novo;
    } else {
        l_int->fim->prox = novo;
    }
    l_int->fim = novo;
    l_int->tamanho++;
}

StrFigura* removerFiguraLista(LISTA l, int id) {
    StrLista* l_int = (StrLista*)l;
    NoLista* ant = NULL;
    NoLista* aux = l_int->inicio;
    
    while (aux != NULL && aux->figura->id != id) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) return NULL; // Não achou

    if (ant == NULL) { // É o primeiro
        l_int->inicio = aux->prox;
    } else {
        ant->prox = aux->prox;
    }
    
    if (aux == l_int->fim) { // É o último
        l_int->fim = ant;
    }

    StrFigura* fig_removida = aux->figura;
    free(aux);
    l_int->tamanho--;
    
    return fig_removida;
}

void limparLista(LISTA l) {
    if (l != NULL) {
        StrLista* l_int = (StrLista*)l;
        NoLista* aux = l_int->inicio;
        while (aux != NULL) {
            NoLista* temp = aux;
            aux = aux->prox;
            
            free(temp); 
        }
        free(l_int);
    }
}

void destruirLista(LISTA l) {
    if (l == NULL) return;
    
    StrLista* lista = (StrLista*) l;
    NoLista* atual = lista->inicio;
    
    while (atual != NULL) {
        NoLista* proximo = atual->prox;
        free(atual); 
        atual = proximo;
    }
    
    free(lista); 
}