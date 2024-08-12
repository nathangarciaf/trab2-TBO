#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aresta Aresta;
typedef struct aresta_list ArestaList;
typedef struct Grafo Grafo;

Grafo * inicializa_grafo(int v, int s, int c, int m);
Grafo * adiciona_vertice(Grafo *grafo, int id, char tipo);
Grafo * adiciona_aresta(Grafo *grafo, int id_no1, int id_no2, float peso);
Grafo *read_graph(FILE *f);
void libera_grafo(Grafo *grafo);

int get_vertex(Grafo *g);
Aresta **retorna_vetor_vizinhos(Grafo *g, int id);
int retorna_tamanho_vetor_vizinhos(Grafo *g, int id);
double retorna_peso_aresta(Aresta *a);
int retorna_id_aresta(Aresta *a);
void print_costs(double *custos, int tam_grafo, int origem);
double *get_cost_array(Grafo *g, int id);
double get_cost(Grafo *g, int id1, int id2);

int get_server_tam(Grafo *g);
int get_monitor_tam(Grafo *g);
int get_client_tam(Grafo *g);

int get_server(Grafo *g, int id);
int get_monitor(Grafo *g, int id);
int get_client(Grafo *g, int id);

// para fins de depuracao
void imprime_grafo(Grafo *grafo);

#endif