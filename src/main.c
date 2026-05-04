#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lista.h"
#include "fila.h"
#include "poligono.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "svg.h"

// --- FUNÇÕES AUXILIARES ---

char* clonar_string(const char* str) {
    if (str == NULL) return NULL;
    char* copia = (char*) malloc(strlen(str) + 1);
    if (copia != NULL) {
        strcpy(copia, str);
    }
    return copia;
}

void juntaCaminho(char *destino, char *diretorio, char *arquivo) {
    if (diretorio == NULL || strlen(diretorio) == 0) {
        strcpy(destino, arquivo);
    } else {
        if (diretorio[strlen(diretorio) - 1] == '/') {
            sprintf(destino, "%s%s", diretorio, arquivo);
        } else {
            sprintf(destino, "%s/%s", diretorio, arquivo);
        }
    }
}

void extraiNomeBase(char *nomeBase, char *arquivo) {
    char temp[256];
    strcpy(temp, arquivo);
    char *nome = strrchr(temp, '/');
    if (nome != NULL) nome++;
    else nome = temp;
    char *ext = strrchr(nome, '.');
    if (ext != NULL) *ext = '\0';
    strcpy(nomeBase, nome);
}

StrFigura* buscarFiguraPorId(LISTA lista, int id) {
    StrFigura* atual = getPrimeiroLista(lista);
    while (atual != NULL) {
        if (atual->id == id) return atual;
        atual = getProximoLista(lista, atual);
    }
    return NULL;
}


bool estaDentro(StrFigura* f, double selX, double selY, double selW, double selH) {
    double x = 0, y = 0;
    if (f->tipo == 'c') { x = getXCirculo(f->forma); y = getYCirculo(f->forma); }
    else if (f->tipo == 'r') { x = getXRetangulo(f->forma); y = getYRetangulo(f->forma); }
    else if (f->tipo == 'l') { x = getX1Linha(f->forma); y = getY1Linha(f->forma); }
    else if (f->tipo == 't') { x = getXTexto(f->forma); y = getYTexto(f->forma); }
    else return false;
    
    return (x >= selX && x <= (selX + selW) && y >= selY && y <= (selY + selH));
}

