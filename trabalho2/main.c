#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "dijkstra.h"
#include "PQ.h"
#include "item.h"

int main(){
    int v, e, s, c, m;
    int id_aux;
    int id1, id2;
    float peso;
    char tipo;

    scanf("%d %d", &v, &e);
    scanf("%d %d %d", &s, &c, &m);

    Grafo *grafo = inicializa_grafo(v, s, c, m);

    //inicializacao do grafo
    tipo = 'S';
    for (int i = 0; i < s; i++){
        scanf("%d", &id_aux);
        grafo = adiciona_vertice(grafo, id_aux, tipo);
    }

    tipo = 'C';
    for (int i = 0; i < c; i++){
        scanf("%d", &id_aux);
        grafo = adiciona_vertice(grafo, id_aux, tipo);
    }

    tipo = 'M';
    for (int i = 0; i < m; i++){
        scanf("%d", &id_aux);
        grafo = adiciona_vertice(grafo, id_aux, tipo);
    }

    for(int i = 0; i < e; i++){
        scanf("%d %d %f", &id1, &id2, &peso);
        grafo = adiciona_aresta(grafo, id1, id2, peso);
    }

    imprime_grafo(grafo);
    libera_grafo(grafo);
}