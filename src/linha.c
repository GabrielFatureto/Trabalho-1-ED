#include <stdlib.h>
#include <string.h>
#include "linha.h"

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

void setX1Linha(LINHA l, double x) {
    if (l != NULL) ((StructLinha*)l)->x1 = x;
}

void setY1Linha(LINHA l, double y) {
    if (l != NULL) ((StructLinha*)l)->y1 = y;
}

void setX2Linha(LINHA l, double x) {
    if (l != NULL) ((StructLinha*)l)->x2 = x;
}

void setY2Linha(LINHA l, double y) {
    if (l != NULL) ((StructLinha*)l)->y2 = y;
}

void limparLinha(LINHA l) {
    if (l != NULL) {
        free(l);
    }
}