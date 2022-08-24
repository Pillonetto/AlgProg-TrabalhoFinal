#include "definicoes.h"

void DesenhaPlayer(Player *player, int frames);

// Facilita a escolha de tiles para o retângulo source
Rectangle Tile(int x, int y) {
    return (Rectangle){.x=x-1, .y=y-1};
}

// Define a posição do retângulo de sourcing dentro do tileset
Rectangle DefineTile(Sprite tileset, char mapa[MAPA_L][MAPA_C], int l, int c, int lMax, int cMax) {
    Rectangle tile;

    if (mapa[l][c] == 'H')              // ESCADA
        tile = Tile(23, 5);
    else if (isdigit(mapa[l][c]) > 0)   // PORTA
        tile = Tile(23, 6);
    else if (mapa[l][c] == 'C')         // CAIXA
        tile = Tile(23, 7);
    else if (mapa[l][c] == 'P')         // OBJETIVO
        tile = Tile(23, 8);
    else                                // PAREDES
    {
        if (CIMA && ESQ && DIR) tile = Tile(8, 12);
        else if (CIMA && ESQ && BAIXO) tile = Tile(11, 11);
        else if (CIMA && ESQ) tile = Tile(23, 4);
        else if (CIMA && BAIXO && DIR) tile = Tile(10, 11);
        else if (CIMA && BAIXO) tile = Tile(11, 5);
        else if (CIMA && DIR) tile = Tile(23, 1);
        else if (CIMA) tile = Tile(7, 6);
        else if (ESQ && BAIXO && DIR) tile = Tile(2, 1);
        else if (ESQ && BAIXO) tile = Tile(23, 3);
        else if (ESQ && DIR) tile = Tile(13, 9);
        else if (ESQ) tile = Tile(8, 4);
        else if (BAIXO && DIR) tile = Tile(23, 2);
        else if (BAIXO) tile = Tile(7, 3);
        else if (DIR) tile = Tile(6, 4);
        else tile = Tile(11, 1);
    }

    // Dimensões do retângulo de sourcing
    tile.width = tileset.width;
    tile.height = tileset.height;
    tile.x *= tileset.width;
    tile.y *= tileset.height;
    return tile;
}

// Desenha o mapa do jogo na tela
void DesenhaTiles(char mapa[MAPA_L][MAPA_C], Sprite tileset, int l, int c) {
    Rectangle tileSource; // Representa o tile dentro da textura
    Vector2 tilePos; // Representa a posição do tile na tela
    int i, j;

    for (i = 0; i < l; i++) {
        tilePos.y = i * tileset.height; // Pos vertical
        for (j = 0; j < c; j++) {
            tilePos.x = j * tileset.width; // Pos horizontal
            if (mapa[i][j] != ' ') {
                tileSource = DefineTile(tileset, mapa, i, j, l, c);
                DrawTextureRec(tileset.textura, tileSource, tilePos, WHITE);
            }
        }
    }
}

void RenderJogo(char mapa[MAPA_L][MAPA_C], int l, int c, Sprite tileset, Player *player, int frames) {
        DesenhaTiles(mapa, tileset, l, c);
        DesenhaPlayer(player, frames);
}
