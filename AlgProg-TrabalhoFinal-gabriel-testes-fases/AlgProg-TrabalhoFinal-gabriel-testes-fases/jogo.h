#ifndef JOGO_H
#define JOGO_H

#include "mapa.h"
#include "raylib.h"

#define N_ANIM 10
#define N_ITENS 7
#define MAX_CAIXAS 7

/* Estrutura utilizada em casos onde s�o necess�rias m�ltiplas
inst�ncias de uma textura (exemplo: caixas) */
typedef struct {
    Texture2D textura;
    Rectangle source[N_ANIM];
} AnimacaoArr;

/* Estrutura utilizada para sprites animados de itens */
typedef struct {
    Texture2D textura;
    Rectangle source;
    Rectangle dest;
    float rotation;
    int flag; // [0, 1]: Determina se a anima��o deve ocorrer ou n�o
    float velocidade; // Velocidade de movimenta��o do render
} AnimacaoItem;

typedef struct {
    Texture2D textura;
    int x; // Posi��o X (horizontal) do player na matriz
    int y; // Posi��o Y (vertical) do player na matriz
    int vidas;
    int pontos;
    int chave;
    int fase;
    int estado; // Estado do player (idle, andando, caindo, etc)
    int direcao; // Direcao que o player est� olhando (+1: direita, -1: esquerda)
    Rectangle spriteAtual; // Corresponde ao sprite sendo usado atualmente (source para o DrawTexturePro)
    Rectangle render; // Ret�ngulo que representa o player na tela do jogo (dest. para o DrawTexturePro)
} Player;

void inicializaPlayer(Player *player);
void Jogo(Mapa *mapa, Texture2D tileset, Player *player, int frames, AnimacaoArr *caixa, int *caixasAbertas,
          int caixas[MAX_CAIXAS], AnimacaoItem *explosao, Vector2 *renderPos, AnimacaoItem itens[N_ITENS]);
void MovimentoVertical(Mapa *mapa, Player *player, int direcao, int *caixasAbertas, int caixas[MAX_CAIXAS], AnimacaoItem itens[N_ITENS]);
void MovimentoHorizontal(Mapa *mapa, Player *player, int direcao);
void busca_porta(Mapa mapa, int playerX, int playerY, int *x_porta, int *y_porta);

#endif // JOGO_H
