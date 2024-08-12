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
     

    PQ *results = PQ_init(get_server_tam(grafo)*get_client_tam(grafo));
    rtt(grafo, results);
    libera_grafo(grafo);

    FILE *saida = fopen(argv[2],"w");
    if(!saida){
        printf("ARQUIVO DE SAIDA NÃO CONSEGUIU SER CRIADO!\n");
        return 0;
    }

    print_rtt(results, saida);
    fclose(saida);

    PQ_finish(results);

    return 0;
    
}