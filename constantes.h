#ifndef CONSTANTES_H
#define CONSTANTES_H

// Constantes gerais
#define MAX_ESTADOS 8
#define MAX_CIDADES 4
#define MAX_NOME 30
#define PRIMEIRO_ID 'A'

// Códigos de erro
#define ERRO_ALOCACAO 1
#define ERRO_ESTADO_NAO_ENCONTRADO 2
#define ERRO_LIMITE_ESTADOS 3
#define ERRO_LIMITE_CIDADES 4

// Códigos de cores ANSI
#define COR_VERMELHO "\033[0;31m"
#define COR_RESET "\033[0m"

// Enum para opções do menu
typedef enum
{
    SAIR = 0,
    LISTAR = 1,
    COMPARAR = 2,
    INSERIR = 3,
    APAGAR = 4
} OpcaoMenu;

#endif // CONSTANTES_H
