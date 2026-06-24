#include <stdio.h>
#include "game.h"

int main() {
    char mapa[ALTURA][LARGURA];
    Entidade flicky = {5, 5}; 
    char comando;

    inicializarMapa(mapa);

    while(1) {
        // 1. Aplica gravidade e desenha
        aplicarGravidade(mapa, &flicky);
        desenharJogo(mapa, flicky);
        
        // 2. Input
        printf("\nMover (w/a/s/d) ou 'q' para sair: ");
        scanf(" %c", &comando);

        // 3. Movimento
        if (comando == 'q') break;
        if (comando == 'w' && flicky.y > 1) flicky.y--;
        if (comando == 's' && flicky.y < ALTURA - 2) flicky.y++;
        if (comando == 'a' && flicky.x > 1) flicky.x--;
        if (comando == 'd' && flicky.x < LARGURA - 2) flicky.x++;
    }
    return 0;
}