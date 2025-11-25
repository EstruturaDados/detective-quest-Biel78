#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ==========================================================
   ESTRUTURAS DE DADOS
   ========================================================== */

// Estrutura da sala (mesma do nível Novato)
typedef struct Sala {
    char nome[50];
    char pista[50];   // pista encontrada na sala ("" se não tiver)
    struct Sala *esq;
    struct Sala *dir;
} Sala;

// Nó da Árvore de Busca (BST) de pistas
typedef struct NodePista {
    char pista[50];
    struct NodePista *esq, *dir;
} NodePista;

/* ==========================================================
   FUNÇÕES DA BST (Árvore de Busca de Pistas)
   ========================================================== */

// Insere pista em ordem alfabética
NodePista* inserir(NodePista* raiz, const char* pista) {
    if (raiz == NULL) {
        NodePista* novo = (NodePista*) malloc(sizeof(NodePista));
        strcpy(novo->pista, pista);
        novo->esq = novo->dir = NULL;
        return novo;
    }

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esq = inserir(raiz->esq, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->dir = inserir(raiz->dir, pista);

    return raiz;
}

// Exibe pistas em ordem alfabética
void emOrdem(NodePista* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf(" - %s\n", raiz->pista);
        emOrdem(raiz->dir);
    }
}

/* ==========================================================
   FUNÇÕES DA ÁRVORE DE SALAS
   ========================================================== */

Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista); // pista opcional
    nova->esq = nova->dir = NULL;
    return nova;
}

// Exploração da mansão com coleta de pistas
void explorarSalas(Sala* atual, NodePista** arvorePistas) {
    char opcao;

    while (1) {
        printf("\nVocê está em: %s\n", atual->nome);

        // Se a sala tiver pista:
        if (strlen(atual->pista) > 0) {
            printf("Você encontrou uma pista: %s\n", atual->pista);
            *arvorePistas = inserir(*arvorePistas, atual->pista);
        }

        // Se for folha:
        if (atual->esq == NULL && atual->dir == NULL) {
            printf("Fim do caminho! Você chegou a um cômodo sem saída.\n");
            return;
        }

        printf("\nEscolha um caminho:\n");
        printf("  (e) Ir para ESQUERDA\n");
        printf("  (d) Ir para DIREITA\n");
        printf("  (p) Ver todas as pistas\n");
        printf("  (s) Sair da exploração\n");
        printf("Sua escolha: ");
        scanf(" %c", &opcao);

        if (opcao == 'e') {
            if (atual->esq != NULL) atual = atual->esq;
            else printf("Não há caminho para a esquerda!\n");
        }
        else if (opcao == 'd') {
            if (atual->dir != NULL) atual = atual->dir;
            else printf("Não há caminho para a direita!\n");
        }
        else if (opcao == 'p') {
            printf("\n===== PISTAS COLETADAS =====\n");
            emOrdem(*arvorePistas);
            printf("=============================\n");
        }
        else if (opcao == 's') {
            printf("Exploração encerrada!\n");
            return;
        }
        else {
            printf("Opção inválida!\n");
        }
    }
}


/* ==========================================================
   MAIN — CRIA A MANSÃO + INICIA O JOGO
   ========================================================== */

int main() {

    // Criação das salas (algumas contém pistas)
    Sala* hall        = criarSala("Hall de Entrada", "");
    Sala* salaEstar   = criarSala("Sala de Estar", "Chave dourada");
    Sala* biblioteca  = criarSala("Biblioteca", "");
    Sala* cozinha     = criarSala("Cozinha", "Pegada suspeita");
    Sala* porao       = criarSala("Porão", "Mapa rasgado");
    Sala* escritorio  = criarSala("Escritório", "Bilhete misterioso");

    // Conexões da árvore de salas
    hall->esq = salaEstar;
    hall->dir = biblioteca;

    salaEstar->esq = cozinha;
    salaEstar->dir = porao;

    biblioteca->esq = escritorio;

    // Árvore de pistas começa vazia
    NodePista* arvorePistas = NULL;

    printf("===== DETECTIVE QUEST - Nível Aventureiro =====\n");
    printf("Explore a mansão, colete pistas e descubra segredos!\n");

    explorarSalas(hall, &arvorePistas);

    printf("\n===== PISTAS FINAIS COLETADAS =====\n");
    emOrdem(arvorePistas);

    return 0;
}
