#include "definicoes.h"

// Fundo no menu: movimenta-se para a esquerda e volta à origem quando alcança o fim da tela
void DesenhaFundoMenu(Background bg[N_BG]) {
    int i;
    for (i = 0; i < N_BG; i++) {
        /* ANIMAÇÃO VERTICAL DO FUNDO -------------
        Enquanto a origem do fundo estiver acima (val menor) da origem da tela, aumenta a pos y
        do fundo em um valor 100x menor que a distância entre a origem da tela e a origem do fundo,
        com um coeficiente relacionado ao índice do fundo */
        if (bg[i].y != 0)
            bg[i].y += (float)(0 - bg[i].y)/100 * (i+1);

        /* ANIMAÇÃO HORIZONTAL DO FUNDO -----------
        Aumenta a posição horizontal do fundo em uma qtd equivalente à sua posição no vetor */
        bg[i].x += (i+1)*2;
        /* Se a origem da textura for maior que a origem da tela, retorna o centro da textura
        para a origem da tela */
        if (bg[i].x >= 0)
            bg[i].x = -bg[i].textura.width/2*SCALE;

        DrawTextureEx(bg[i].textura, (Vector2){bg[i].x, bg[i].y}, 0, SCALE, WHITE);
    }
}

// Fundo no jogo: movimenta-se conforme a posição do jogador no mapa */
// WIP
void DesenhaFundoJogo(Background bg[N_BG], int tilesTam, int l) {
    int i;
    for (i = 0; i < N_BG; i++) {
        DrawTextureEx(bg[i].textura, (Vector2){bg[i].x, bg[i].y}, 0, SCALE*0.9, WHITE);
    }
}
