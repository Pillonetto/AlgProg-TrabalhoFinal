#include <math.h>
#include <ctype.h>
#include "raylib.h"
#include "render_player.h"
#include "render_jogo.h"
#include "jogo.h"

/* Controla a posição e estado de animação do render com base na distância entre o render
e a posição do player na matriz */
void AnimaPlayerPos(Player *player, char mapa[MAPA_L][MAPA_C], int c) {
    int playerX = player->x * TAM_TILES;
    int playerY = player->y * TAM_TILES;

    // Movimentação horizontal --------------------------------
    // Tolerância de 0.05
    if (player->render.x != playerX)
    {
        // Andando para a esquerda
        if (player->render.x > playerX) {
                player->render.x -= 1;
                player->estado = ANDANDO;
                player->direcao = P_ESQUERDA;
        }
        // Andando para a direita
        else if (player->render.x < playerX) {
                player->render.x += 1;
                player->estado = ANDANDO;
                player->direcao = P_DIREITA;
        }
    }

    // Movimentação vertical ----------------------------------
    // Tolerância de 0.05
    else if (fabs(player->render.y - playerY) > 0.05)
    {
        // Escada para cima
        if (player->render.y > playerY) {
            player->render.y -= 1;
            player->estado = ESCADA;
        }
        /* Escada para baixo
        Se desloca pela escada se o player estiver em uma escada e a dist. entre o render
        e o player for menor ou igual a 1 tile */
        else if (mapa[player->y][player->x] == 'H' && fabs(player->render.y - playerY) <= TAM_TILES) {
            player->render.y += 1;
            player->estado = ESCADA;
        }
        // Caindo (WIP)
        else {
            player->render.y += 3;
            player->estado = CAINDO;
        }
    }

    // Idle ---------------------------------------------------
    else player->estado = IDLE;
}

// Realiza a animação do sprite do player de forma cíclica
void AnimaPlayerSprite(Player *player, int frames, int numSprites, int frameRate) {
    // Passa para a próxima animação cada x frames
    if (frames % frameRate == 0)
        player->spriteAtual.x += player->spriteAtual.width;
    // Quando for para o último sprite, reseta a animação
    if (player->spriteAtual.x > numSprites * player->spriteAtual.width)
        player->spriteAtual.x = 0;
}

void DesenhaPlayer(Player *player, int frames) {
    Rectangle source;

    // Posiciona o retângulo de sourcing do sprite na linha equivalente ao estado atual
    player->spriteAtual.y = player->spriteAtual.height * player->estado;

    switch(player->estado)
    {
        case IDLE:
            AnimaPlayerSprite(player, frames, 5, 7);
            break;
        case ANDANDO:
            AnimaPlayerSprite(player, frames, 8, 6);
            break;
        case ESCADA:
            AnimaPlayerSprite(player, frames, 6, 5);
        case CAINDO:
            AnimaPlayerSprite(player, frames, 5, 15);
    }

    source = player->spriteAtual;
    /* Caso o player esteja andando para a esquerda e o retângulo de source tenha largura
    positiva, inverte a largura (invertendo a orientação do sprite) */
    if (player->direcao == P_ESQUERDA && source.width > 0)
        source.width *= -1;

    DrawTexturePro(player->textura, source, player->render, (Vector2){0.0f,0.0f}, 0, WHITE);
}
