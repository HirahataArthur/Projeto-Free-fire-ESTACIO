#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// Estrutura do componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Função para exibir os componentes
void mostrarComponentes(Componente c[], int n) {
    printf("\n--- Componentes da Torre ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. Nome: %s | Tipo: %s | Prioridade: %d\n", i + 1, c[i].nome, c[i].tipo, c[i].prioridade);
    }
}

// Bubble Sort por nome
int bubbleSortNome(Componente c[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(c[j].nome, c[j + 1].nome) > 0) {
                Componente temp = c[j];
                c[j] = c[j + 1];
                c[j + 1] = temp;
            }
        }
    }
    return comparacoes;
}

// Insertion Sort por tipo
int insertionSortTipo(Componente c[], int n) {
    int comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = c[i];
        int j = i - 1;
        while (j >= 0 && strcmp(c[j].tipo, chave.tipo) > 0) {
            c[j + 1] = c[j];
            j--;
            comparacoes++;
        }
        if (j >= 0) comparacoes++;
        c[j + 1] = chave;
    }
    return comparacoes;
}

// Selection Sort por prioridade
int selectionSortPrioridade(Componente c[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (c[j].prioridade < c[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            Componente temp = c[i];
            c[i] = c[min];
            c[min] = temp;
        }
    }
    return comparacoes;
}

// Busca binária por nome
int buscaBinariaPorNome(Componente c[], int n, char chave[], int* comparacoes) {
    int ini = 0, fim = n - 1;
    *comparacoes = 0;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(c[meio].nome, chave);
        if (cmp == 0) return meio;
        else if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// Função para medir tempo e comparações
void medirTempo(int (*algoritmo)(Componente[], int), Componente c[], int n, const char* nomeAlgoritmo) {
    clock_t inicio = clock();
    int comparacoes = algoritmo(c, n);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nAlgoritmo: %s\n", nomeAlgoritmo);
    printf("Comparações: %d\n", comparacoes);
    printf("Tempo de execução: %.6f segundos\n", tempo);
    mostrarComponentes(c, n);
}

int main() {
    Componente torre[MAX_COMPONENTES];
    int total = 0;
    int opcao;
    char chave[30];

    printf("Cadastro de até 20 componentes da torre de fuga:\n");
    printf("Digite o número de componentes: ");
    scanf("%d", &total);
    getchar(); // Limpa o buffer

    if (total > MAX_COMPONENTES) total = MAX_COMPONENTES;

    for (int i = 0; i < total; i++) {
        printf("\nComponente %d:\n", i + 1);
        printf("Nome: ");
        fgets(torre[i].nome, 30, stdin);
        torre[i].nome[strcspn(torre[i].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(torre[i].tipo, 20, stdin);
        torre[i].tipo[strcspn(torre[i].tipo, "\n")] = '\0';

        printf("Prioridade (1 a 10): ");
        scanf("%d", &torre[i].prioridade);
        getchar(); // Limpa o buffer
    }

    do {
        printf("\n--- Menu de Estratégia ---\n");
        printf("1. Ordenar por Nome (Bubble Sort)\n");
        printf("2. Ordenar por Tipo (Insertion Sort)\n");
        printf("3. Ordenar por Prioridade (Selection Sort)\n");
        printf("4. Buscar Componente-chave por Nome (Binária)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                medirTempo(bubbleSortNome, torre, total, "Bubble Sort (Nome)");
                break;
            case 2:
                medirTempo(insertionSortTipo, torre, total, "Insertion Sort (Tipo)");
                break;
            case 3:
                medirTempo(selectionSortPrioridade, torre, total, "Selection Sort (Prioridade)");
                break;
            case 4:
                printf("Digite o nome do componente-chave: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = '\0';
                int comparacoes;
                int pos = buscaBinariaPorNome(torre, total, chave, &comparacoes);
                if (pos != -1) {
                    printf("Componente encontrado na posição %d: %s | %s | Prioridade %d\n",
                           pos + 1, torre[pos].nome, torre[pos].tipo, torre[pos].prioridade);
                } else {
                    printf("Componente não encontrado.\n");
                }
                printf("Comparações realizadas: %d\n", comparacoes);
                break;
        }
    } while (opcao != 0);

    printf("Missão encerrada. Boa sorte na fuga!\n");
    return 0;
}