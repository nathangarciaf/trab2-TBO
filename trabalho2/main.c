#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"
#include "dijkstra.h"
#include "PQ.h"
#include "item.h"

#include <time.h> 


int main(int argc, char *argv[]){
    FILE *file = fopen(argv[1], "r");

    if(argc < 3){
        printf("DIRETÓRIO INSUFICIENTE!\n");
        return 0;
    }

    if(!file){
        printf("ARQUIVO DE ENTRADA INEXISTENTE!\n");
        return 0;
    }

    clock_t start = clock();
    Grafo *grafo = read_graph(file);
    clock_t read = clock();


    double time_taken = ((double)(read-start))/CLOCKS_PER_SEC; // in seconds 
    printf("LEITURA: %f\n", time_taken);
    fclose(file);
    //imprime_grafo(grafo);
     
    FILE *saida = fopen(argv[2],"w");
    if(!saida){
        printf("ARQUIVO DE SAIDA NÃO CONSEGUIU SER CRIADO!\n");
        return 0;
    }

    clock_t rtt_start = clock();
    rtt(grafo, saida);
    clock_t rtt_end = clock();

    time_taken = ((double)(rtt_end-rtt_start))/CLOCKS_PER_SEC; // in seconds 
    printf("LEITURA: %f\n", time_taken);

    fclose(saida);
    libera_grafo(grafo);
    return 0;
    
}