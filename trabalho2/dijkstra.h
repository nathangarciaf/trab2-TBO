#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"

float dijkstra(Grafo *g, int origem, int dest);
double dijkstra_l(Grafo * grafo, int origem, int destino);

#endif