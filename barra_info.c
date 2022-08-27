#include "raylib.h"
#include "barra_info.h"

/* * * WIP * * */
void BarraInformacoes(float posBarra, float tamBarra, Font fonte, Texture2D vidaTextura) {
    int i;
    float tamFonte = tamBarra*0.8f;
    char *informacoes;
    char chave[50] = "Chave Encontrada";
    Vector2 tamStrChave = MeasureTextEx(fonte, chave, tamFonte, 1);

    vidaTextura.width *= tamBarra/vidaTextura.width;
    vidaTextura.height = vidaTextura.width;

    /* TESTES
    Essas variáveis virão como parâmetros */
    int level = 1;
    int pontos = 1500;
    int vidas = 3;
    bool chaveEncontrada = false;
    if (IsKeyDown(KEY_K)) chaveEncontrada = true;
    /* ---------------------------------- */

    // String que segura as informações
    informacoes = TextFormat("Vidas: \t\t\t\t\t\t\tNivel: %d \t Pontos: %d", level, pontos);

    // Desenhando a barra e o texto na tela:
    DrawRectangle(0, posBarra, GetScreenWidth(), tamBarra, (Color){25,25,35,255});
    DrawTextEx(fonte, informacoes, (Vector2){5.0f,posBarra+5}, tamFonte, 1, RAYWHITE);
    if (chaveEncontrada)
        DrawTextEx(fonte, chave, (Vector2){GetScreenWidth()-5.0f-tamStrChave.x,posBarra+5}, tamFonte, 1, RAYWHITE);
    for (i = 0; i < vidas; i++)
        DrawTexture(vidaTextura, MeasureTextEx(fonte, "Vidas:  ", tamFonte, 1).x + i*vidaTextura.width, posBarra, WHITE);
}
