#include <ctype.h>
#include "raylib.h"
#include "render_player.h"
#include "render_jogo.h"

// Facilita a escolha de tiles para o retângulo source
Rectangle Tile(int x, int y) {
    return (Rectangle){.x=x-1, .y=y-1};
}

// Define a posição do retângulo de sourcing dentro do tileset
Rectangle DefineTile(Mapa mapa, int l, int c) {
    Rectangle tile;

    if (mapa.matriz[l][c] == 'H')              // ESCADA
        tile = Tile(23, 5);
    else if (isdigit(mapa.matriz[l][c]) > 0)   // PORTA
        tile = Tile(23, 6);
    else if (mapa.matriz[l][c] == 'C')         // CAIXA
        tile = Tile(23, 7);
    else if (mapa.matriz[l][c] == 'P')         // OBJETIVO
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
    tile.width = TAM_TILES;
    tile.height = TAM_TILES;
    tile.x *= TAM_TILES;
    tile.y *= TAM_TILES;
    return tile;
}

void DesenhaNumPorta(char num, int x, int y) {
    DrawText(TextFormat("%c", num), x*TAM_TILES+TAM_TILES/2, y*TAM_TILES, 1, RAYWHITE);
}

// Desenha o mapa do jogo na tela
void DesenhaTiles(Mapa mapa, Texture2D tileset) {
    Rectangle tileSource; // Representa o tile dentro da textura
    Vector2 tilePos; // Representa a posição do tile na tela
    int i, j;

    for (i = 0; i < mapa.linhas; i++) {
        tilePos.y = i * TAM_TILES; // Pos vertical
        for (j = 0; j < mapa.colunas; j++) {
            tilePos.x = j * TAM_TILES; // Pos horizontal
            if (mapa.matriz[i][j] != ' ') {
                tileSource = DefineTile(mapa, i, j);
                DrawTextureRec(tileset, tileSource, tilePos, WHITE);
                if (isdigit(mapa.matriz[i][j]) > 0)
                    DesenhaNumPorta(mapa.matriz[i][j], j, i);
            }
        }
    }
}

void RenderJogo(Mapa mapa, Texture2D tileset, Player *player, int frames) {
        // Bordas laterais
        int alturaTela = TAM_TILES*mapa.linhas;
        int larguraTela = TAM_TILES*mapa.colunas;
        int larguraBorda = TAM_TILES/2;

        DrawRectangle(0, 0, larguraBorda, alturaTela, BLACK);
        DrawRectangle(larguraTela - larguraBorda, 0, larguraBorda, alturaTela, BLACK);

        DesenhaTiles(mapa, tileset);
        DesenhaPlayer(player, frames);
}
