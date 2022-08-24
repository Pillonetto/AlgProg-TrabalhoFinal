#include "definicoes.h"
#include "controleMatriz.h"

void AnimaPlayerPos(Player *player, char mapa[MAPA_L][MAPA_C], int c);
void RenderJogo(char mapa[MAPA_L][MAPA_C], int l, int c, Texture2D tileset, Player *player, int frames);
void MovimentoVertical(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, Player *player, int direcao);
void MovimentoHorizontal(char mapa[MAPA_L][MAPA_C], int colunas, Player *player, int direcao);

void Jogo(char mapa[MAPA_L][MAPA_C], int l, int c, Texture2D tileset, Player *player, int frames) {

    if (player->estado == IDLE)
    {
        // funções de movimentação aqui:
        if (IsKeyPressed(KEY_LEFT))
            MovimentoHorizontal(mapa, c, player, -1);
        if (IsKeyPressed(KEY_RIGHT))
            MovimentoHorizontal(mapa, c, player, +1);
        if (IsKeyPressed(KEY_UP))
            MovimentoVertical(mapa, l, c, player, +1);
        if (IsKeyPressed(KEY_DOWN))
            MovimentoVertical(mapa, l, c, player, -1);
        if (IsKeyPressed(KEY_C)) // DEBUG: Cair
            player->y = 8;
    }

    AnimaPlayerPos(player, mapa, c);
    RenderJogo(mapa, l, c, tileset, player, frames);
}
