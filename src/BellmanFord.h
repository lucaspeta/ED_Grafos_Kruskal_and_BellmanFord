//Lucas Ferreira e Sabrina Nawcki - BellmanFord

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
 
#define MAX 100

struct aresta {
	int origem, destino, peso;
};

struct grafo {
    int V, A;
    struct aresta* aresta;
};
 
struct grafo* criaGrafo(int V, int A) {
    struct grafo* grafo = (struct grafo*) malloc(sizeof(struct grafo));
 
    grafo->V = V; 
 
    grafo->A = A;
 
    grafo->aresta = (struct aresta*) malloc( grafo->A * sizeof( struct aresta ) );
 
    return grafo;
}
 
void imprimeGrafo(int dist[], int n) {
    printf("\nVertice   Distancia do vertice de origem\n");
    int i;
 
    for (i = 0; i < n; ++i){
        printf("%d        %d\n", i, dist[i]);
    }
}
 
void BellmanFord(struct grafo* grafo, int origem) {
    int V = grafo->V;
 
    int A = grafo->A;
 
    int distancia[V];
 
    int i,j;
 
    for (i = 0; i < V; i++)
        distancia[i] = MAX;
 
    distancia[origem] = 0;
 
	for (i = 1; i <= V-1; i++) {
        for (j = 0; j < A; j++) {
            int u = grafo->aresta[j].origem;
 
            int v = grafo->aresta[j].destino;
 
            int peso = grafo->aresta[j].peso;
 
            if (distancia[u] + peso < distancia[v])
                distancia[v] = distancia[u] + peso;
        }
    }
 
    for (i = 0; i < A; i++) {
        int u = grafo->aresta[i].origem;
 
        int v = grafo->aresta[i].destino;
 
        int peso = grafo->aresta[i].peso;
 
        if (distancia[u] + peso < distancia[v])
            printf("Esse grafo possui aresta negativa\n");
    }
 
    imprimeGrafo(distancia, V);
 
    return;
}
 
//void criaGrafoBellmanFord() {
    //struct grafo* grafo = criaGrafo(V, A); //isso aqui deveria estar no Ler();
 
	//tendo o grafo feito, se faz os apontamentos, dentro do ler da seguinte forma:
	//grafo->aresta[i].origem = elementos_int[j++];
	//grafo->aresta[i].destino = elementos_int[j++] ;
	//grafo->aresta[i++].peso = elementos_int[j];
 
    //BellmanFord(grafo, S); // S eh a raiz, o ponto de partida
//}
