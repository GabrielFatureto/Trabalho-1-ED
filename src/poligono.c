#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poligono.h"
#include "linha.h"



typedef struct {
    int id;
    FILA coordenadas; 
} StrPoligono;



POLIGONO cria_poligono() {
    StrPoligono* p = (StrPoligono*) malloc(sizeof(StrPoligono));
    if (p == NULL) return NULL;

    p->id = -1;
    p->coordenadas = cria_fila();

    return (POLIGONO) p;
}



int getIdPoligono(POLIGONO p) {
    if (p == NULL) return -1;
    return ((StrPoligono*)p)->id;
}

void setIdPoligono(POLIGONO p, int novoId) {
    if (p != NULL) {
        ((StrPoligono*)p)->id = novoId;
    }
}



void inserirCoordenadaPoligono(POLIGONO p, double x, double y) {
    if (p != NULL) {
        inserirFila(((StrPoligono*)p)->coordenadas, x, y);
    }
}

StrPonto removerCoordenadaPoligono(POLIGONO p) {
    StrPonto ponto_vazio = {0.0, 0.0};
    if (p != NULL) {
        return removerFila(((StrPoligono*)p)->coordenadas);
    }
    return ponto_vazio;
}

int gerarLinhas(POLIGONO p, LISTA l, int id_inicio, double d, char* corb, char* corp) {
    if (p == NULL || l == NULL) return id_inicio;

    StrPoligono* poly = (StrPoligono*) p;
    int qtd = getTamanhoFila(poly->coordenadas);
    
    
    if (qtd < 3) return id_inicio; 

    StrPonto pontos[qtd];
    for (int i = 0; i < qtd; i++) {
        pontos[i] = removerFila(poly->coordenadas);
        inserirFila(poly->coordenadas, pontos[i].x, pontos[i].y);
    }

    double ymin = pontos[0].y;
    double ymax = pontos[0].y;
    for (int i = 1; i < qtd; i++) {
        if (pontos[i].y < ymin) ymin = pontos[i].y;
        if (pontos[i].y > ymax) ymax = pontos[i].y;
    }

    for (int i = 0; i < qtd; i++) {
        StrPonto p1 = pontos[i];
        StrPonto p2 = pontos[(i + 1) % qtd];
        
        int id_atual = id_inicio++;
        LINHA borda = cria_linha(id_atual, p1.x, p1.y, p2.x, p2.y, corb);
        
        StrFigura* figBorda = (StrFigura*) malloc(sizeof(StrFigura));
        figBorda->id = id_atual;
        figBorda->tipo = 'l';
        figBorda->forma = borda;
        figBorda->corb = NULL; 
        figBorda->corp = NULL;
        
        inserirLista(l, figBorda); 
    }

    for (double y = ymin + (d / 2.0); y <= ymax; y += d) { 
        double inter[qtd]; 
        int num_inter = 0;

        for (int i = 0; i < qtd; i++) {
            StrPonto p1 = pontos[i];
            StrPonto p2 = pontos[(i + 1) % qtd];

            double menor_y = (p1.y < p2.y) ? p1.y : p2.y;
            double maior_y = (p1.y > p2.y) ? p1.y : p2.y;

            if (p1.y != p2.y && y >= menor_y && y < maior_y) {
                double x_cruzamento = p1.x + (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
                inter[num_inter++] = x_cruzamento;
            }
        }

        for (int i = 0; i < num_inter - 1; i++) {
            for (int j = 0; j < num_inter - i - 1; j++) {
                if (inter[j] > inter[j + 1]) {
                    double temp = inter[j];
                    inter[j] = inter[j + 1];
                    inter[j + 1] = temp;
                }
            }
        }

        for (int i = 0; i < num_inter; i += 2) {
            if (i + 1 < num_inter) { 
                int id_atual = id_inicio++;
                LINHA hachura = cria_linha(id_atual, inter[i], y, inter[i+1], y, corp);
                
                StrFigura* figHachura = (StrFigura*) malloc(sizeof(StrFigura));
                figHachura->id = id_atual;
                figHachura->tipo = 'l';
                figHachura->forma = hachura;
                figHachura->corb = NULL;
                figHachura->corp = NULL;

                inserirLista(l, figHachura); 
            }
        }
    }

    return id_inicio; 
}



void limparPoligono(POLIGONO p) {
    if (p != NULL) {
        StrPoligono* poly = (StrPoligono*) p;
        limparFila(poly->coordenadas); 
        free(poly); 
    }
}