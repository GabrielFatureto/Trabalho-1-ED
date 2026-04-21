#include <stdio.h>
#include <stdlib.h>
#include "svg.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

void exportarSVG(LISTA listaGeometria, char* caminho_completo) {
    if (listaGeometria == NULL || caminho_completo == NULL) return;

    FILE* fSvg = fopen(caminho_completo, "w");
    if (fSvg == NULL) {
        printf("ERRO: Nao foi possivel criar o arquivo SVG em %s\n", caminho_completo);
        return;
    }

    /* Cabeçalho padrão de um arquivo SVG */
    fprintf(fSvg, "\n");
    fprintf(fSvg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");

    /* Iterando por todas as figuras da lista */
    StrFigura* atual = getPrimeiroLista(listaGeometria);
    while (atual != NULL) {
        
        switch (atual->tipo) {
            case 'c': {
                CIRCULO c = (CIRCULO) atual->forma;
                fprintf(fSvg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"2\" />\n",
                        getXCirculo(c), getYCirculo(c), getRaioCirculo(c), 
                        getCorbCirculo(c), getCorpCirculo(c));
                break;
            }
            case 'r': {
                RETANGULO r = (RETANGULO) atual->forma;
                fprintf(fSvg, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"2\" />\n",
                        getXRetangulo(r), getYRetangulo(r), getWRetangulo(r), getHRetangulo(r), 
                        getCorbRetangulo(r), getCorpRetangulo(r));
                break;
            }
            case 'l': {
                LINHA l = (LINHA) atual->forma;
                fprintf(fSvg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"2\" />\n",
                        getX1Linha(l), getY1Linha(l), getX2Linha(l), getY2Linha(l), getCorLinha(l));
                break;
            }
            case 't': {
                TEXTO t = (TEXTO) atual->forma;
                char* anchor = "start";
                if (getAncoraTexto(t) == 'm') anchor = "middle";
                else if (getAncoraTexto(t) == 'f') anchor = "end";

                fprintf(fSvg, "\t<text x=\"%lf\" y=\"%lf\" stroke=\"%s\" fill=\"%s\" text-anchor=\"%s\">%s</text>\n",
                        getXTexto(t), getYTexto(t), getCorbTexto(t), getCorpTexto(t), 
                        anchor, getStringTexto(t));
                break;
            }
        }
        
        atual = getProximoLista(listaGeometria, atual);
    }

    /* Fechamento do arquivo SVG */
    fprintf(fSvg, "</svg>\n");
    fclose(fSvg);
}