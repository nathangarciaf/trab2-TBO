#include "dijkstra.h"
#include "item.h"

Item make_item(int id, double value) {
    Item t;
    id(t) = id;
    value(t) = value;
    return t;
}

void fuck(Grafo *g){
    double rtt_aux = 0.0;

    for(int i = 0; i < get_server_tam(g); i++){
        for(int j = 0; j < get_client_tam(g); j++){

            double rtt_real = 0.0;
            rtt_real += dijkstra_l(g, get_server(g, i), get_client(g,j));
            rtt_real += dijkstra_l(g, get_client(g,j), get_server(g, i));

            for(int k = 0; k < get_monitor_tam(g); k++){

                double rtt_aprox = 0.0;

                rtt_aprox += dijkstra_l(g, get_server(g, i), get_monitor(g, k));
                rtt_aprox += dijkstra_l(g, get_monitor(g, k), get_server(g, i));

                rtt_aprox += dijkstra_l(g, get_client(g,j), get_monitor(g, k));
                rtt_aprox += dijkstra_l(g, get_monitor(g, k), get_client(g,j));

                if(rtt_aux == 0){
                    rtt_aux = rtt_aprox/rtt_real;
                }
                else {
                    if(rtt_aux > rtt_aprox/rtt_real){
                        rtt_aux = rtt_aprox/rtt_real;
                    }
                }
            }
            printf("S:%d , C: %d, RELAÇÃO: %lf\n\n", get_server(g, i),  get_client(g,j), rtt_aux);
            rtt_aux = 0;
        }
    }
    return;
}

double dijkstra_l(Grafo *grafo, int origem, int destino){
    int tam_grafo = get_vertex(grafo);

    int * visitados = (int*)calloc(tam_grafo, sizeof(int));
    PQ * nao_visitados = PQ_init(tam_grafo);
    double * custos = (double*)calloc(tam_grafo, sizeof(double));
    int * antecessores = (int*)calloc(tam_grafo, sizeof(int));

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

    return result;
}

/*
float dijkstra(Grafo *g, int origem, int dest){
    int vertices = get_vertex(g);
    printf("VERTICES: %d\n", vertices);
    int *visitados = (int*)calloc(vertices,sizeof(int));
    float *distancias = (float*)calloc(vertices, sizeof(float));
    int *pred = (int*)calloc(vertices, sizeof(int));

    for(int i = 0; i < vertices; i++){
        visitados[i] = 0;
        pred[i] = origem;
        distancias[i] = __FLT_MAX__;
    }

    for(int i = 0; i < vertices; i++){
        printf("%.2f\n",distancias[i]);
    }

    free(visitados);
    free(distancias);
    free(pred);

    return 1.0;
}*/