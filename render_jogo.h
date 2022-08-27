#ifndef RENDER_JOGO_H
#define RENDER_JOGO_H

#include "mapa.h"
#include "jogo.h"

// Tamanho dos tiles em pixels
#define TAM_TILES 24

/* MACROS PARA TILES
Determinam se a posição em questão está ocupada (caso não esteja fora dos limites) */
#define CIMA  (mapa.matriz[l-1][c]=='X' && l-1 != -1)
#define BAIXO (mapa.matriz[l+1][c]=='X' && l+1 != mapa.linhas)
#define DIR   (mapa.matriz[l][c+1]=='X' && c+1 != mapa.colunas)
#define ESQ   (mapa.matriz[l][c-1]=='X' && c-1 != -1)

Rectangle Tile(int x, int y);
Rectangle DefineTile(Mapa mapa, int l, int c);
void DesenhaNumPorta(char num, int x, int y);
void DesenhaTiles(Mapa mapa, Texture2D tileset);
void RenderJogo(Mapa mapa, Texture2D tileset, Player *player, int frames);

#endif // RENDER_JOGO_H
