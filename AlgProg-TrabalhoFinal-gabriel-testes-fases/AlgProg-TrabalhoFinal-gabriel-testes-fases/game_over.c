#include "raylib.h"
#include "game_over.h"
#include "menu_principal.h"

void gameOver(Font fonte, int *opc, int *telaAtual, Rectangle *select, int *menuInit) {
    char textoEnunciado[][50] = {"Game Over", "Deseja entrar para o ranking?"};
    char textoOpcoes[N_OPCOES_GO][25] = {"Sim", "Nao"};
    int i;
    Vector2 textoPos;
    int tamFonte = GetScreenHeight()/20;
    Rectangle selectS = *select;
    selectS.height = tamFonte;

    AtualizaMenu(fonte, opc, N_OPCOES_GO);

    if (IsKeyPressed(KEY_ENTER)) {
        if (*opc == 0) {
            // pede o nome do player e salva as informações
        }
        *opc = -1;
        *telaAtual = MENU;
        *menuInit = false;
    }

    textoPos.x = (GetScreenWidth() - MeasureTextEx(fonte, textoEnunciado[0], tamFonte*1.5, 0).x) / 2;
    textoPos.y = GetScreenHeight()/2 - (tamFonte*5);
    DrawTextEx(fonte, textoEnunciado[0], textoPos, tamFonte*1.5, 1, WHITE);
    textoPos.x = (GetScreenWidth() - MeasureTextEx(fonte, textoEnunciado[1], tamFonte, 0).x) / 2;
    textoPos.y = GetScreenHeight()/2 - (tamFonte*1.5);
    DrawTextEx(fonte, textoEnunciado[1], textoPos, tamFonte, 1, WHITE);

    for (i = 0; i < N_OPCOES_SL; i++) {
        // Alinha o texto horizontalmente ao centro da tela
        textoPos.x = (GetScreenWidth() - MeasureTextEx(fonte, textoOpcoes[i], tamFonte, 0).x) / 2;
        // Coloca o texto na segunda metade vertical da tela, com a metade do tamanho da fonte de espaçamento
        textoPos.y = GetScreenHeight()/2 + (i*(tamFonte*1.5));

        // Desenha e anima um retângulo em cima da opção selecionada
        if (i == *opc)
        {
            /* Anima o retângulo chegando na posição selecionada, movendo-se em 1/3 da distância
            entre o retângulo e o texto a cada frame*/
            if (select->y != textoPos.y)
                select->y += (textoPos.y - select->y)/3;

            DrawRectangleRec(selectS, Fade(BLACK, 0.45));
        }

        // Desenha as opções
        DrawTextEx(fonte, textoOpcoes[i], textoPos, tamFonte, 1, WHITE);
    }
}
