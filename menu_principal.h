#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H

// TELAS ---------------------------------------
#define FECHAR -1
#define MENU    0
#define JOGO    1
#define LOAD    2
#define RANK    3
#define SAVE    4

#define N_OPCOES 4 // Número de opções no menu principal
#define N_OPCOES_SL 2 // Número de opções do menu de load

void AtualizaMenu(Font fonteMenu, int *opc, int nOpcoes);
void DesenhaMenu(RenderTexture2D render, Font fonte, int selecionada, Rectangle *select);
void MenuPrincipal(RenderTexture2D render, Font fonteMenu, int *opc, int *telaAtual, Rectangle *select);

#endif // MENU_PRINCIPAL_H
