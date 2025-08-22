// Olá, tudo bem? Eu atuo como desenvolvedor há 4 anos e gostei muito do desafio e estou amando poder aprender e revisar bastante coisa com os estudos na estácio.
// Como eu já tenho experiência, acabei tomando a liberdade de construir o desafio completo logo a partir do nivel novato. Espero que tenha gostado.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

NodeEstado *inserirEstado(NodeEstado *lista, char nome[], char id);
void inserirCidade(NodeEstado *estado, Cidade c);
NodeEstado *apagarEstado(NodeEstado *lista, char id);
void listarEstados(NodeEstado *lista);
Cidade cadastrarCidade(NodeEstado *estado);
NodeEstado *inserirCarta(NodeEstado *listaEstados, int *proximoIndiceEstado);
NodeEstado *buscarEstadoPorId(NodeEstado *lista, char id);
void compararCartas(NodeEstado *lista);

NodeEstado *inserirEstado(NodeEstado *lista, char nome[], char id)
{
    NodeEstado *novo = (NodeEstado *)malloc(sizeof(NodeEstado));
    if (!novo)
    {
        printf("Falha ao alocar memoria.\n");
        exit(1);
    }
    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';
    novo->id = id;
    novo->quantidadeCidades = 0;
    novo->prox = lista;
    return novo;
}

void inserirCidade(NodeEstado *estado, Cidade c)
{
    if (!estado)
        return;
    if (estado->quantidadeCidades < 4)
    {
        estado->cidades[estado->quantidadeCidades] = c;
        estado->quantidadeCidades++;
    }
    else
    {
        printf("Esse estado (%c) ja tem 4 cidades!\n", estado->id);
    }
}

NodeEstado *apagarEstado(NodeEstado *lista, char id)
{
    NodeEstado *ant = NULL, *p = lista;
    while (p)
    {
        if (p->id == id)
        {
            if (ant)
                ant->prox = p->prox;
            else
                lista = p->prox;
            free(p);
            return lista;
        }
        ant = p;
        p = p->prox;
    }
    printf("Estado %c nao encontrado!\n", id);
    return lista;
}

void listarEstados(NodeEstado *lista)
{
    if (!lista)
    {
        printf("\033[0;31mNenhuma carta cadastrada!\033[0m\n\n");
        return;
    }
    for (NodeEstado *e = lista; e; e = e->prox)
    {
        printf("\nEstado %c - %s\n", e->id, e->nome);
        for (int i = 0; i < e->quantidadeCidades; i++)
        {
            Cidade c = e->cidades[i];
            printf("  Cidade %s - %s\n", c.id, c.nome);
            printf("    Populacao: %d\n", c.populacao);
            printf("    Area: %.2f\n", c.area);
            printf("    PIB: %.2f\n", c.pib);
            printf("    Pontos turisticos: %d\n", c.pontosTuristicos);
            printf("    Densidade: %.2f\n", c.densidade);
            printf("    PIB per Capita: %.2f\n", c.pibPerCapita);
        }
    }
}

Cidade cadastrarCidade(NodeEstado *estado)
{
    Cidade c;

    int idx = estado->quantidadeCidades + 1;
    sprintf(c.id, "%c%02d", estado->id, idx);

    printf("\n--- Cadastro da cidade %s ---\n", c.id);
    printf("Nome: ");
    scanf(" %29s", c.nome);
    printf("Populacao: ");
    scanf("%d", &c.populacao);
    printf("Pontos turisticos: ");
    scanf("%d", &c.pontosTuristicos);
    printf("Area: ");
    scanf("%f", &c.area);
    printf("PIB: ");
    scanf("%f", &c.pib);

    c.densidade = (c.area > 0.0f) && (c.populacao > 0) ? (c.populacao / c.area) : 0.0f;
    c.pibPerCapita = (c.populacao > 0) ? (c.pib / c.populacao) : 0.0f;

    return c;
}

