#ifndef GAME_H
#define GAME_H

#define LARGURA 20
#define ALTURA 10

typedef struct {
    int x, y;
    float vy;
} Entidade;

void inicializarMapa(char mapa[ALTURA][LARGURA]);
void desenharJogo(char mapa[ALTURA][LARGURA], Entidade flicky);
void aplicarGravidade(char mapa[ALTURA][LARGURA], Entidade *flicky);

#endif