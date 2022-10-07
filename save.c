#include "save.h"
#include "menu_principal.h"
#include <stdio.h>

void menuSave(Mapa mapa, Player player, Font fonte, int *opc, int *telaAtual, Rectangle *select) {
    char textoEnunciado[] = "Deseja salvar o jogo atual?";
    char textoOpcoes[N_OPCOES_SL][5] = {"Sim", "Nao"};
    int i;
    Vector2 textoPos;
    int tamFonte = GetScreenHeight()/20;
    Rectangle selectS = *select;
    selectS.height = tamFonte;

    AtualizaMenu(fonte, opc, N_OPCOES_SL);

    if (IsKeyPressed(KEY_ENTER)) {
        if (*opc == 0)
            salvaJogo(mapa, player);
        *telaAtual = JOGO;
    }

    textoPos.x = (GetScreenWidth() - MeasureTextEx(fonte, textoEnunciado, tamFonte, 0).x) / 2;
    textoPos.y = GetScreenHeight()/2 - (tamFonte*1.5);
    DrawTextEx(fonte, textoEnunciado, textoPos, tamFonte, 1, WHITE);

    for (i = 0; i < N_OPCOES_SL; i++) {
        // Alinha o texto horizontalmente ao centro da tela
        textoPos.x = (GetScreenWidth() - MeasureTextEx(fonte, textoOpcoes[i], tamFonte, 0).x) / 2;
        // Coloca o texto na segunda metade vertical da tela, com a metade do tamanho da fonte de espa�amento
        textoPos.y = GetScreenHeight()/2 + (i*(tamFonte*1.5));

        // Desenha e anima um ret�ngulo em cima da op��o selecionada
        if (i == *opc)
        {
            /* Anima o ret�ngulo chegando na posi��o selecionada, movendo-se em 1/3 da dist�ncia
            entre o ret�ngulo e o texto a cada frame*/
            if (select->y != textoPos.y)
                select->y += (textoPos.y - select->y)/3;

            DrawRectangleRec(selectS, Fade(BLACK, 0.45));
        }

        // Desenha as op��es
        DrawTextEx(fonte, textoOpcoes[i], textoPos, tamFonte, 1, WHITE);
    }

}

//Salvar Mapa e Player.
void salvaJogo (Mapa mapa, Player player){

    FILE *save = fopen("game_files/jogo.dat", "wb");
    if (save == NULL){
        printf("Erro ao ler arquivo");
        return;
    }
    // Limites do mapa
    fwrite(&mapa.linhas, sizeof(int), 1, save);
    fwrite(&mapa.colunas, sizeof(int), 1, save);
    // Posicao do fim do mapa
    fwrite(&mapa.fim_x, sizeof(int), 1, save);
    fwrite(&mapa.fim_y, sizeof(int), 1, save);
    // Matriz do mapa
    for (int i = 0; i < mapa.linhas; i++)
        fwrite(&mapa.matriz[i], mapa.colunas, 1, save);

    // Posicao do player
    fwrite(&player.x, sizeof(int), 1, save);
    fwrite(&player.y, sizeof(int), 1, save);
    // Vidas e pontos
    fwrite(&player.vidas, sizeof(int), 1, save);
    fwrite(&player.pontos, sizeof(int), 1, save);
    // Esta com a chave?
    fwrite(&player.chave, sizeof(int), 1, save);

    // Numero da fase atual.
    fwrite(&player.fase, sizeof(int), 1, save);

    fclose(save);
}

//Obter informacoes do save
void recuperaJogo (Mapa *mapa, Player *player){

    FILE *save = fopen("game_files/jogo.dat", "rb");

    mapa->fim = 0;

    // Limites do mapa
    fread(&mapa->linhas, sizeof(int), 1, save);
    fread(&mapa->colunas, sizeof(int), 1, save);
    // Fim de fase
    fread(&mapa->fim_x, sizeof(int), 1, save);
    fread(&mapa->fim_y, sizeof(int), 1, save);
    // Matriz do mapa
    for (int i = 0; i < mapa->linhas; i++)
        fread(&mapa->matriz[i], mapa->colunas, 1, save);

    // Posicao do player
    fread(&player->x, sizeof(int), 1, save);
    fread(&player->y, sizeof(int), 1, save);
    // Vidas e pontos
    fread(&player->vidas, sizeof(int), 1, save);
    fread(&player->pontos,  sizeof(int), 1, save);
    // Estava com a chave?
    fread(&player->chave, sizeof(int), 1, save);

    // Numero da fase
    fread(&player->fase, sizeof(int), 1, save);

    fclose(save);

}

