#include "raylib.h"
#include "menu_principal.h"
#include "mapa.h"
#include "jogo.h"
#include "render_jogo.h"

void AtualizaMenu(Font fonteMenu, int *opc, int nOpcoes) {
    // Se uma das setas verticais for pressionada com o menu "zerado", coloca a opcão em 0
    if (*opc == -1 && (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN)))
        *opc = 0;

    // SETA PARA CIMA
    else if (IsKeyPressed(KEY_UP)) {
        if (*opc == 0)
            *opc = nOpcoes-1;
        else
            *opc = *opc - 1;
    }
    // SETA PARA BAIXO
    else if (IsKeyPressed(KEY_DOWN)) {
        if (*opc == nOpcoes-1)
            *opc = 0;
        else
            *opc = *opc + 1;
    }
}

void DesenhaMenu(RenderTexture2D render, Font fonte, int selecionada, Rectangle *select) {
    char textoMenu[N_OPCOES][20] = {"Novo Jogo", "Carregar Jogo", "Ranking", "Sair"};
    int i;
    Vector2 textoPos;
    int tamFonte = GetScreenHeight()/15;

    select->height = tamFonte;

    for (i = 0; i < N_OPCOES; i++) {
        // Alinha o texto horizontalmente ao centro da tela
        textoPos.x = (GetScreenWidth() - MeasureTextEx(fonte, textoMenu[i], tamFonte, 0).x) / 2;
        // Coloca o texto na segunda metade vertical da tela, com a metade do tamanho da fonte de espaçamento
        textoPos.y = GetScreenHeight()/2 + (i*(tamFonte*1.5));

        // Desenha e anima um retângulo em cima da opção selecionada
        if (i == selecionada)
        {
            /* Anima o retângulo chegando na posição selecionada, movendo-se em 1/3 da distância
            entre o retângulo e o texto a cada frame*/
            if (select->y != textoPos.y)
                select->y += (textoPos.y - select->y)/3;

            DrawRectangleRec(*select, Fade(BLACK, 0.45));
        }
        // Desenha as opções
        DrawTextEx(fonte, textoMenu[i], textoPos, tamFonte, 1, WHITE);
    }
}

void DesenhaLoad(RenderTexture2D render, Font fonte, int selecionada, Rectangle *select) {
    char textoEnunciado[] = "Deseja carregar o jogo salvo?";
    char textoOpcoes[N_OPCOES_SL][5] = {"Sim", "Nao"};
    int i;
    Vector2 textoPos;
    int tamFonte = GetScreenHeight()/15;

    textoPos.x = (GetScreenWidth() - MeasureTextEx(fonte, textoEnunciado, tamFonte, 0).x) / 2;
    textoPos.y = GetScreenHeight()/2 - (tamFonte*1.5);
    DrawTextEx(fonte, textoEnunciado, textoPos, tamFonte, 1, WHITE);

    for (i = 0; i < N_OPCOES_SL; i++) {
        // Alinha o texto horizontalmente ao centro da tela
        textoPos.x = (GetScreenWidth() - MeasureTextEx(fonte, textoOpcoes[i], tamFonte, 0).x) / 2;
        // Coloca o texto na segunda metade vertical da tela, com a metade do tamanho da fonte de espaçamento
        textoPos.y = GetScreenHeight()/2 + (i*(tamFonte*1.5));

        // Desenha e anima um retângulo em cima da opção selecionada
        if (i == selecionada)
        {
            /* Anima o retângulo chegando na posição selecionada, movendo-se em 1/3 da distância
            entre o retângulo e o texto a cada frame*/
            if (select->y != textoPos.y)
                select->y += (textoPos.y - select->y)/3;

            DrawRectangleRec(*select, Fade(BLACK, 0.45));
        }

        // Desenha as opções
        DrawTextEx(fonte, textoOpcoes[i], textoPos, tamFonte, 1, WHITE);
    }
}

void ControlaLoad(RenderTexture2D render, Font fonteMenu, int *opc, int *telaAtual, Rectangle *select, Mapa *mapa, Player *player,
                  int *mapaInit, int *playerInit) {
    AtualizaMenu(fonteMenu, opc, N_OPCOES_SL);

    if (IsKeyPressed(KEY_ENTER)) {
        switch(*opc) {
            case 0:
                inicializaPlayer(player, *mapa);
                *mapaInit = true;
                *playerInit = true;
                *telaAtual = JOGO;
                recuperaJogo(mapa, player);
                player->render.x = player->x * TAM_TILES;
                player->render.y = player->y * TAM_TILES;
                break;
            case 1:
                *opc = 0;
                *telaAtual = MENU;
                break;
        }
    }

    ClearBackground(BLACK);
    DesenhaLoad(render, fonteMenu, *opc, select);
}

void MenuPrincipal(RenderTexture2D render, Font fonteMenu, int *opc, int *telaAtual, Rectangle *select) {

    AtualizaMenu(fonteMenu, opc, N_OPCOES);

    // Muda a tela conforme a opção escolhida
    if (IsKeyPressed(KEY_ENTER)) {
        switch(*opc) {
            case 0:
                *telaAtual = JOGO;
                break;
            case 1:
                *opc = 0;
                *telaAtual = LOAD;
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
