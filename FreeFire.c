#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#define MAX_ITENS 10

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
    int prioridade;
} Item;

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
} CriterioOrdenacao;

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).
Item mochila[MAX_ITENS];
int numItens = 0;
bool ordenadaPorNome = false;

// ======================================================
// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.
void limparTela() {
    for (int i = 0; i < 20; i++) {
        printf("\n");
    }
}

// ======================================================
// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.
void exibirMenu() {
    printf("=== MOCHILA VIRTUAL – NIVEL MESTRE ===\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Ordenar itens\n");
    printf("5. Buscar item por nome (busca binária)\n");
    printf("0. Sair\n");
    printf("--------------------------------------\n");
    printf("Status da mochila: %s\n", ordenadaPorNome ? "Ordenada por nome" : "Não ordenada");
    printf("Escolha uma opção: ");
}

// ======================================================
// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\n--- Adicionar Item ---\n");
    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    printf("Prioridade (1 a 5): ");
    scanf("%d", &novo.prioridade);
    getchar();

    mochila[numItens++] = novo;
    ordenadaPorNome = false;
    printf("Item adicionado com sucesso!\n");
}

// ======================================================
// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.
void removerItem() {
    if (numItens == 0) {
        printf("A mochila está vazia!\n");
        return;
    }

    char nome[50];
    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do item: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            numItens--;
            ordenadaPorNome = false;
            printf("Item removido com sucesso!\n");
            return;
        }
    }

    printf("Item não encontrado.\n");
}

// ======================================================
// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void listarItens() {
    if (numItens == 0) {
        printf("A mochila está vazia!\n");
        return;
    }

    printf("\n--- Itens na Mochila ---\n");
    printf("%-20s %-15s %-10s %-10s\n", "Nome", "Tipo", "Qtd", "Prioridade");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < numItens; i++) {
        printf("%-20s %-15s %-10d %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
}

// ======================================================
// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)
int insertionSort(CriterioOrdenacao criterio) {
    int comparacoes = 0;

    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        bool condicao;

        while (j >= 0) {
            condicao = false;

            if (criterio == ORDENAR_NOME) {
                comparacoes++;
                condicao = strcmp(mochila[j].nome, chave.nome) > 0;
            } else if (criterio == ORDENAR_TIPO) {
                comparacoes++;
                condicao = strcmp(mochila[j].tipo, chave.tipo) > 0;
            } else if (criterio == ORDENAR_PRIORIDADE) {
                comparacoes++;
                condicao = mochila[j].prioridade < chave.prioridade;
            }

            if (!condicao) break;

            mochila[j + 1] = mochila[j];
            j--;
        }

        mochila[j + 1] = chave;
    }

    return comparacoes;
}

// ======================================================
// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).
void menuDeOrdenacao() {
    if (numItens == 0) {
        printf("A mochila está vazia!\n");
        return;
    }

    int opc;
    printf("\n--- Ordenar Itens ---\n");
    printf("1. Por nome\n");
    printf("2. Por tipo\n");
    printf("3. Por prioridade\n");
    printf("Escolha: ");
    scanf("%d", &opc);
    getchar();

    int comparacoes = insertionSort(opc);
    printf("Itens ordenados com sucesso!\n");
    printf("Comparações realizadas: %d\n", comparacoes);

    ordenadaPorNome = (opc == ORDENAR_NOME);
}

// ======================================================
// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
void buscaBinariaPorNome() {
    if (!ordenadaPorNome) {
        printf("A mochila precisa estar ordenada por nome para usar a busca binária.\n");
        return;
    }

    if (numItens == 0) {
        printf("A mochila está vazia!\n");
        return;
    }

    char nome[50];
    printf("\n--- Buscar Item (Binária) ---\n");
    printf("Digite o nome do item: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int inicio = 0, fim = numItens - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(nome, mochila[meio].nome);

        if (cmp == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            return;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    printf("Item não encontrado.\n");
}

// ======================================================
// main()
// Menu principal com opções:
// 1. Adicionar um item
// 2. Remover um item
// 3. Listar todos os itens
// 4. Ordenar os itens por critério (nome, tipo, prioridade)
// 5. Realizar busca binária por nome
// 0. Sair
// A estrutura switch trata cada opção chamando a função correspondente.
// A ordenação e busca binária exigem que os dados estejam bem organizados.
int main() {
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); // limpa o buffer
        limparTela();

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: menuDeOrdenacao(); break;
            case 5: buscaBinariaPorNome(); break;
            case 0: printf("Encerrando o programa... Você se tornou um verdadeiro mestre da sobrevivência!\n"); break;
            default: printf("Opção inválida! Tente novamente.\n");
        }

        printf("\n");
    } while (opcao != 0);

    return 0;
}