#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 26

// -----------------------------------------------------------------------------
// -------------------------------  B S T  -------------------------------------
// -----------------------------------------------------------------------------

typedef struct NoBST {
    char pista[100];
    struct NoBST *esq, *dir;
} NoBST;

// Criar novo nó da BST
NoBST* novoNo(char *pista) {
    NoBST *n = malloc(sizeof(NoBST));
    strcpy(n->pista, pista);
    n->esq = n->dir = NULL;
    return n;
}

// Inserir pista na BST
NoBST* inserirBST(NoBST *raiz, char *pista) {
    if (raiz == NULL)
        return novoNo(pista);

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esq = inserirBST(raiz->esq, pista);
    else
        raiz->dir = inserirBST(raiz->dir, pista);

    return raiz;
}

// Mostrar pistas em ordem
void exibirBST(NoBST *raiz) {
    if (raiz == NULL) return;
    exibirBST(raiz->esq);
    printf(" - %s\n", raiz->pista);
    exibirBST(raiz->dir);
}

// -----------------------------------------------------------------------------
// ---------------------------  TABELA HASH  -----------------------------------
// -----------------------------------------------------------------------------

typedef struct NoHash {
    char pista[100];
    char suspeito[100];
    struct NoHash *prox;
} NoHash;

typedef struct {
    NoHash *buckets[TAM_HASH];
} TabelaHash;


// Função de hash baseada na primeira letra da pista
int funcaoHash(char *p) {
    char c = p[0];
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a';
    return 0;
}

// Inicializar tabela hash
void inicializarHash(TabelaHash *t) {
    for (int i = 0; i < TAM_HASH; i++)
        t->buckets[i] = NULL;
}

// Inserir pista → suspeito
void inserirNaHash(TabelaHash *t, char *pista, char *suspeito) {
    int index = funcaoHash(pista);

    NoHash *novo = malloc(sizeof(NoHash));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);

    novo->prox = t->buckets[index];
    t->buckets[index] = novo;
}

// Mostrar todas as associações
void exibirAssociacoes(TabelaHash *t) {
    printf("\n=== ASSOCIAÇÕES PISTA → SUSPEITO ===\n");

    for (int i = 0; i < TAM_HASH; i++) {
        NoHash *aux = t->buckets[i];
        while (aux != NULL) {
            printf("Pista: %-20s  →  Suspeito: %s\n", aux->pista, aux->suspeito);
            aux = aux->prox;
        }
    }
}

// ----------------------- Contagem de suspeitos --------------------------------

typedef struct Contador {
    char suspeito[100];
    int qtd;
    struct Contador *prox;
} Contador;

void adicionarOuIncrementar(Contador **lista, char *suspeito) {
    Contador *aux = *lista;

    while (aux != NULL) {
        if (strcmp(aux->suspeito, suspeito) == 0) {
            aux->qtd++;
            return;
        }
        aux = aux->prox;
    }

    Contador *novo = malloc(sizeof(Contador));
    strcpy(novo->suspeito, suspeito);
    novo->qtd = 1;
    novo->prox = *lista;
    *lista = novo;
}

// Determinar culpado
char* suspeitoMaisCitado(TabelaHash *t) {
    Contador *lista = NULL;

    for (int i = 0; i < TAM_HASH; i++) {
        NoHash *aux = t->buckets[i];
        while (aux != NULL) {
            adicionarOuIncrementar(&lista, aux->suspeito);
            aux = aux->prox;
        }
    }

    if (lista == NULL)
        return "Nenhum suspeito registrado.";

    Contador *maior = lista;
    Contador *aux = lista;

    while (aux != NULL) {
        if (aux->qtd > maior->qtd)
            maior = aux;
        aux = aux->prox;
    }

    return maior->suspeito;
}

// -----------------------------------------------------------------------------
// ---------------------------  FLUXO DO JOGO ----------------------------------
// -----------------------------------------------------------------------------

void menu() {
    printf("\n=====================================\n");
    printf("         JOGO DA MANSÃO - NÍVEL MESTRE\n");
    printf("=====================================\n");
    printf("[1] Inserir pista\n");
    printf("[2] Mostrar pistas (BST)\n");
    printf("[3] Relacionar pista → suspeito\n");
    printf("[4] Mostrar associações\n");
    printf("[5] Suspeito mais citado\n");
    printf("[0] Sair\n");
    printf("Escolha: ");
}

int main() {
    NoBST *bst = NULL;
    TabelaHash hash;
    inicializarHash(&hash);

    int op;
    char pista[100], suspeito[100];

    do {
        menu();
        scanf("%d", &op);
        getchar(); // limpar buffer

        switch (op) {

        case 1:
            printf("Digite a pista: ");
            fgets(pista, 100, stdin);
            pista[strcspn(pista, "\n")] = 0;
            bst = inserirBST(bst, pista);
            printf("Pista inserida na BST.\n");
            break;

        case 2:
            printf("\n=== PISTAS COLETADAS (BST) ===\n");
            exibirBST(bst);
            break;

        case 3:
            printf("Digite a pista: ");
            fgets(pista, 100, stdin);
            pista[strcspn(pista, "\n")] = 0;

            printf("Digite o suspeito associado: ");
            fgets(suspeito, 100, stdin);
            suspeito[strcspn(suspeito, "\n")] = 0;

            inserirNaHash(&hash, pista, suspeito);
            printf("Associação registrada.\n");
            break;

        case 4:
            exibirAssociacoes(&hash);
            break;

        case 5: {
            char *culpado = suspeitoMaisCitado(&hash);
            printf("\n>>> SUSPEITO MAIS CITADO: %s\n", culpado);
            break;
        }

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida.\n");
        }

    } while (op != 0);

    return 0;
}
