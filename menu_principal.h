#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H

#include "mapa.h"
#include "jogo.h"

// TELAS ---------------------------------------
#define FECHAR   -1
#define MENU      0
#define JOGO      1
#define LOAD      2
#define RANK      3
#define SAVE      4
#define GAME_OVER 5
#define ADD_RANK  6

#define N_OPCOES 4 // Número de opções no menu principal
#define N_OPCOES_SL 2 // Número de opções do menu de load
#define N_OPCOES_GO 2 // Número de opções do menu de game over

void AtualizaMenu(Font fonteMenu, int *opc, int nOpcoes);
void DesenhaMenu(RenderTexture2D render, Font fonte, int selecionada, Rectangle *select);
void MenuPrincipal(RenderTexture2D render, Font fonteMenu, int *opc, int *telaAtual, Rectangle *select);
void ControlaLoad(RenderTexture2D render, Font fonteMenu, int *opc, int *telaAtual, Rectangle *select, Mapa *mapa, Player *player,
                  int *mapaInit, int *playerInit);

#endif // MENU_PRINCIPAL_H
