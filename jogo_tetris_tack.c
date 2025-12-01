#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5   // tamanho fixo da fila
#define TAM_PILHA 3  // capacidade máxima da pilha

// --------------------------------------------
// Estrutura da peça
// --------------------------------------------
typedef struct {
    char nome;  // tipo: 'I', 'O', 'T', 'L'
    int id;     // identificador único
} Peca;

// --------------------------------------------
// Estrutura da fila circular
// --------------------------------------------
typedef struct {
    Peca vetor[TAM_FILA];
    int inicio;
    int fim;
    int qtd;
} Fila;

// --------------------------------------------
// Estrutura da pilha linear
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
int dequeue(Fila *f, Peca *removida);

int push(Pilha *p, Peca x);
int pop(Pilha *p, Peca *removida);

void exibirFila(Fila *f);
void exibirPilha(Pilha *p);

Peca gerarPeca(int id);

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
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(idAtual++));
    }

    do {
        printf("\n=====================================\n");
        printf("        ESTADO ATUAL DO JOGO\n");
        printf("=====================================\n");

        exibirFila(&fila);
        exibirPilha(&pilha);

        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            // Jogar peça
            Peca jogada;
            if (dequeue(&fila, &jogada)) {
                printf("\nPeça jogada: [%c %d]\n", jogada.nome, jogada.id);
                enqueue(&fila, gerarPeca(idAtual++));
            } else {
                printf("\nA fila está vazia!\n");
            }
        }
        else if (opcao == 2) {
            // Reservar peça
            Peca removida;
            if (pilha.topo == TAM_PILHA - 1) {
                printf("\nA pilha está cheia! Não é possível reservar.\n");
            }
            else if (dequeue(&fila, &removida)) {
                push(&pilha, removida);
                printf("\nPeça reservada: [%c %d]\n", removida.nome, removida.id);
                enqueue(&fila, gerarPeca(idAtual++));
            } else {
                printf("\nA fila está vazia! Não é possível reservar.\n");
            }
        }
        else if (opcao == 3) {
            // Usar peça reservada
            Peca usada;
            if (pop(&pilha, &usada)) {
                printf("\nPeça usada da reserva: [%c %d]\n", usada.nome, usada.id);
            } else {
                printf("\nA pilha está vazia! Nenhuma peça para usar.\n");
            }
        }

    } while (opcao != 0);

    printf("\nEncerrando o programa...\n");
    return 0;
}

// --------------------------------------------
// Implementações
// --------------------------------------------

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
int dequeue(Fila *f, Peca *removida) {
    if (f->qtd == 0) return 0;
    *removida = f->vetor[f->inicio];
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
int pop(Pilha *p, Peca *removida) {
    if (p->topo == -1) return 0;
    *removida = p->vetor[p->topo--];
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

// Geração automática de peças
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}