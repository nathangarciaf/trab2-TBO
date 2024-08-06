#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT 100

struct aresta {
    int id;
    float peso;
};

struct aresta_list {
    Aresta **arestas_vizinhas;
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
    }

    grafo->a = a_list;

    grafo->tam_v = v;
    
    /*grafo->a = (ArestaList*)calloc(v, sizeof(ArestaList));
    for(int i = 0; i < v; i++){
        grafo->a[i].arestas_vizinhas = (Aresta**)calloc(INIT, sizeof(Aresta*));
        grafo->a[i].alloc = INIT;
        grafo->a[i].tam = 0;
    }*/

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
        grafo->a[id_no1].arestas_vizinhas = (Aresta **)realloc(grafo->a[id_no1].arestas_vizinhas, grafo->a[id_no1].alloc * sizeof(Aresta*));
        
    }

    Aresta *a = (Aresta*)calloc(1, sizeof(Aresta));
    a->id = id_no2;
    a->peso = peso;

    grafo->a[id_no1].arestas_vizinhas[grafo->a[id_no1].tam] = a;

    grafo->a[id_no1].tam++;

    return grafo;
} 

void libera_grafo(Grafo *grafo){
    for(int i = 0; i < grafo->tam_v; i++){
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

    printf("Servidores:\n");
    for(int i = 0; i < grafo->tam_s; i++){
        printf("%d\n", grafo->servidores[i]);
    }

    printf("Clientes:\n");
    for(int i = 0; i < grafo->tam_c; i++){
        printf("%d\n", grafo->clientes[i]);
    }

    printf("Monitores:\n");
    for(int i = 0; i < grafo->tam_m; i++){
        printf("%d\n", grafo->monitores[i]);
    }

    printf("Arestas\n");
    for(int i = 0; i < grafo->tam_v; i++){
        for(int j = 0; j < grafo->a[i].tam; i++){
            printf("%d, %d : %f\n", i, grafo->a[i].arestas_vizinhas[j]->id, grafo->a[i].arestas_vizinhas[j]->peso);
        }
    }
}