#ifndef RANKING_H
#define RANKING_H

#define NOME_SIZE 3
#define RANKING_SIZE 10

typedef struct {

    char nome[NOME_SIZE];
    int pontos;

} Score;

int checkInserir(Score ranking[RANKING_SIZE], int pontos);
void insereScore(Score ranking[RANKING_SIZE], Score entrada, int posicao);
void salvaRanking(Score ranking[RANKING_SIZE]);
void leRanking(Score ranking[RANKING_SIZE]);

#endif // RANKING_H
