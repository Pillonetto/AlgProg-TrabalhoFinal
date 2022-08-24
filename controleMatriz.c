#include "controleMatriz.h"

/*
 * Fun��o que carrega o mapa do jogo
 * @param mapa matriz de caracteres que representa o mapa do jogo
 * @param *linhas ponteiro para inteiro que guardar� o n�mero de linhas ocupadas pelo mapa do jogo (par�metro de sa�da)
 * @param *colunas ponteiro para inteiro que guardar� o n�mero de colunas ocupadas pelo mapa do jogo (par�metro de sa�da)
 * @param *porta ponteiro para char que guardar� um espa�o em branco (' ') caso o jogador n�o esteja sobre uma porta, ou o identificador da porta, caso o jogador esteja parado sobre uma porta ('1', '2', etc)
 * @param *escada ponteiro para inteiros que indica se o jogador est� parado sobre uma escada. Cont�m o valor 1 caso esteja e 0 caso n�o esteja
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

/*
 * Fun��o que imprime o mapa do jogo na tela
 * @param mapa Mapa do jogo
 * @param linhas n�mero de linhas do mapa
 * @param colunas n�mero de colunas do mapa
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
 * Fun��o que retorna a localiza��o do jogador no mapa
 * @param mapa Mapa do jogo
 * @param linhas n�mero de linhas do mapa
 * @param colunas n�mero de colunas do mapa
 * @param *x_jog par�metro de sa�da, indicando a posi��o da linha do jogador
 * @param *y_jog par�metro de sa�da que indica a posi��o da coluna em que o jogador se encontra
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
 * Fun��o para buscar a localiza��o do par de uma porta no mapa
 * @param mapa Mapa do jogo
 * @param linhas n�mero de linhas do mapa
 * @param colunas n�mero de colunas do mapa
 * @param porta identificador (char) de uma porta
 * @param *x_porta par�metro de sa�da, indicando a posi��o da linha da porta
 * @param *y_porta par�metro de sa�da que indica a posi��o da coluna em que a porta se encontra
 */
void busca_porta(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, int playerX, int playerY, int *x_porta, int *y_porta) {

 /* Como a porta em que se localiza o player não é apagada da matriz, os testes 
    buscam porta de mesmo número, mas de posição diferente do parâmetro passado */


    for (int i = 0; i < linhas; i++){

        for (int j = 0; j < colunas; j++){

            if ( mapa[i][j] == mapa[playerX][playerY] && (i != playerX && j != playerY) ) {

                *x_porta = i;
                *y_porta = j;

            }

        }

    }
}
