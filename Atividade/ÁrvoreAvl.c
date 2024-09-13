//arycia cabral pezente

#include <stdio.h>
#include <stdlib.h>

// Definindo macros para obter a altura de um nó e o maior valor entre dois números
#define ALTURA(no) ((no) ? (no)->altura : -1)
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Estrutura de um nó da árvore AVL
struct NoArvore {
    int valor;
    int altura;
    struct NoArvore *esq;
    struct NoArvore *dir;
};

// Função para criar um novo nó
struct NoArvore *criaNovoNo(int valor) {
    struct NoArvore *novoNo = (struct NoArvore *)malloc(sizeof(struct NoArvore));
    if (!novoNo) {
        printf("Erro de memória\n");
        return NULL;
    }
    novoNo->valor = valor;
    novoNo->esq = novoNo->dir = NULL;
    novoNo->altura = 0;
    return novoNo;
}

// Função para calcular o fator de balanceamento de um nó
int calcularFatorBalanceamento(struct NoArvore *no) {
    return ALTURA(no->esq) - ALTURA(no->dir);
}

// Rotação à direita
struct NoArvore *rotacaoDireita(struct NoArvore *no) {
    struct NoArvore *novoNo = no->esq;
    no->esq = novoNo->dir;
    novoNo->dir = no;

    no->altura = 1 + MAX(ALTURA(no->esq), ALTURA(no->dir));
    novoNo->altura = 1 + MAX(ALTURA(novoNo->esq), ALTURA(novoNo->dir));

    return novoNo;
}

// Rotação à esquerda
struct NoArvore *rotacaoEsquerda(struct NoArvore *no) {
    struct NoArvore *novoNo = no->dir;
    no->dir = novoNo->esq;
    novoNo->esq = no;

    no->altura = 1 + MAX(ALTURA(no->esq), ALTURA(no->dir));
    novoNo->altura = 1 + MAX(ALTURA(novoNo->esq), ALTURA(novoNo->dir));

    return novoNo;
}

// Função para balancear a árvore após inserção ou remoção
struct NoArvore *realizarBalanceamento(struct NoArvore *raiz) {
    int bal = calcularFatorBalanceamento(raiz);

    if (bal > 1) {
        if (calcularFatorBalanceamento(raiz->esq) < 0)
            raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    if (bal < -1) {
        if (calcularFatorBalanceamento(raiz->dir) > 0)
            raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

// Função para inserir um valor na árvore
struct NoArvore *inserir(struct NoArvore *raiz, int valor) {
    if (!raiz) return criaNovoNo(valor);

    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);
    else
        return raiz;

    raiz->altura = 1 + MAX(ALTURA(raiz->esq), ALTURA(raiz->dir));
    return realizarBalanceamento(raiz);
}

// Função para encontrar o nó com o menor valor
struct NoArvore *encontrarMinimo(struct NoArvore *no) {
    while (no->esq) no = no->esq;
    return no;
}

// Função para remover um valor da árvore
struct NoArvore *remover(struct NoArvore *raiz, int valor) {
    if (!raiz) return raiz;

    if (valor < raiz->valor)
        raiz->esq = remover(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = remover(raiz->dir, valor);
    else {
        if (!raiz->esq || !raiz->dir) {
            struct NoArvore *temp = raiz->esq ? raiz->esq : raiz->dir;
            if (!temp) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            struct NoArvore *temp = encontrarMinimo(raiz->dir);
            raiz->valor = temp->valor;
            raiz->dir = remover(raiz->dir, temp->valor);
        }
    }

    if (!raiz) return raiz;

    raiz->altura = 1 + MAX(ALTURA(raiz->esq), ALTURA(raiz->dir));
    return realizarBalanceamento(raiz);
}

// Função para imprimir a árvore
void imprimeArvore(struct NoArvore *raiz, int espaco) {
    if (!raiz) return;

    espaco += 5;
    imprimeArvore(raiz->dir, espaco);

    printf("\n");
    for (int i = 5; i < espaco; i++) printf(" ");
    printf("%d\n", raiz->valor);

    imprimeArvore(raiz->esq, espaco);
}

// Função para buscar um valor na árvore
struct NoArvore *buscar(struct NoArvore *raiz, int valor) {
    if (!raiz) {
        printf("Valor %d não encontrado.\n", valor);
        return NULL;
    }

    if (valor == raiz->valor) {
        printf("Valor %d encontrado.\n", valor);
        return raiz;
    }

    return valor < raiz->valor ? buscar(raiz->esq, valor) : buscar(raiz->dir, valor);
}

// Função principal
int main(void) {
    struct NoArvore *raiz = NULL;

    raiz = inserir(raiz, 11);
    raiz = inserir(raiz, 19);
    raiz = inserir(raiz, 22);
    raiz = inserir(raiz, 45);
    raiz = inserir(raiz, 9);

    buscar(raiz, 19);
    buscar(raiz, 22);
    buscar(raiz, 80);

    imprimeArvore(raiz, 0);

    raiz = remover(raiz, 19);
    imprimeArvore(raiz, 9);

    return 0;
}
