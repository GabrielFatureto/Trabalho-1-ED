#include <stdio.h>
#include <stdlib.h>
#include "svg.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#define SEGURA(s) ((s) != NULL ? (s) : "none")
// Tive que criar essa macro pra evitar que, caso alguma cor venha como NULL, o SVG quebre. Agora, se a cor for NULL, ela será tratada como "none" (sem cor) no SVG.

void exportarSVG(LISTA listaGeometria, char* caminho_completo) {
    if (listaGeometria == NULL || caminho_completo == NULL) return;

    FILE* fSvg = fopen(caminho_completo, "w");
    if (fSvg == NULL) {
        printf("ERRO: Nao foi possivel criar o arquivo SVG em %s\n", caminho_completo);
        return;
    }

    fprintf(fSvg, "\n");
    fprintf(fSvg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");

    StrFigura* atual = getPrimeiroLista(listaGeometria);
    int contador = 1;
    
    while (atual != NULL) {
        
        if (atual->forma == NULL) {
            atual = getProximoLista(listaGeometria, atual);
            contador++;
            continue; 
        }
        
        switch (atual->tipo) {
            case 'c': {
                CIRCULO c = (CIRCULO) atual->forma;
                fprintf(fSvg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"2\" />\n",
                        getXCirculo(c), getYCirculo(c), getRaioCirculo(c), 
                        SEGURA(getCorbCirculo(c)), SEGURA(getCorpCirculo(c)));
                break;
            }
            case 'r': {
                RETANGULO r = (RETANGULO) atual->forma;
                fprintf(fSvg, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"2\" />\n",
                        getXRetangulo(r), getYRetangulo(r), getWRetangulo(r), getHRetangulo(r), 
                        SEGURA(getCorbRetangulo(r)), SEGURA(getCorpRetangulo(r)));
                break;
            }
            case 'l': {
                LINHA l = (LINHA) atual->forma;
                fprintf(fSvg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"2\" />\n",
                        getX1Linha(l), getY1Linha(l), getX2Linha(l), getY2Linha(l), SEGURA(getCorLinha(l)));
                break;
            }
            case 't': {
                TEXTO t = (TEXTO) atual->forma;
                char* anchor = "start";
                if (getAncoraTexto(t) == 'm') anchor = "middle";
                else if (getAncoraTexto(t) == 'f') anchor = "end";

                fprintf(fSvg, "\t<text x=\"%lf\" y=\"%lf\" stroke=\"%s\" fill=\"%s\" text-anchor=\"%s\">%s</text>\n",
                        getXTexto(t), getYTexto(t), SEGURA(getCorbTexto(t)), SEGURA(getCorpTexto(t)), 
                        anchor, SEGURA(getStringTexto(t)));
                break;
            }
        }
        
        atual = getProximoLista(listaGeometria, atual);
        contador++;
    }

    fprintf(fSvg, "</svg>\n");
    fclose(fSvg);
}