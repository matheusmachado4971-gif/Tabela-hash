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

        aux = aux->prox;
    }

    printf("\nPalavra nao encontrada!\n");
}

void removerPalavra(Hash *h, char *palavra) {

    int indice = funcaoHash(palavra);

    No *atual = h->tabela[indice];
    No *anterior = NULL;

    while (atual != NULL) {

        if (strcmp(atual->palavra, palavra) == 0) {

            if (anterior == NULL) {
                h->tabela[indice] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            free(atual);

            h->elementos--;

            printf("\nPalavra removida com sucesso!\n");

            return;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("\nPalavra nao encontrada!\n");
}

}

void removerPalavra(Hash *h, char *palavra) {

    int indice = funcaoHash(palavra);

    No *atual = h->tabela[indice];
    No *anterior = NULL;

    while (atual != NULL) {

        if (strcmp(atual->palavra, palavra) == 0) {

            if (anterior == NULL) {
                h->tabela[indice] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            free(atual);

            h->elementos--;

            printf("\nPalavra removida com sucesso!\n");

            return;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("\nPalavra nao encontrada!\n");
}

void exibirTabela(Hash *h) {

    printf("\n=========== TABELA HASH ===========\n");

    for (int i = 0; i < TAMANHO; i++) {

        printf("[%d] -> ", i);

        No *aux = h->tabela[i];

        while (aux != NULL) {
            printf("(%s) -> ", aux->palavra);
            aux = aux->prox;
        }

        printf("NULL\n");
    }
}

int maiorLista(Hash *h) {

    int maior = 0;

    for (int i = 0; i < TAMANHO; i++) {

        int contador = 0;

        No *aux = h->tabela[i];

        while (aux != NULL) {
            contador++;
            aux = aux->prox;
        }

        if (contador > maior) {
            maior = contador;
        }
    }

    return maior;
}

void exibirEstatisticas(Hash *h) {

    float fatorCarga =
        (float) h->elementos / TAMANHO;

    printf("\n=========== ESTATISTICAS ===========\n");

    printf("Quantidade de elementos : %d\n",
           h->elementos);

    printf("Quantidade de colisoes : %d\n",
           h->colisoes);

    printf("Fator de carga         : %.2f\n",
           fatorCarga);

    printf("Maior lista encadeada  : %d\n",
           maiorLista(h));
}

void liberarMemoria(Hash *h) {

    for (int i = 0; i < TAMANHO; i++) {

        No *aux = h->tabela[i];

        while (aux != NULL) {

            No *temp = aux;

            aux = aux->prox;

            free(temp);
        }

        h->tabela[i] = NULL;
    }
}

int main() {

    Hash dicionario;

    inicializar(&dicionario);

    int opcao;

    char palavra[50];
    char definicao[200];

    do {

        printf("\n====================================");
        printf("\n DICIONARIO UTILIZANDO TABELA HASH");
        printf("\n====================================");
        printf("\n1 - Inserir palavra");
        printf("\n2 - Buscar palavra");
        printf("\n3 - Remover palavra");
        printf("\n4 - Exibir tabela hash");
        printf("\n5 - Exibir estatisticas");
        printf("\n0 - Sair");
        printf("\n\nEscolha: ");




