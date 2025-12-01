#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// --------------------------------------------
// Definição da peça
// --------------------------------------------
typedef struct {
    char nome;
    int id;
} Peca;


// --------------------------------------------
// Definição da Fila circular
// --------------------------------------------
typedef struct {
    Peca vetor[TAM_FILA];
    int inicio;
    int fim;
    int qtd;
} Fila;


// --------------------------------------------
// Definição da Pilha
// --------------------------------------------
typedef struct {
    Peca vetor[TAM_PILHA];
    int topo;
} Pilha;


// --------------------------------------------
// Protótipos
// --------------------------------------------
void inicializarFila(Fila *f);
void inicializarPilha(Pilha *p);

int enqueue(Fila *f, Peca p);
int dequeue(Fila *f, Peca *r);

int push(Pilha *p, Peca x);
int pop(Pilha *p, Peca *r);

void exibirFila(Fila *f);
void exibirPilha(Pilha *p);

Peca gerarPeca(int id);

void trocarUmaPeca(Fila *f, Pilha *p);
void trocaMultipla(Fila *f, Pilha *p);


// --------------------------------------------
// Função principal
// --------------------------------------------
int main() {
    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    srand(time(NULL));

    int idAtual = 0;
    int opcao;

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++)
        enqueue(&fila, gerarPeca(idAtual++));

    do {
        printf("\n=========================================\n");
        printf("              ESTADO ATUAL\n");
        printf("=========================================\n");

        exibirFila(&fila);
        exibirPilha(&pilha);

        printf("\nOpções:\n");
        printf("1 - Jogar peça da fila\n");
        printf("2 - Reservar peça (fila → pilha)\n");
        printf("3 - Usar peça reservada (pop)\n");
        printf("4 - Trocar peça da fila com a pilha\n");
        printf("5 - Troca múltipla (3 peças)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca jogada;
            if (dequeue(&fila, &jogada)) {
                printf("\nPeça jogada: [%c %d]\n", jogada.nome, jogada.id);
                enqueue(&fila, gerarPeca(idAtual++)); // mantém a fila cheia
            }
        }

        else if (opcao == 2) {
            if (pilha.topo == TAM_PILHA - 1) {
                printf("\nA pilha está cheia! Não é possível reservar.\n");
            } else {
                Peca removida;
                if (dequeue(&fila, &removida)) {
                    push(&pilha, removida);
                    printf("\nPeça reservada: [%c %d]\n", removida.nome, removida.id);
                    enqueue(&fila, gerarPeca(idAtual++));
                }
            }
        }

        else if (opcao == 3) {
            Peca usada;
            if (pop(&pilha, &usada)) {
                printf("\nPeça da reserva usada: [%c %d]\n", usada.nome, usada.id);
            } else {
                printf("\nA pilha está vazia!\n");
            }
        }

        else if (opcao == 4) {
            trocarUmaPeca(&fila, &pilha);
        }

        else if (opcao == 5) {
            trocaMultipla(&fila, &pilha);
        }

    } while (opcao != 0);

    printf("\nEncerrando o programa...\n");
    return 0;
}



// =====================================================================
// Implementações
// =====================================================================

// Inicializar fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
}

// Inicializar pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}


// Inserir na fila
int enqueue(Fila *f, Peca p) {
    if (f->qtd == TAM_FILA) return 0;
    f->vetor[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->qtd++;
    return 1;
}

// Remover da fila
int dequeue(Fila *f, Peca *r) {
    if (f->qtd == 0) return 0;
    *r = f->vetor[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->qtd--;
    return 1;
}

// Push na pilha
int push(Pilha *p, Peca x) {
    if (p->topo == TAM_PILHA - 1) return 0;
    p->vetor[++p->topo] = x;
    return 1;
}

// Pop da pilha
int pop(Pilha *p, Peca *r) {
    if (p->topo == -1) return 0;
    *r = p->vetor[p->topo--];
    return 1;
}



// Exibir fila
void exibirFila(Fila *f) {
    printf("\nFila de peças:\n");
    if (f->qtd == 0) {
        printf("[vazia]\n");
        return;
    }

    int pos = f->inicio;
    for (int i = 0; i < f->qtd; i++) {
        printf("[%c %d] ", f->vetor[pos].nome, f->vetor[pos].id);
        pos = (pos + 1) % TAM_FILA;
    }
    printf("\n");
}

// Exibir pilha
void exibirPilha(Pilha *p) {
    printf("\nPilha de reserva (Topo -> Base):\n");

    if (p->topo == -1) {
        printf("[vazia]\n");
        return;
    }

    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->vetor[i].nome, p->vetor[i].id);
    }
    printf("\n");
}



// ---------------------------------------------------------------------
// Trocar peça da fila com o topo da pilha
// ---------------------------------------------------------------------
void trocarUmaPeca(Fila *f, Pilha *p) {
    if (p->topo == -1) {
        printf("\nA pilha está vazia! Nada para trocar.\n");
        return;
    }

    int idxFila = f->inicio;  // índice da primeira peça da fila

    Peca temp = f->vetor[idxFila];
    f->vetor[idxFila] = p->vetor[p->topo];
    p->vetor[p->topo] = temp;

    printf("\nTroca realizada entre a peça da fila e a da pilha.\n");
}



// ---------------------------------------------------------------------
// Troca múltipla (3 primeiras da fila ↔ 3 da pilha)
// ---------------------------------------------------------------------
void trocaMultipla(Fila *f, Pilha *p) {
    if (f->qtd < 3 || p->topo + 1 < 3) {
        printf("\nTroca impossível! É necessário ter pelo menos 3 peças na fila e 3 na pilha.\n");
        return;
    }

    // Troca posição a posição
    for (int i = 0; i < 3; i++) {
        int idxFila = (f->inicio + i) % TAM_FILA;
        int idxPilha = p->topo - i;

        Peca temp = f->vetor[idxFila];
        f->vetor[idxFila] = p->vetor[idxPilha];
        p->vetor[idxPilha] = temp;
    }

    printf("\nTroca múltipla (3 peças) realizada com sucesso!\n");
}



// ---------------------------------------------------------------------
// Criar peça aleatória
// ---------------------------------------------------------------------
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}