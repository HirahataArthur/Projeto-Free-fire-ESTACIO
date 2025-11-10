#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 100

// Estrutura do item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Variáveis globais
Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;
No* mochilaLista = NULL;

// Funções para vetor
void inserirItemVetor() {
    if (totalVetor >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }
    printf("Nome: "); scanf("%s", mochilaVetor[totalVetor].nome);
    printf("Tipo: "); scanf("%s", mochilaVetor[totalVetor].tipo);
    printf("Quantidade: "); scanf("%d", &mochilaVetor[totalVetor].quantidade);
    totalVetor++;
}

void removerItemVetor(char* nome) {
    for (int i = 0; i < totalVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            totalVetor--;
            printf("Item removido.\n");
            return;
        }
    }
    printf("Item não encontrado.\n");
}

void listarItensVetor() {
    for (int i = 0; i < totalVetor; i++) {
        printf("%s | %s | %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
    if (totalVetor == 0) printf("Mochila vazia.\n");
}

int buscarSequencialVetor(char* nome, int* comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < totalVetor; i++) {
        (*comparacoes)++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("Encontrado: %s | %s | %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            return i;
        }
    }
    printf("Item não encontrado.\n");
    return -1;
}

void ordenarVetor() {
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = 0; j < totalVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("Itens ordenados por nome.\n");
}

int buscarBinariaVetor(char* nome, int* comparacoes) {
    int inicio = 0, fim = totalVetor - 1;
    *comparacoes = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(mochilaVetor[meio].nome, nome);
        if (cmp == 0) {
            printf("Encontrado: %s | %s | %d\n", mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("Item não encontrado.\n");
    return -1;
}

// Funções para lista encadeada
void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));
    printf("Nome: "); scanf("%s", novo->dados.nome);
    printf("Tipo: "); scanf("%s", novo->dados.tipo);
    printf("Quantidade: "); scanf("%d", &novo->dados.quantidade);
    novo->proximo = mochilaLista;
    mochilaLista = novo;
}

void removerItemLista(char* nome) {
    No *atual = mochilaLista, *anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) mochilaLista = atual->proximo;
            else anterior->proximo = atual->proximo;
            free(atual);
            printf("Item removido.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item não encontrado.\n");
}

void listarItensLista() {
    No* atual = mochilaLista;
    if (atual == NULL) {
        printf("Mochila vazia.\n");
        return;
    }
    while (atual != NULL) {
        printf("%s | %s | %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

int buscarSequencialLista(char* nome, int* comparacoes) {
    No* atual = mochilaLista;
    *comparacoes = 0;
    while (atual != NULL) {
        (*comparacoes)++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Encontrado: %s | %s | %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            return 1;
        }
        atual = atual->proximo;
    }
    printf("Item não encontrado.\n");
    return 0;
}

// Menu principal
int main() {
    int estrutura, opcao;
    char nomeBusca[30];
    int comparacoes;

    printf("Escolha a estrutura: 1 - Vetor | 2 - Lista Encadeada: ");
    scanf("%d", &estrutura);

    do {
        printf("\n1. Inserir\n2. Remover\n3. Listar\n4. Buscar Sequencial\n5. Ordenar (vetor)\n6. Buscar Binária (vetor)\n0. Sair\nOpção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (estrutura == 1) inserirItemVetor();
                else inserirItemLista();
                break;
            case 2:
                printf("Nome do item: "); scanf("%s", nomeBusca);
                if (estrutura == 1) removerItemVetor(nomeBusca);
                else removerItemLista(nomeBusca);
                break;
            case 3:
                if (estrutura == 1) listarItensVetor();
                else listarItensLista();
                break;
            case 4:
                printf("Nome do item: "); scanf("%s", nomeBusca);
                if (estrutura == 1) buscarSequencialVetor(nomeBusca, &comparacoes);
                else buscarSequencialLista(nomeBusca, &comparacoes);
                printf("Comparações: %d\n", comparacoes);
                break;
            case 5:
                if (estrutura == 1) ordenarVetor();
                else printf("Ordenação não disponível para lista encadeada.\n");
                break;
            case 6:
                if (estrutura == 1) {
                    printf("Nome do item: "); scanf("%s", nomeBusca);
                    buscarBinariaVetor(nomeBusca, &comparacoes);
                    printf("Comparações: %d\n", comparacoes);
                } else {
                    printf("Busca binária não disponível para lista encadeada.\n");
                }
                break;
        }
    } while (opcao != 0);

    printf("Sistema encerrado.\n");
    return 0;
}
