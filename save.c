#include "save.h"
#include <stdio.h>

//Salvar Mapa e Player.
void salvaJogo (Mapa mapa, Player player){

    FILE *save = fopen("jogo.dat", "wb");
    if (save == NULL){
        printf("Erro ao ler arquivo");
        return;
    }
    // Limites do mapa
    fwrite(&mapa.linhas, sizeof(int), 1, save);
    fwrite(&mapa.colunas, sizeof(int), 1, save);
    // Posicao do fim do mapa
    fwrite(&mapa.fim_x, sizeof(int), 1, save);
    fwrite(&mapa.fim_y, sizeof(int), 1, save);
    // Matriz do mapa
    for (int i = 0; i < mapa.linhas; i++)
        fwrite(&mapa.matriz[i], mapa.colunas, 1, save);

    // Posicao do player
    fwrite(&player.x, sizeof(int), 1, save);
    fwrite(&player.y, sizeof(int), 1, save);
    // Vidas e pontos
    fwrite(&player.vidas, sizeof(int), 1, save);
    fwrite(&player.pontos, sizeof(int), 1, save);
    // Esta com a chave?
    fwrite(&player.chave, sizeof(int), 1, save);

    // Numero da fase atual.
    fwrite(&player.fase, sizeof(int), 1, save);

    fclose(save);
}

//Obter informacoes do save
void recuperaJogo (Mapa *mapa, Player *player){

    FILE *save = fopen("jogo.dat", "rb");

    // Limites do mapa
    fread(mapa->linhas, sizeof(int), 1, save);
    fread(mapa->colunas, sizeof(int), 1, save);
    // Fim de fase
    fread(mapa->fim_x, sizeof(int), 1, save);
    fread(mapa->fim_y, sizeof(int), 1, save);
    // Matriz do mapa
    for (int i = 0; i < mapa->linhas; i++)
        fread(mapa->matriz[i], mapa->colunas, 1, save);

    // Posicao do player
    fread(player->x, sizeof(int), 1, save);
    fread(player->y, sizeof(int), 1, save);
    // Vidas e pontos
    fread(player->vidas, sizeof(int), 1, save);
    fread(player->pontos,  sizeof(int), 1, save);
    // Estava com a chave?
    fread(player->chave, sizeof(int), 1, save);

    // Numero da fase
    fread(player->fase, sizeof(int), 1, save);

    fclose(save);

}

