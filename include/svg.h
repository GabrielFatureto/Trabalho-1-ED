#ifndef SVG_H
#define SVG_H

#include "lista.h"

/// @brief Exporta todas as figuras geométricas contidas na lista para um arquivo SVG
/// @param listaGeometria A lista contendo as figuras (StrFigura)
/// @param caminho_completo O caminho com o nome do arquivo final (ex: "./saida/desenho.svg")
void exportarSVG(LISTA listaGeometria, char* caminho_completo);

#endif