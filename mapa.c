#include <string.h>
#include "mapa.h"

/* Funcao carrega mapa para funcao main de acordo com o nome da fase atual.

    @param mapa do jogo
    @param numero de fase */

void CarregaMapa(Mapa *mapa, int fase) {

    mapa->fim = 0;

    switch (fase) {
        case 1:
            strcpy(mapa->matriz[0], "XXXXXXXXXXX");
            strcpy(mapa->matriz[1], "X1 C  C2  X");
            strcpy(mapa->matriz[2], "XXHX  XX  X");
            strcpy(mapa->matriz[3], "XCH    1  X");
            strcpy(mapa->matriz[4], "XXX HXHX XX");
            strcpy(mapa->matriz[5], "X   H H   X");
            strcpy(mapa->matriz[6], "X   H HC2 X");
            strcpy(mapa->matriz[7], "X HXX XXXXX");
            strcpy(mapa->matriz[8], "X H X     X");
            strcpy(mapa->matriz[9], "XXXXXXXXXXX");
            mapa->linhas = 10;
            mapa->colunas = 11;
            mapa->fim_x = 9;
            mapa->fim_y =  8;
            break;

        case 2:
            //Mapa 2
            strcpy(mapa->matriz[0], "XXXXXXXXXXX");
            strcpy(mapa->matriz[1], "X         X");
            strcpy(mapa->matriz[2], "X C 2   1CX");
            strcpy(mapa->matriz[3], "XXXXXXH XXX");
            strcpy(mapa->matriz[4], "X     H C X");
            strcpy(mapa->matriz[5], "X 2   HXXXX");
            strcpy(mapa->matriz[6], "XXX  CH   X");
            strcpy(mapa->matriz[7], "X   XXXXH X");
            strcpy(mapa->matriz[8], "X   C 1 H X");
            strcpy(mapa->matriz[9], "XXXXXXXXXXX");
            mapa->linhas = 10;
            mapa->colunas = 11;
            mapa->fim_x = 1;
            mapa->fim_y =  5;
            break;

        case 3:
            //Mapa3
            strcpy(mapa->matriz[0], "XXXXXXXXXXX");
            strcpy(mapa->matriz[1], "XC2  C  1CX");
            strcpy(mapa->matriz[2], "XXX  XXHXXX");
            strcpy(mapa->matriz[3], "X   C  H  X");
            strcpy(mapa->matriz[4], "XXXXXXXX  X");
            strcpy(mapa->matriz[5], "X      C  X");
            strcpy(mapa->matriz[6], "X 2 XXXXH X");
            strcpy(mapa->matriz[7], "XXXX    H X");
            strcpy(mapa->matriz[8], "X    1  HCX");
            strcpy(mapa->matriz[9], "XXXXXXXXXXX");
            mapa->linhas = 10;
            mapa->colunas = 11;
            mapa->fim_x = 5;
            mapa->fim_y =  5;
            break;
    }

}
