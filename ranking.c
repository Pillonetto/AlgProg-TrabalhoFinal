#include "raylib.h"
#include "ranking.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "menu_principal.h"
// Retorna a posicao onde um Score deve ser colocado no ranking, garantindo que ficara ordenado.
// Se pontuacao nao foi suficiente para o ranking, retorna -1
int checkInserir(Score ranking[RANKING_SIZE], int pontos){

    int pos = -1;

    for(int i = 0; i < RANKING_SIZE; i++){

        if(pontos >= ranking[i].pontos)
            pos++;
        else
            break;

    }
    //Se pos > -1, sabemos que eh pra inserir na posicao retornada.
    return pos;

}
// Atualiza o array de Scores e salva o arquivo ranks.
void insereScore(Score ranking[RANKING_SIZE], Score entrada, int posicao){

    //Realizar alteracao em todos os valores abaixo da entrada
    for(int i = 0; i < posicao; i++){

        ranking[i] = ranking[i + 1];
    }

    ranking[posicao] = entrada;
    //Atualiza o arquivo.
    salvaRanking(ranking);

}
// Salva em ranks.txt os nomes e pontuacoes do ranking
void salvaRanking(Score ranking[RANKING_SIZE]){


    FILE *ranks = fopen("game_files/ranks.txt", "w+");

    if(ranks == NULL){
        printf("SalvaRanking : Erro ao ler arquivo\n");
        printf("Error number: %d", errno);
        return 1;
    }


    for(int i = 0; i < RANKING_SIZE; i++){

        fprintf(ranks, "%s %d\n", ranking[i].nome, ranking[i].pontos);

    }

    fclose(ranks);

}
// Carrega os nomes e pontuacoes para um array de Scores
void leRanking(Score ranking[RANKING_SIZE]){

    FILE *ranks = fopen("game_files/ranks.txt", "r");

    if(ranks == NULL){
        printf("Erro ao ler arquivo");
        printf("Error number: %d", errno);
        return 1;
    }

    Score copia;

    for(int i = 0; i < RANKING_SIZE; i++){

        fscanf(ranks, "%s %d", &copia.nome, &copia.pontos);
        ranking[i] = copia;

    }

    fclose(ranks);

}

void menuRank(Font fonte, Score ranking[], int *telaAtual) {
    char textoEnunciado[][50] = {"Ranking", "Aperte ENTER para sair"};
    int tamFonte = GetScreenHeight()/20;
    Vector2 textoPos;

    if (IsKeyPressed(KEY_ENTER)) {
        *telaAtual = MENU;
    }

    textoPos.x = (GetScreenWidth() - MeasureTextEx(fonte, textoEnunciado[0], tamFonte*1.5, 0).x) / 2;
    textoPos.y = (tamFonte*2);
    DrawTextEx(fonte, textoEnunciado[0], textoPos, tamFonte*1.5, 1, WHITE);

    textoPos.x = (GetScreenWidth() - MeasureTextEx(fonte, textoEnunciado[1], tamFonte, 0).x) / 2;
    textoPos.y = GetScreenHeight() - (tamFonte*3);
    DrawTextEx(fonte, textoEnunciado[1], textoPos, tamFonte, 1, WHITE);

    textoPos.y = GetScreenHeight()/2 - tamFonte*6;

    for (int i = 0; i < RANKING_SIZE; i++) {
        textoPos.x = GetScreenWidth()/2 - MeasureTextEx(fonte, "00. abcdefghijk", tamFonte, 0).x;
        textoPos.y += tamFonte;
        DrawTextEx(fonte, TextFormat("%2.d.\t%s", i+1, ranking[RANKING_SIZE-i-1].nome), textoPos, tamFonte, 0, WHITE);
        textoPos.x += 2*GetScreenWidth()/5 - MeasureTextEx(fonte, TextFormat("%d", ranking[RANKING_SIZE-i-1].pontos), tamFonte, 0).x;
        DrawTextEx(fonte, TextFormat("%d", ranking[RANKING_SIZE-i-1].pontos), textoPos, tamFonte, 0, GOLD);
    }
}
