#include "raylib.h"
#include "barra_info.h"

/* * * WIP * * */
void BarraInformacoes(float posBarra, float tamBarra, Font fonte, Texture2D vidaTextura, Player player) {

    int i;
    float tamFonte = tamBarra*0.8f;
    char *informacoes;
    char chave[50] = "Chave Encontrada";
    Vector2 tamStrChave = MeasureTextEx(fonte, chave, tamFonte, 1);

    vidaTextura.width *= tamBarra/vidaTextura.width;
    vidaTextura.height = vidaTextura.width;


    int level = 1;
    int pontos = player.pontos;
    int vidas = player.vidas;
    bool chaveEncontrada = player.chave;

    // String que segura as informa��es
    informacoes = TextFormat("Vidas: \t\t\t\t\t\t\tNivel: %d \t Pontos: %d", level, pontos);

    // Desenhando a barra e o texto na tela:
    DrawRectangle(0, posBarra, GetScreenWidth(), tamBarra, (Color){25,25,35,255});
    DrawTextEx(fonte, informacoes, (Vector2){5.0f,posBarra+5}, tamFonte, 1, RAYWHITE);

    if (chaveEncontrada)
        DrawTextEx(fonte, chave, (Vector2){GetScreenWidth()-5.0f-tamStrChave.x,posBarra+5}, tamFonte, 1, RAYWHITE);
    for (i = 0; i < vidas; i++)
        DrawTexture(vidaTextura, MeasureTextEx(fonte, "Vidas:  ", tamFonte, 1).x + i*vidaTextura.width, posBarra, WHITE);

}

