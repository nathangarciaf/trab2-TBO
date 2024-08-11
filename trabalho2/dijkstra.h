#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "PQ.h"
#include <time.h> 

//float dijkstra(Grafo *g, int origem, int dest);
double dijkstra_l(Grafo *grafo, int origem, int destino);
double dijkstra(Grafo *grafo, int origem, int destino);
void rtt(Grafo *g, FILE *s);

#endif