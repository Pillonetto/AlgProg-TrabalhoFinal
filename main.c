#include <string.h>
#include "definicoes.h"

void CarregaMapa(char mapa[MAPA_L][MAPA_C], int *linhas, int *colunas);
void MenuPrincipal(Font fonteMenu, int *opc, int *telaAtual, Rectangle *select);
void Jogo(char mapa[MAPA_L][MAPA_C], int l, int c, Sprite tileset, Player *player, int frames);
void DesenhaFundoMenu(Background bg[N_BG]);
void DesenhaFundoJogo(Background bg[N_BG], int tilesTam, int l);
void RedimensionaJanela(Rectangle *janela);

int main() {

    int i;

    InitWindow(800, 600, "Trabalho Final de Sandro e Gabriel");
    SetTargetFPS(60);


    // VARIÁVEIS -----------------------------------------------------

    // Mapa
    char mapa[MAPA_L][MAPA_C];
    int l, c;

    // Variáveis de controle
    Rectangle janela; // Controla o tamanho e posição da janela
    int frames = 0; // Utilizada em animações
    int telaAtual = MENU;
    int opc = -1; // Opção do menu principal selecionada (inic. sem seleção)
    Rectangle select; // Controla o botão de select do menu principal
    select = (Rectangle){.y = 3 * RES_VERTICAL/4, .height = TAM_FONTE, .width = RES_HORIZONT};
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
    Font fonteMenu = LoadFontEx("resources/alagard.ttf", 80, 0, 250);
    /* Fundo do jogo, contendo a textura de cada camada e suas posições */
    Background bg[N_BG];
    bg[0].textura = LoadTexture("resources/background_layer_1.png");
    bg[1].textura = LoadTexture("resources/background_layer_2.png");
    bg[2].textura = LoadTexture("resources/background_layer_3.png");
    for (i = 0; i < N_BG; i++)
        // Inic. para cima da tela (div. por 2 porque a segunda metade da textura é filamento)
        bg[i].y = -bg[i].textura.height/2 * SCALE;


    // LOOP DO JOGO --------------------------------------------------
    while (!WindowShouldClose() && !fecharJogo)
    {
        // Caso o tamanho da janela esteja incorreto, corrige o tamanho e posição
        if (GetRenderWidth() != (int)janela.width || GetRenderHeight() != (int)janela.height)
            RedimensionaJanela(&janela);

        switch(telaAtual)
        {
            case MENU:
                DesenhaFundoMenu(bg);
                MenuPrincipal(fonteMenu, &opc, &telaAtual, &select);
                break;

            case JOGO:
                /* Inicialização do jogo
                Organizar em uma função após criar o sistema de níveis */
                if (!jogoInit)
                {
                    CarregaMapa(mapa, &l, &c);
                    for (i = 0; i < N_BG; i++) {
                        bg[i].x = 0;
                        bg[i].y = 0;
                    }
                    player.render = (Rectangle){.width = TAM_TILES,
                                                .height = TAM_TILES,
                                                .x = (player.x * TAM_TILES) + TAM_BORDAS,
                                                .y = (player.y * TAM_TILES)};
                    player.x = 1;
                    player.y = 1;
                    jogoInit = true;
                }
                DesenhaFundoJogo(bg, tileset.width, l);
                Jogo(mapa, l, c, tileset, &player, frames);
                break;

            case RANK:
                /*
                . . .
                */
                break;

            case FECHAR:
                fecharJogo = true;
                break;
        }

        frames++;
        // Reseta a contagem de frames a cada 5 segundos (300 frames)
        if (frames > 300)
            frames = 0;

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

void RedimensionaJanela(Rectangle *janela) {
    janela->width = RES_HORIZONT;
    janela->height = RES_VERTICAL;
    janela->x = (GetMonitorWidth(0) - RES_HORIZONT) / 2;
    janela->y = (GetMonitorHeight(0) - RES_VERTICAL) / 2;

    SetWindowSize(janela->width, janela->height);
    SetWindowPosition(janela->x, janela->y);
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
