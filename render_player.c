#include "definicoes.h"
#include <math.h>

// Determina se o player est� em cima de uma porta
bool PlayerEmPorta(Player *player, char mapa[MAPA_L][MAPA_C]) {
    return (isdigit(mapa[player->y][player->x]) > 0);
}

/* Controla a posi��o e estado de anima��o do render com base na dist�ncia entre o render
e a posi��o do player na matriz */
void AnimaPlayerPos(Player *player, Sprite tileset, char mapa[MAPA_L][MAPA_C], int c) {
    int playerX = player->x * tileset.width;
    int playerY = player->y * tileset.height;

    /* Teleporte para portas ----------------------------------
    Teleporta o render caso o player esteja em uma porta e a dist�ncia entre o
    render e o player seja maior que 1 tile */
    if ((fabs(player->render.x - playerX) > tileset.width
        || fabs(player->render.y - playerY) > tileset.width)
        && PlayerEmPorta(player, mapa)) {
        player->render.x = playerX;
        player->render.y = playerY;
    }

    // Movimenta��o horizontal --------------------------------
    // Toler�ncia de 0.05
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

    // Movimenta��o vertical ----------------------------------
    // Toler�ncia de 0.05
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
        else if (mapa[player->y][player->x] == 'H' && fabs(player->render.y - playerY) <= tileset.height) {
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

// Realiza a anima��o do sprite do player de forma c�clica
void AnimaPlayerSprite(Player *player, int frames, int numSprites, int frameRate) {
    // Passa para a pr�xima anima��o cada x frames
    if (frames % frameRate == 0)
        player->spriteAtual.x += player->spriteAtual.width;
    // Quando for para o �ltimo sprite, reseta a anima��o
    if (player->spriteAtual.x > numSprites * player->spriteAtual.width)
        player->spriteAtual.x = 0;
}

void DesenhaPlayer(Player *player, int frames) {
    Rectangle source;

    // Posiciona o ret�ngulo de sourcing do sprite na linha equivalente ao estado atual
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
    /* Caso o player esteja andando para a esquerda e o ret�ngulo de source tenha largura
    positiva, inverte a largura (invertendo a orienta��o do sprite) */
    if (player->direcao == P_ESQUERDA && source.width > 0)
        source.width *= -1;

    DrawTexturePro(player->textura, source, player->render, (Vector2){0.0f,0.0f}, 0, WHITE);
}
