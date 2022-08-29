#ifndef CAIXAS_H
#define CAIXAS_H

#include "mapa.h"
#include "jogo.h"

//Constantes para caixas
#define CHAVE 1
#define BOMBA 2

//MACROS PARA ITENS. Probabilidade de cada item (numero aleatorio gerado vai de 0 a 9)
#define COROA (item == 9) //10%
#define ANEL (item == 8) //10%
#define RUBI (item > 5) //(6, 7) -> 20%
#define SAFIRA (item > 2) //(3, 4, 5) -> 30%
                        //Ametista (0, 1, 2) -> 30%

void preencheCaixas (int caixasTotal, int fase, int caixas[MAX_CAIXAS]);
void geraitens (int caixasTotal, int caixas[MAX_CAIXAS]);
int abreCaixa (int contagemCaixas, int caixas[MAX_CAIXAS], Mapa *mapa, Player *player);

#endif // CAIXAS_H

