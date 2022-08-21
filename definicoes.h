#include "raylib.h"

/* Pega a resolução do monitor e coloca em uma resolução
no formato 4:3 com 55% do tamanho */
#define RES_HORIZONT (int)GetMonitorWidth(0)/2 * 1.1
#define RES_VERTICAL (int)RES_HORIZONT/4 * 3 * 1.1

#define MAPA_L 30  // N MAX de linhas do mapa
#define MAPA_C 120 // N MAX de colunas do mapa

#define SCALE (float)RES_VERTICAL/180 // Escala dos assets do jogo
#define SCALE_TILES SCALE*0.70 // Escala dos tiles na tela

// CONSTANTES MENU -----------------------------
#define N_OPCOES 4 // Número de opções no menu principal
#define TAM_FONTE RES_VERTICAL/15 // Tamanho (vertical) da fonte
#define N_BG 3 // Número de imagens de fundo
#define TAM_V_FUNDO RES_VERTICAL/bg[0].textura.height // Tamanho vertical do fundo

// TELAS ---------------------------------------
#define FECHAR -1
#define MENU    0
#define JOGO    1
#define RANK    2

/* MACROS PARA TILES
Determinam se a posição em questão está ocupada (caso não esteja fora dos limites) */
#define CIMA  (mapa[l-1][c]=='X' && l-1 != -1)
#define BAIXO (mapa[l+1][c]=='X' && l+1 != lMax)
#define DIR   (mapa[l][c+1]=='X' && c+1 != cMax)
#define ESQ   (mapa[l][c-1]=='X' && c-1 != -1)

// Tamanho dos tiles e bordas na tela
#define TAM_TILES (tileset.width * SCALE_TILES) // Tamanho real de cada tile na tela
#define TAM_BORDAS (RES_HORIZONT - (c*TAM_TILES))/2 // Tamanho das bordas laterais do jogo

// MACROS ESTADO PLAYER
#define IDLE     0
#define ANDANDO  1
#define ESCADA   2
#define CAINDO   3
#define MORRENDO 4

// MACROS DIRECAO PLAYER
#define P_DIREITA  +1
#define P_ESQUERDA -1


// ESTRUTURAS ----------------------------------
typedef struct {
    Texture2D textura;
    int width; // Largura de cada sprite na textura
    int height; // Altura de cada sprite na textura
} Sprite;

typedef struct {
    Texture2D textura;
    int x; // Posição horizontal do background na tela
    int y; // Posição vertical do background na tela
} Background;

typedef struct {
    Texture2D textura;
    int x; // Posição X (horizontal) do player na matriz
    int y; // Posição Y (vertical) do player na matriz
    int estado; // Estado do player (idle, andando, caindo, etc)
    int direcao; // Direcao que o player está olhando (+1: direita, -1: esquerda)
    Rectangle spriteAtual; // Corresponde ao sprite sendo usado atualmente (source para o DrawTexturePro)
    Rectangle render; // Retângulo que representa o player na tela do jogo (destination para o DrawTexturePro)
} Player;
