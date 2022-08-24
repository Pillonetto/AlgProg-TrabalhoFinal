#include <string.h>
#include "definicoes.h"

void CarregaMapa(char mapa[MAPA_L][MAPA_C], int *linhas, int *colunas);
void MenuPrincipal(RenderTexture2D render, Font fonteMenu, int *opc, int *telaAtual, Rectangle *select);
void Jogo(char mapa[MAPA_L][MAPA_C], int l, int c, Sprite tileset, Player *player, int frames);
void DesenhaFundoMenu(Background bg[N_BG], int frames);
void DesenhaFundoJogo(Background bg[N_BG], int alturaMapa, Player player);
void ContaFrames(int *frames);
void RedimensionarJanela(Rectangle render);
float Scale(float alturaRender);

int main() {

    int i;

    InitWindow(800, 600, "Trabalho Final de Sandro e Gabriel");
    SetTargetFPS(60);


    // VARIÁVEIS -----------------------------------------------------

    // Mapa
    char mapa[MAPA_L][MAPA_C];
    int l, c;

    // Variáveis de controle
    int telaAtual = MENU;
    int frames = 0; // Utilizada em animações
    int opc = -1; // Opção do menu principal selecionada (inic. sem seleção)
    Rectangle select; // Controla o botão de select do menu principal
    Player player;

    // Flags
    int fecharJogo = false;
    int jogoInit = false;


    // RESOURCES -----------------------------------------------------

    /* Tileset usado nos mapas, contendo a textura, a altura de cada
    tile e a largura de cada tile */
    Sprite tileset;
    tileset.textura = LoadTexture("resources/oak_woods_tileset.png");
    tileset.width = tileset.textura.width/23;
    tileset.height = tileset.textura.height/15;
    /* Sprites usados pelo player */
    player.textura = LoadTexture("resources/player_sprite.png");
    player.spriteAtual.width = player.textura.width/8;
    player.spriteAtual.height = player.textura.height/5;
    player.spriteAtual.x = 0;
    player.spriteAtual.y = 0;
    /* Fonte usada no menu */
    Font fonteMenu = LoadFontEx("resources/alagard.ttf", TAM_FONTE, 0, 250);

    /* Fundo do jogo, contendo a textura de cada camada e suas posições */
    Background bg[N_BG];
    bg[0].textura = LoadTexture("resources/background_layer_1.png");
    bg[1].textura = LoadTexture("resources/background_layer_2.png");
    bg[2].textura = LoadTexture("resources/background_layer_3.png");
    for (i = 0; i < N_BG; i++)
        bg[i].y = -bg[i].textura.height/(i+2);

    // Textura onde será renderizado o jogo
    RenderTexture2D render = LoadRenderTexture(bg[0].textura.width/2, bg[0].textura.height/2);
    Rectangle renderSource = {.width=render.texture.width, .height=-render.texture.height}; // OpenGL inverte a textura por padrão
    Rectangle renderDest = {.width=render.texture.width*SCALE, .height=render.texture.height*SCALE};

    select = (Rectangle){.y = 3 * render.texture.height*SCALE/4,
                         .height = TAM_FONTE,
                         .width = render.texture.width*SCALE};

    // LOOP DO JOGO --------------------------------------------------
    while (!WindowShouldClose() && !fecharJogo)
    {
        // Desenha o jogo na textura ------------------------------------------
        BeginTextureMode(render);

        switch(telaAtual)
        {
            case MENU:
                DesenhaFundoMenu(bg, frames);
                break;

            case JOGO:
                /* Inicialização do jogo
                Organizar em funções após criar o sistema de níveis */
                if (!jogoInit)
                {
                    CarregaMapa(mapa, &l, &c);
                    for (i = 0; i < N_BG; i++) {
                        bg[i].x = -bg[i].textura.width/2;
                        bg[i].y = 0;
                    }
                    player.render = (Rectangle){.width = tileset.width,
                                                .height = tileset.height,
                                                .x = (player.x * tileset.width),
                                                .y = (player.y * tileset.height)};
                    player.x = 1;
                    player.y = 1;
                    player.render.x = player.x * tileset.width;
                    player.render.y = player.y * tileset.height;
                    UnloadRenderTexture(render);
                    render = LoadRenderTexture(tileset.width*c, tileset.height*l);
                    renderDest.width = render.texture.width*SCALE;
                    renderDest.height = render.texture.height*SCALE;
                    renderSource.width = render.texture.width;
                    renderSource.height = -render.texture.height;
                    jogoInit = true;
                }
                DesenhaFundoJogo(bg, tileset.width*l, player);
                Jogo(mapa, l, c, tileset, &player, frames);
                break;

            case FECHAR:
                fecharJogo = true;
                break;
        }

        EndTextureMode();

        // Ajusta o tamanho da janela -----------------------------------------
        if (GetScreenWidth() != renderDest.width || GetScreenHeight() != renderDest.height)
            RedimensionarJanela(renderDest);

        // Desenha a textura na tela ------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTexturePro(render.texture, renderSource, renderDest, (Vector2){0.0f,0.0f}, 0, WHITE);
            switch(telaAtual)
            {
                case MENU:
                    MenuPrincipal(render, fonteMenu, &opc, &telaAtual, &select);
                    break;
            }


        EndDrawing();

        ContaFrames(&frames);
}

    // DESLIGANDO PROGRAMA -------------------------------------------

    // Unloading de resources
    UnloadFont(fonteMenu);
    UnloadTexture(tileset.textura);
    for (i = 0; i < N_BG; i++)
        UnloadTexture(bg[i].textura);
    UnloadTexture(player.textura);

    CloseWindow();

    return 0;
}

void RedimensionarJanela(Rectangle render) {
    SetWindowSize(render.width, render.height);
    SetWindowPosition((GetMonitorWidth(0) - render.width)/2, (GetMonitorHeight(0) - render.height)/2);
}

void ContaFrames(int *frames) {
    *frames += 1;
    // Reseta a contagem de frames a cada 5 segundos (300 frames)
    if (*frames > 300)
        *frames = 0;
}

float Scale(float alturaRender) {
    /* Retorna o coeficiente que aumenta a altura da tela para
    2/3 da altura da resolução utilizada pelo monitor */
    return 2 * GetMonitorHeight(0) / (3 * alturaRender);
}

void CarregaMapa(char mapa[MAPA_L][MAPA_C], int *linhas, int *colunas) {
    strcpy(mapa[0], "XXXXXXXXXXX");
    strcpy(mapa[1], "X1 C  C2  X");
    strcpy(mapa[2], "XXHX  XX  X");
    strcpy(mapa[3], "XCH    1  X");
    strcpy(mapa[4], "XXX HXHX XX");
    strcpy(mapa[5], "X   H H   X");
    strcpy(mapa[6], "X   H HC2 X");
    strcpy(mapa[7], "X HXX XXXXX");
    strcpy(mapa[8], "X H X    PX");
    strcpy(mapa[9], "XXXXXXXXXXX");
    *linhas = 10;
    *colunas = 11;
}
