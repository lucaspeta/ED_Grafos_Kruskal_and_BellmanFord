//Lucas Ferreira e Sabrina Nawcki - Kruskal

#include<stdlib.h>
#include<stdio.h>
 
#define NIL -1
#define MAX 100

struct arestaK {
	int vertice_A, vertice_B, peso;
	struct arestaK *link;
}*frente = NULL;
 
void cria_arvore(struct arestaK arvore[]);
struct arestaK *insere_aresta_peso(int vertice_A, int vertice_B, int peso);
struct arestaK *deleta_aresta_peso() ;
int ehVazio();
void criaGrafoKruskal(); 
void criaGrafoEx();
int vertices;

void criaGrafoKruskal()
{
	struct arestaK arvore[MAX];
	//no ler a funcao o cria grafo seria = insere_aresta_peso(elementos_int[j++], elementos_int[j++], elementos_int[j]);
	//a variavel global dessa funcao chamada vertices precisa receber um valor
	//vertices = ?;
	cria_arvore(arvore);
	imprime(arvore);
}

void imprime(struct arestaK arvore[]){
	int peso_da_arvore = 0, count;

	printf("Arestas no MST:\n");
	for(count = 1; count <= vertices - 1; count++)
	{
	printf("%d -> %d = peso %d\n", arvore[count].vertice_A, arvore[count].vertice_B, arvore[count].peso);
	peso_da_arvore = peso_da_arvore + arvore[count].peso;
	}
	printf("Peso total da arvore minima: %d\n", peso_da_arvore);
}
 
void cria_arvore(struct arestaK arvore[]) {
	struct arestaK *tmp;
  
	int y1, y2, raiz_y1, raiz_y2;
	int pai[MAX];
	int i, count = 0;

	for(i = 0; i < vertices; i++) {
		pai[i] = NIL;
	}
  
	while(!ehVazio() && count < vertices - 1) {
		tmp = deleta_aresta_peso();
		y1  = tmp->vertice_A;
		y2  = tmp->vertice_B; 
		while(y1 != NIL) {
			raiz_y1 = y1;
			y1 	  = pai[y1];
		}
		while(y2 != NIL) {
			raiz_y2 = y2;
			y2 	  = pai[y2];
		}
		if(raiz_y1 != raiz_y2) {
			count++;
			arvore[count].vertice_A = tmp->vertice_A;
			arvore[count].vertice_B = tmp->vertice_B;
			arvore[count].peso		= tmp->peso;
			pai[raiz_y2] 			= raiz_y1;
		}
		if(count < vertices - 1)
		{
			printf("O grafo esta desconectado. Por isso, criar a arvore foi impossivel\n");
			exit(1);
		}
	}
 }

struct arestaK* insere_aresta_peso(int vertice_A, int vertice_B, int peso) {
	struct arestaK *tmp, *q;
  
	tmp 				= (struct arestaK *)malloc(sizeof(struct arestaK));
	tmp->vertice_A 	= vertice_A;
	tmp->vertice_B 	= vertice_B;
	tmp->peso			= peso;
  
	if(frente == NULL || tmp->peso < frente->peso) {
		tmp->link = frente;
		frente 	  = tmp;
	}
	else{
	    q = frente;
	    
	    while(q->link != NULL && q->link->peso <= tmp->peso) {
	    	q = q->link;
	    }
	    
	    tmp->link = q->link;
	    q->link   = tmp;
	    
	    if(q->link == NULL) 
	    {
	        tmp->link = NULL;
	    }
  	}
}
 
struct arestaK *deleta_aresta_peso() {
	struct aresta *tmp;
  
	tmp 	 = frente;
	frente = frente->link;
  
	return tmp;
}
 
int ehVazio() {
	if(frente == NULL) {
		return 1;
	} else {
		return 0;
	}
}
 
//void criaGrafoEx() {
	/*
	    1-----p8----2---p7---3
	p4/ |         /p2\p4     | \p9
	 /  |       /     \      |  \
	0   p11   8		   \    p14  4
	 \  |  /p7 \p6      \    | /
	p8\ |/      \        \   |/p10
	   7----p1---6--p2-----5
	
	*/
	/*vertices = 9;

	insere_aresta_peso(0, 1, 4); 	//G(0,1) d(G) = 4	
	insere_aresta_peso(0, 7, 8);	//G(0,7) d(G) = 8
	
	insere_aresta_peso(1, 2, 8);	
	insere_aresta_peso(1, 7, 11);
		
	insere_aresta_peso(2, 3, 7);	
	insere_aresta_peso(2, 5, 4);	
	insere_aresta_peso(2, 8, 2);
	
	insere_aresta_peso(3, 4, 9);	
	insere_aresta_peso(3, 5, 14);
	
	insere_aresta_peso(4, 5, 10);
		
	insere_aresta_peso(5, 6, 2);
		
	insere_aresta_peso(6, 7, 1);	
	insere_aresta_peso(6, 8, 6);
		
	insere_aresta_peso(7, 8, 7);
}*/
