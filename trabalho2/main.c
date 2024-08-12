#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"
#include "dijkstra.h"
#include "PQ.h"
#include "item.h"

#include <string.h>
#include <time.h> 


int main(int argc, char *argv[]){
    FILE *file = fopen(argv[1], "r");

    if(argc < 3){
        printf("DIRETÓRIO INSUFICIENTE!\n");
        fclose(file);
        return 0;
    }

    if(!file){
        printf("ARQUIVO DE ENTRADA INEXISTENTE!\n");
        return 0;
    }

    Grafo *grafo = read_graph(file);

    fclose(file);
    //imprime_grafo(grafo);
     
    FILE *saida = fopen(argv[2],"w");
    if(!saida){
        printf("ARQUIVO DE SAIDA NÃO CONSEGUIU SER CRIADO!\n");
        return 0;
    }

    clock_t rtt_start = clock();
    rtt_l(grafo, saida);
    clock_t rtt_end = clock();

    double time_taken = ((double)(rtt_end-rtt_start))/CLOCKS_PER_SEC; // in seconds 
    printf("RTT: %f\n\n", time_taken);

    fclose(saida);
    libera_grafo(grafo);
    return 0;
    
}