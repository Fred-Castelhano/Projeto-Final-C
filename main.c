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

    Entidade flicky; 
    flicky.pontuacao = 0; 
    flicky.vidas = 5;     
    flicky.vy = 0;

    esconderCursor();
    Porta porta;
    int nivelAtual = 1;
    Colecionavel pintos[5];
    
    Inimigo gatos[2]; 
    carregarMapa(nivelAtual, mapa, pintos, gatos, &porta, &flicky);

    static int contador = 0;
    static int highScore = 0;
    int pintosEntreguesNaSequencia = 0;
    int jogoAtivo = 1;
    int entrando = 0;

    while(jogoAtivo) {

        // 1. INPUT
        int movX = 0;
        int tentarSaltar = 0;
        
    if (!entrando) {
        //Controlos
        if (GetAsyncKeyState('A') & 0x8000) movX = -1;
        if (GetAsyncKeyState('D') & 0x8000) movX = 1;
        if (GetAsyncKeyState('W') & 0x8000) tentarSaltar = 1;

        if (GetAsyncKeyState('Q') & 0x8000) break;

        // 2. LÓGICA DE SALTO
        if (tentarSaltar && flicky.vy == 0) {
            flicky.vy = -2.5;
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

        // 4 LÓGICA DOS INIMIGOS
        moverInimigos(gatos, 2, &flicky, mapa); // Gatos a perseguir

if (verificarColisaoGato(&flicky, gatos, 2)) { // Função que retorna 1 se colidir
    flicky.vidas--;
    if (flicky.vidas <= 0) {
        printf("GAME OVER! Pontuacao: %d | Recorde: %d\n", flicky.pontuacao, highScore);
        // Reinicia pontuação, mas mantém o highScore
        flicky.pontuacao = 0; 
        flicky.vidas = 5; 
        
        nivelAtual = 1;
        carregarMapa(nivelAtual, mapa, pintos, gatos, &porta, &flicky);
        
        Sleep(2000); // Pausa para o jogador ler o Game Over
    } else {
        // Reiniciar posição do Flicky
        flicky.x = 9; 
        flicky.y = 3;

        // Reset Gatos (usa um ciclo para resetar todos)
        gatos[0].x = 0; gatos[0].y = 0;
        gatos[1].x = 19; gatos[1].y = 9;

        system("cls");
        printf("Perdeste uma vida! Vidas restantes: %d\n", flicky.vidas);
        Sleep(1000);
        
        }
    }
}

        // 5. LÓGICA DO JOGO
    if (!entrando) {
        atualizarHistorico(&flicky);
        aplicarGravidade(mapa, &flicky);
        verificarColisoes(&flicky, pintos, 5);
        atualizarColecionaveis(&flicky, pintos, 5);

        }

       // Lógica de Pintos na Porta e Pontuação
int flickyNaPorta = (flicky.x >= porta.x && flicky.x < porta.x + porta.largura && 
                     flicky.y >= porta.y && flicky.y < porta.y + porta.altura);

if (flickyNaPorta) {
    int pintosParaEntregar = 0;
    for (int i = 0; i < 5; i++) {
        // Verifica se o pinto está na mesma zona que a porta
        if (!pintos[i].entrouNaPorta && pintos[i].seguindo) {
            entrando = 1;
                
                // Entrega um pinto de cada vez
                    pintos[i].entrouNaPorta = 1;
                    pintos[i].seguindo = 0;
                    pintosEntreguesNaSequencia++;
                    flicky.pontuacao += (pintosEntreguesNaSequencia * 100);

                    // Desenha a subida dos pontos
                    desenharJogo(mapa, flicky, pintos, 5, porta, gatos, 2, highScore);
                    Sleep(200); // Pausa entre cada pinto entregue

                    // Verifica se bateu o recorde
                    if (flicky.pontuacao > highScore) {
                    highScore = flicky.pontuacao;

                    }
                }
            }
                
                // Limpa o estado após todos os pintos serem processados
            if (entrando) {
                GetAsyncKeyState('A'); GetAsyncKeyState('D'); GetAsyncKeyState('W');
                entrando = 0; // Liberta o Flicky
            }
        } else {
            pintosEntreguesNaSequencia = 0;
        }

        // Verifica vitória
        if (verificarVitoria(&flicky, pintos, 5, &porta)) {
    nivelAtual++;
    
    // Loop de níveis 1 a 3
    if (nivelAtual > 3) nivelAtual = 1;

    // Carrega novo mapa e entidades
    carregarMapa(nivelAtual, mapa, pintos, gatos, &porta, &flicky);
    
    // Reset de entidades
    flicky.x = 9; flicky.y = 3;
    for(int i = 0; i < 5; i++) {
        pintos[i].entrouNaPorta = 0;
        pintos[i].seguindo = 0;
    }

    printf("\nNivel Completo! Avancando para o Nivel %d\n", nivelAtual);
    Sleep(1000);
    printf("\nPontuacao: %d\n", flicky.pontuacao);
    } else {
            // Se ainda não venceu, desenha o estado atual do jogo
            desenharJogo(mapa, flicky, pintos, 5, porta, gatos, 2, highScore);
        }
        
        Sleep(30);
    }

    return 0;
}