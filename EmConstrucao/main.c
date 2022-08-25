#include "raylib.h"
#include "controleMatriz.h"

//Adicionar às constantes do jogo
#define CHAVE 1
#define BOMBA 2
#define MAX_CAIXAS 7

//Probabilidade de cada item (numero aleatorio gerado vai de 0 a 9)
#define COROA (item == 9) //10% 
#define ANEL (item == 8) //10%
#define RUBI (item > 5) //(6, 7) -> 20%
#define SAFIRA (item > 2) //(3, 4, 5) -> 30%
                        //Ametista (0, 1, 2) -> 30%


/* Funcao recebe o número de caixas da fase e 
    gera array com o valor dos bens aleatórios + chave 
    Bombas = 2, Chave = 1, Bens = pontuação respectiva 
    OBS: Inicializar vetor de caixas com 0s   */

void preencheCaixas (int numeroCaixas, int fase, int caixas[MAX_CAIXAS]){

    int index;
    srand(time(NULL));

    //Gera indice aleatorio entre 0 e o número de caixas
    index = rand() % numeroCaixas;
    caixas[index] = CHAVE;

    //Distribuição de bombas (1ª fase -> 1 bomba..)
    for (int i = 0; i < fase; i++){

        index = rand() % numeroCaixas;

        if (caixas[index] != CHAVE)
            caixas[index] = BOMBA;

    }

    //Para caixas restantes, gerar bens aleatórios
    geraitens(numeroCaixas, fase, caixas);

}

/*  Funcao auxiliar que gera itens para caixas restantes
    baseados nas probabilidades definidas nas constantes 
    COROA, ANEL, RUBI, SAFIRA, (AMETISTA). */

void geraitens (int numeroCaixas, int fase, int caixas[MAX_CAIXAS]){

    int index;

    //Gera itens para o numero de caixas sem bombas
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
            else    //Caso Ametista
                caixas[index] = 50;

        }


    }

}

/* Função chamada ao interagir com caixas. 
    Retorna o valor do item recebido 
    BOMBA = 1, CHAVE = 2, BEM = Pontuação correspondente */

int abreCaixa (int *contagemCaixas, int caixas[MAX_CAIXAS], char mapa[MAPA_L][MAPA_C], Player player){
    
    //Número da caixa aberta pelo player. Resetado a cada nova fase.
    *contagemCaixas++;

    /* Para identificar caixa que já foi aberta. Caso animação de abrir baú 
        seja possível, desenvolver função para isso. 
        Sprites de baú (do mesmo criador que fez os outros sprites que usamos)
        https://brullov.itch.io/2d-platformer-asset-pack-castle-of-despair  */

    mapa[player.x][player.y] = 'O';

    return caixas[contagemCaixas];
}