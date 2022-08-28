#ifndef JOGO_H
#define JOGO_H

#include "mapa.h"

#define N_ANIM 10

typedef struct {
    Texture2D textura;
    Rectangle source[N_ANIM];
} Animacao;

typedef struct {
    Texture2D textura;
    int x; // Posição X (horizontal) do player na matriz
    int y; // Posição Y (vertical) do player na matriz
    int estado; // Estado do player (idle, andando, caindo, etc)
    int direcao; // Direcao que o player está olhando (+1: direita, -1: esquerda)
    Rectangle spriteAtual; // Corresponde ao sprite sendo usado atualmente (source para o DrawTexturePro)
    Rectangle render; // Retângulo que representa o player na tela do jogo (dest. para o DrawTexturePro)
} Player;

void Jogo(Mapa mapa, Texture2D tileset, Player *player, int frames, Animacao *caixa);
void MovimentoVertical(Mapa mapa, Player *player, int direcao);
void MovimentoHorizontal(Mapa mapa, Player *player, int direcao);
void busca_porta(Mapa mapa, int playerX, int playerY, int *x_porta, int *y_porta);

#endif // JOGO_H
