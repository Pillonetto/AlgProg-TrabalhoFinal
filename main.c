#include "raylib.h"
#include "barra_info.h"
#include "fundo.h"
#include "menu_principal.h"
#include "render_jogo.h"
#include "mapa.h"
#include "caixas.h"

// Macro para a escala dos objetos na tela
#define SCALE Scale(render.texture.height)

void RedimensionarJanela(Rectangle render);
void ContaFrames(int *frames);
float Scale(float alturaRender);

int main() {

    int i;

    InitWindow(800, 600, "Trabalho Final de Sandro e Gabriel");
    SetTargetFPS(60);


    // VARIÁVEIS -----------------------------------------------------

    Mapa mapa;

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

    // Tileset usado nos mapas
    Texture2D tileset = LoadTexture("resources/oak_woods_tileset.png");
    // Sprites usados pelo player
    player.textura = LoadTexture("resources/player_sprite.png");
    player.spriteAtual.width = player.textura.width/8;
    player.spriteAtual.height = player.textura.height/5;
    player.spriteAtual.x = 0;
    player.spriteAtual.y = 0;
    // Fonte usada no menu
    Font fonteMenu = LoadFontEx("resources/alagard.ttf", 50, 0, 250);
    // Coração usado na barra do jogo
    Texture2D vidaTextura = LoadTexture("resources/life_points.png");
    // Spritesheet utilizado para as caixas
    AnimacaoArr caixa;
    caixa.textura = LoadTexture("resources/chest_sprite.png");
    for (i = 0; i < N_ANIM; i++)
        caixa.source[i] = (Rectangle){0, 0, 30, 24};
    /* Fundo do jogo, contendo a textura de cada camada e suas posições */
    Background bg[N_BG];
    bg[0].textura = LoadTexture("resources/background_layer_1.png");
    bg[1].textura = LoadTexture("resources/background_layer_2.png");
    bg[2].textura = LoadTexture("resources/background_layer_3.png");
    for (i = 0; i < N_BG; i++)
        bg[i].y = -bg[i].textura.height/(i+2);
    // Spritesheet utilizado nas explosões (bombas)
    AnimacaoItem explosao;
    explosao.textura = LoadTexture("resources/explosion.png");
    explosao.source = (Rectangle){0, 0, 64, 40};
    explosao.flag = 0;
    /* Sprites usados nos itens das caixas
    [0: Chave, 1: Bomba, 2: Coroa, 3: Anel, 4: Rubi, 5: Safira, 6: Ametista] */
    AnimacaoItem itens[N_ITENS];
    itens[0].textura = LoadTexture("resources/key.png");
    itens[1].textura = LoadTexture("resources/bomb.png");
    itens[2].textura = LoadTexture("resources/crown.png");
    itens[3].textura = LoadTexture("resources/ring.png");
    itens[4].textura = LoadTexture("resources/ruby.png");
    itens[5].textura = LoadTexture("resources/sapphire.png");
    itens[6].textura = LoadTexture("resources/amethyst.png");
    for (i = 0; i < N_ITENS; i++) {
        itens[i].source = (Rectangle){0, 0, itens[i].textura.width/6, itens[i].textura.height};
        itens[i].dest = itens[i].source;
        itens[i].rotation = 0;
        itens[i].flag = 0;
        itens[i].velocidade = 2.5;
    }


    // Textura onde será renderizado o jogo
    RenderTexture2D render = LoadRenderTexture(bg[0].textura.width/2, bg[0].textura.height/2);
    Rectangle renderSource = {.width=render.texture.width, .height=-render.texture.height}; // OpenGL inverte a textura por padrão
    Rectangle renderDest = {.width=render.texture.width*SCALE, .height=render.texture.height*SCALE};
    Vector2 renderPos = {0, 0};

    select = (Rectangle){.y = 3 * render.texture.height*SCALE/4,
                         .width = render.texture.width*SCALE};

    //VARIAVEIS QUE DEVEM SER INICIALIZADAS A CADA NOVA FASE. Usadas aqui para testes

    int caixasTotal = 4;
    int fase = 1;
    int caixasAbertas = 0;
    //Vetor que contem os itens que o player recebera
    int caixas[MAX_CAIXAS] = { 0 };

    //Preenchimento do vetor acima
    preencheCaixas(caixasTotal, fase, caixas);

    //FIM DE VARIAVEIS DE CAIXAS ---------------------------------------------------

    // LOOP DO JOGO --------------------------------------------------
    while (!WindowShouldClose() && !fecharJogo)
    {
        // Desenha o jogo na textura ------------------------------------------
        BeginTextureMode(render);

        ClearBackground(BLACK);
        switch(telaAtual)
        {
            case MENU:
                DesenhaFundoMenu(bg, frames);
                break;

            case JOGO:
                /* Inicialização do jogo
                Organizar em funções após criar o sistema de níveis */
                if (IsKeyPressed(KEY_R)) jogoInit = false; // teste
                if (!jogoInit)
                {
                    CarregaMapa(&mapa);
                    for (i = 0; i < N_BG; i++) {
                        bg[i].x = -bg[i].textura.width/2;
                        bg[i].y = 0;
                    }
                    player.render = (Rectangle){.width = TAM_TILES,
                                                .height = TAM_TILES,
                                                .x = (player.x * TAM_TILES),
                                                .y = (player.y * TAM_TILES)};
                    player.x = 6;
                    player.y = 6;
                    player.render.x = player.x * TAM_TILES;
                    player.render.y = player.y * TAM_TILES;
                    UnloadRenderTexture(render);
                    render = LoadRenderTexture(TAM_TILES*mapa.colunas, TAM_TILES*mapa.linhas + TAM_BARRA);
                    renderDest.width = render.texture.width*SCALE;
                    renderDest.height = render.texture.height*SCALE;
                    renderSource.width = render.texture.width;
                    renderSource.height = -render.texture.height;
                    jogoInit = true;
                }
                DesenhaFundoJogo(bg, TAM_TILES*mapa.linhas, player);
                Jogo(&mapa, tileset, &player, frames, &caixa, &caixasAbertas, caixas, &explosao, &renderPos, itens);
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

            ClearBackground(BLACK);
            DrawTexturePro(render.texture, renderSource, renderDest, renderPos, 0, WHITE);
            switch(telaAtual)
            {
                case MENU:
                    MenuPrincipal(render, fonteMenu, &opc, &telaAtual, &select);
                    break;

                case JOGO:
                    BarraInformacoes(TAM_TILES*mapa.linhas*SCALE, TAM_BARRA*SCALE, fonteMenu, vidaTextura);
                    break;
            }


        EndDrawing();

        ContaFrames(&frames);
}

    // DESLIGANDO PROGRAMA -------------------------------------------

    // Unloading de resources
    UnloadFont(fonteMenu);
    UnloadTexture(tileset);
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
    return 3 * GetMonitorHeight(0) / (4 * alturaRender);
}
