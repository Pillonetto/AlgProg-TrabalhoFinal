#include <string.h>
#include "raylib.h"
#include "game_over.h"
#include "menu_principal.h"
#include "ranking.h"

void gameOver(Font fonte, int *opc, int *telaAtual, Rectangle *select, int *menuInit, Score ranking[], int *posicao, int pontos) {
    char textoEnunciado[][100] = {"Pontos insuficientes. Ver ranking?", "Deseja entrar para o ranking?", "Fim de jogo!",};
    char textoOpcoes[N_OPCOES_GO][25] = {"Sim", "Nao"};
    int i, ehSufic = 0;
    Vector2 textoPos;
    int tamFonte = GetScreenHeight()/20;
    Rectangle selectS = *select;
    selectS.height = tamFonte;

    *posicao = checkInserir(ranking, pontos);
    if (*posicao > -1)
        ehSufic = 1;

    AtualizaMenu(fonte, opc, N_OPCOES_GO);

    if (IsKeyPressed(KEY_ENTER)) {
        if (*opc == 0) {
            if (ehSufic)
                *telaAtual = ADD_RANK;
            else
                *telaAtual = RANK;
        }
        else {
            *opc = -1;
            *telaAtual = MENU;
        }
        *menuInit = false;
    }

    textoPos.x = (GetScreenWidth() - MeasureTextEx(fonte, textoEnunciado[2], tamFonte*1.5, 0).x) / 2;
    textoPos.y = GetScreenHeight()/2 - (tamFonte*5);
    DrawTextEx(fonte, textoEnunciado[2], textoPos, tamFonte*1.5, 1, WHITE);
    textoPos.x = (GetScreenWidth() - MeasureTextEx(fonte, textoEnunciado[ehSufic], tamFonte, 0).x) / 2;
    textoPos.y = GetScreenHeight()/2 - (tamFonte*1.5);
    DrawTextEx(fonte, textoEnunciado[ehSufic], textoPos, tamFonte, 1, WHITE);

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

void menuAddRank(Font fonte, char *nome, Score ranking[], int posicao, int pontos, int *telaAtual, int *menuInit) {
    char textoEnunciado[][50] = {"Digite seu nome", "(aperte ENTER quando finalizar)"};
    int tamFonte = GetScreenHeight()/20;
    Vector2 textoPos;
    Score entrada;
    int pos = checkInserir(ranking, pontos);

    int letra = GetCharPressed();

    if (letra > 31 && letra < 126 && strlen(nome) < NOME_SIZE) {
        nome[strlen(nome)] = (char)letra;
        nome[strlen(nome)] = '\0';
    }

    if (IsKeyPressed(KEY_BACKSPACE))
        nome[strlen(nome) - 1] = '\0';

    if (IsKeyPressed(KEY_ENTER) && nome[0] != '\0') {
        strcpy(entrada.nome, nome);
        entrada.pontos = pontos;
        insereScore(ranking, entrada, pos);
        for (int i = 0; nome[i] != '\0'; i++)
            nome[i] = '\0';
        *menuInit = false;
        *telaAtual = RANK;
    }

    textoPos.x = (GetScreenWidth() - MeasureTextEx(fonte, textoEnunciado[0], tamFonte*1.5, 0).x) / 2;
    textoPos.y = GetScreenHeight()/2 - (tamFonte*5);
    DrawTextEx(fonte, textoEnunciado[0], textoPos, tamFonte*1.5, 1, WHITE);
    textoPos.x = (GetScreenWidth() - MeasureTextEx(fonte, textoEnunciado[1], tamFonte, 0).x) / 2;
    textoPos.y = GetScreenHeight()/2 - (tamFonte*1.5);
    DrawTextEx(fonte, textoEnunciado[1], textoPos, tamFonte, 1, WHITE);

    textoPos.x = (GetScreenWidth() - MeasureTextEx(fonte, nome, tamFonte*1.5, 0).x) / 2;
    textoPos.y = GetScreenHeight()/2;
    DrawTextEx(fonte, nome, textoPos, tamFonte*1.5, 1, GOLD);
}
