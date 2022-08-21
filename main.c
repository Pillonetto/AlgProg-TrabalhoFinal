#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "raylib.h"

#define MAPA_L 30
#define MAPA_C 120


void carrega_mapa(char mapa[MAPA_L][MAPA_C], int *linhas, int *colunas, char *porta, int *escada);
void moveVert(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, char *porta, int *escada, int direcao);
void moveHor(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, char *porta, int *escada, int direcao);
void imprime_mapa(char mapa[MAPA_L][MAPA_C], int linhas, int colunas);
void localiza_jogador(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, int *x_jog, int *y_jog);
void busca_porta(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, char porta, int *x_porta, int *y_porta);


int main(void) {

    char mapa[MAPA_L][MAPA_C];
    int linhas, colunas, escada;
    char porta, mov;

    carrega_mapa(mapa, &linhas, &colunas, &porta, &escada);


    do{

        imprime_mapa(mapa, linhas, colunas);
        printf("Informe movimento ");
        scanf(" %c", &mov);

        switch(mov){

            case 'w':
                moveVert(mapa, linhas, colunas, &porta, &escada, -1);
                break;
            case 's':
                moveVert(mapa, linhas, colunas, &porta, &escada, 1);
                break;
            case 'a':
                moveHor(mapa, linhas, colunas, &porta, &escada, -1);
                break;
            case 'd':
                moveHor(mapa, linhas, colunas, &porta, &escada, 1);
                break;
        }
    } while(mov != 'q');

    return 0;
}

/*
 * Função que carrega o mapa do jogo
 * @param mapa matriz de caracteres que representa o mapa do jogo
 * @param *linhas ponteiro para inteiro que guardará o número de linhas ocupadas pelo mapa do jogo (parâmetro de saída)
 * @param *colunas ponteiro para inteiro que guardará o número de colunas ocupadas pelo mapa do jogo (parâmetro de saída)
 * @param *porta ponteiro para char que guardará um espaço em branco (' ') caso o jogador não esteja sobre uma porta, ou o identificador da porta, caso o jogador esteja parado sobre uma porta ('1', '2', etc)
 * @param *escada ponteiro para inteiros que indica se o jogador está parado sobre uma escada. Contém o valor 1 caso esteja e 0 caso não esteja
 */
void carrega_mapa(char mapa[MAPA_L][MAPA_C], int *linhas, int *colunas, char *porta, int *escada) {
    strcpy(mapa[0], "XXXXXXXXXX");
    strcpy(mapa[1], "X1 C  C2 X");
    strcpy(mapa[2], "XXHX  XX X");
    strcpy(mapa[3], "XCH    1 X");
    strcpy(mapa[4], "XXX HXHX X");
    strcpy(mapa[5], "X   H H  X");
    strcpy(mapa[6], "X   H HC2X");
    strcpy(mapa[7], "X HXX XXXX");
    strcpy(mapa[8], "XDH X   PX");
    strcpy(mapa[9], "XXXXXXXXXX");
    *linhas = 10;
    *colunas = 10;
    *porta = ' ';
    *escada = 0;
}

void moveVert(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, char *porta, int *escada, int direcao){

    int jogX, jogY, porX, porY;

    localiza_jogador(mapa, linhas, colunas, &jogX, &jogY);

    //se jogador estiver tentando sair do mapa
    if(jogX + direcao > linhas)
        return;

    if (*porta == ' '){

        //se estiver em escada, sobe e checa se ainda esta em escada
        if (direcao == -1 && *escada){

                *escada = (mapa[jogX + direcao][jogY] == 'H')? 1 : 0;

                mapa[jogX + direcao][jogY] = 'D';
                mapa[jogX][jogY] = 'H';

        }

        //se for para baixo, checa se pode descer, desce e muda a flag de escada
        else if(direcao == 1 && mapa[jogX + direcao][jogY] == 'H'){

            mapa[jogX + direcao][jogY] = 'D';

            if (*escada)
                mapa[jogX][jogY] = 'H';
            else
                mapa[jogX][jogY] = ' ';

            *escada = 1;

        }

    }
    //se estiver em uma porta
    else {

        busca_porta(mapa, linhas, colunas, *porta, &porX, &porY);

        //atualizar posicao atual do jogador para porta correspondente e atualizar porta anterior
        mapa[jogX][jogY] = *porta;

        mapa[porX][porY] = 'D';

    }

}

