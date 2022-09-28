#include "ranking.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
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


