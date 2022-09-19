#ifndef SAVE_H
#define SAVE_H

#include "jogo.h"
#include "mapa.h"

void menuSave(Mapa mapa, Player player, Font fonte, int *opc, int *telaAtual, Rectangle *select);
void salvaJogo (Mapa mapa, Player player);
void recuperaJogo (Mapa *mapa, Player *player);

#endif // SAVE_H
