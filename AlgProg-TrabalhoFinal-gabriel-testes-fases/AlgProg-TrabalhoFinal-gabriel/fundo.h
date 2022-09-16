#ifndef FUNDO_H
#define FUNDO_H

#include "jogo.h"

#define N_BG 3 // N�mero de imagens de fundo

typedef struct {
    Texture2D textura;
    float x; // Posi��o horizontal do background na tela
    float y; // Posi��o vertical do background na tela
} Background;

void DesenhaFundoMenu(Background bg[N_BG], int frames);
void DesenhaFundoJogo(Background bg[N_BG], int alturaMapa, Player player);

#endif // FUNDO_H
