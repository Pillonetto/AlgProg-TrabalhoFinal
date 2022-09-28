#ifndef MAPA_H
#define MAPA_H

#define MAPA_L 30  // N MAX de linhas do mapa
#define MAPA_C 120 // N MAX de colunas do mapa

typedef struct {
    char matriz[MAPA_L][MAPA_C];
    int linhas;
    int colunas;
    int fim;
    int fim_x;
    int fim_y;
} Mapa;

void CarregaMapa(Mapa *mapa, int fase);

#endif // MAPA_H
