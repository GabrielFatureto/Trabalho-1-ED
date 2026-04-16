#include <stdlib.h>
#include <string.h>
#include "texto.h"

typedef struct texto {
    int id;
    double x;
    double y;
    char corb[30];
    char corp[30];
    char ancora;
    char* txto; // Alocado dinamicamente
} StructTexto;

TEXTO cria_texto(int id, double x, double y, char* corb, char* corp, char a, char* txto) {
    StructTexto* t = (StructTexto*) malloc(sizeof(StructTexto));
    if (t == NULL) return NULL;

    t->id = id;
    t->x = x;
    t->y = y;
    t->ancora = a;
    strcpy(t->corb, corb);
    strcpy(t->corp, corp);

    // Aloca espaço exato para a string + caractere nulo
    t->txto = (char*) malloc((strlen(txto) + 1) * sizeof(char));
    if (t->txto != NULL) {
        strcpy(t->txto, txto);
    }

    return (TEXTO) t;
}

int getIdTexto(TEXTO t) {
    return ((StructTexto*)t)->id;
}

double getXTexto(TEXTO t) {
    return ((StructTexto*)t)->x;
}

double getYTexto(TEXTO t) {
    return ((StructTexto*)t)->y;
}

char* getCorbTexto(TEXTO t) {
    return ((StructTexto*)t)->corb;
}

char* getCorpTexto(TEXTO t) {
    return ((StructTexto*)t)->corp;
}

char getAncoraTexto(TEXTO t) {
    return ((StructTexto*)t)->ancora;
}

char* getStringTexto(TEXTO t) {
    return ((StructTexto*)t)->txto;
}

void limparTexto(TEXTO t) {
    if (t != NULL) {
        StructTexto* st = (StructTexto*) t;
        if (st->txto != NULL) {
            free(st->txto); // Libera a string interna
        }
        free(st); // Libera a struct
    }
}