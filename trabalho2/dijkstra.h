#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "PQ.h"

//float dijkstra(Grafo *g, int origem, int dest);
double dijkstra_l(Grafo *grafo, int origem, int destino);
void fuck(Grafo *g);

#endif