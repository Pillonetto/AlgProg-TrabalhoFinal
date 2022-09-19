#ifndef SAVE_H
#define SAVE_H

#include "jogo.h"
#include "mapa.h"

void salvaJogo (Mapa mapa, Player player);
void recuperaJogo (Mapa *mapa, Player *player);

#endif // SAVE_H
