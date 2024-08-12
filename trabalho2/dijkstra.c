#include "dijkstra.h"
#include "item.h"

Item make_item(int id, double value) {
    Item t;
    id(t) = id;
    id2(t) = 0;
    value(t) = value;
    return t;
}

Item make_edge(int id, int id2, double value) {
    Item t;
    id(t) = id;
    id2(t) = id2;
    value(t) = value;
    return t;
}

void rtt(Grafo *g, PQ *pq){
    double rtt_aux = 0.0;

    for(int i = 0; i < get_server_tam(g); i++){
        dijkstra(g,get_server(g, i));
    }

    for(int i = 0; i < get_client_tam(g); i++){
        dijkstra(g,get_client(g, i));
    }

    for(int i = 0; i < get_monitor_tam(g); i++){
        dijkstra(g,get_monitor(g,i));
    }

    for(int i = 0; i < get_server_tam(g); i++){
        int server = get_server(g, i);

        for(int j = 0; j < get_client_tam(g); j++){

            double rtt_real = 0.0;
            int client = get_client(g, j);
            rtt_real += get_cost(g,server,client);
            double volta_rtt = get_cost(g,client,server);
            //printf("IDA: %lf // VOLTA: %lf\n", rtt_real,volta_rtt);
            rtt_real += volta_rtt;
            //printf("RTT REAL: %lf\n", rtt_real);

            for(int k = 0; k < get_monitor_tam(g); k++){
                
                int monitor = get_monitor(g, k);
                double rtt_aprox = 0.0;

                rtt_aprox += get_cost(g,server,monitor);
                rtt_aprox += get_cost(g,monitor,server);

                rtt_aprox += get_cost(g,monitor,client);
                rtt_aprox += get_cost(g,client, monitor);

                if(rtt_aux == 0){
                    rtt_aux = rtt_aprox/rtt_real;
                }
                else {
                    if(rtt_aux > rtt_aprox/rtt_real){
                        rtt_aux = rtt_aprox/rtt_real;
                    }
                }

            }

            Item item = make_edge(get_server(g, i), get_client(g,j), rtt_aux);
            PQ_insert(pq,item);

            rtt_aux = 0;
        }
    }
    return;
}

void dijkstra(Grafo *grafo, int origem){
    int tam_grafo = get_vertex(grafo);

    int *visitados = (int *)calloc(tam_grafo, sizeof(int));
    double *custos = get_cost_array(grafo, origem);
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

    free(visitados);
    free(antecessores);
    PQ_finish(nao_visitados);    
}

void print_rtt(PQ *pq, FILE *s){
    while(!PQ_empty(pq)){
        Item t = PQ_delmin(pq);
        fprintf(s, "%d %d %lf\n", id(t), id2(t), value(t));
    }
}