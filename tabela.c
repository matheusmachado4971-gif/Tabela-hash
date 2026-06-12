#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 10

typedef struct No {
    char palavra[50];
    char definicao[200];
    struct No *prox;
} No;

typedef struct {
    No *tabela[TAMANHO];
    int elementos;
    int colisoes;
} Hash;

int funcaoHash(char *palavra) {
    int soma = 0;

    for (int i = 0; palavra[i] != '\0'; i++) {
        soma += palavra[i];
    }

    return soma % TAMANHO;
}

void inicializar(Hash *h) {
    for (int i = 0; i < TAMANHO; i++) {
        h->tabela[i] = NULL;
    }

    h->elementos = 0;
    h->colisoes = 0;
}

int palavraExiste(Hash *h, char *palavra) {
    int indice = funcaoHash(palavra);

    No *aux = h->tabela[indice];

    while (aux != NULL) {
        if (strcmp(aux->palavra, palavra) == 0) {
            return 1;
        }

        aux = aux->prox;
    }

    return 0;
}

