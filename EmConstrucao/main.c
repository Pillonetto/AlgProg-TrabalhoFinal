#include "raylib.h"
#include "controleMatriz.h"


/* Funcao recebe o número de caixas da fase e 
    gera array com o valor dos bens aleatórios + chave 
    Bombas = 1, Chave = 2, Bens = pontuação respectiva */

void geraItens (int numeroCaixas, int fase, int caixas[MAX_CAIXAS]){

    int itemAtual, index;
    srand(time(NULL));

    //Chave em posição aleatória
    index = rand() % numeroCaixas;
    caixas[index] = CHAVE;

    //Distribuição de bombas (1ª fase -> 1 bomba..)
    for (int i = 0; i < fase; i++){

        //Gera indice aleatorio entre 0 e o número de caixas - 1
        index = rand() % numeroCaixas;

        if (caixas[index] != CHAVE)
            caixas[index] = BOMBA;

    }

    //Para caixas restantes, gerar bens aleatórios
    

}



