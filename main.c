#include "raylib.h"
#include "controleMatriz.c"

void moveVert(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, char *porta, int *escada, int direcao);
void moveHor(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, char *porta, int *escada, int direcao);

int main(void) {

    char mapa[MAPA_L][MAPA_C];
    int linhas, colunas, escada;
    char porta, mov;

    carrega_mapa(mapa, &linhas, &colunas, &porta, &escada);


    do{

        imprime_mapa(mapa, linhas, colunas);
        printf("Informe movimento ");
        scanf(" %c", &mov);

        switch(mov){

            case 'w':
                moveVert(mapa, linhas, colunas, &porta, &escada, -1);
                break;
            case 's':
                moveVert(mapa, linhas, colunas, &porta, &escada, 1);
                break;
            case 'a':
                moveHor(mapa, linhas, colunas, &porta, &escada, -1);
                break;
            case 'd':
                moveHor(mapa, linhas, colunas, &porta, &escada, 1);
                break;
        }
    } while(mov != 'q');

    return 0;
}

void moveVert(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, char *porta, int *escada, int direcao){

    int jogX, jogY, porX, porY;

    localiza_jogador(mapa, linhas, colunas, &jogX, &jogY);

    //se jogador estiver tentando sair do mapa
    if(jogX + direcao > linhas)
        return;

    if (*porta == ' '){

        //se estiver em escada, sobe e checa se ainda esta em escada
        if (direcao == -1 && *escada){

                *escada = (mapa[jogX + direcao][jogY] == 'H')? 1 : 0;

                mapa[jogX + direcao][jogY] = 'D';
                mapa[jogX][jogY] = 'H';

        }

        //se for para baixo, checa se pode descer, desce e muda a flag de escada
        else if(direcao == 1 && mapa[jogX + direcao][jogY] == 'H'){

            mapa[jogX + direcao][jogY] = 'D';

            if (*escada)
                mapa[jogX][jogY] = 'H';
            else
                mapa[jogX][jogY] = ' ';

            *escada = 1;

        }

    }
    //se estiver em uma porta
    else {

        busca_porta(mapa, linhas, colunas, *porta, &porX, &porY);

        //atualizar posicao atual do jogador para porta correspondente e atualizar porta anterior
        mapa[jogX][jogY] = *porta;

        mapa[porX][porY] = 'D';

    }

}

void moveHor(char mapa[MAPA_L][MAPA_C], int linhas, int colunas, char *porta, int *escada, int direcao){

    int jogX, jogY;
    localiza_jogador(mapa, linhas, colunas, &jogX, &jogY);

    //se jogador estiver tentando sair do mapa
    if (jogY + direcao > colunas || jogY + direcao < 0)
        return;

    if (mapa[jogX][jogY + direcao] != 'X'){

        //se estava em uma escada ou porta, repoe escada ou porta na matriz
        if (*escada){
            mapa[jogX][jogY] = 'H';
        }
        else if (*porta != ' '){
            mapa[jogX][jogY] = *porta;
            *porta = ' ';
        }
        else
            mapa[jogX][jogY] = ' ';

        //se esta indo para uma porta, atualiza a variavel porta
        if (isdigit(mapa[jogX][jogY + direcao]))
            *porta = mapa[jogX][jogY + direcao];


        mapa[jogX][jogY + direcao] = 'D';

        *escada = (mapa[jogX - 1][jogY + direcao] == 'H') ? 1 : 0;

        //se o persongem andou para uma posicao sem chao
        if (mapa[jogX + 1][jogY + direcao] == ' '){

            int blocos = 0;
            localiza_jogador(mapa, linhas, colunas, &jogX, &jogY);

            while (mapa[jogX + 1][jogY] == ' ' || isdigit(mapa[jogX + 1][jogY])){

                //checa se o jogador vai cair em uma porta
                if (isdigit(mapa[jogX + 1][jogY]))
                    *porta = mapa[jogX + 1][jogY];

                //move o jogador para baixo e atualiza a contagem de blocos
                mapa[jogX + 1][jogY] = 'D';
                mapa[jogX][jogY] = ' ';
                blocos++;

                //pra testar se vai cair mais
                localiza_jogador(mapa, linhas, colunas, &jogX, &jogY);

            }


        }

    }

}

