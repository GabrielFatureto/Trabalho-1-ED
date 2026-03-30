#include "retangulo.h"

RETANGULO cria_retangulo(int id, double x, double y, double w, double h, char* corb, char* corp) {
    StrRetangulo* r = (StrRetangulo*) malloc(sizeof(StrRetangulo));
    if (r == NULL) return NULL;

    r->id = id;
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;
    
    r->corb = (char*) malloc((strlen(corb) + 1) * sizeof(char));
    strcpy(r->corb, corb);
    
    r->corp = (char*) malloc((strlen(corp) + 1) * sizeof(char));
    strcpy(r->corp, corp);

    return r;
}

int getIdRetangulo(RETANGULO r) { 
    return ((StrRetangulo*)r)->id; 
}

double getXRetangulo(RETANGULO r) { 
    return ((StrRetangulo*)r)->x; 
}
    
double getYRetangulo(RETANGULO r) { 
    return ((StrRetangulo*)r)->y; 
}

double getWRetangulo(RETANGULO r) { 
    return ((StrRetangulo*)r)->w; 
}

double getHRetangulo(RETANGULO r) { 
    return ((StrRetangulo*)r)->h; 
}

char* getCorbRetangulo(RETANGULO r) { 
    return ((StrRetangulo*)r)->corb; 
}

char* getCorpRetangulo(RETANGULO r) { 
    return ((StrRetangulo*)r)->corp; 
}

void setIdRetangulo(RETANGULO r, int novoId) { 
    ((StrRetangulo*)r)->id = novoId; 
}

void setXRetangulo(RETANGULO r, double x) { 
    ((StrRetangulo*)r)->x = x; 
}
    
void setYRetangulo(RETANGULO r, double y) { 
    ((StrRetangulo*)r)->y = y; 
}

void setWRetangulo(RETANGULO r, double w) { 
    ((StrRetangulo*)r)->w = w; 
}

void setHRetangulo(RETANGULO r, double h) { 
    ((StrRetangulo*)r)->h = h; 
}

void setCorbRetangulo(RETANGULO r, char* corb) {
    StrRetangulo* r_int = (StrRetangulo*)r;
    free(r_int->corb);
    r_int->corb = (char*) malloc((strlen(corb) + 1) * sizeof(char));
    strcpy(r_int->corb, corb);
}

void setCorpRetangulo(RETANGULO r, char* corp) {
    StrRetangulo* r_int = (StrRetangulo*)r;
    free(r_int->corp);
    r_int->corp = (char*) malloc((strlen(corp) + 1) * sizeof(char));
    strcpy(r_int->corp, corp);
}

void limparRetangulo(RETANGULO r) {
    if (r != NULL) {
        StrRetangulo* r_int = (StrRetangulo*)r;
        free(r_int->corb);
        free(r_int->corp);
        free(r_int);
    }
}