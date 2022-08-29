#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"
#include "render_player.h"
#include "render_jogo.h"

void DesenhaItem(AnimacaoItem itens[N_ITENS], Rectangle playerPos, int frames, int i, AnimacaoItem *explosao) {
    Vector2 origin = {.x = itens[i].dest.width/2, .y = itens[i].dest.height/2};
    float playerX = playerPos.x + playerPos.width/2;
    float playerY = playerPos.y + playerPos.height/2;

    // Inicialização do render
    if (itens[i].source.x == 0) {
        itens[i].dest.x = playerX;
        itens[i].dest.y = playerY;
        itens[i].source.x += itens[i].source.width;
    }

    // Animação do sprite
    if (frames % 10 == 0 && itens[i].source.x != itens[i].textura.width-itens[i].source.width)
        itens[i].source.x += itens[i].source.width;

    // Animação do item subindo e descendo
    itens[i].dest.y -= itens[i].velocidade;
    if (itens[i].velocidade < 0.4 && itens[i].velocidade > -0.4)
        itens[i].velocidade -= 0.025; // Mantém o item mais tempo no ar
    else
        itens[i].velocidade -= 0.1;

    // Animação do item indo em direção ao jogador (horizontalmente)
    if (itens[i].dest.x > playerX)
        itens[i].dest.x -= 0.5;
    if (itens[i].dest.x < playerX)
        itens[i].dest.x += 0.5;

    itens[i].rotation += 0.5;

    DrawTexturePro(itens[i].textura, itens[i].source, itens[i].dest, origin, itens[i].rotation, WHITE);

    // Finaliza a animação
    if (itens[i].dest.y > playerY) {
        itens[i].source.x = 0;
        itens[i].rotation = 0;
        itens[i].velocidade = 2.5;
        itens[i].flag = 0;
        if (i == 1) // Se for bomba, inicia explosão
            explosao->flag = 1;
    }
}

void DesenhaExplosao(AnimacaoItem *explosao, Rectangle playerPos, Vector2 *renderPos) {
    Vector2 pos;
    int screenShake = 2;

    pos.x = playerPos.x + playerPos.width/2 - 32;
    pos.y = playerPos.y - (explosao->textura.height-playerPos.height);
    explosao->source.x += 64;

    DrawTextureRec(explosao->textura, explosao->source, pos, WHITE);
    DrawText("-1", playerPos.x, playerPos.y-explosao->source.x/64, 1, Fade(WHITE, 64/explosao->source.x*20));

    // SCREEN SHAKE
    if (explosao->source.x < explosao->textura.width/2) {
        if (rand() > RAND_MAX/2)
            screenShake *= -1;
        if (fabs(renderPos->x + screenShake) < 4)
            renderPos->x += screenShake;

        if (rand() > RAND_MAX/2)
            screenShake *= -1;
        if (fabs(renderPos->y + screenShake) < 4)
            renderPos->y += screenShake;
    }
    else {
        renderPos->x -= renderPos->x/5;
        renderPos->y -= renderPos->y/5;
    }

    // RESETA VARIÁVEIS
    if (explosao->source.x == explosao->textura.width-64) {
        explosao->flag = 0;
        explosao->source.x = 0;
        *renderPos = (Vector2){0.0f, 0.0f};
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

void RenderJogo(Mapa mapa, Texture2D tileset, Player *player, int frames, AnimacaoArr *caixa, AnimacaoItem *explosao, Vector2 *renderPos,
                AnimacaoItem itens[N_ITENS]) {
        int i;

        // Bordas laterais
        int alturaTela = TAM_TILES*mapa.linhas;
        int larguraTela = TAM_TILES*mapa.colunas;
        int larguraBorda = TAM_TILES/2;

        DrawRectangle(0, 0, larguraBorda, alturaTela, BLACK);
        DrawRectangle(larguraTela - larguraBorda, 0, larguraBorda, alturaTela, BLACK);

        DesenhaTiles(mapa, tileset, caixa, frames);

        for (i = 0; i < N_ITENS; i++) {
            if (itens[i].flag == 1) {
                DesenhaItem(itens, player->render, frames, i, explosao);
            }
        }

        DesenhaPlayer(player, frames);

        if (explosao->flag == 1)
            DesenhaExplosao(explosao, player->render, renderPos);
}
