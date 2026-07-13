#ifndef GAME_H
#define GAME_H

#define LARGURA 20
#define ALTURA 10
#define MAX_RASTO 20 // Tamanho máximo da fila de pintos

typedef struct {
    int x, y;
    float vy;
    int historicoX[MAX_RASTO]; // Guarda as últimas posições X
    int historicoY[MAX_RASTO]; // Guarda as últimas posições Y
    int pontuacao;
    int vidas;
} Entidade;

typedef struct {
    int x, y;
    int seguindo;
    int entrouNaPorta;
    int id; 
} Colecionavel;

typedef struct {
    int x, y;
    int largura;
    int altura;
} Porta;

typedef struct {
    int x, y;
    int ativo; // Para controlar se o gato está em jogo
} Inimigo;

void carregarMapa(int nivel, char mapa[ALTURA][LARGURA], Colecionavel *pintos, Inimigo *gatos, Porta *porta, Entidade *flicky);
void desenharJogo(char mapa[ALTURA][LARGURA], Entidade flicky, Colecionavel *pintos, int numPintos, Porta porta, Inimigo *gatos, int numGatos, int highScore);
void aplicarGravidade(char mapa[ALTURA][LARGURA], Entidade *flicky);
void verificarColisoes(Entidade *p, Colecionavel *c, int numColecionaveis);
void atualizarColecionaveis(Entidade *p, Colecionavel *c, int numColecionaveis);
void atualizarHistorico(Entidade *e);
int verificarVitoria(Entidade *flicky, Colecionavel *pintos, int numPintos, Porta *p);
int verificarColisaoGato(Entidade *flicky, Inimigo *gatos, int numGatos);
void moverInimigos(Inimigo *gatos, int numGatos, Entidade *flicky, char mapa[ALTURA][LARGURA]);

#endif