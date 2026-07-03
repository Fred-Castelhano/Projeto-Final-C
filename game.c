#include <stdio.h>
#include "game.h"

void inicializarMapa(char mapa[ALTURA][LARGURA]) {
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            mapa[i][j] = ' ';
        }
    }

    // Colisão 
    // Chão inferior
    for (int j = 0; j < LARGURA; j++) mapa[ALTURA - 1][j] = '#';

    // Plataformas intermédias
    for (int j = 0; j < 8; j++) mapa[7][j] = '#'; // Plataforma esquerda baixo
    for (int j = 12; j < LARGURA; j++) mapa[7][j] = '#'; // Plataforma direita baixo

    for (int j = 4; j < 16; j++) mapa[4][j] = '#'; // Plataforma central

    for (int j = 0; j < 6; j++) mapa[2][j] = '#'; // Plataforma esquerda cima
    for (int j = 14; j < LARGURA; j++) mapa[2][j] = '#'; // Plataforma direita cima

    }

    void aplicarGravidade(char mapa[ALTURA][LARGURA], Entidade *flicky) {
    // 1. Aplica a gravidade (se estiver no ar)
    if (mapa[flicky->y + 1][flicky->x] != '#') {
       float gravidade = (flicky->vy < 0) ? 0.15f : 0.35f;
        flicky->vy += gravidade;
    } else {
        if (flicky->vy > 0) flicky->vy = 0; //Aterra no chão
    }

    // 2. Aplica a velocidade à posição
    int novoY = flicky->y + (int)flicky->vy;
    
    if (novoY >= 0 && novoY < ALTURA && mapa[novoY][flicky->x] != '#') {
        flicky->y = novoY;
    } else if (flicky->vy > 0) {
        flicky->vy = 0; // Colisão com chão
    }
}

   void desenharJogo(char mapa[ALTURA][LARGURA], Entidade flicky) {
    printf("\033[H"); 
    
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            if (i == flicky.y && j == flicky.x)
                printf("@ ");
            else
                printf("%c ", mapa[i][j]);
        }
        printf("\n");
    }
}


