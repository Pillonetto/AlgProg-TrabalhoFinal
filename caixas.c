#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "caixas.h"
#include "jogo.h"

/*  Contagem de caixas e vetor caixas devem ser declarados no inicio de cada fase
    Funcao recebe o n�mero de caixas da fase e
    gera array com o valor dos bens aleat�rios + chave
    Bombas = 2, Chave = 1, Bens = pontua��o respectiva
    OBS: Inicializar vetor de caixas com 0s   */

void preencheCaixas (int caixasTotal, int fase, int caixas[MAX_CAIXAS]){

    int index;
    srand(time(NULL));

    //Gera indice aleatorio entre 0 e o n�mero de caixas
    index = (rand() % caixasTotal);
    caixas[index] = CHAVE;

    printf("Posicao da chave %d\n", index);

    //Distribuicaoo de bombas (1� fase -> 1 bomba..)
    for (int i = 0; i < fase; i++){

        index = rand() % caixasTotal;

        printf("Posicao da(s) bomba(s) %d\n", index);

        if (caixas[index] != CHAVE)
            caixas[index] = BOMBA;

    }

    //Para caixas restantes, gerar bens aleat�rios
    geraitens(caixasTotal, caixas);

}

/*  Funcao auxiliar que gera itens preenche caixas restantes
    baseados nas probabilidades definidas nas constantes
    COROA, ANEL, RUBI, SAFIRA, (AMETISTA). */

void geraitens (int caixasTotal, int caixas[MAX_CAIXAS]){

    //Gera itens para o numero de caixas menos o numero de bombas e chave
    for (int j = 0; j < caixasTotal; j++){

        //Se caixa estiver vazia
        if (caixas[j] == 0){

            //Gera numero aleatorio entre 0 e 9 para definir item
            int item = rand() % 10;

            //Interpretacao do numero aleatorio gerado
            if (COROA)
                caixas[j] = 300;

            if (ANEL)
                caixas[j] = 200;

            if (RUBI)
                caixas[j] = 150;

            if (SAFIRA)
                caixas[j] = 100;

            else    //Caso Ametista
                caixas[j] = 50;

        }


    }

}

/* Fun��o chamada ao interagir com caixas.
    Retorna o valor do item recebido.
    BOMBA = 1, CHAVE = 2, BEM = Pontua��o correspondente */

int abreCaixa (int contagemCaixas, int caixas[MAX_CAIXAS], Mapa *mapa, Player *player){

    //Atualizacao da matriz para caixa aberta
    mapa->matriz[player->y][player->x] = 'O';

    //Para testes
    printf("Caixa numero %d  ", contagemCaixas);

    int itemRecebido = caixas[contagemCaixas];

    //Retorna o valor do item que esta na caixa contagemCaixas
    return itemRecebido;
}
