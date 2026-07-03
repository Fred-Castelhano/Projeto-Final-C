#include <stdio.h>
#include "game.h"
#include <conio.h>
#include <windows.h>

void esconderCursor() {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(out, &cursorInfo);
}

int main() {
    char mapa[ALTURA][LARGURA];
    Entidade flicky = {5, 5, 0.0}; 
    esconderCursor();
    inicializarMapa(mapa);
    static int contador = 0;

    while(1) {
        // 1. INPUT
        int movX = 0;
        int tentarSaltar = 0;

        if (GetAsyncKeyState('A') & 0x8000) movX = -1;
        if (GetAsyncKeyState('D') & 0x8000) movX = 1;
        if (GetAsyncKeyState('W') & 0x8000) tentarSaltar = 1;
        if (GetAsyncKeyState('Q') & 0x8000) break;

        // 2. LÓGICA DE SALTO
        if (tentarSaltar && flicky.vy == 0) {
            flicky.vy = -1.5;
        }

        // 3. MOVIMENTO LATERAL
        contador++;
        if (movX != 0 && contador % 2 == 0) {
            int novoX = flicky.x + movX;

            // Screen Wrap
            if (novoX < 0) novoX = LARGURA - 1;
            else if (novoX >= LARGURA) novoX = 0;

            // Colisão
            if (mapa[flicky.y][novoX] != '#') {
                flicky.x = novoX;
            }
        }

        // 3. Gravidade e Desenho
        aplicarGravidade(mapa, &flicky);
        desenharJogo(mapa, flicky);
        
        Sleep(30);
    }

    return 0;
}