#include <stdlib.h>
#include <string.h>
#include "linha.h"

// A struct escondida
typedef struct linha {
    int id;
    double x1;
    double y1;
    double x2;
    double y2;
    char cor[30];
} StructLinha;

LINHA cria_linha(int id, double x1, double y1, double x2, double y2, char* cor) {
    StructLinha* l = (StructLinha*) malloc(sizeof(StructLinha));
    if (l == NULL) return NULL;

    l->id = id;
    l->x1 = x1;
    l->y1 = y1;
    l->x2 = x2;
    l->y2 = y2;
    strcpy(l->cor, cor);

    return (LINHA) l;
}

int getIdLinha(LINHA l) {
    return ((StructLinha*)l)->id;
}

double getX1Linha(LINHA l) {
    return ((StructLinha*)l)->x1;
}

double getY1Linha(LINHA l) {
    return ((StructLinha*)l)->y1;
}

double getX2Linha(LINHA l) {
    return ((StructLinha*)l)->x2;
}

double getY2Linha(LINHA l) {
    return ((StructLinha*)l)->y2;
}

char* getCorLinha(LINHA l) {
    return ((StructLinha*)l)->cor;
}

void limparLinha(LINHA l) {
    if (l != NULL) {
        free(l);
    }
}