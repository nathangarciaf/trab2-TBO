#include "dijkstra.h"
#include "item.h"

Item make_item(int id, double value) {
    Item t;
    id(t) = id;
    value(t) = value;
    return t;
}

double dijkstra_l(Grafo * grafo, int origem, int destino){
    int tam_grafo = retorna_tamanho_grafo(grafo);

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
}

/*
float dijkstra(Grafo * grafo, int origem, int destino){
    // vetores auxiliares
    float *distancias = (float*)calloc(grafo->qtd_vertices, sizeof(float));
    int *anterior = (int*)calloc(grafo->qtd_vertices, sizeof(int));
    PQ * pq = PQ_init(grafo->qtd_vertices);

    int atual = origem;

    for (int i = 0; i < grafo->qtd_vertices; i++){
        distancias[i] = __FLT_MAX__; //define como infinito
        anterior[i] = -1;
        PQ_insert(pq, make_item(i, distancias[i]));
    }

    distancias[origem] = 0;
    PQ_decrease_key(pq, origem, distancias[origem]);

    while (PQ_size(pq) > 0){
        Item item = PQ_delmin(pq);
        atual = id(item);

        if (atual == destino) {
            break;
        }

        for (int i = 0; i < grafo->qtd_vertices; i++){
            if (grafo->arestas[atual][i] != 0){
                if (distancias[i] > distancias[atual] + grafo->arestas[atual][i]){
                    distancias[i] = distancias[atual] + grafo->arestas[atual][i];
                    anterior[i] = atual;
                    PQ_decrease_key(pq, i, distancias[i]);
                }
            }
        }
    }

    float custo = distancias[destino];

    free(distancias);
    free(anterior);
    PQ_finish(pq);

    return custo;
}
*/