**Sessão 3 – 03/07/2026**



**Funcionalidades implementadas hoje:**



\-Sistema de Input Polling: Substitui o\_kbhit/\_getch por GetAsyncKeyState, permitindo o processamento de múltiplas teclas em simultâneo.



\-Implementação de movimento lateral fluido enquanto o boneco está a meio de um salto.



\-Otimização da Física (Game Feel): Introdução de gravidade variável (mais leve na subida, mais pesada na descida) para um efeito de salto mais natural e preciso.



\-Implementação das funções de entrada, física e renderização para garantir que o jogo não "trava" durante o salto.



**Maior dificuldade encontrada e como resolvi:**



\-Dificuldade: O conflito entre o movimento lateral e o salto. O boneco não continuava no movimento ao saltar, fazendo com que se tivesse de pressionar novamente as teclas de direção.



Como resolvi: Percebi que estava a misturar a lógica do input com a física. Isolei as duas coisas: agora o Input lê as teclas continuamente (polling) e a Física trata apenas da gravidade. Também aproveitei para limpar umas chavetas que estavam a deixar o compilador confuso.



**Próximo passo planeado:**



\-Implementar um sistema de inimigos e colecionáveis.



\-Implementar sistema de pontuação



**Linhas de código escritas hoje:**



Aproximadamente 60-80 linhas de código (entre a reescrita do main.c e o ajuste do game.c).

