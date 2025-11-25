#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó (sala da mansão)
typedef struct Sala {
    char nome[50];
    struct Sala *esq;
    struct Sala *dir;
} Sala;

// Cria uma sala (nó da árvore)
Sala* criarSala(const char* nome) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    if (!nova) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esq = NULL;
    nova->dir = NULL;
    return nova;
}

// Exploração interativa das salas
void explorarSalas(Sala* atual) {
    char opcao;

    while (1) {
        printf("\nVocê está em: %s\n", atual->nome);

        // Se for folha, fim do caminho
        if (atual->esq == NULL && atual->dir == NULL) {
            printf("Fim do caminho! Você chegou a um cômodo sem saída.\n");
            return;
        }

        printf("Escolha um caminho:\n");
        printf("  (e) Ir para ESQUERDA\n");
        printf("  (d) Ir para DIREITA\n");
        printf("  (s) Sair da exploração\n");
        printf("Sua escolha: ");
        scanf(" %c", &opcao);

        if (opcao == 'e') {
            if (atual->esq != NULL) {
                atual = atual->esq;
            } else {
                printf("Não há caminho para a esquerda!\n");
            }
        }
        else if (opcao == 'd') {
            if (atual->dir != NULL) {
                atual = atual->dir;
            } else {
                printf("Não há caminho para a direita!\n");
            }
        }
        else if (opcao == 's') {
            printf("Exploração encerrada!\n");
            return;
        }
        else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}

int main() {

    // ----- Construção da árvore da mansão -----
    // Exemplo simples, pode ser expandido

    Sala* hall = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* porao = criarSala("Porão");
    Sala* escritorio = criarSala("Escritório");

    // Conectando os cômodos (árvore binária)
    hall->esq = salaEstar;
    hall->dir = biblioteca;

    salaEstar->esq = cozinha;
    salaEstar->dir = porao;

    biblioteca->esq = escritorio;
    // biblioteca->dir permanece NULL (folha)

    // Início do jogo
    printf("===== DETECTIVE QUEST - Nível Novato =====\n");
    printf("Explore a mansão e encontre seu caminho!\n");

    explorarSalas(hall);

        return 0;
}
