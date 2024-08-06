#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"
#include "dijkstra.h"
#include "PQ.h"
#include "item.h"

int main(int argc, char *argv[]){
    int vertices, arestas, servidores, clientes, monitores;
    int id_aux;
    int id1, id2;
    float peso;
    char tipo;

    FILE *file = fopen(argv[1], "r");
    if(!file){
        printf("ARQUIVO DE ENTRADA INEXISTENTE!\n");
    }

    scanf("%d %d", &vertices, &arestas);
    scanf("%d %d %d", &servidores, &clientes, &monitores);

    Grafo *grafo = inicializa_grafo(vertices, servidores, clientes, monitores);

    //inicializacao do grafo
    tipo = 'S';
    for (int i = 0; i < servidores; i++){
        scanf("%d", &id_aux);
        grafo = adiciona_vertice(grafo, id_aux, tipo);
    }

    tipo = 'C';
    for (int i = 0; i < clientes; i++){
        scanf("%d", &id_aux);
        grafo = adiciona_vertice(grafo, id_aux, tipo);
    }

    tipo = 'M';
    for (int i = 0; i < monitores; i++){
        scanf("%d", &id_aux);
        grafo = adiciona_vertice(grafo, id_aux, tipo);
    }

    for(int i = 0; i < arestas; i++){
        scanf("%d %d %f", &id1, &id2, &peso);
        grafo = adiciona_aresta(grafo, id1, id2, peso);
    }

    imprime_grafo(grafo);
    libera_grafo(grafo);
}