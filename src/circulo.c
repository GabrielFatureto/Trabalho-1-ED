#include "circulo.h"

CIRCULO cria_circulo(int id, double x, double y, double r, char* corb, char* corp) {
    StrCirculo* c = (StrCirculo*) malloc(sizeof(StrCirculo));
    if (c == NULL) return NULL;

    c->id = id;
    c->x = x;
    c->y = y;
    c->r = r;
    
    c->corb = (char*) malloc((strlen(corb) + 1) * sizeof(char));
    strcpy(c->corb, corb);
    
    c->corp = (char*) malloc((strlen(corp) + 1) * sizeof(char));
    strcpy(c->corp, corp);

    return c;
}

int getIdCirculo(CIRCULO c) {
    return ((StrCirculo*)c)->id;
}

double getXCirculo(CIRCULO c) {
    return ((StrCirculo*)c)->x;
}

double getYCirculo(CIRCULO c) {
    return ((StrCirculo*)c)->y;
}

double getRaioCirculo(CIRCULO c) {
    return ((StrCirculo*)c)->r;
}

char* getCorbCirculo(CIRCULO c) {
    return ((StrCirculo*)c)->corb;
}

char* getCorpCirculo(CIRCULO c) {
    return ((StrCirculo*)c)->corp;
}

void setIdCirculo(CIRCULO c, int novoId) {
    ((StrCirculo*)c)->id = novoId;
}

void setXCirculo(CIRCULO c, double x) {
    ((StrCirculo*)c)->x = x;
}

void setYCirculo(CIRCULO c, double y) {
    ((StrCirculo*)c)->y = y;
}

void setRaioCirculo(CIRCULO c, double r) {
    ((StrCirculo*)c)->r = r;
}

void setCorbCirculo(CIRCULO c, char* corb) {
    StrCirculo* c_int = (StrCirculo*)c;
    free(c_int->corb);
    c_int->corb = (char*) malloc((strlen(corb) + 1) * sizeof(char));
    strcpy(c_int->corb, corb);
}

void setCorpCirculo(CIRCULO c, char* corp) {
    StrCirculo* c_int = (StrCirculo*)c;
    free(c_int->corp);
    c_int->corp = (char*) malloc((strlen(corp) + 1) * sizeof(char));
    strcpy(c_int->corp, corp);
}

void limparCirculo(CIRCULO c) {
    if (c != NULL) {
        StrCirculo* c_int = (StrCirculo*)c;
        free(c_int->corb);
        free(c_int->corp);
        free(c_int);
    }
}