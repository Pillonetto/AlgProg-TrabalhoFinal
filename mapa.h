#ifndef MAPA_H
#define MAPA_H

#define MAPA_L 30  // N MAX de linhas do mapa
#define MAPA_C 120 // N MAX de colunas do mapa

typedef struct {
    char matriz[MAPA_L][MAPA_C];
    int linhas;
    int colunas;
} Mapa;

void CarregaMapa(Mapa *mapa);

#endif // MAPA_H
