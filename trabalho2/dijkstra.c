#include "dijkstra.h"
#include "item.h"

Item make_item(int id, double value) {
    Item t;
    id(t) = id;
    value(t) = value;
    return t;
}

void rtt(Grafo *g,  FILE *s){
    double rtt_aux = 0.0;
    for(int i = 0; i < get_server_tam(g); i++){
        for(int j = 0; j < get_client_tam(g); j++){

            double rtt_real = 0.0;
            rtt_real += dijkstra(g, get_server(g, i), get_client(g,j));
            rtt_real += dijkstra(g, get_client(g,j), get_server(g, i));
            for(int k = 0; k < get_monitor_tam(g); k++){
                double rtt_aprox = 0.0;

                rtt_aprox += dijkstra(g, get_server(g, i), get_monitor(g, k));
                rtt_aprox += dijkstra(g, get_monitor(g, k), get_server(g, i));

                rtt_aprox += dijkstra(g, get_client(g,j), get_monitor(g, k));
                rtt_aprox += dijkstra(g, get_monitor(g, k), get_client(g,j));

                if(rtt_aux == 0){
                    rtt_aux = rtt_aprox/rtt_real;
                }
                else {
                    if(rtt_aux > rtt_aprox/rtt_real){
                        rtt_aux = rtt_aprox/rtt_real;
                    }
                }
            }
            fprintf(s,"%d %d %lf\n", get_server(g, i),  get_client(g,j), rtt_aux);
            rtt_aux = 0;
        }
    }
    return;
}

double dijkstra_l(Grafo *grafo, int origem, int destino){
    clock_t dji_s = clock();
    int tam_grafo = get_vertex(grafo);

    int * visitados = (int*)calloc(tam_grafo, sizeof(int));
    PQ * nao_visitados = PQ_init(tam_grafo);
    double *custos = (double*)calloc(tam_grafo, sizeof(double));
    int *antecessores = (int*)calloc(tam_grafo, sizeof(int));

    PQ_insert(nao_visitados, make_item(origem, 0));

    for(int i = 0; i < tam_grafo; i++){
        custos[i] = __DBL_MAX__;
    }

    custos[origem] = 0;

    while(!PQ_empty(nao_visitados)){
        Item item = PQ_delmin(nao_visitados);
        int id = id(item);
        visitados[id] = 1;
        
        int qtd_vizinhos = retorna_tamanho_vetor_vizinhos(grafo, id);
        Aresta ** vizinhos = retorna_vetor_vizinhos(grafo, id);

        for(int i = 0; i < qtd_vizinhos; i++){
            int id_vizinho = retorna_id_aresta(vizinhos[i]);
            double peso = retorna_peso_aresta(vizinhos[i]);

            if(visitados[id_vizinho] == 0){

                if(custos[id_vizinho] > custos[id] + peso){
                    custos[id_vizinho] = custos[id] + peso;
                    PQ_insert(nao_visitados, make_item(id_vizinho, custos[id_vizinho]));
                    antecessores[id_vizinho] = id;
                }

            }
        }
    }

    double result = custos[destino];

    free(visitados);
    free(custos);
    free(antecessores);
    PQ_finish(nao_visitados);

    clock_t dji_e = clock();
    double time_taken = ((double)(dji_e-dji_s))/CLOCKS_PER_SEC; // in seconds 
    printf("DJIKSTRA: %f\n", time_taken);
    return result;
}

double dijkstra(Grafo *grafo, int origem, int destino) {
    int tam_grafo = get_vertex(grafo);

    int *visitados = (int *)calloc(tam_grafo, sizeof(int));
    double *custos = (double *)calloc(tam_grafo, sizeof(double));
    int *antecessores = (int *)calloc(tam_grafo, sizeof(int));
    PQ *nao_visitados = PQ_init(tam_grafo);

    for (int i = 0; i < tam_grafo; i++) {
        custos[i] = __DBL_MAX__;
        antecessores[i] = -1;
    }
    
    custos[origem] = 0;
    PQ_insert(nao_visitados, make_item(origem, 0));

    while (!PQ_empty(nao_visitados)) {
        Item item = PQ_delmin(nao_visitados);
        int id = id(item);

        if (id == destino) 
            break; 
        
        if (visitados[id]) 
            continue;

        visitados[id] = 1;

        

        int qtd_vizinhos = retorna_tamanho_vetor_vizinhos(grafo, id);
        Aresta **vizinhos = retorna_vetor_vizinhos(grafo, id);

        for (int i = 0; i < qtd_vizinhos; i++) {
            int id_vizinho = retorna_id_aresta(vizinhos[i]);
            double peso = retorna_peso_aresta(vizinhos[i]);

            if (!visitados[id_vizinho]) {
                double novo_custo = custos[id] + peso;
                if (novo_custo < custos[id_vizinho]) {
                    custos[id_vizinho] = novo_custo;
                    antecessores[id_vizinho] = id;
                    PQ_insert(nao_visitados, make_item(id_vizinho, novo_custo));
                }
            }
        }
    }

    double result = custos[destino];

    free(visitados);
    free(custos);
    free(antecessores);
    PQ_finish(nao_visitados);
    
    return result;
}