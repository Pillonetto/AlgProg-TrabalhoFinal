#include "raylib.h"
#include "controle.h"

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
    2/3 da altura da resolu��o utilizada pelo monitor */
    return 3 * GetMonitorHeight(0) / (4 * alturaRender);
}
