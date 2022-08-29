#include <ctype.h>
#include "raylib.h"
#include "render_player.h"
#include "render_jogo.h"

void DesenhaExplosao(AnimacaoItem *explosao, Rectangle playerPos) {
    Vector2 pos;
    pos.x = playerPos.x + playerPos.width/2 - 32;
    pos.y = playerPos.y - (explosao->textura.height-playerPos.height);
    explosao->source.x += 64;
    DrawTextureRec(explosao->textura, explosao->source, pos, WHITE);
    DrawText("-1", playerPos.x, playerPos.y-explosao->source.x/64, 1, Fade(WHITE, 512/explosao->source.x));
    if (explosao->source.x == explosao->textura.width-64) {
        explosao->flag = 0;
        explosao->source.x = 0;
    }
}

// Facilita a escolha de tiles para o retângulo source
Rectangle Tile(int x, int y) {
    Rectangle tile;
    tile.width = TAM_TILES;
    tile.height = TAM_TILES;
    tile.x = TAM_TILES * (x-1);
    tile.y = TAM_TILES * (y-1);
    return tile;
}

// Define a posição do retângulo de sourcing dentro do tileset
Rectangle DefineTileParede(Mapa mapa, int l, int c) {
    Rectangle tile;

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

    return tile;
}

void DesenhaCaixa(AnimacaoArr *caixa, Vector2 tilePos, char elemento, int numCaixa, int frames) {
    if (elemento == 'O'
        && caixa->source[numCaixa].x < caixa->textura.width/10 * 9
        && frames % 4 == 0)
        caixa->source[numCaixa].x += caixa->textura.width/10;

    DrawTextureRec(caixa->textura, caixa->source[numCaixa], tilePos, WHITE);
}

void DesenhaNumPorta(char num, int x, int y) {
    DrawText(TextFormat("%c", num), x*TAM_TILES+TAM_TILES/2, y*TAM_TILES, 1, RAYWHITE);
}

// Desenha o mapa do jogo na tela
void DesenhaTiles(Mapa mapa, Texture2D tileset, AnimacaoArr *caixa, int frames) {
    Rectangle tileSource; // Representa o tile dentro da textura
    Vector2 tilePos; // Representa a posição do tile na tela
    int i, j;
    int caixas = 0;

    for (i = 0; i < mapa.linhas; i++)
    {
        tilePos.y = i * TAM_TILES; // Pos vertical
        for (j = 0; j < mapa.colunas; j++)
        {
            tilePos.x = j * TAM_TILES; // Pos horizontal
            switch (mapa.matriz[i][j])
            {
                // Paredes
                case 'X':
                    tileSource = DefineTileParede(mapa, i, j);
                    DrawTextureRec(tileset, tileSource, tilePos, WHITE);
                    break;

                // Escadas
                case 'H':
                    tileSource = Tile(23, 5);
                    DrawTextureRec(tileset, tileSource, tilePos, WHITE);
                    break;

                // Objetivo
                case 'P':
                    tileSource = Tile(23, 8);
                    DrawTextureRec(tileset, tileSource, tilePos, WHITE);
                    break;

                case ' ':
                    break;

                default:
                    // Portas
                    if (isdigit(mapa.matriz[i][j]) > 0) {
                        tileSource = Tile(23, 6);
                        DrawTextureRec(tileset, tileSource, tilePos, WHITE);
                        DesenhaNumPorta(mapa.matriz[i][j], j, i);
                    }

                    // Caixas
                    else {
                        DesenhaCaixa(caixa, tilePos, mapa.matriz[i][j], caixas, frames);
                        caixas++;
                    }
            }
        }
    }
}

void RenderJogo(Mapa mapa, Texture2D tileset, Player *player, int frames, AnimacaoArr *caixa, AnimacaoItem *explosao) {
        // Bordas laterais
        int alturaTela = TAM_TILES*mapa.linhas;
        int larguraTela = TAM_TILES*mapa.colunas;
        int larguraBorda = TAM_TILES/2;

        DrawRectangle(0, 0, larguraBorda, alturaTela, BLACK);
        DrawRectangle(larguraTela - larguraBorda, 0, larguraBorda, alturaTela, BLACK);

        DesenhaTiles(mapa, tileset, caixa, frames);
        DesenhaPlayer(player, frames);
        if (IsKeyPressed(KEY_B)) explosao->flag = 1;
        if (explosao->flag == 1)
            DesenhaExplosao(explosao, player->render);
}
