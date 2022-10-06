#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "ranking.h"

void gameOver(Font fonte, int *opc, int *telaAtual, Rectangle *select, int *menuInit, Score ranking[], int *posicao, int pontos);
void menuAddRank(Font fonte, char *nome, Score ranking[], int posicao, int pontos, int *telaAtual, int *menuInit);

#endif // GAME_OVER_H