void moveHor(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, char *porta, int *escada, int direcao){

    int jogX, jogY;
    localiza_jogador(mapa, linhas, colunas, &jogX, &jogY);

    //se jogador estiver tentando sair do mapa
    if (jogY + direcao > colunas || jogY + direcao < 0)
        return;

    if (mapa[jogX][jogY + direcao] != 'X'){

        //se estava em uma escada ou porta, repoe escada ou porta na matriz
        if (*escada){
            mapa[jogX][jogY] = 'H';
        }
        else if (*porta != ' '){
            mapa[jogX][jogY] = *porta;
            *porta = ' ';
        }
        else
            mapa[jogX][jogY] = ' ';

        //se esta indo para uma porta, atualiza a variavel porta
        if (isdigit(mapa[jogX][jogY + direcao]))
            *porta = mapa[jogX][jogY + direcao];


        mapa[jogX][jogY + direcao] = 'D';

        *escada = (mapa[jogX - 1][jogY + direcao] == 'H') ? 1 : 0;

        //se o persongem andou para uma posicao sem chao
        if (mapa[jogX + 1][jogY + direcao] == ' '){

            int blocos = 0;
            localiza_jogador(mapa, linhas, colunas, &jogX, &jogY);

            while (mapa[jogX + 1][jogY] == ' ' || isdigit(mapa[jogX + 1][jogY])){

                //checa se o jogador vai cair em uma porta
                if (isdigit(mapa[jogX + 1][jogY]))
                    *porta = mapa[jogX + 1][jogY];

                //move o jogador para baixo e atualiza a contagem de blocos
                mapa[jogX + 1][jogY] = 'D';
                mapa[jogX][jogY] = ' ';
                blocos++;

                //pra testar se vai cair mais
                localiza_jogador(mapa, linhas, colunas, &jogX, &jogY);

            }


        }

}

}

/*
 * Função que imprime o mapa do jogo na tela
 * @param mapa Mapa do jogo
 * @param linhas número de linhas do mapa
 * @param colunas número de colunas do mapa
 */
void imprime_mapa(char mapa[MAPA_L][MAPA_C], int linhas, int colunas) {

//    for (int i = 0; i < linhas; i++){
//        int size = MeasureText(mapa[i], 30);
//        size = 400 - size;
//        Vector2 pos;
//        pos.x = 0;
//        pos.y = (i*30) + 60;
//
//        DrawTextEx(fonte, mapa[i], pos, 30, 5, BLACK);
//    }


     for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            printf("%c", mapa[i][j]);
            printf(" ");
        }

        printf("\n");
    }
    printf("\n");

}

/*
 * Função que retorna a localização do jogador no mapa
 * @param mapa Mapa do jogo
 * @param linhas número de linhas do mapa
 * @param colunas número de colunas do mapa
 * @param *x_jog parâmetro de saída, indicando a posição da linha do jogador
 * @param *y_jog parâmetro de saída que indica a posição da coluna em que o jogador se encontra
 */
void localiza_jogador(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, int *x_jog, int *y_jog) {

    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            if (mapa[i][j] == 'D'){
                *x_jog = i;
                *y_jog = j;
            }
}

/*
 * Função para buscar a localização do par de uma porta no mapa
 * @param mapa Mapa do jogo
 * @param linhas número de linhas do mapa
 * @param colunas número de colunas do mapa
 * @param porta identificador (char) de uma porta
 * @param *x_porta parâmetro de saída, indicando a posição da linha da porta
 * @param *y_porta parâmetro de saída que indica a posição da coluna em que a porta se encontra
 */
void busca_porta(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, char porta, int *x_porta, int *y_porta) {

    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            if (mapa[i][j] == porta){
                *x_porta = i;
                *y_porta = j;
            }
        }
    }
}


