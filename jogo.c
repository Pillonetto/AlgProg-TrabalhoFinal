#include <stdio.h>
#include <ctype.h>
#include "raylib.h"
#include "render_player.h"
#include "render_jogo.h"
#include "jogo.h"
#include "caixas.h"

void Jogo(Mapa *mapa, Texture2D tileset, Player *player, int frames, AnimacaoArr *caixa, int *caixasAbertas, int caixas[MAX_CAIXAS], AnimacaoItem *explosao) {

    if (player->estado == IDLE)
    {
        // funções de movimentação aqui:
        if (IsKeyPressed(KEY_LEFT))
            MovimentoHorizontal(mapa, player, -1);
        if (IsKeyPressed(KEY_RIGHT))
            MovimentoHorizontal(mapa, player, +1);
        if (IsKeyPressed(KEY_UP))
            MovimentoVertical(mapa, player, -1, caixasAbertas, caixas, explosao);
        if (IsKeyPressed(KEY_DOWN))
            MovimentoVertical(mapa, player, +1, caixasAbertas, caixas, explosao);
        if (IsKeyPressed(KEY_C)) // DEBUG: Cair
            player->y = 8;
    }

    AnimaPlayerPos(player, mapa->matriz);
    RenderJogo(*mapa, tileset, player, frames, caixa, explosao);
}

void MovimentoVertical(Mapa *mapa, Player *player, int direcao, int *caixasAbertas, int caixas[MAX_CAIXAS], AnimacaoItem *explosao){

    //Localizacao do player e portas na matriz mapa
    char posAtualPlayer = mapa->matriz[player->y][player->x];
    int portaX, portaY, item;

    //Player esta em porta?
    if (isdigit(posAtualPlayer) && direcao == -1){
        busca_porta(*mapa, player->y, player->x, &portaY, &portaX);

        player->x = portaX;
        player->y = portaY;
        player->render.x = portaX*24;
        player->render.y = portaY*24;

        return;

    }

    //Caso player esteja interagindo com caixa
    if(posAtualPlayer == 'C'){

        //Recebe o valor do item da caixa aberta
        item = abreCaixa(*caixasAbertas, caixas, mapa, player);

        //Aumenta a contagem de caixas abertas
        ++(*caixasAbertas);

        //Para testes
        printf("ITEM RECEBIDO %d\n", item);

        //Interpretacao do item recebido
        switch(item){

                case CHAVE:
                    //Som?
                    //chaveEncontrada = true;
                    break;
                case BOMBA:
                    explosao->flag = 1;
                    //vidas--;
                    break;
                default:
                    //pontos += item;

        }

        return;

    }

    //Impede o jogador de andar por paredes
    if (mapa->matriz[player->y + direcao][player->x] == 'X')
        return;

    //Se player estiver em escada ou em cima de escada, atualiza o valor X conforme o movimento desejado
    if (posAtualPlayer == 'H' || mapa->matriz[player->y+direcao][player->x] == 'H'){

        //ESTADO->ESCADA
        player->y += direcao;

    }
    //Se nao estiver em escada, movimento vertical nao e permitido

}

void MovimentoHorizontal(Mapa *mapa, Player *player, int direcao){

    int colunas = mapa->colunas;
    //Variavel de contagem da altura da queda
    int blocosQueda = 0;

    //Impede o jogador de sair dos limites do mapa
    if (player->x + direcao > colunas || player->x + direcao < 0)
        return;

    //Impede o jogador de andar sobre paredes
    if (mapa->matriz[player->y][player->x + direcao] == 'X')
        return;

    //ESTADO->ANDANDO

    //Atualiza o valor Y conforme movimento desejado
    player->x += direcao;

    //Char da matriz abaixo da posicao atual do player
    char posAbaixo = mapa->matriz[player->y + 1][player->x];

    //Player andou para posicao sem chao?

    //Enquanto jogador nao estiver sobre escada ou chao
    while (posAbaixo != 'H' && posAbaixo != 'X'){

        //ESTADO->CAINDO

        player->y++;
        blocosQueda++;

        //Para continuar realizando teste da posicao abaixo
        posAbaixo = mapa->matriz[player->y + 1][player->x];

    }

        /* Queda de mais de 3 blocos reduz vida.
           Inserir funcao/variavel de controle de vidas quando construida(s) */

        //ESTADO->MORRENDO

}


void busca_porta(Mapa mapa, int playerX, int playerY, int *x_porta, int *y_porta) {

    int linhas = mapa.linhas;
    int colunas = mapa.colunas;

 /* Como a porta em que se localiza o player nao eh apagada da matriz, os testes
    buscam porta de mesmo numero, mas de posicao diferente do parametro passado */


    for (int i = 0; i < linhas; i++){

        for (int j = 0; j < colunas; j++){

            if ( mapa.matriz[i][j] == mapa.matriz[playerX][playerY] && (i != playerX && j != playerY) ) {

                *x_porta = i;
                *y_porta = j;

            }

        }

    }
}
