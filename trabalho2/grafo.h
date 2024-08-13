#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aresta Aresta;
typedef struct aresta_list ArestaList;
typedef struct Grafo Grafo;

Grafo * graph_init(int v, int s, int c, int m, int a);
Grafo * add_vertex(Grafo *grafo, int id, char tipo);
Grafo * add_edge(Grafo *grafo, int id_no1, int id_no2, float peso);
Grafo *read_graph(FILE *f);
void free_graph(Grafo *grafo);

int get_vertex(Grafo *g);

Aresta **get_neighboring_edges(Grafo *g, int id);
int get_neighboring_edges_tam(Grafo *g, int id);

double get_edge_value(Aresta *a);
int get_edge_id(Aresta *a);

double *get_cost_array(Grafo *g, int id);
double get_cost(Grafo *g, int id1, int id2);

int get_server_tam(Grafo *g);
int get_monitor_tam(Grafo *g);
int get_client_tam(Grafo *g);

int get_edge_alloc(Grafo *g);

int get_server(Grafo *g, int id);
int get_monitor(Grafo *g, int id);
int get_client(Grafo *g, int id);

// para fins de depuracao

#endif