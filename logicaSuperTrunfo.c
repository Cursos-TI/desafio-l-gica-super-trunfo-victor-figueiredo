#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "estado.h"
#include "constantes.h"
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

        switch (opcao)
        {
        case LISTAR:
            listarEstados(listaEstados);
            break;
        case COMPARAR:
            if (listaEstados == NULL)
            {
                printf("%sNenhuma carta cadastrada!%s\n\n", COR_VERMELHO, COR_RESET);
            }
            else
            {
                compararCartas(listaEstados);
            }
            break;
        case INSERIR:
            listaEstados = inserirCarta(listaEstados, &proximoIndiceEstado);
            break;
        case APAGAR:
        {
            char apagarId;
            printf("Digite o ID do estado a apagar: ");
            scanf(" %c", &apagarId);
            listaEstados = apagarEstado(listaEstados, apagarId);
            break;
        }
        case SAIR:
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != SAIR);

    // Liberar memória alocada
    while (listaEstados)
    {
        NodeEstado *tmp = listaEstados;
        listaEstados = listaEstados->prox;
        free(tmp);
    }
    return 0;
}
