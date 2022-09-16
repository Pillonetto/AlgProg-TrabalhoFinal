#include <string.h>
#include "mapa.h"

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
            break;

        case 3:
            //Mapa3
            break;
    }

}
