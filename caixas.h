#ifndef CAIXAS_H
#define CAIXAS_H

#include "mapa.h"

//Constantes para caixas
#define CHAVE 1
#define BOMBA 2
#define MAX_CAIXAS 7

//MACROS PARA ITENS. Probabilidade de cada item (numero aleatorio gerado vai de 0 a 9)
#define COROA (item == 9) //10%
#define ANEL (item == 8) //10%
#define RUBI (item > 5) //(6, 7) -> 20%
#define SAFIRA (item > 2) //(3, 4, 5) -> 30%
                        //Ametista (0, 1, 2) -> 30%

#endif // CAIXAS_H

