#ifndef GRAFO_H
#define GRAFO_H

typedef struct aresta Aresta;
typedef struct aresta_list ArestaList;
typedef struct Grafo Grafo;

Grafo * inicializa_grafo(int v, int s, int c, int m);
Grafo * adiciona_vertice(Grafo *grafo, int id, char tipo);
Grafo * adiciona_aresta(Grafo *grafo, int id_no1, int id_no2, float peso);
void libera_grafo(Grafo *grafo);

// para fins de depuracao
void imprime_grafo(Grafo *grafo);

#endif