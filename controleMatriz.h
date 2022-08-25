#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAPA_L 30
#define MAPA_C 120

void carrega_mapa(char mapa[MAPA_L][MAPA_C], int *linhas, int *colunas, char *porta, int *escada);
void imprime_mapa(char mapa[MAPA_L][MAPA_C], int linhas, int colunas);
void localiza_jogador(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, int *x_jog, int *y_jog);
void busca_porta(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, int playerX, int playerY, int *x_porta, int *y_porta);