NodeEstado *inserirCarta(NodeEstado *listaEstados, int *proximoIndiceEstado)
{
    if (*proximoIndiceEstado >= 8)
    {
        printf("Limite de 8 estados atingido!\n");
    }
    else
    {
        char nomeEstado[30];
        printf("Digite o nome do Estado: ");
        scanf(" %29s", nomeEstado);

        char estadoId = (char)('A' + *proximoIndiceEstado);

        listaEstados = inserirEstado(listaEstados, nomeEstado, estadoId);
        NodeEstado *novoEstado = listaEstados;
        (*proximoIndiceEstado)++;

        for (int i = 0; i < 4; i++)
        {
            Cidade c = cadastrarCidade(novoEstado);
            inserirCidade(novoEstado, c);
        }
    }
    return listaEstados;
}

NodeEstado *buscarEstadoPorId(NodeEstado *lista, char id)
{
    for (NodeEstado *p = lista; p; p = p->prox)
        if (p->id == id)
            return p;
    return NULL;
}

void compararCartas(NodeEstado *lista)
{
    char id1, id2;

    printf("Cartas disponíveis:\n");
    NodeEstado *atual = lista;
    while (atual != NULL)
    {
        printf("Estado %c - %s\n", atual->id, atual->nome);
        atual = atual->prox;
    }

    printf("Jogador 1, escolha o ID do seu estado: ");
    scanf(" %c", &id1);
    NodeEstado *carta1 = buscarEstadoPorId(lista, id1);

    printf("Jogador 2, escolha o ID do seu estado: ");
    scanf(" %c", &id2);
    NodeEstado *carta2 = buscarEstadoPorId(lista, id2);

    if (!carta1 || !carta2)
    {
        printf("Carta inválida!\n");
        return;
    }

    printf("\n=== Comparação de Cartas ===\n");
    for (int i = 0; i < 4; i++)
    {
        Cidade a = carta1->cidades[i];
        Cidade b = carta2->cidades[i];

        printf("\nCidade %s vs %s\n", a.id, b.id);
        printf("População: %s vence\n", (a.populacao > b.populacao) ? a.id : b.id);
        printf("Área: %s vence\n", (a.area > b.area) ? a.id : b.id);
        printf("PIB: %s vence\n", (a.pib > b.pib) ? a.id : b.id);
        printf("Pontos Turísticos: %s vence\n", (a.pontosTuristicos > b.pontosTuristicos) ? a.id : b.id);
        printf("Densidade: %s vence\n", (a.densidade < b.densidade) ? a.id : b.id);
        printf("PIB per Capita: %s vence\n", (a.pibPerCapita > b.pibPerCapita) ? a.id : b.id);

        float super1 = a.populacao + a.area + a.pib + a.pontosTuristicos + a.pibPerCapita + (1 / a.densidade);
        float super2 = b.populacao + b.area + b.pib + b.pontosTuristicos + b.pibPerCapita + (1 / b.densidade);

        printf("Super Poder: %s vence (%.2f vs %.2f)\n",
               (super1 > super2) ? a.id : b.id, super1, super2);
    }
}

int main()
{
    NodeEstado *listaEstados = NULL;
    int opcao;
    int proximoIndiceEstado = 0;

    do
    {
        printf("\n=== MENU ===\n");
        printf("1 - Listar cartas\n");
        printf("2 - Comparar cartas\n");
        printf("3 - Inserir carta\n");
        printf("4 - Apagar carta\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            listarEstados(listaEstados);
        }
        else if (opcao == 2)
        {
            if (listaEstados == NULL)
            {
                printf("\033[0;31mNenhuma carta cadastrada!\033[0m\n\n");
            }
            else
            {
                compararCartas(listaEstados);
            }
        }
        else if (opcao == 3)
        {
            listaEstados = inserirCarta(listaEstados, &proximoIndiceEstado);
        }
        else if (opcao == 4)
        {
            char apagarId;
            printf("Digite o ID do estado a apagar: ");
            scanf(" %c", &apagarId);
            listaEstados = apagarEstado(listaEstados, apagarId);
        }

    } while (opcao != 0);

    while (listaEstados)
    {
        NodeEstado *tmp = listaEstados;
        listaEstados = listaEstados->prox;
        free(tmp);
    }
    return 0;
}
