//Lucas Ferreira e Sabrina Nawcki - Main
#include <stdio.h>
#include <stdlib.h>
#include "BellmanFord.h"
#include "Kruskal.h"
#include "LerArquivo.h"

int main(int argc, char *argv[]) {	
	Ler("grafo.csv", BELLMANFORD);
	return 0;
}
