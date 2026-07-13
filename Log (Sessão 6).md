**Sessão 6 – 13/07/2026**



**Funcionalidades implementadas hoje:**



Expansão do jogo com a criação e integração de novos níveis.



Implementação do sistema de persistência de pontuação máxima (Highscore).



Refinamento da lógica de transição entre níveis.





**Maior dificuldade encontrada e como resolvi (ou não resolvi):**



Dificuldade: A maior dificuldade foi a implementação dos novos níveis e a integração da lógica de progressão. Era necessário garantir que o carregarMapa reiniciasse corretamente as posições do jogador, dos pintos e dos gatos para cada nível, sem gerar conflitos com o estado anterior ou erros na deteção de colisões.  



Resolução: Estruturei o carregarMapa com condicionais (if/else if) para cada nível, garantindo que as coordenadas das entidades fossem redefinidas individualmente. Adicionalmente, no main, implementei um ciclo de controlo de nível que efetua o reset manual das bandeiras (entrouNaPorta, seguindo) de todos os colecionáveis antes de carregar o novo cenário, garantindo assim uma transição limpa.



**Próximo passo planeado:**



Em principio esta é a última sessão, mas se eventualmente voltar devo seguir com o desenvolvimento de um menu inicial com interface de texto e introdução de efeitos sonoros básicos para melhorar a experiência do utilizador.





**Linhas de código escritas hoje (estimativa):**



Aproximadamente 270 linhas inseridas e 170 removidas.

