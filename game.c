#include <stdio.h>
#include "game.h"

void carregarMapa(int nivel, char mapa[ALTURA][LARGURA], Colecionavel *pintos, Inimigo *gatos, Porta *porta, Entidade *flicky) {

    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            mapa[i][j] = ' ';
        }
    }

    // Colisão 
    // Chão inferior
    for (int j = 0; j < LARGURA; j++) mapa[ALTURA - 1][j] = '#';

    // Nível 1
    if (nivel == 1) {

    // Plataformas intermédias
    for (int j = 0; j < 6; j++) mapa[7][j] = '#'; // Plataforma esquerda baixo
    for (int j = 12; j < LARGURA; j++) mapa[7][j] = '#'; // Plataforma direita baixo

    for (int j = 4; j < 16; j++) mapa[5][j] = '#'; // Plataforma central

    for (int j = 0; j < 7; j++) mapa[2][j] = '#'; // Plataforma esquerda cima
    for (int j = 14; j < LARGURA; j++) mapa[2][j] = '#'; // Plataforma direita cima

        // Posições Nível 1
        porta->x = 9; porta->y = 8;
        porta->largura = 2; porta->altura = 1;
        flicky->x = 9; flicky->y = 3;

        pintos[0] = (Colecionavel){1, 1, 0, 0, 0}; 
        pintos[1] = (Colecionavel){18, 1, 0, 0, 1};
        pintos[2] = (Colecionavel){1, 6, 0, 0, 2};
        pintos[3] = (Colecionavel){18, 8, 0, 0, 3};
        pintos[4] = (Colecionavel){10, 2, 0, 0, 4};

        gatos[0] = (Inimigo){0, 0}; 
        gatos[1] = (Inimigo){19, 9};

    } 
    // Nível 2
    else if (nivel == 2) {
        
        // Plataforma Superior 
    for (int j = 7; j < 13; j++) {
        mapa[2][j] = '#'; 
    }

    // Plataformas Médio e Inferior 
    for (int j = 5; j < 15; j++) {
        mapa[5][j] = '#'; 
        mapa[8][j] = '#'; 
    }

    // Plataformas laterais
    for (int j = 0; j < 4; j++) {
        mapa[5][j] = '#';      mapa[5][16+j] = '#';
        mapa[7][j] = '#';      mapa[7][16+j] = '#';
        }
        
        // Posições Nível 2
        porta->x = 12; porta->y = 4;
        porta->largura = 2; porta->altura = 1;
        flicky->x = 18; flicky->y = 6;

        pintos[0] = (Colecionavel){1, 1, 0, 0, 0}; 
        pintos[1] = (Colecionavel){18, 1, 0, 0, 1};
        pintos[2] = (Colecionavel){1, 8, 0, 0, 2};
        pintos[3] = (Colecionavel){18, 8, 0, 0, 3};
        pintos[4] = (Colecionavel){10, 4, 0, 0, 4};

        gatos[0] = (Inimigo){0, 0}; 
        gatos[1] = (Inimigo){19, 9};
    } 
    // Nível 3
    else if (nivel == 3) {
    // Plataforma superior central
    for (int j = 6; j < 14; j++) mapa[2][j] = '#'; 
    
    // Plataformas intermédias laterais
    for (int j = 0; j < 6; j++) mapa[4][j] = '#'; // Esq
    for (int j = 14; j < LARGURA; j++) mapa[4][j] = '#'; // Dir
    
    // Plataformas intermédias inferiores
    for (int j = 0; j < 7; j++) mapa[6][j] = '#'; // Esq
    for (int j = 13; j < LARGURA; j++) mapa[6][j] = '#'; // Dir
    
    // Plataforma base central
    for (int j = 6; j < 14; j++) mapa[8][j] = '#';

    // Posições Nível 3
    porta->x = 9; porta->y = 1;
    porta->largura = 2; porta->altura = 1;
    flicky->x = 18; flicky->y = 5;

    pintos[0] = (Colecionavel){2, 3, 0, 0, 0};
    pintos[1] = (Colecionavel){17, 3, 0, 0, 1};
    pintos[2] = (Colecionavel){2, 5, 0, 0, 2};
    pintos[3] = (Colecionavel){17, 5, 0, 0, 3};
    pintos[4] = (Colecionavel){10, 5, 0, 0, 4};

    gatos[0] = (Inimigo){5, 4}; 
    gatos[1] = (Inimigo){14, 7};
}

    }

    void aplicarGravidade(char mapa[ALTURA][LARGURA], Entidade *flicky) {
    // 1. Aplica a gravidade (se estiver no ar)
    int proximoY = flicky->y + (flicky->vy > 0 ? 1 : -1);

    // Se estiver a mover-se (vy != 0), verifica colisão passo a passo
    if (flicky->vy != 0) {
        if (proximoY >= 0 && proximoY < ALTURA && mapa[proximoY][flicky->x] != '#') {
            flicky->y = proximoY;
            // Reduz a velocidade gradualmente até parar
            if (flicky->vy > 0) flicky->vy -= 0.2f; 
            if (flicky->vy < 0) flicky->vy += 0.2f;
        } else {
            flicky->vy = 0; // Bateu em algo, para o movimento
        }
    } 
    // Se vy é 0, aplica gravidade normal (cair)
    else if (mapa[flicky->y + 1][flicky->x] != '#') {
        flicky->y += 1;
        
    }
}

