#ifndef JOGO_H
#define JOGO_H

#include "mapa.h"

typedef struct {
    Texture2D textura;
    int x; // Posição X (horizontal) do player na matriz
    int y; // Posição Y (vertical) do player na matriz
    int estado; // Estado do player (idle, andando, caindo, etc)
    int direcao; // Direcao que o player está olhando (+1: direita, -1: esquerda)
    Rectangle spriteAtual; // Corresponde ao sprite sendo usado atualmente (source para o DrawTexturePro)
    Rectangle render; // Retângulo que representa o player na tela do jogo (dest. para o DrawTexturePro)
} Player;

void Jogo(char mapa[MAPA_L][MAPA_C], int l, int c, Texture2D tileset, Player *player, int frames);
void MovimentoVertical(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, Player *player, int direcao);
void MovimentoHorizontal(char mapa[MAPA_L][MAPA_C], int colunas, Player *player, int direcao);
void busca_porta(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, int playerX, int playerY, int *x_porta, int *y_porta);

#endif // JOGO_H
