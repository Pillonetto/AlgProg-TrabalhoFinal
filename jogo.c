#include "raylib.h"
#include "jogo.h"
#include "render_player.h"

void Jogo(char mapa[MAPA_L][MAPA_C], int l, int c, Texture2D tileset, Player *player, int frames) {

    if (player->estado == IDLE)
    {
        // funções de movimentação aqui:
        if (IsKeyPressed(KEY_LEFT))
            MovimentoHorizontal(mapa, c, player, -1);
        if (IsKeyPressed(KEY_RIGHT))
            MovimentoHorizontal(mapa, c, player, +1);
        if (IsKeyPressed(KEY_UP))
            MovimentoVertical(mapa, l, c, player, -1);
        if (IsKeyPressed(KEY_DOWN))
            MovimentoVertical(mapa, l, c, player, +1);
        if (IsKeyPressed(KEY_C)) // DEBUG: Cair
            player->y = 8;
    }

    AnimaPlayerPos(player, mapa, c);
    RenderJogo(mapa, l, c, tileset, player, frames);
}

void MovimentoVertical(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, Player *player, int direcao){

    //Localizacao do player e portas na matriz mapa
    char posAtualPlayer = mapa[player->y][player->x];
    int portaX, portaY;

    //Player esta em porta?
    if (isdigit(posAtualPlayer)){
        busca_porta(mapa, linhas, colunas, player->y, player->x, &portaY, &portaX);

        player->x = portaX;
        player->y = portaY;
        player->render.x = portaX*24;
        player->render.y = portaY*24;

    }
    else {

        //Impede o jogador de andar por paredes
        if (mapa[player->y + direcao][player->x] == 'X')
            return;

        //Se player estiver em escada ou em cima de escada, atualiza o valor X conforme o movimento desejado
        if (posAtualPlayer == 'H' || mapa[player->y+direcao][player->x] == 'H'){

            //ESTADO->ESCADA
            player->y += direcao;

        }
        //Se nao estiver em escada, movimento vertical nao e permitido

        /*  A DEFINIR

        if(posAtualPlayer == 'C')
            //Interacao com caixa

        */

    }

}

void MovimentoHorizontal(char mapa[MAPA_L][MAPA_C], int colunas, Player *player, int direcao){

    //Impede o jogador de sair dos limites do mapa
    if (player->x + direcao > colunas || player->x + direcao < 0)
        return;

    //Impede o jogador de andar sobre paredes
    if (mapa[player->y][player->x + direcao] == 'X')
        return;

    //ESTADO->ANDANDO

    //Atualiza o valor Y conforme movimento desejado
    player->x += direcao;

    //Char da matriz abaixo da posicao atual do player
    char posAbaixo = mapa[player->y + 1][player->x];

    //Player andou para posicao sem chao?

    if (posAbaixo == ' '){

        //Variavel de contagem da altura da queda
        int blocosQueda = 0;

        //Enquanto jogador nao estiver sobre escada ou chao
        while (posAbaixo != 'H' && posAbaixo != 'X'){

            //ESTADO->CAINDO

            player->y++;
            blocosQueda++;

            //Para continuar realizando teste da posicao abaixo
            posAbaixo = mapa[player->y + 1][player->x];

        }

        /* Queda de mais de 3 blocos reduz vida.
           Inserir funcao/variavel de controle de vidas quando construida(s) */

        //ESTADO->MORRENDO

    }

}

void busca_porta(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, int playerX, int playerY, int *x_porta, int *y_porta) {

 /* Como a porta em que se localiza o player nao eh apagada da matriz, os testes
    buscam porta de mesmo numero, mas de posicao diferente do parametro passado */


    for (int i = 0; i < linhas; i++){

        for (int j = 0; j < colunas; j++){

            if ( mapa[i][j] == mapa[playerX][playerY] && (i != playerX && j != playerY) ) {

                *x_porta = i;
                *y_porta = j;

            }

        }

    }
}
