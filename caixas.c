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
    OBS: Inicializar vetor de caixas com 0s

    @param caixasTotal Numero de caixas na fase atual
    @param fase Numero da fase atual. Utilizado para determinar quantidade de bombas geradas
    @param caixas Vetor que recebera os itens gerados. */

void preencheCaixas (int caixasTotal, int fase, int caixas[MAX_CAIXAS]){

    int index, bomba = fase;
    srand(time(NULL));

    //Reseta o vetor de caixas
    for (int i = 0; i < MAX_CAIXAS; i++)
        caixas[i] = 0;

    //Gera indice aleatorio entre 0 e o n�mero de caixas
    index = (rand() % caixasTotal);
    caixas[index] = CHAVE;

    printf("Posicao da chave %d\n", index);

    //Distribuicaoo de bombas (1� fase -> 1 bomba..)
    while (bomba) {

        index = rand() % caixasTotal;

        if (caixas[index] != CHAVE){
            caixas[index] = BOMBA;
            bomba--;
            printf("Posicao das bombas %d\n", index);
        }


    }

    //Para caixas restantes, gerar bens aleat�rios
    geraitens(caixasTotal, caixas);

}

/*  Funcao auxiliar que gera itens preenche caixas restantes
    baseados nas probabilidades definidas nas constantes
    COROA, ANEL, RUBI, SAFIRA, (AMETISTA).

    @param caixasTotal Numero de caixas presentes na fase
    @param caixas Vetor que ira conter os valores dos itens gerados para esta fase */

void geraitens (int caixasTotal, int caixas[MAX_CAIXAS]){

    //Gera itens para o numero de caixas
    for (int j = 0; j < caixasTotal; j++){

        //Se caixa estiver vazia
        if (caixas[j] == 0){

            //Gera numero aleatorio entre 0 e 9 para definir item
            int item = rand() % 10;

            //Interpretacao do numero aleatorio gerado
            if (COROA)
                caixas[j] = 300;

            else if (ANEL)
                caixas[j] = 200;

            else if (RUBI)
                caixas[j] = 150;

            else if (SAFIRA)
                caixas[j] = 100;

            else    //Caso Ametista
                caixas[j] = 50;

        }


    }

}

/* Fun��o chamada ao interagir com caixas.
    Retorna o valor do item recebido.
    BOMBA = 1, CHAVE = 2, BEM = Pontua��o correspondente

    @param contagemCaixas Numero de caixas já abertas pelo jogador (inicializado para 0 em cada nova fase)
    @param caixas Vetor com os itens desta fase
    @param *mapa Utilizado para identificar baús já abertos
    @param *player Utilizado para identificar a posição do jogador.

    @return Valor do item recebido ao abrir caixa */

int abreCaixa (int contagemCaixas, int caixas[MAX_CAIXAS], Mapa *mapa, Player *player){

    //Atualizacao da matriz para caixa aberta
    mapa->matriz[player->y][player->x] = 'O';

    //Para testes
    printf("Caixa numero %d  ", contagemCaixas);

    int itemRecebido = caixas[contagemCaixas];

    //Retorna o valor do item que esta na caixa contagemCaixas
    return itemRecebido;
}
