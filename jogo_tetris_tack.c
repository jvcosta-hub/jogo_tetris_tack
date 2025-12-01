#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5   // tamanho fixo da fila

// -----------------------------
// Definição da peça
// -----------------------------
typedef struct {
    char nome;   // tipo da peça ('I', 'O', 'T', 'L')
    int id;      // identificador único
} Peca;

// -----------------------------
// Fila circular
// -----------------------------
typedef struct {
    Peca vetor[TAM_FILA];
    int inicio;   // posição do primeiro elemento
    int fim;      // posição da próxima inserção
    int qtd;      // quantidade de elementos armazenados
} Fila;

// -----------------------------
// Protótipos
// -----------------------------
void inicializarFila(Fila *f);
int enqueue(Fila *f, Peca p);
int dequeue(Fila *f, Peca *removida);
void exibirFila(Fila *f);
Peca gerarPeca(int id);

// -----------------------------
// Função principal
// -----------------------------
int main() {
    Fila fila;
    inicializarFila(&fila);

    srand(time(NULL));  // para gerar peças aleatórias

    int idAtual = 0;   // controle para IDs únicos

    // Inicializa a fila com 5 peças
    for(int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(idAtual++));
    }

    int opcao;

    do {
        printf("\n=============================\n");
        printf("   Fila de Peças do Tetris\n");
        printf("=============================\n");
        exibirFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if(opcao == 1) {
            Peca removida;
            if(dequeue(&fila, &removida)) {
                printf("\nPeça jogada: [%c %d]\n", removida.nome, removida.id);
            } else {
                printf("\nA fila está vazia! Nada a remover.\n");
            }
        }
        else if(opcao == 2) {
            if(enqueue(&fila, gerarPeca(idAtual++))) {
                printf("\nNova peça inserida com sucesso.\n");
            } else {
                printf("\nFila cheia! Não é possível inserir nova peça.\n");
            }
        }

    } while(opcao != 0);

    printf("\nEncerrando o programa...\n");
    return 0;
}

// -----------------------------
// Funções
// -----------------------------

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
}

// Insere peça na fila
int enqueue(Fila *f, Peca p) {
    if(f->qtd == TAM_FILA) {
        return 0;  // fila cheia
    }
    f->vetor[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->qtd++;
    return 1;
}

// Remove peça da fila
int dequeue(Fila *f, Peca *removida) {
    if(f->qtd == 0) {
        return 0; // fila vazia
    }
    *removida = f->vetor[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->qtd--;
    return 1;
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    printf("\nFila de peças:\n");

    if(f->qtd == 0) {
        printf("[vazia]\n");
        return;
    }

    int pos = f->inicio;
    for(int i = 0; i < f->qtd; i++) {
        printf("[%c %d] ", f->vetor[pos].nome, f->vetor[pos].id);
        pos = (pos + 1) % TAM_FILA;
    }
    printf("\n");
}

// Gera automaticamente uma peça aleatória
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}