void processarGeo(FILE *fGeo, LISTA listaGeometria) {
    char linha[512]; 
    while (fgets(linha, sizeof(linha), fGeo) != NULL) {
        char comando[10];
        if (sscanf(linha, "%s", comando) <= 0) continue;

        if (strcmp(comando, "c") == 0) {
            int id; double x, y, r; 
            char corb[30] = "", corp[30] = "";
            sscanf(linha, "%*s %d %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp);
            CIRCULO c = cria_circulo(id, x, y, r, corb, corp);
            StrFigura* f = (StrFigura*) malloc(sizeof(StrFigura));
            f->id = id; f->tipo = 'c'; f->forma = c;
            f->corb = clonar_string(corb); f->corp = clonar_string(corp);
            inserirLista(listaGeometria, f);
            
        } else if (strcmp(comando, "r") == 0) {
            int id; double x, y, w, h; 
            char corb[30] = "", corp[30] = "";
            sscanf(linha, "%*s %d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);
            RETANGULO r = cria_retangulo(id, x, y, w, h, corb, corp);
            StrFigura* f = (StrFigura*) malloc(sizeof(StrFigura));
            f->id = id; f->tipo = 'r'; f->forma = r;
            f->corb = clonar_string(corb); f->corp = clonar_string(corp);
            inserirLista(listaGeometria, f);
            
        } else if (strcmp(comando, "l") == 0) {
            int id; double x1, y1, x2, y2; 
            char cor[30] = "";
            sscanf(linha, "%*s %d %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, cor);
            LINHA l = cria_linha(id, x1, y1, x2, y2, cor);
            StrFigura* f = (StrFigura*) malloc(sizeof(StrFigura));
            f->id = id; f->tipo = 'l'; f->forma = l;
            f->corb = clonar_string(cor); f->corp = NULL;
            inserirLista(listaGeometria, f);
            
        } else if (strcmp(comando, "t") == 0) {
            int id; double x, y; char a; 
            char corb[30] = "", corp[30] = "", txto[256] = "";
            sscanf(linha, "%*s %d %lf %lf %s %s %c %[^\n]", &id, &x, &y, corb, corp, &a, txto);
            TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);
            StrFigura* f = (StrFigura*) malloc(sizeof(StrFigura));
            f->id = id; f->tipo = 't'; f->forma = t;
            f->corb = clonar_string(corb); f->corp = clonar_string(corp);
            inserirLista(listaGeometria, f);
        }
    }
}


void processarQry(FILE *fQry, LISTA listaGeometria, char* dirSaida, char* nomeBaseGeo, char* nomeBaseQry) {
    char linha[256];
    char nomeSvgQry[256];
    sprintf(nomeSvgQry, "%s-%s.svg", nomeBaseGeo, nomeBaseQry);
    char pathSvgQry[512];
    juntaCaminho(pathSvgQry, dirSaida, nomeSvgQry);

    double selX = 0, selY = 0, selW = 0, selH = 0; 

    while (fgets(linha, sizeof(linha), fQry) != NULL) {
        char comando[10];
        if (sscanf(linha, "%s", comando) <= 0) continue;

        if (strcmp(comando, "sel") == 0) {
            sscanf(linha, "%*s %lf %lf %lf %lf", &selX, &selY, &selW, &selH);
        } 
        else if (strcmp(comando, "dels") == 0) {
            StrFigura* fig = getPrimeiroLista(listaGeometria);
            while (fig != NULL) {
                StrFigura* proximo = getProximoLista(listaGeometria, fig);
                if (estaDentro(fig, selX, selY, selW, selH)) {
                    
                    removerFiguraLista(listaGeometria, fig->id); 
                    
                    if (fig->corb) free(fig->corb);
                    if (fig->corp) free(fig->corp);
                    if (fig->forma) {
                        if (fig->tipo == 'c') { limparCirculo(fig->forma); }
                        else if (fig->tipo == 'r') { limparRetangulo(fig->forma); }
                        else if (fig->tipo == 't') { limparTexto(fig->forma); }
                        else if (fig->tipo == 'l') { limparLinha(fig->forma); }
                    }
                    free(fig); 
                }
                fig = proximo; 
            }
        } 
        else if (strcmp(comando, "mcs") == 0) {
            double nx, ny; 
            char cb[30] = "", cp[30] = ""; // <-- Inicializadas vazias!
            if (sscanf(linha, "%*s %lf %lf %s %s", &nx, &ny, cb, cp) == 4) {
                StrFigura* fig = getPrimeiroLista(listaGeometria);
                while (fig != NULL) {
                    if (estaDentro(fig, selX, selY, selW, selH)) {
                        if (fig->tipo == 'c') { setXCirculo(fig->forma, nx); setYCirculo(fig->forma, ny); }
                        else if (fig->tipo == 'r') { setXRetangulo(fig->forma, nx); setYRetangulo(fig->forma, ny); }
                        else if (fig->tipo == 'l') { 
                            double dx = nx - getX1Linha(fig->forma);
                            double dy = ny - getY1Linha(fig->forma);
                            setX1Linha(fig->forma, nx); 
                            setY1Linha(fig->forma, ny);
                            setX2Linha(fig->forma, getX2Linha(fig->forma) + dx);
                            setY2Linha(fig->forma, getY2Linha(fig->forma) + dy);
                        } 
                        else if (fig->tipo == 't') { setXTexto(fig->forma, nx); setYTexto(fig->forma, ny); }
                        
                        if (fig->corb) { free(fig->corb); fig->corb = clonar_string(cb); }
                        if (fig->corp && fig->tipo != 'l') { free(fig->corp); fig->corp = clonar_string(cp); }
                    }
                    fig = getProximoLista(listaGeometria, fig);
                }
            }
        }
        else if (strcmp(comando, "inp") == 0) {
            int id_pol, id_fig;
            

            sscanf(linha, "%*s %d %d", &id_pol, &id_fig);
            

            StrFigura* figBase = buscarFiguraPorId(listaGeometria, id_fig);
            
            if (figBase != NULL) {
                double ancoraX = 0, ancoraY = 0;
                
                if (figBase->tipo == 'c') { 
                    ancoraX = getXCirculo(figBase->forma); 
                    ancoraY = getYCirculo(figBase->forma); 
                } 
                else if (figBase->tipo == 'r') { 
                    ancoraX = getXRetangulo(figBase->forma); 
                    ancoraY = getYRetangulo(figBase->forma); 
                } 
                else if (figBase->tipo == 't') { 
                    ancoraX = getXTexto(figBase->forma); 
                    ancoraY = getYTexto(figBase->forma); 
                } 
                else if (figBase->tipo == 'l') { 
                    double x1 = getX1Linha(figBase->forma);
                    double y1 = getY1Linha(figBase->forma);
                    double x2 = getX2Linha(figBase->forma);
                    double y2 = getY2Linha(figBase->forma);
                    
                    if (x1 < x2) {
                        ancoraX = x1; ancoraY = y1;
                    } else if (x2 < x1) {
                        ancoraX = x2; ancoraY = y2;
                    } else { // x1 == x2
                        ancoraX = x1;
                        ancoraY = (y1 < y2) ? y1 : y2;
                    }
                }

                StrFigura* figPol = buscarFiguraPorId(listaGeometria, id_pol);
                if (figPol == NULL) {
                    POLIGONO p = cria_poligono();
                    setIdPoligono(p, id_pol);
                    figPol = (StrFigura*) malloc(sizeof(StrFigura));
                    figPol->id = id_pol; 
                    figPol->tipo = 'p'; 
                    figPol->forma = p;
                    figPol->corb = NULL; 
                    figPol->corp = NULL;
                    inserirLista(listaGeometria, figPol);
                }

                inserirCoordenadaPoligono(figPol->forma, ancoraX, ancoraY);
            }
        } else if (strcmp(comando, "rmp") == 0) {
            int id;
            sscanf(linha, "%*s %d", &id);
            StrFigura* fig = buscarFiguraPorId(listaGeometria, id);
            if (fig != NULL && fig->tipo == 'p') {
                removerCoordenadaPoligono(fig->forma);
            }

        } else if (strcmp(comando, "pol") == 0) {
            int id; double d, espessura;
            char corb[30] = "", corp[30] = "";

            sscanf(linha, "%*s %d %lf %lf %s %s", &id, &d, &espessura, corb, corp);

            StrFigura* fig = buscarFiguraPorId(listaGeometria, id);
            if (fig != NULL && fig->tipo == 'p') {
                if (fig->corb) free(fig->corb);
                if (fig->corp) free(fig->corp);
                fig->corb = clonar_string(corb);
                fig->corp = clonar_string(corp);

                gerarLinhas(fig->forma, listaGeometria, 0, d, corb, corp);
            }
        }
    }
    exportarSVG(listaGeometria, pathSvgQry);
}

// --- MAIN ---
int main(int argc, char *argv[]) {
    char *dirEntrada = NULL, *arqGeo = NULL, *arqQry = NULL, *dirSaida = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) dirEntrada = argv[++i];
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) arqGeo = argv[++i];
        else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) arqQry = argv[++i];
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) dirSaida = argv[++i];
    }

    if (arqGeo == NULL || dirSaida == NULL) {
        printf("Erro: Faltam parâmetros obrigatórios (-f e/ou -o).\n");
        return 1;
    }

    char pathGeo[256], nomeBaseGeo[100];
    juntaCaminho(pathGeo, dirEntrada, arqGeo);
    extraiNomeBase(nomeBaseGeo, arqGeo);

    LISTA listaGeometria = cria_lista();
    
    FILE *fGeo = fopen(pathGeo, "r");
    if (fGeo != NULL) {
        processarGeo(fGeo, listaGeometria);
        fclose(fGeo);
        
        char pathSvgGeo[512];
        sprintf(pathSvgGeo, "%s/%s.svg", dirSaida, nomeBaseGeo);
        exportarSVG(listaGeometria, pathSvgGeo);
    } else {
        printf("Erro: Nao abriu GEO em %s\n", pathGeo);
        return 1;
    }

    if (arqQry != NULL) {
        char pathQry[256], nomeBaseQry[100];
        juntaCaminho(pathQry, dirEntrada, arqQry);
        extraiNomeBase(nomeBaseQry, arqQry);
        FILE *fQry = fopen(pathQry, "r");
        if (fQry != NULL) {
            processarQry(fQry, listaGeometria, dirSaida, nomeBaseGeo, nomeBaseQry);
            fclose(fQry);
        } else {
            printf("Aviso: Nao abriu QRY em %s\n", pathQry);
        }
    }

    StrFigura* atual = getPrimeiroLista(listaGeometria);
    while (atual != NULL) {
        StrFigura* proximo = getProximoLista(listaGeometria, atual);
        
        if (atual->corb) free(atual->corb);
        if (atual->corp) free(atual->corp);
        
        if (atual->forma) {
            if (atual->tipo == 'c') { limparCirculo(atual->forma); }
            else if (atual->tipo == 'r') { limparRetangulo(atual->forma); }
            else if (atual->tipo == 't') { limparTexto(atual->forma); }
            else if (atual->tipo == 'l') { limparLinha(atual->forma); }
        }
        free(atual);
        atual = proximo;
    }
    destruirLista(listaGeometria);
    
    return 0;
}