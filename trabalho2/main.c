#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"
#include "dijkstra.h"
#include "PQ.h"
#include "item.h"

int main(int argc, char *argv[]){
    int vertices, arestas, servidores, clientes, monitores;

    FILE *file = fopen(argv[1], "r");
    if(!file){
        printf("ARQUIVO DE ENTRADA INEXISTENTE!\n");
        return 0;
    }

    fscanf(file,"%d %d", &vertices, &arestas);
    fscanf(file, "%d %d %d", &servidores, &clientes, &monitores);

    Grafo *grafo = read_graph(file, vertices,servidores,clientes, monitores, arestas);


    imprime_grafo(grafo);
    libera_grafo(grafo);
}