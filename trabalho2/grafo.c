#include "grafo.h"

#define INIT 100

struct aresta {
    int id;
    double peso;
};

struct aresta_list {
    Aresta **arestas_vizinhas;
    double *custos;
    int tam, alloc;
};

struct Grafo {
    ArestaList *a;
    int tam_v;

    int *servidores;
    int tam_s, alloc_s;

    int *monitores;
    int tam_m, alloc_m;

    int *clientes;
    int tam_c, alloc_c;
};

Grafo *read_graph(FILE *f){
    int vertices, arestas, servidores, clientes, monitores;

    fscanf(f,"%d %d", &vertices, &arestas);
    fscanf(f, "%d %d %d", &servidores, &clientes, &monitores);

    Grafo  *g = inicializa_grafo(vertices,servidores,clientes,monitores);
    int id_aux, id1, id2;
    float peso;
    char tipo;

    tipo = 'S';
    for (int i = 0; i < servidores; i++){
        fscanf(f,"%d", &id_aux);
        g = adiciona_vertice(g, id_aux, tipo);
    }

    tipo = 'C';
    for (int i = 0; i < clientes; i++){
        fscanf(f,"%d", &id_aux);
        g = adiciona_vertice(g, id_aux, tipo);
    }

    tipo = 'M';
    for (int i = 0; i < monitores; i++){
        fscanf(f,"%d", &id_aux);
        g = adiciona_vertice(g, id_aux, tipo);
    }

    for(int i = 0; i < arestas; i++){
        fscanf(f, "%d %d %f", &id1, &id2, &peso);
        g = adiciona_aresta(g, id1, id2, peso);
    }
    return g;
}


Grafo * inicializa_grafo(int v, int s, int c, int m){
    Grafo *grafo = (Grafo*)calloc(1, sizeof(Grafo));

    grafo->servidores = (int*)calloc(s, sizeof(int));
    grafo->tam_s = 0;
    grafo->alloc_s = s;

    grafo->clientes = (int*)calloc(c, sizeof(int));
    grafo->tam_c = 0;
    grafo->alloc_c = c;

    grafo->monitores = (int*)calloc(m, sizeof(int));
    grafo->tam_m = 0;
    grafo->alloc_m = m;

    ArestaList *a_list = (ArestaList*)calloc(v, sizeof(ArestaList));
    for(int i = 0; i < v; i++){
        a_list[i].arestas_vizinhas = (Aresta**)calloc(INIT, sizeof(Aresta*));
        a_list[i].alloc = INIT;
        a_list[i].tam = 0;
        a_list[i].custos = (double*)calloc(v, sizeof(double));
    }

    grafo->a = a_list;
    grafo->tam_v = v;

    return grafo;
}

Grafo * adiciona_vertice(Grafo *grafo, int id, char tipo){
    if(tipo == 'S'){
        grafo->servidores[grafo->tam_s] = id;
        grafo->tam_s++;
    }
    else if(tipo == 'C'){
        grafo->clientes[grafo->tam_c] = id;
        grafo->tam_c++;
    }
    else {
        grafo->monitores[grafo->tam_m] = id;
        grafo->tam_m++;
    }

    return grafo;
}

Grafo * adiciona_aresta(Grafo *grafo, int id_no1, int id_no2, float peso){
    if(grafo->a[id_no1].alloc == grafo->a[id_no1].tam){
        grafo->a[id_no1].alloc *= 2;
        grafo->a[id_no1].arestas_vizinhas = (Aresta **)realloc(grafo->a[id_no1].arestas_vizinhas, grafo->a[id_no1].alloc *sizeof(Aresta*));
    }

    Aresta *a = (Aresta*)calloc(1, sizeof(Aresta));
    a->id = id_no2;
    a->peso = peso;

    grafo->a[id_no1].arestas_vizinhas[grafo->a[id_no1].tam] = a;

    grafo->a[id_no1].tam++;

    return grafo;
}

int get_vertex(Grafo *g){
    return g->tam_v;
}

int get_server_tam(Grafo *g){
    return g->tam_s;
}

int get_monitor_tam(Grafo *g){
    return g->tam_m;
}

int get_client_tam(Grafo *g){
    return g->tam_c;
}

int get_server(Grafo *g, int id){
    return g->servidores[id];
}

int get_monitor(Grafo *g, int id){
    return g->monitores[id];
}

int get_client(Grafo *g, int id){
    return g->clientes[id];
}

double *get_cost_array(Grafo *g, int id){
    ArestaList *a = g->a;
    return a[id].custos;
}

Aresta **retorna_vetor_vizinhos(Grafo *g, int id){
    ArestaList *a = g->a;
    return a[id].arestas_vizinhas;
}

int retorna_tamanho_vetor_vizinhos(Grafo *g, int id){
    ArestaList *a = g->a;
    return a[id].tam;
}

double retorna_peso_aresta(Aresta *a){
    return a->peso;
}

int retorna_id_aresta(Aresta *a) {
    return a->id;
}

double get_cost(Grafo *g, int id1, int id2){
    ArestaList *a = g->a;
    return a[id1].custos[id2];
}

void print_costs(double *custos, int tam_grafo, int origem){
    printf("\n  COSTS:  \n");
    for(int i = 0; i < tam_grafo; i++){
        if(i != origem)
            printf("DIST %d to %d: %lf\n", origem, i, custos[i]);
    }
    printf("\n");
}


void libera_grafo(Grafo *grafo){
    for(int i = 0; i < grafo->tam_v; i++){
        free(grafo->a[i].custos);
        for(int j = 0; j < grafo->a[i].tam; j++){
            free(grafo->a[i].arestas_vizinhas[j]);
        }
        free(grafo->a[i].arestas_vizinhas);
    }
    free(grafo->a);
    free(grafo->servidores);
    free(grafo->clientes);
    free(grafo->monitores);
    free(grafo);
}

void imprime_grafo(Grafo *grafo){

    printf("Servidores (%d):\n", grafo->tam_s);
    for(int i = 0; i < grafo->tam_s; i++){
        printf("%d\n", grafo->servidores[i]);
    }

    printf("Clientes (%d):\n", grafo->tam_c);
    for(int i = 0; i < grafo->tam_c; i++){
        printf("%d\n", grafo->clientes[i]);
    }

    printf("Monitores (%d):\n", grafo->tam_m);
    for(int i = 0; i < grafo->tam_m; i++){
        printf("%d\n", grafo->monitores[i]);
    }

    printf("Arestas:\n");
    for(int i = 0; i < grafo->tam_v; i++){
        for(int j = 0; j < grafo->a[i].tam; j++){
            Aresta *a = grafo->a[i].arestas_vizinhas[j];
            printf("%d, %d : %f\n", i, a->id, a->peso);
        }
    }
}