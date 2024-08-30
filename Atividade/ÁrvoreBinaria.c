//arycia cabral pezente

#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó da árvore binária
typedef struct noArvore {
    int valor;
    struct noArvore* esquerda;
    struct noArvore* direita;
} no;

// Função para criar um novo nó da árvore
no* criarNo(int valor) {
    no* novo = (no*)malloc(sizeof(no));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Função para inserir um valor na árvore binária
no* inserirNo(no* raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);  // Cria um novo nó se a raiz for nula
    }

    // Verifica se o valor já existe na árvore
    if (valor < raiz->valor) {
        raiz->esquerda = inserirNo(raiz->esquerda, valor);  // Inserir na subárvore esquerda
    } else if (valor > raiz->valor) {
        raiz->direita = inserirNo(raiz->direita, valor);  // Inserir na subárvore direita
    } else {
        printf("Valor %d já existe na árvore.\n", valor);
    }

    return raiz;
}

// Função para buscar um valor na árvore
void buscarNo(no* raiz, int valor) {
    if (raiz == NULL) {
        printf("Valor %d não encontrado.\n", valor);
        return;
    }

    if (valor == raiz->valor) {
        printf("Valor %d encontrado.\n", valor);
    } else if (valor < raiz->valor) {
        buscarNo(raiz->esquerda, valor);  // Buscar na subárvore esquerda
    } else {
        buscarNo(raiz->direita, valor);   // Buscar na subárvore direita
    }
}

// Função para imprimir a árvore em níveis
void imprimirArvore(no* raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }

    imprimirArvore(raiz->direita, nivel + 1);  // Primeiro imprime a subárvore direita

    for (int i = 0; i < nivel; i++) {
        printf("     ");  // Indenta de acordo com o nível
    }
    printf("%d\n", raiz->valor);

    imprimirArvore(raiz->esquerda, nivel + 1);  // Depois imprime a subárvore esquerda
}

// Função para calcular a altura da árvore
int alturaDaArvore(no* raiz) {
    if (raiz == NULL) {
        return 0;
    }

    int alturaEsquerda = alturaDaArvore(raiz->esquerda);
    int alturaDireita = alturaDaArvore(raiz->direita);

    return (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita) + 1;
}

// Função para remover um nó da árvore binária
no* removerNo(no* raiz, int valor) {
    if (raiz == NULL) {
        return NULL;
    }

    // Busca o nó a ser removido
    if (valor < raiz->valor) {
        raiz->esquerda = removerNo(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = removerNo(raiz->direita, valor);
    } else {
        // Caso 1: Nó sem filhos
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }
        // Caso 2: Nó com um filho
        else if (raiz->esquerda == NULL) {
            no* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            no* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        // Caso 3: Nó com dois filhos
        else {
            no* temp = raiz->direita;
            // Encontra o menor valor da subárvore direita
            while (temp->esquerda != NULL) {
                temp = temp->esquerda;
            }
            raiz->valor = temp->valor;
            raiz->direita = removerNo(raiz->direita, temp->valor);
        }
    }
    return raiz;
}

// Função principal (main)
int main(void) {
    no* raiz = NULL;

    // Inserção de nós
    int valores[] = {12, 8, 15, 7, 4, 6, 13, 14, 11, 10};
    int tamanho = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < tamanho; i++) {
        raiz = inserirNo(raiz, valores[i]);
    }

    // Exibe a árvore antes da remoção
    printf("Árvore antes da remoção:\n");
    imprimirArvore(raiz, 0);

    // Remove um nó e exibe a árvore depois
    int valorRemover = 8;
    raiz = removerNo(raiz, valorRemover);
    printf("\nÁrvore após remoção: %d:\n", valorRemover);
    imprimirArvore(raiz, 0);

    // Exibe a altura da árvore
    printf("\nAltura da árvore: %d\n", alturaDaArvore(raiz));

    return 0;
}
