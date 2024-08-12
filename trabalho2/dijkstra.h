#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "PQ.h"
#include <time.h> 

//float dijkstra(Grafo *g, int origem, int dest);
void dijkstra(Grafo *grafo, int origem);
void rtt(Grafo *g, PQ *pq);
void print_rtt(PQ *pq, FILE *s);

#endif