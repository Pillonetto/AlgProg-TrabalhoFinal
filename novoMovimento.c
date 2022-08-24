#include "controleMatriz.h"
#include "definicoes.h"

void MovimentoVertical(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, Player *player, int direcao){

    //Localização do player e portas na matriz mapa
    char posAtualPlayer = mapa[player->y][player->x];
    int portaX, portaY;

    //Player está em porta?

    if (isalpha(posAtualPlayer)){
        //Se player estiver em escada, atualiza o valor X conforme o movimento desejado
        if (posAtualPlayer == 'H' && mapa[player->y + 1][player->x] == 'H'){

            //ESTADO->ESCADA

            player->y -= direcao;

        }
        //Se não estiver em escada, movimento vertical não é permitido

        /*  A DEFINIR

        if(posAtualPlayer == 'C')
            //Interacao com caixa

        */

    }

    else if (isdigit(posAtualPlayer)){
        busca_porta(mapa, linhas, colunas, player->y, player->x, &portaY, &portaX);

        player->x = portaX;
        player->y = portaY;
        player->render.x = portaX*24;
        player->render.y = portaY*24;

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

    //Char da matriz abaixo da posição atual do player
    char posAbaixo = mapa[player->y + 1][player->x];

    //Player andou para posição sem chão?

    if (posAbaixo == ' '){

        //Variável de contagem da altura da queda
        int blocosQueda = 0;

        //Enquanto jogador não estiver sobre escada ou chão
        while (posAbaixo != 'H' && posAbaixo != 'X'){

            //ESTADO->CAINDO

            player->y++;
            blocosQueda++;

            //Para continuar realizando teste da posição abaixo
            posAbaixo = mapa[player->y + 1][player->x];

        }

        /* Queda de mais de 3 blocos reduz vida.
           Inserir função/variável de controle de vidas quando construída(s) */

        //ESTADO->MORRENDO

    }

}

