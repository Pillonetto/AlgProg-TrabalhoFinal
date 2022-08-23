#include "controleMatriz.h"

void MovimentoVertical(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, Player *player, int direcao){

    //Localização do player e portas na matriz mapa
    char posAtualPlayer = mapa[player->x][player->y];
    int portaX, portaY;
    
    //Impede o jogador de sair dos limites do mapa
    if(player->x + direcao > linhas || player->x + direcao < 0)
        return;

    //Impede o jogador de andar sobre paredes
    if (mapa[player->x + direcao][player->y] == 'X')
        return;

    //Player está em porta?

    if (isalpha(posAtualPlayer)){

        //Se player estiver em escada, atualiza o valor X conforme o movimento desejado
        if (posAtualPlayer == 'H'){

            //ESTADO->ESCADA

            player->x += direcao;

        }
        //Se não estiver em escada, movimento vertical não é permitido
        
        /*  A DEFINIR
        
        if(posAtualPlayer == 'C')
            //Interacao com caixa
            
        */

    }
    
    else if (isdigit(posAtualPlayer)){

        busca_porta(mapa, linhas, colunas, player->x, player->y, &portaX, &portaY);
        
        player->x = portaX;
        player->y = portaY;

    }

}

void MovimentoHorizontal(char mapa[MAPA_L][MAPA_C], int colunas, Player *player, int direcao){

    //Impede o jogador de sair dos limites do mapa
    if (player->y + direcao > colunas || player->y + direcao < 0)
        return;

    //Impede o jogador de andar sobre paredes
    if (mapa[player->x][player->y + direcao] == 'X')
        return;

    //ESTADO->ANDANDO

    //Atualiza o valor Y conforme movimento desejado
    player->y += direcao;

    //Char da matriz abaixo da posição atual do player
    char posAbaixo = mapa[player->x + 1][player->y];

    //Player andou para posição sem chão?

    if (posAbaixo == ' '){

        //Variável de contagem da altura da queda
        int blocosQueda = 0;
        
        //Enquanto jogador não estiver sobre escada ou chão
        while (posAbaixo != 'H' && posAbaixo != 'X'){

            //ESTADO->CAINDO

            player->x++;
            blocosQueda++;

            //Para continuar realizando teste da posição abaixo
            posAbaixo = mapa[player->x + 1][player->y];

        }

        /* Queda de mais de 3 blocos reduz vida.
           Inserir função/variável de controle de vidas quando construída(s) */

        //ESTADO->MORRENDO

    }

}

