#include "dijkstra.h"
#include "item.h"

Item make_item(int id, double value) {
    Item t;
    id(t) = id;
    value(t) = value;
    return t;
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