#include "raylib.h"

//Adicionar às constantes do jogo
#define BOMBA 1
#define CHAVE 2
#define MAX_CAIXAS 7

//Probabilidade de cada item (numero aleatorio gerado vai de 0 a 9)
#define COROA (item == 9) //10% 
#define ANEL (item == 8) //10%
#define RUBI (item > 5) //(6, 7) -> 20%
#define SAFIRA (item > 2) //(3, 4, 5) -> 30%
                        //Ametista (0, 1, 2) -> 30%


/* Funcao recebe o número de caixas da fase e 
    gera array com o valor dos bens aleatórios + chave 
    Bombas = 1, Chave = 2, Bens = pontuação respectiva 
    OBS: Inicializar vetor de caixas com 0s   */

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

    for (int j = 0; j < numeroCaixas - fase){

        //Gera indice aleatorio entre 0 e o número de caixas - 1
        index = rand() % numeroCaixas;

        //Se caixa estiver vazia
        if (caixas[index] == 0){

            //Gera numero aleatorio entre 0 e 9 para definir item
            int item = rand() % 10;

            //Interpretacao do numero aleatorio gerado
            if (COROA)
                caixas[index] = 300;
            else if (ANEL)
                caixas[index] = 200;
            else if (RUBI)
                caixas[index] = 150;
            else if (SAFIRA)
                caixas[index] = 100;
            else
                caixas[index] = 50;

        }


    }


}



