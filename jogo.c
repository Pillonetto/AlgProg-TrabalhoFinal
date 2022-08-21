#include "definicoes.h"

void AnimaPlayerPos(Player *player, Sprite tileset, char mapa[MAPA_L][MAPA_C], int c);
void RenderJogo(char mapa[MAPA_L][MAPA_C], int l, int c, Sprite tileset, Player *player, int frames);

void Jogo(char mapa[MAPA_L][MAPA_C], int l, int c, Sprite tileset, Player *player, int frames) {

    if (player->estado == IDLE)
    {
        // funções de movimentação aqui:
        if (IsKeyPressed(KEY_LEFT))
            player->x--;
        if (IsKeyPressed(KEY_RIGHT))
            player->x++;
        if (IsKeyPressed(KEY_UP))
            player->y--;
        if (IsKeyPressed(KEY_DOWN))
            player->y++;
        if (IsKeyPressed(KEY_P)) { // DEBUG: Teleporte porta (sem animação ainda)
            player->y = 3;
            player->x = 7;
        }
        if (IsKeyPressed(KEY_C)) // DEBUG: Cair
            player->y = 8;
    }

    AnimaPlayerPos(player, tileset, mapa, c);
    RenderJogo(mapa, l, c, tileset, player, frames);
}
