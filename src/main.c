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

char* clonar_string(const char* str) {
    if (str == NULL) return NULL;
    char* copia = (char*) malloc(strlen(str) + 1);
    if (copia != NULL) {
        strcpy(copia, str);
    }
    return copia;
}

/* Concatena diretórios e arquivos de forma segura */
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

/* Extrai o nome do arquivo sem a extensão (ex: "teste.geo" -> "teste") */
void extraiNomeBase(char *nomeBase, char *arquivo) {
    char temp[256];
    strcpy(temp, arquivo);
    
    // Remove os diretórios antes do nome
    char *nome = strrchr(temp, '/');
    if (nome != NULL) nome++; // Pula a barra
    else nome = temp;

    // Remove a extensão
    char *ext = strrchr(nome, '.');
    if (ext != NULL) *ext = '\0';

    strcpy(nomeBase, nome);
}

/* ================== PARSER DO ARQUIVO .GEO ================== */
void processarGeo(FILE *fGeo, LISTA listaGeometria) {
    char linha[256];

    while (fgets(linha, sizeof(linha), fGeo) != NULL) {
        char comando[10];
        if (sscanf(linha, "%s", comando) <= 0) continue;

        if (strcmp(comando, "c") == 0) {
            int id; double x, y, r; char corb[30], corp[30];
            sscanf(linha, "%*s %d %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp);
            CIRCULO c = cria_circulo(id, x, y, r, corb, corp);
            
            StrFigura* f = (StrFigura*) malloc(sizeof(StrFigura));
            f->id = id; f->tipo = 'c'; f->ancora.x = x; f->ancora.y = y;
            f->corb = clonar_string(corb); f->corp = clonar_string(corp); f->forma = c;
            inserirLista(listaGeometria, f);

        } else if (strcmp(comando, "r") == 0) {
            int id; double x, y, w, h; char corb[30], corp[30];
            sscanf(linha, "%*s %d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);
            RETANGULO r = cria_retangulo(id, x, y, w, h, corb, corp);
            
            StrFigura* f = (StrFigura*) malloc(sizeof(StrFigura));
            f->id = id; f->tipo = 'r'; f->ancora.x = x; f->ancora.y = y;
            f->corb = clonar_string(corb); f->corp = clonar_string(corp); f->forma = r;
            inserirLista(listaGeometria, f);

        } else if (strcmp(comando, "l") == 0) {
            int id; double x1, y1, x2, y2; char cor[30];
            sscanf(linha, "%*s %d %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, cor);
            LINHA l = cria_linha(id, x1, y1, x2, y2, cor);
            
            StrFigura* f = (StrFigura*) malloc(sizeof(StrFigura));
            f->id = id; f->tipo = 'l'; f->ancora.x = x1; f->ancora.y = y1;
            f->corb = clonar_string(cor); f->corp = NULL; f->forma = l;
            inserirLista(listaGeometria, f);

        } else if (strcmp(comando, "t") == 0) {
            int id; double x, y; char corb[30], corp[30], a; char txto[100];
            sscanf(linha, "%*s %d %lf %lf %s %s %c %[^\n]", &id, &x, &y, corb, corp, &a, txto);
            TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);
            
            StrFigura* f = (StrFigura*) malloc(sizeof(StrFigura));
            f->id = id; f->tipo = 't'; f->ancora.x = x; f->ancora.y = y;
            f->corb = clonar_string(corb); f->corp = clonar_string(corp); f->forma = t;
            inserirLista(listaGeometria, f);
        }
    }
}

/* ================== PARSER DO ARQUIVO .QRY ================== */
void processarQry(FILE *fQry, LISTA listaGeometria, char* dirSaida, char* nomeBaseGeo, char* nomeBaseQry) {
    char linha[256];
    
    // O nome do arquivo SVG do qry será: dirSaida/nomegeo-nomeqry.svg
    char nomeSvgQry[256];
    sprintf(nomeSvgQry, "%s-%s.svg", nomeBaseGeo, nomeBaseQry);
    
    char pathSvgQry[512];
    juntaCaminho(pathSvgQry, dirSaida, nomeSvgQry);

    printf("--> Processando consultas (.qry)...\n");

    while (fgets(linha, sizeof(linha), fQry) != NULL) {
        char comando[10];
        if (sscanf(linha, "%s", comando) <= 0) continue;

        if (strcmp(comando, "sel") == 0) {
            double x, y, w, h;
            sscanf(linha, "%*s %lf %lf %lf %lf", &x, &y, &w, &h);
            printf("Comando SEL lido: x=%lf y=%lf w=%lf h=%lf\n", x, y, w, h);
            // TODO: Iterar na listaGeometria e colocar figuras contidas na região em uma 'listaSelecionados'

        } else if (strcmp(comando, "dels") == 0) {
            printf("Comando DELS lido.\n");
            // TODO: Remover formas selecionadas da listaGeometria principal

        } else if (strcmp(comando, "pol") == 0) {
            int id; double d; char corb[30], corp[30];
            sscanf(linha, "%*s %d %lf %s %s", &id, &d, corb, corp);
            printf("Comando POL lido.\n");
            // TODO: Chamar o Polígono (gerarLinhas)
        }
    }

    // Após processar as modificações do QRY, gera um novo SVG
    exportarSVG(listaGeometria, pathSvgQry);
    printf("--> SVG modificado (pós-QRY) gerado em: %s\n", pathSvgQry);
}


/* ================== MAIN ================== */
int main(int argc, char *argv[]) {
    char *dirEntrada = NULL;
    char *arqGeo = NULL;
    char *arqQry = NULL;
    char *dirSaida = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) dirEntrada = argv[++i];
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) arqGeo = argv[++i];
        else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) arqQry = argv[++i];
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) dirSaida = argv[++i];
    }

    if (arqGeo == NULL || dirSaida == NULL) {
        printf("ERRO: Parametros -f e -o sao obrigatorios.\n");
        return 1;
    }

    char pathGeo[256];
    juntaCaminho(pathGeo, dirEntrada, arqGeo);

    char nomeBaseGeo[100];
    extraiNomeBase(nomeBaseGeo, arqGeo);

    LISTA listaGeometria = cria_lista();

    // 1. LER O .GEO
    FILE *fGeo = fopen(pathGeo, "r");
    if (fGeo != NULL) {
        printf("Lendo arquivo GEO: %s\n", pathGeo);
        processarGeo(fGeo, listaGeometria);
        fclose(fGeo);
        
        // Exportar o SVG apenas com o GEO
        char nomeSvgGeo[256];
        sprintf(nomeSvgGeo, "%s.svg", nomeBaseGeo);
        char pathSvgGeo[512];
        juntaCaminho(pathSvgGeo, dirSaida, nomeSvgGeo);
        
        exportarSVG(listaGeometria, pathSvgGeo);
        printf("--> SVG original gerado em: %s\n", pathSvgGeo);
    } else {
        printf("Erro ao abrir arquivo GEO.\n");
        return 1;
    }

    // 2. LER O .QRY (Se existir)
    if (arqQry != NULL) {
        char pathQry[256];
        juntaCaminho(pathQry, dirEntrada, arqQry);

        char nomeBaseQry[100];
        extraiNomeBase(nomeBaseQry, arqQry);

        FILE *fQry = fopen(pathQry, "r");
        if (fQry != NULL) {
            printf("\nLendo arquivo QRY: %s\n", pathQry);
            processarQry(fQry, listaGeometria, dirSaida, nomeBaseGeo, nomeBaseQry);
            fclose(fQry);
        } else {
            printf("Erro ao abrir arquivo QRY.\n");
        }
    }

    // 3. LIMPEZA FINAL (O Lixeiro)
    StrFigura* atual = getPrimeiroLista(listaGeometria);
    while (atual != NULL) {
        StrFigura* proximo = getProximoLista(listaGeometria, atual); // Pega o próximo antes de apagar o atual!
        
        // Libera as strings clonadas da StrFigura
        if (atual->corb != NULL) free(atual->corb);
        if (atual->corp != NULL) free(atual->corp);
        
        // Libera as strings internas de cada TAD específico e depois a struct
        if (atual->forma != NULL) {
            switch (atual->tipo) {
                case 'c':
                    free(getCorbCirculo(atual->forma));
                    free(getCorpCirculo(atual->forma));
                    break;
                case 'r':
                    free(getCorbRetangulo(atual->forma));
                    free(getCorpRetangulo(atual->forma));
                    break;
                case 't':
                    free(getStringTexto(atual->forma));
                    break;
                case 'l':
                    // Sem malloc interno na linha detectado pelo Valgrind.
                    break;
            }
            free(atual->forma); // Destrói a caixa da forma
        }
        
        free(atual); // Destrói a StrFigura
        atual = proximo;
    }
    
    // Destroi a lista vazia
    destruirLista(listaGeometria);

    printf("\nPrograma finalizado!\n");
    return 0;
}