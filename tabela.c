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

void inserir(Hash *h, char *palavra, char *definicao) {

    if (palavraExiste(h, palavra)) {
        printf("\nEssa palavra ja existe no dicionario!\n");
        return;
    }

    int indice = funcaoHash(palavra);

    if (h->tabela[indice] != NULL) {
        h->colisoes++;
    }

    No *novo = (No *) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }

    strcpy(novo->palavra, palavra);
    strcpy(novo->definicao, definicao);

    novo->prox = h->tabela[indice];
    h->tabela[indice] = novo;

    h->elementos++;

    printf("\nPalavra inserida com sucesso!\n");
}

void buscar(Hash *h, char *palavra) {

    int indice = funcaoHash(palavra);

    No *aux = h->tabela[indice];

    while (aux != NULL) {

        if (strcmp(aux->palavra, palavra) == 0) {

            printf("\n================================");
            printf("\nPalavra: %s", aux->palavra);
            printf("\nDefinicao: %s", aux->definicao);
            printf("\n================================\n");

            return;
        }

