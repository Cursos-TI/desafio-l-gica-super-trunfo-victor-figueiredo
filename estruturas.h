#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct Cidade
{
    char id[4];
    char nome[30];
    int populacao;
    int pontosTuristicos;
    float area;
    float pib;
    float densidade;
    float pibPerCapita;
} Cidade;

typedef struct NodeEstado
{
    char id;
    char nome[30];
    int quantidadeCidades;
    Cidade cidades[4];
    struct NodeEstado *prox;
} NodeEstado;

#endif // ESTRUTURAS_H
