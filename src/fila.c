#include "fila.h"

FILA cria_fila() {
    StrFila* f = (StrFila*) malloc(sizeof(StrFila));
    if (f != NULL) {
        f->inicio = NULL;
        f->fim = NULL;
        f->tamanho = 0;
    }
    return f;
}

int getTamanhoFila(FILA f) {
    return ((StrFila*)f)->tamanho;
}

StrPonto getPrimeiroFila(FILA f) {
    StrFila* f_int = (StrFila*)f;
    StrPonto p = {0, 0};
    if (f_int->inicio != NULL) {
        p = f_int->inicio->ponto;
    }
    return p;
}

void inserirFila(FILA f, double x, double y) {
    StrFila* f_int = (StrFila*)f;
    NoFila* novo = (NoFila*) malloc(sizeof(NoFila));
    
    novo->ponto.x = x;
    novo->ponto.y = y;
    novo->prox = NULL;

    if (f_int->inicio == NULL) {
        f_int->inicio = novo;
    } else {
        f_int->fim->prox = novo;
    }
    f_int->fim = novo;
    f_int->tamanho++;
}

StrPonto removerFila(FILA f) {
    StrFila* f_int = (StrFila*)f;
    StrPonto p = {0, 0};

    if (f_int->inicio != NULL) {
        NoFila* temp = f_int->inicio;
        p = temp->ponto;
        
        f_int->inicio = temp->prox;
        if (f_int->inicio == NULL) {
            f_int->fim = NULL;
        }
        
        free(temp);
        f_int->tamanho--;
    }
    return p;
}

void limparFila(FILA f) {
    if (f != NULL) {
        StrFila* f_int = (StrFila*)f;
        while (f_int->inicio != NULL) {
            removerFila(f);
        }
        free(f_int);
    }
}