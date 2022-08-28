#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H

// TELAS ---------------------------------------
#define FECHAR -1
#define MENU    0
#define JOGO    1
#define RANK    2

#define N_OPCOES 4 // Número de opções no menu principal

void AtualizaMenu(Font fonteMenu, int *opc);
void DesenhaMenu(RenderTexture2D render, Font fonte, int selecionada, Rectangle *select);
void MenuPrincipal(RenderTexture2D render, Font fonteMenu, int *opc, int *telaAtual, Rectangle *select);

#endif // MENU_PRINCIPAL_H
