#include "mapa.h"

void CarregaMapa(char mapa[MAPA_L][MAPA_C], int *linhas, int *colunas) {
    strcpy(mapa[0], "XXXXXXXXXXX");
    strcpy(mapa[1], "X1 C  C2  X");
    strcpy(mapa[2], "XXHX  XX  X");
    strcpy(mapa[3], "XCH    1  X");
    strcpy(mapa[4], "XXX HXHX XX");
    strcpy(mapa[5], "X   H H   X");
    strcpy(mapa[6], "X   H HC2 X");
    strcpy(mapa[7], "X HXX XXXXX");
    strcpy(mapa[8], "X H X    PX");
    strcpy(mapa[9], "XXXXXXXXXXX");
    *linhas = 10;
    *colunas = 11;
}