void atualizarHistorico(Entidade *e) {
    for (int i = MAX_RASTO - 1; i > 0; i--) {
        e->historicoX[i] = e->historicoX[i - 1];
        e->historicoY[i] = e->historicoY[i - 1];
    }
    e->historicoX[0] = e->x;
    e->historicoY[0] = e->y;
}

void verificarColisoes(Entidade *p, Colecionavel *c, int numColecionaveis) {
    for (int i = 0; i < numColecionaveis; i++) {
        if (!c[i].seguindo && p->x == c[i].x && p->y == c[i].y) {
            c[i].seguindo = 1; // Faz com que os pintos sigam o Flicky
        }
    }
}
void moverInimigos(Inimigo *gatos, int numGatos, Entidade *flicky, char mapa[ALTURA][LARGURA]) {
    static int contadorGatos = 0;
    contadorGatos++;

    if (contadorGatos >= 10) {
        for (int i = 0; i < numGatos; i++) {
            // Movimento horizontal
            int proximoX = gatos[i].x;
            if (gatos[i].x < flicky->x) proximoX++;
            else if (gatos[i].x > flicky->x) proximoX--;

        
            if (mapa[gatos[i].y][proximoX] != '#') {
                gatos[i].x = proximoX;
            }

            // Desce plataformas
            // Só desce se não houver um bloco (#) logo abaixo
            if (gatos[i].y + 1 < ALTURA && mapa[gatos[i].y + 1][gatos[i].x] != '#') {
                gatos[i].y++;
            } 
            // Lógica de salto
            // Se o Flicky está acima e não há plataforma, o gato salta
            else if (gatos[i].y > flicky->y) {
                // Tenta subir até 2 blocos se não houver parede
                if (gatos[i].y - 2 >= 0 && mapa[gatos[i].y - 1][gatos[i].x] != '#' && mapa[gatos[i].y - 2][gatos[i].x] != '#') {
                    gatos[i].y -= 2; // Salto mais alto
                } else if (mapa[gatos[i].y - 1][gatos[i].x] != '#') {
                    gatos[i].y--; // Salto normal
                }
            }
        }
        contadorGatos = 0;
    }
}
int verificarColisaoGato(Entidade *flicky, Inimigo *gatos, int numGatos) {
    for (int i = 0; i < numGatos; i++) {
        if (flicky->x == gatos[i].x && flicky->y == gatos[i].y) {
            return 1; // Colisão detetada
        }
    }
    return 0; // Sem colisão
}

void atualizarColecionaveis(Entidade *p, Colecionavel *c, int numColecionaveis) {
    int offset = 2; 
    for (int i = 0; i < numColecionaveis; i++) {
        if (c[i].seguindo) {
            int indiceNoRasto = i * offset; 
            if (indiceNoRasto < MAX_RASTO) {
                c[i].x = p->historicoX[indiceNoRasto];
                c[i].y = p->historicoY[indiceNoRasto];
            }
        }
    }
}
      int verificarVitoria(Entidade *flicky, Colecionavel *pintos, int numPintos, Porta *p) {
    // Verifica se todos os pintos já entraram na porta
    for (int i = 0; i < numPintos; i++) {
        if (!pintos[i].entrouNaPorta) {
            return 0; // Se encontrar um pinto que não entrou, não há vitória
        }
    }
    
    // Se chegou aqui, todos entraram. Retorna 1 (Vitória)
    return 1; 
}

void desenharJogo(char mapa[ALTURA][LARGURA], Entidade flicky, Colecionavel *pintos, int numPintos, Porta porta, Inimigo *gatos, int numGatos, int highScore) {
    printf("\033[H"); 
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            int desenhado = 0;

            // Lógica para desenhar a Porta
            if (i == porta.y && j == porta.x) {
                printf("[]");
                desenhado = 1;
                j++;
            } 
            // Desenha o jogador
            else if (i == flicky.y && j == flicky.x) {
                printf("@ ");
                desenhado = 1;
            } 
            // Desenha colecionáveis
            else {
                for(int k = 0; k < numPintos; k++) {
                    if(!pintos[k].entrouNaPorta && i == pintos[k].y && j == pintos[k].x) {
                        printf("o ");
                        desenhado = 1;
                        break;
                    }
                }
            }
        // Desenha inimigos (Gatos)
        if (!desenhado) {
        for(int k = 0; k < numGatos; k++) {
        if (i == gatos[k].y && j == gatos[k].x) {
            printf("G ");
            desenhado = 1;
            break;
                    }
                }
            }
            if (!desenhado) printf("%c ", mapa[i][j]);
        }
        printf("\n");
    }
    printf("Pontuacao: %d | Recorde: %d | Vidas: %d\n", flicky.pontuacao, highScore, flicky.vidas);
}