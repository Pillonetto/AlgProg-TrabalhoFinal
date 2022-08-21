#include "definicoes.h"

void DesenhaPlayer(Player *player, int frames);

// Facilita a escolha de tiles para o retângulo source
Rectangle Tile(int x, int y) {
    return (Rectangle){.x=x-1, .y=y-1};
}

// Define a posição do retângulo de sourcing dentro do tileset
Rectangle DefineTile(Sprite tileset, char mapa[MAPA_L][MAPA_C], int l, int c, int lMax, int cMax) {
    Rectangle tile;

    if (mapa[l][c] == 'H') // ESCADA --------
        tile = Tile(23, 5);
    else if (isdigit(mapa[l][c]) > 0)
        tile = Tile(23, 6);
    else if (mapa[l][c] == 'C')
        tile = Tile(23, 7);
    else if (mapa[l][c] == 'P')
        tile = Tile(23, 8);
    else // PAREDES -------------------------
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

    tile.width = tileset.width;
    tile.height = tileset.height;
    tile.x *= tileset.width;
    tile.y *= tileset.height;
    return tile;
}

// Desenha o mapa do jogo na tela
void DesenhaTiles(char mapa[MAPA_L][MAPA_C], Sprite tileset, int l, int c) {
    Rectangle tileSource; // Representa o tile dentro da textura
    Rectangle tileDest; // Representa o tile na tela do jogo
    int i, j;

    tileDest.width = tileset.width * SCALE_TILES;
    tileDest.height = tileset.height * SCALE_TILES;

    for (i = 0; i < l; i++)
    {
        tileDest.y = i * tileset.height * SCALE_TILES;
        for (j = 0; j < c; j++)
        {
            tileDest.x = (j * tileset.width * SCALE_TILES) + TAM_BORDAS;
            if (mapa[i][j] != ' ') {
                tileSource = DefineTile(tileset, mapa, i, j, l, c);
                DrawTexturePro(tileset.textura, tileSource, tileDest, (Vector2){0.0f, 0.0f}, 0, WHITE);
            }
        }
    }
}

// Desenha as bordas laterais
void DesenhaBordas(Sprite tileset, int c) {
    int i;

    Rectangle tileSource = Tile(13, 1);
    tileSource.width = tileset.width;
    tileSource.height = tileset.height;
    tileSource.x *= tileset.width;
    tileSource.y *= tileset.height;

    Rectangle tileDest;
    tileDest.width = TAM_BORDAS * 1.5; // 1.5x p/ garantir que o fundo não apareça
    tileDest.height = RES_VERTICAL;

    for (i = 0; i < 2; i++) {
        tileDest.x = i * ((c*tileset.width*SCALE_TILES)+TAM_BORDAS*0.9);
        DrawRectangleRec(tileDest, (Color){31,21,19,255});
        DrawTextureTiled(tileset.textura, tileSource, tileDest, (Vector2){0.0f,0.0f}, 0, SCALE_TILES, DARKGRAY);
    }
}

// Desenha a barra de informações do jogo (WIP)
void DesenhaInfo() {
    DrawRectangle(0, RES_VERTICAL*0.9, RES_HORIZONT, RES_VERTICAL*0.1, (Color){25,23,20,255});
}

void RenderJogo(char mapa[MAPA_L][MAPA_C], int l, int c, Sprite tileset, Player *player, int frames) {
    BeginDrawing();
        DesenhaBordas(tileset, c);
        DesenhaInfo();
        DesenhaTiles(mapa, tileset, l, c);
        DesenhaPlayer(player, frames);
    EndDrawing();
}
