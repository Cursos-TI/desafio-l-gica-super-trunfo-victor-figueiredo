#ifndef ESTADO_H
#define ESTADO_H

#include "estruturas.h"

NodeEstado *inserirEstado(NodeEstado *lista, char nome[], char id);
void inserirCidade(NodeEstado *estado, Cidade c);
NodeEstado *apagarEstado(NodeEstado *lista, char id);
void listarEstados(NodeEstado *lista);
Cidade cadastrarCidade(NodeEstado *estado);
NodeEstado *inserirCarta(NodeEstado *listaEstados, int *proximoIndiceEstado);
NodeEstado *buscarEstadoPorId(NodeEstado *lista, char id);
void compararCartas(NodeEstado *lista);

#endif // ESTADO_H
