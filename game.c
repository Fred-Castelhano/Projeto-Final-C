#include <stdio.h>
#include "game.h"

void inicializarMapa(char mapa[ALTURA][LARGURA]) {
    // 1. Limpa tudo com espaço vazio
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
    // Se a posição imediatamente abaixo do Flicky for um espaço vazio ('.') ou vazio (' ')
    // E se não estivermos na última linha do ecrã
    if (flicky->y < ALTURA - 1 && mapa[flicky->y + 1][flicky->x] == ' ') {
        flicky->y++; // O Flicky desce uma linha
   
    }
    }

   void desenharJogo(char mapa[ALTURA][LARGURA], Entidade flicky) {
    printf("\033[H\033[J"); // Limpa o terminal
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

