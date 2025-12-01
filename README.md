# jogo_tetris_tack

📘 Manual do Jogo — Tetris Stack Manager

Este projeto simula o gerenciamento de peças no jogo Tetris Stack, utilizando duas estruturas fundamentais da computação:

Fila Circular → representa as peças futuras

Pilha Linear → representa as peças reservadas pelo jogador

O objetivo é permitir que o jogador execute ações estratégicas com as peças, como jogar, reservar, recuperar e até realizar trocas entre fila e pilha.

🎮 Como o jogo funciona
🧱 Peças do Jogo

Cada peça possui:

Tipo: uma das letras I, O, T, L

ID: número único que identifica sua ordem de criação

As peças são sempre geradas automaticamente pelo sistema.

🔄 Estruturas utilizadas
📌 1. Fila Circular (5 posições)

Armazena sempre 5 peças futuras, organizadas em ordem FIFO (First In, First Out).
Sempre que uma peça é removida, uma nova é gerada automaticamente e colocada no fim da fila.

📌 2. Pilha de Reserva (3 posições)

Armazena peças que o jogador deseja reservar para uso posterior, seguindo o padrão LIFO (Last In, First Out).

🕹️ Ações Disponíveis

O jogador pode escolher entre as seguintes ações:

1️⃣ Jogar peça da fila

Remove a peça da frente da fila (como se estivesse jogando no tabuleiro).
Após a remoção, uma nova peça é criada para manter a fila cheia.

2️⃣ Reservar peça

Move a peça da frente da fila para o topo da pilha de reserva.
Só é possível reservar se a pilha não estiver cheia.
Uma nova peça é gerada para completar a fila.

3️⃣ Usar peça reservada

Remove a peça do topo da pilha, simulando seu uso.
Peças usadas não voltam para a fila.

4️⃣ Trocar peça atual

Troca a peça da frente da fila com a peça do topo da pilha.

Permite corrigir decisões estratégicas ou escolher outra peça rapidamente.

5️⃣ Troca múltipla (3 peças)

Troca as três primeiras peças da fila com as três peças da pilha.

Condições:

A fila deve ter pelo menos 3 peças (sempre tem).

A pilha deve estar cheia (3 peças).

Essa ação permite uma mudança estratégica agressiva no fluxo das peças.

0️⃣ Sair

Finaliza o programa.
