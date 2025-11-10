#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// Estrutura que representa um item do inventário
typedef struct {
    char nome[30];     // Nome do item
    char tipo[20];     // Tipo do item (arma, munição, cura, etc.)
    int quantidade;    // Quantidade do item
} Item;

// Função para inserir um novo item na mochila
void inserirItem(Item mochila[], int* total) {
    if (*total >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("Cadastro do item %d:\n", *total + 1);
    printf("Nome: ");
    scanf("%s", mochila[*total].nome);
    printf("Tipo: ");
    scanf("%s", mochila[*total].tipo);
    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);

    (*total)++;
    printf("Item adicionado com sucesso!\n");
}

// Função para remover um item da mochila pelo nome
void removerItem(Item mochila[], int* total) {
    char nomeBusca[30];
    printf("Digite o nome do item a ser removido: ");
    scanf("%s", nomeBusca);

    int encontrado = 0;
    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("Item removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Item não encontrado na mochila.\n");
    }
}

// Função para listar todos os itens da mochila
void listarItens(Item mochila[], int total) {
    printf("\n--- Itens na Mochila ---\n");
    for (int i = 0; i < total; i++) {
        printf("Item %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
        printf("------------------------\n");
    }
    if (total == 0) {
        printf("Mochila vazia.\n");
    }
}

// Função para buscar um item pelo nome
void buscarItem(Item mochila[], int total) {
    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    scanf("%s", nomeBusca);

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }
    printf("Item não encontrado.\n");
}

// Função principal com menu de opções
int main() {
    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    do {
        printf("\n--- Menu de Inventário ---\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                break;
            case 0:
                printf("Encerrando o sistema de inventário...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

