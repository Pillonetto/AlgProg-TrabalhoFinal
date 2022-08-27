#ifndef RENDER_JOGO_H
#define RENDER_JOGO_H

#include "mapa.h"
#include "jogo.h"

// Tamanho dos tiles em pixels
#define TAM_TILES 24

/* MACROS PARA TILES
Determinam se a posição em questão está ocupada (caso não esteja fora dos limites) */
#define CIMA  (mapa[l-1][c]=='X' && l-1 != -1)
#define BAIXO (mapa[l+1][c]=='X' && l+1 != lMax)
#define DIR   (mapa[l][c+1]=='X' && c+1 != cMax)
#define ESQ   (mapa[l][c-1]=='X' && c-1 != -1)

Rectangle Tile(int x, int y);
Rectangle DefineTile(char mapa[MAPA_L][MAPA_C], int l, int c, int lMax, int cMax);
void DesenhaNumPorta(char num, int x, int y);
void DesenhaTiles(char mapa[MAPA_L][MAPA_C], Texture2D tileset, int l, int c);
void RenderJogo(char mapa[MAPA_L][MAPA_C], int l, int c, Texture2D tileset, Player *player, int frames);

#endif // RENDER_JOGO_H
