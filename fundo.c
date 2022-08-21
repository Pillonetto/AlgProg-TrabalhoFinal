#include "definicoes.h"

// Fundo no menu: movimenta-se para a esquerda e volta � origem quando alcan�a o fim da tela
void DesenhaFundoMenu(Background bg[N_BG]) {
    int i;
    for (i = 0; i < N_BG; i++) {
        /* ANIMA��O VERTICAL DO FUNDO -------------
        Enquanto a origem do fundo estiver acima (val menor) da origem da tela, aumenta a pos y
        do fundo em um valor 100x menor que a dist�ncia entre a origem da tela e a origem do fundo,
        com um coeficiente relacionado ao �ndice do fundo */
        if (bg[i].y != 0)
            bg[i].y += (float)(0 - bg[i].y)/100 * (i+1);

        /* ANIMA��O HORIZONTAL DO FUNDO -----------
        Aumenta a posi��o horizontal do fundo em uma qtd equivalente � sua posi��o no vetor */
        bg[i].x += (i+1)*2;
        /* Se a origem da textura for maior que a origem da tela, retorna o centro da textura
        para a origem da tela */
        if (bg[i].x >= 0)
            bg[i].x = -bg[i].textura.width/2*SCALE;

        DrawTextureEx(bg[i].textura, (Vector2){bg[i].x, bg[i].y}, 0, SCALE, WHITE);
    }
}

// Fundo no jogo: movimenta-se conforme a posi��o do jogador no mapa */
// WIP
void DesenhaFundoJogo(Background bg[N_BG], int tilesTam, int l) {
    int i;
    for (i = 0; i < N_BG; i++) {
        DrawTextureEx(bg[i].textura, (Vector2){bg[i].x, bg[i].y}, 0, SCALE*0.9, WHITE);
    }
}
