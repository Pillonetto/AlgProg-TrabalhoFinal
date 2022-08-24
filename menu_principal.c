#include "definicoes.h"

void AtualizaMenu(Font fonteMenu, int *opc) {
    // Se uma das setas verticais for pressionada com o menu "zerado", coloca a opcão em 0
    if (*opc == -1 && (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN)))
        *opc = 0;

    // SETA PARA CIMA
    else if (IsKeyPressed(KEY_UP)) {
        if (*opc == 0)
            *opc = N_OPCOES-1;
        else
            *opc = *opc - 1;
    }
    // SETA PARA BAIXO
    else if (IsKeyPressed(KEY_DOWN)) {
        if (*opc == N_OPCOES-1)
            *opc = 0;
        else
            *opc = *opc + 1;
    }
}

void DesenhaMenu(RenderTexture2D render, Font fonte, int selecionada, Rectangle *select) {
    char textoMenu[N_OPCOES][20] = {"Novo Jogo", "Carregar Jogo", "Ranking", "Sair"};
    int i;
    Vector2 textoPos;

    for (i = 0; i < N_OPCOES; i++) {
        // Alinha o texto horizontalmente ao centro da tela
        textoPos.x = (GetScreenWidth() - MeasureTextEx(fonte, textoMenu[i], TAM_FONTE, 0).x) / 2;
        // Coloca o texto na segunda metade vertical da tela, com a metade do tamanho da fonte de espaçamento
        textoPos.y = GetScreenHeight()/2 + (i*(TAM_FONTE*1.5));

        // Desenha e anima um retângulo em cima da opção selecionada
        if (i == selecionada)
        {
            /* Anima o retângulo chegando na posição selecionada, movendo-se em 1/3 da distância
            entre o retângulo e o texto a cada frame*/
            if (select->y != textoPos.y)
                select->y += (textoPos.y - select->y)/3;

            DrawRectangleRec(*select, Fade(BLACK, 0.65));
        }
        // Desenha as opções
        DrawTextEx(fonte, textoMenu[i], textoPos, TAM_FONTE, 1, WHITE);
    }
}

void MenuPrincipal(RenderTexture2D render, Font fonteMenu, int *opc, int *telaAtual, Rectangle *select) {

    AtualizaMenu(fonteMenu, opc);

    // Muda a tela conforme a opção escolhida
    if (IsKeyPressed(KEY_ENTER)) {
        switch(*opc) {
            case 0:
            case 1:
                *telaAtual = JOGO;
                break;
            case 2:
                *telaAtual = RANK;
                break;
            case 3:
                *telaAtual = FECHAR;
        }
    }

    ClearBackground(BLACK);
    DesenhaMenu(render, fonteMenu, *opc, select);
}
