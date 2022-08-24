#include "definicoes.h"

// Fundo no menu: movimenta-se para a esquerda e volta à origem quando alcança o fim da tela
void DesenhaFundoMenu(Background bg[N_BG], int frames) {
    int i;
    for (i = 0; i < N_BG; i++) {
        /* ANIMAÇÃO VERTICAL DO FUNDO -------------
        Enquanto a origem do fundo estiver acima (val menor) da origem da tela, aumenta a pos y
        do fundo em um valor 100x menor que a distância entre a origem da tela e a origem do fundo,
        com um coeficiente relacionado ao índice do fundo */
        if (bg[i].y < 0)
            bg[i].y -= (float)-bg[i].textura.height/(i+2) / 250;

        /* ANIMAÇÃO HORIZONTAL DO FUNDO -----------
        Aumenta a posição horizontal do fundo em uma qtd equivalente à sua posição no vetor */
            bg[i].x += (float)(i+1)/2;
        /* Se a origem da textura for maior que a origem da tela, retorna o centro da textura
        para a origem da tela */
        if (bg[i].x >= 0)
            bg[i].x = -bg[i].textura.width/2;

        DrawTextureEx(bg[i].textura, (Vector2){bg[i].x, bg[i].y}, 0, 1, WHITE);
    }
}

// Fundo no jogo: movimenta-se conforme a posição do jogador no mapa */
void DesenhaFundoJogo(Background bg[N_BG], int alturaMapa, Player player) {
    int i;
    float scaleBg = alturaMapa / (float)(bg[0].textura.height/2);
    float posBg = -(bg[2].x + ((float)bg[2].textura.width/2));
    float posPlayer = (player.render.x/2);

    for (i = 0; i < N_BG; i++) {
        if (posBg != posPlayer) {
            bg[i].x += (posBg - posPlayer) / (i + 1);
        }
        DrawTextureEx(bg[i].textura, (Vector2){bg[i].x, bg[i].y}, 0, scaleBg, WHITE);
    }
}
