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
    //imprime_grafo(grafo);
    
    fuck(grafo);
    float v = dijkstra_l(grafo, 0, 4);
    printf("%f\n", v);
    libera_grafo(grafo);
    return 0;
    
}