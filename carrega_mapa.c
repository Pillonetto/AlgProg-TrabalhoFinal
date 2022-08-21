#include <stdio.h>

#define MAPA_L 30
#define MAPA_C 120

void carrega_mapa(char mapa[MAPA_L][MAPA_C], int *linhas, int *colunas);

int main() {
    char mapa[MAPA_L][MAPA_C];
    int l, c;

    carrega_mapa(mapa, &l, &c);

    return 0;
}

void carrega_mapa(char mapa[MAPA_L][MAPA_C], int *linhas, int *colunas) {
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
}
