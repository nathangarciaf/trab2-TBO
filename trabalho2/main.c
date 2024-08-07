#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"
#include "dijkstra.h"
#include "PQ.h"
#include "item.h"

int main(int argc, char *argv[]){
    FILE *file = fopen(argv[1], "r");
    if(!file){
        printf("ARQUIVO DE ENTRADA INEXISTENTE!\n");
        return 0;
    }

    Grafo *grafo = read_graph(file);

    fclose(file);
    imprime_grafo(grafo);
    libera_grafo(grafo);
}