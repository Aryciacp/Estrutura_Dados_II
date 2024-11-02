//Aryca cabral pezente

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No {
    int dado;
    int prioridade;
    struct No* direito;
    struct No* esquerdo;
} No;

No* criar_no(int dado);
void liberar_arvore(No* raiz);
No* rotacionar_direita(No* no);
No* rotacionar_esquerda(No* no);
No* inserir_no(No* no, int dado);
No* deletar_no(No* no, int dado);
int buscar_no(No* no, int dado);
void imprimir_arvore(No* raiz, int nivel);

int main() {
    srand(time(NULL));
    No* raiz = NULL;
    int dado, entrada;

    do {
        printf("-------------- Árvore Treap --------------\n");
        printf("1- Inserir Valor\n2- Buscar Valor\n3- Deletar Valor\n4- Exibir Árvore\n5- Inserir Valores Aleatórios\n0- Sair\n");
        scanf("%d", &entrada);

        switch (entrada) {
            case 1:
                printf("Valor a ser inserido: ");
                scanf("%d", &dado);
                raiz = inserir_no(raiz, dado);
                break;
            case 2:
                printf("Valor a ser buscado: ");
                scanf("%d", &dado);
                printf("Valor %d %s encontrado.\n", dado, buscar_no(raiz, dado) ? "" : "não");
                break;
            case 3:
                printf("Valor a ser deletado: ");
                scanf("%d", &dado);
                raiz = deletar_no(raiz, dado);
                break;
            case 4:
                printf("-----------------------------------------\n");
                imprimir_arvore(raiz, 0);
                printf("-----------------------------------------\n");
                break;
            case 5:
                for (int i = 0; i < 10; i++) {
                    raiz = inserir_no(raiz, rand() % 101);
                }
                printf("Valores aleatórios inseridos!\n");
                break;
            default:
                if (entrada != 0) printf("Opção inválida!\n");
        }
    } while (entrada != 0);

    liberar_arvore(raiz);
    printf("Encerrando aplicação!\n");
    return 0;
}

No* criar_no(int dado) {
    No* novo_no = (No*)malloc(sizeof(No));
    if (!novo_no) {
        printf("Erro de alocação de memória.\n");
        exit(-1);
    }
    novo_no->dado = dado;
    novo_no->prioridade = rand() % 100;
    novo_no->direito = novo_no->esquerdo = NULL;
    return novo_no;
}

void liberar_arvore(No* raiz) {
    if (!raiz) return;
    liberar_arvore(raiz->esquerdo);
    liberar_arvore(raiz->direito);
    free(raiz);
}

No* rotacionar_direita(No* no) {
    No* filho_esquerdo = no->esquerdo;
    no->esquerdo = filho_esquerdo->direito;
    filho_esquerdo->direito = no;
    return filho_esquerdo;
}

No* rotacionar_esquerda(No* no) {
    No* filho_direito = no->direito;
    no->direito = filho_direito->esquerdo;
    filho_direito->esquerdo = no;
    return filho_direito;
}

No* inserir_no(No* no, int dado) {
    if (!no) return criar_no(dado);

    if (dado < no->dado) {
        no->esquerdo = inserir_no(no->esquerdo, dado);
        if (no->esquerdo->prioridade > no->prioridade)
            no = rotacionar_direita(no);
    } else if (dado > no->dado) {
        no->direito = inserir_no(no->direito, dado);
        if (no->direito->prioridade > no->prioridade)
            no = rotacionar_esquerda(no);
    } else {
        printf("Valor já existe.\n");
    }
    return no;
}

No* deletar_no(No* no, int dado) {
    if (!no) return NULL;

    if (dado < no->dado) {
        no->esquerdo = deletar_no(no->esquerdo, dado);
    } else if (dado > no->dado) {
        no->direito = deletar_no(no->direito, dado);
    } else {
        if (!no->esquerdo || !no->direito) {
            No* temp = no->esquerdo ? no->esquerdo : no->direito;
            free(no);
            return temp;
        }
        if (no->esquerdo->prioridade > no->direito->prioridade) {
            no = rotacionar_direita(no);
            no->direito = deletar_no(no->direito, dado);
        } else {
            no = rotacionar_esquerda(no);
            no->esquerdo = deletar_no(no->esquerdo, dado);
        }
    }
    return no;
}

int buscar_no(No* no, int dado) {
    if (!no) return 0;
    if (no->dado == dado) return 1;
    return dado < no->dado ? buscar_no(no->esquerdo, dado) : buscar_no(no->direito, dado);
}

void imprimir_arvore(No* raiz, int nivel) {
    if (!raiz) return;
    imprimir_arvore(raiz->direito, nivel + 1);
    for (int i = 0; i < nivel; i++) printf("    ");
    printf("%d (p=%d)\n", raiz->dado, raiz->prioridade);
    imprimir_arvore(raiz->esquerdo, nivel + 1);
}
