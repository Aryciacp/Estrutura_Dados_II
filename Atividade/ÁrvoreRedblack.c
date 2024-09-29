#include <stdio.h>
#include <stdlib.h>

#define VERMELHO 0   // Definindo cor Vermelha
#define PRETO 1      // Definindo cor Preta

typedef struct No {
  int valor;
  int cor;
  struct No *esq, *dir, *pai;
} No;

// Função para criar um novo nó na árvore
No *criarNovoNo(int valor){
  No *novo = (No *)malloc(sizeof(No));
  if (novo == NULL) {
    printf("Erro de alocação de memória.\n");
    exit(1);
  }
  novo->valor = valor;
  novo->cor = VERMELHO;
  novo->esq = novo->dir = novo->pai = NULL;
  return novo;
}

// Função para realizar a rotação à esquerda
void rotacaoEsquerda(No **raiz, No *no){
  No *dir = no->dir;
  no->dir = dir->esq;
  if (dir->esq != NULL) dir->esq->pai = no;

  dir->pai = no->pai;
  if (no->pai == NULL) {
    *raiz = dir;
  } else if (no == no->pai->esq) {
    no->pai->esq = dir;
  } else {
    no->pai->dir = dir;
  }

  dir->esq = no;
  no->pai = dir;
}

// Função para realizar a rotação à direita
void rotacaoDireita(No **raiz, No *no){
  No *esq = no->esq;
  no->esq = esq->dir;
  if (esq->dir != NULL) esq->dir->pai = no;

  esq->pai = no->pai;
  if (no->pai == NULL) {
    *raiz = esq;
  } else if (no == no->pai->dir) {
    no->pai->dir = esq;
  } else {
    no->pai->esq = esq;
  }

  esq->dir = no;
  no->pai = esq;
}

// Função para corrigir as violações da árvore rubro-negra
void corrigirViolacoes(No **raiz, No *no){
  while (no != *raiz && no->pai->cor == VERMELHO) {
    if (no->pai == no->pai->pai->esq) {
      No *tio = no->pai->pai->dir;
      if (tio != NULL && tio->cor == VERMELHO) {
        no->pai->cor = PRETO;
        tio->cor = PRETO;
        no->pai->pai->cor = VERMELHO;
        no = no->pai->pai;
      } else {
        if (no == no->pai->dir) {
          no = no->pai;
          rotacaoEsquerda(raiz, no);
        }
        no->pai->cor = PRETO;
        no->pai->pai->cor = VERMELHO;
        rotacaoDireita(raiz, no->pai->pai);
      }
    } else {
      No *tio = no->pai->pai->esq;
      if (tio != NULL && tio->cor == VERMELHO) {
        no->pai->cor = PRETO;
        tio->cor = PRETO;
        no->pai->pai->cor = VERMELHO;
        no = no->pai->pai;
      } else {
        if (no == no->pai->esq) {
          no = no->pai;
          rotacaoDireita(raiz, no);
        }
        no->pai->cor = PRETO;
        no->pai->pai->cor = VERMELHO;
        rotacaoEsquerda(raiz, no->pai->pai);
      }
    }
  }
  (*raiz)->cor = PRETO;
}

// Função para inserir um valor na árvore
void inserir(No **raiz, int valor){
  No *novo = criarNovoNo(valor);
  No *x = *raiz;
  No *y = NULL;

  while (x != NULL) {
    y = x;
    x = (novo->valor < x->valor) ? x->esq : x->dir;
  }

  novo->pai = y;
  if (y == NULL) {
    *raiz = novo;
  } else if (novo->valor < y->valor) {
    y->esq = novo;
  } else {
    y->dir = novo;
  }

  corrigirViolacoes(raiz, novo);
}

// Função para imprimir a árvore com indentação
void imprimirArvore(No *raiz, int nivel){
  if (raiz == NULL) return;

  imprimirArvore(raiz->dir, nivel + 1);

  for (int i = 0; i < nivel; i++) printf("   ");
  printf("%d(%s)\n", raiz->valor, raiz->cor == VERMELHO ? "V" : "P");

  imprimirArvore(raiz->esq, nivel + 1);
}

// Função para buscar um valor na árvore
No* buscar(No *raiz, int valor) {
  if (raiz == NULL || raiz->valor == valor) return raiz;
  return (valor < raiz->valor) ? buscar(raiz->esq, valor) : buscar(raiz->dir, valor);
}

int main() {
  No *raiz = NULL;

  int valores[] = {30, 67, 32, 19, 22, 9};
  for (int i = 0; i < 6; i++) {
    inserir(&raiz, valores[i]);
  }

  printf("Arvore Rubro-Negra:\n");
  imprimirArvore(raiz, 0);

  int valorBuscado = 25;
  No *resultado = buscar(raiz, valorBuscado);
  printf("Valor %d %s encontrado.\n", valorBuscado, resultado ? "foi" : "não foi");

  return 0;
}
