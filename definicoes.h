#include "raylib.h"

#define MAPA_L 30  // N MAX de linhas do mapa
#define MAPA_C 120 // N MAX de colunas do mapa

// Macro para a escala dos objetos na tela
#define SCALE Scale(render.texture.height)

// CONSTANTES MENU -----------------------------
#define N_OPCOES 4 // N�mero de op��es no menu principal
#define TAM_FONTE 50 // Tamanho (vertical) da fonte
#define N_BG 3 // N�mero de imagens de fundo

// TELAS ---------------------------------------
#define FECHAR -1
#define MENU    0
#define JOGO    1
#define RANK    2

/* MACROS PARA TILES
Determinam se a posi��o em quest�o est� ocupada (caso n�o esteja fora dos limites) */
#define CIMA  (mapa[l-1][c]=='X' && l-1 != -1)
#define BAIXO (mapa[l+1][c]=='X' && l+1 != lMax)
#define DIR   (mapa[l][c+1]=='X' && c+1 != cMax)
#define ESQ   (mapa[l][c-1]=='X' && c-1 != -1)

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
    float x; // Posi��o horizontal do background na tela
    float y; // Posi��o vertical do background na tela
} Background;

typedef struct {
    Texture2D textura;
    int x; // Posi��o X (horizontal) do player na matriz
    int y; // Posi��o Y (vertical) do player na matriz
    int estado; // Estado do player (idle, andando, caindo, etc)
    int direcao; // Direcao que o player est� olhando (+1: direita, -1: esquerda)
    Rectangle spriteAtual; // Corresponde ao sprite sendo usado atualmente (source para o DrawTexturePro)
    Rectangle render; // Ret�ngulo que representa o player na tela do jogo (destination para o DrawTexturePro)
} Player;
