#ifndef RENDER_PLAYER_H
#define RENDER_PLAYER_H

#include "jogo.h"

// MACROS ESTADO PLAYER
#define IDLE     0
#define ANDANDO  1
#define ESCADA   2
#define CAINDO   3
#define MORRENDO 4

// MACROS DIRECAO PLAYER
#define P_DIREITA  +1
#define P_ESQUERDA -1

void AnimaPlayerPos(Player *player, char mapa[MAPA_L][MAPA_C], int c);
void AnimaPlayerSprite(Player *player, int frames, int numSprites, int frameRate);
void DesenhaPlayer(Player *player, int frames);

#endif // RENDER_PLAYER_H
