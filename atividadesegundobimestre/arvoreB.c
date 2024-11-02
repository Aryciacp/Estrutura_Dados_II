//arycia cabral pezente

#include <stdio.h>
#include <stdlib.h>

#define ORDEM 3 // Ordem da árvore B (cada nó pode ter no máximo 2 * ORDEM - 1 chaves)

typedef struct NoB {
    int num_chaves;             // Número de chaves armazenadas no nó
    int chaves[2 * ORDEM - 1];  // Array de chaves
    struct NoB* filhos[2 * ORDEM]; // Ponteiros para os filhos
    int folha;                  // 1 se o nó é folha, 0 se não é
} NoB;

// Funções de criação e liberação de memória
NoB* criar_no(int folha);
void liberar_arvore(NoB* raiz);

// Funções para manipulação da árvore B (inserção, busca)
void inserir(NoB** raiz, int chave);
void inserir_nao_cheio(NoB* no, int chave);
void dividir_filho(NoB* pai, int i, NoB* filho);
NoB* buscar(NoB* no, int chave);

// Função para imprimir a árvore B
void imprimir_arvore(NoB* raiz, int nivel);

int main() {
    NoB* raiz = NULL;
    int chave, entrada;

    do {
        printf("-------------- Árvore B --------------\n");
        printf("1- Inserir Valor\n2- Buscar Valor\n3- Exibir Árvore\n0- Sair\n");
        scanf("%d", &entrada);

        switch (entrada) {
            case 1:
                printf("Valor a ser inserido: ");
                scanf("%d", &chave);
                inserir(&raiz, chave);
                break;
            case 2:
                printf("Valor a ser buscado: ");
                scanf("%d", &chave);
                printf("Valor %d %s encontrado.\n", chave, buscar(raiz, chave) ? "" : "não");
                break;
            case 3:
                printf("-----------------------------------------\n");
                imprimir_arvore(raiz, 0);
                printf("-----------------------------------------\n");
                break;
            default:
                if (entrada != 0) printf("Opção inválida!\n");
        }
    } while (entrada != 0);

    liberar_arvore(raiz);
    printf("Encerrando aplicação!\n");
    return 0;
}

// Função para criar um novo nó da árvore B
NoB* criar_no(int folha) {
    NoB* novo_no = (NoB*)malloc(sizeof(NoB));
    novo_no->num_chaves = 0;
    novo_no->folha = folha;

    for (int i = 0; i < 2 * ORDEM; i++) {
        novo_no->filhos[i] = NULL;
    }
    return novo_no;
}

// Função para liberar a memória da árvore B
void liberar_arvore(NoB* raiz) {
    if (raiz == NULL) return;
    if (!raiz->folha) {
        for (int i = 0; i <= raiz->num_chaves; i++) {
            liberar_arvore(raiz->filhos[i]);
        }
    }
    free(raiz);
}

// Função para buscar uma chave na árvore B
NoB* buscar(NoB* no, int chave) {
    int i = 0;
    while (i < no->num_chaves && chave > no->chaves[i]) i++;

    if (i < no->num_chaves && chave == no->chaves[i]) return no;
    if (no->folha) return NULL;
    return buscar(no->filhos[i], chave);
}

// Função para inserir uma nova chave na árvore B
void inserir(NoB** raiz, int chave) {
    if (*raiz == NULL) {
        *raiz = criar_no(1); // Cria um novo nó raiz
        (*raiz)->chaves[0] = chave;
        (*raiz)->num_chaves = 1;
    } else {
        if ((*raiz)->num_chaves == 2 * ORDEM - 1) {
            NoB* nova_raiz = criar_no(0);
            nova_raiz->filhos[0] = *raiz;
            dividir_filho(nova_raiz, 0, *raiz);
            int i = (chave > nova_raiz->chaves[0]) ? 1 : 0;
            inserir_nao_cheio(nova_raiz->filhos[i], chave);
            *raiz = nova_raiz;
        } else {
            inserir_nao_cheio(*raiz, chave);
        }
    }
}

// Função para inserir uma chave em um nó que não está cheio
void inserir_nao_cheio(NoB* no, int chave) {
    int i = no->num_chaves - 1;

    if (no->folha) {
        while (i >= 0 && chave < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->num_chaves++;
    } else {
        while (i >= 0 && chave < no->chaves[i]) i--;
        i++;
        if (no->filhos[i]->num_chaves == 2 * ORDEM - 1) {
            dividir_filho(no, i, no->filhos[i]);
            if (chave > no->chaves[i]) i++;
        }
        inserir_nao_cheio(no->filhos[i], chave);
    }
}

// Função para dividir um nó filho
void dividir_filho(NoB* pai, int i, NoB* filho) {
    NoB* novo_no = criar_no(filho->folha);
    novo_no->num_chaves = ORDEM - 1;

    for (int j = 0; j < ORDEM - 1; j++) {
        novo_no->chaves[j] = filho->chaves[j + ORDEM];
    }
    if (!filho->folha) {
        for (int j = 0;
