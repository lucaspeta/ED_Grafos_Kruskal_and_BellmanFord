//Lucas Ferreira e Sabrina Nawcki - Leitor de arquivo texto/csv
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define KRUSKAL 	0
#define BELLMANFORD 1

#define STR_MAX 100

void Ler(char* filePath, int grafoTipo){
	// Quantidade de linhas no arquivo
	int linhasQtd = LinhasQtdArq(filePath);
	
	// Vetor de strings para as linhas separadas
	char Linhas[linhasQtd][STR_MAX];
	
	// Separa as linhas no vetor
	CsvSeparaLinhas(filePath, Linhas, linhasQtd);
	
	// Realiza a separacao dos elementos e cria/insere no Grafo
	LinhasParaGrafo(Linhas, linhasQtd, grafoTipo);
}

// Retorna a quantidade de linhas no arquivo csv
int LinhasQtdArq(char* filePath){
	int linhas  = 0;
	
	FILE * file = fopen(filePath,"r");

	if(file == NULL){ //Se nao encontrar o arquivo
		printf("Arquivo nao encontrado.\n");
		exit(EXIT_FAILURE);
	}
	else{
		while(!feof(file)){ //enquanto nao terminar o arquivo
			char c = fgetc(file);

			if(c == EOF){
				if(ferror(file)){
				  perror("Nao foi possivel ler o arquivo");
				  fclose(file);
				}

				continue;
			}
			if(c == '\n'){
				++linhas;
			}
		}
	}
	
	fclose(file);

	return linhas;
}

// Separa as linhas do arquivo csv em um array de strings
// Parametros 
//[filePath]  -> caminho do arquivo 
//[Linhas]    -> Vetor de strings para aramazenar cada linha inteira
//[QtdLinhas] -> Quantidade de linhas no arquivo
void CsvSeparaLinhas(char* filePath, char Linhas[][STR_MAX], int LinhasQtd){
	// Lê o arquivo
	FILE * file = fopen(filePath,"r");
	
	if(file == NULL){ //Se nao encontrar o arquivo
		printf("Arquivo nao encontrado.\n");
		exit(EXIT_FAILURE);
	}
	else{
		int i = 0, j = 0;

		// Enquanto nao terminar o arquivo
		while(!feof(file)){ 
			// pega o char
			char c = fgetc(file);

			// Verifica se não é o final do arquivo
			if(c == EOF){
				if(ferror(file)){
				  perror("Nao foi possivel ler o arquivo");
				  fclose(file);
				}

				continue;
			}
			
			// Verifica se não é um '\n', se for vai para a próxima linha
			if(c == '\n'){
				// Insere o caractere nulo para finalizar a string
				Linhas[i][j] = '\0';
				i++;				
				j = 0;
			}
			else{
				// Insere o char
				Linhas[i][j] = c;				
				j++;
			}
			
			// Insere o caractere nulo na ultima linha, pois não um '\n' na ultima linha
			Linhas[i][j+1] = '\0';
		}

		fclose(file);
	}
}

//Pega o array de strings e transforma em um Grafo
//Parametros
//[Linhas] 		-> Vetor contendo cada linha do arquivo
//[LinhasQtd]   -> Quantidade de linhas no arquivo
void LinhasParaGrafo(char Linhas[][STR_MAX], int LinhasQtd, int grafoTipo){
	int i, j, elementos, n_elementos;
	
	// Verifica se cada linha tem o mesmo numero de elemento
	for(i = 0; i < LinhasQtd; ++i){
		elementos = 0;
		for(j = 0; j < strlen(Linhas[i]); ++j){	
			// É utilizado o ponto e virgula pra saber quantos elementos contem na linha		
			if(Linhas[i][j] == ';'){ 
				elementos++;
			}
		}
		
		if(i == 0){
			n_elementos = elementos;
		} else{
			if(elementos != n_elementos){
				printf("%d, %d\n", elementos, n_elementos);				
				printf("Erro ao ler arquivo, o numero de elementos de ser o mesmo em todas as linhas.\n");
    			exit(EXIT_FAILURE);
			}
		}		
	}
	
	n_elementos++; // Como não tem ponto e virgula no ultimo elemento
	
	char *elementos_array[n_elementos*LinhasQtd]; //array de string com todos os elementos
	int elementos_int[n_elementos*LinhasQtd]; //array para guardar todos os elementos em int
	
	// Pega a linha do arquivo e faz um explode separando os elementos pelo delimitador ';'
	for(i = 0, j = 0; i < LinhasQtd; i++){
		char *tok = strtok(Linhas[i], ";");		
		
		while (tok != NULL) {
		    elementos_array[j] = tok;
		    tok = strtok(NULL, ";");
		    j++;
		}
	}
	
	// Valida o array passando por cada elemento e verificando se não caracteres invalidos
	for(i = 0; i < n_elementos * LinhasQtd; ++i){		
		for(j = 0; j < strlen(elementos_array[i]); j++){					
			if((int) elementos_array[i][j] < 48 || (int) elementos_array[i][j] > 57){ // se for diferente de numero
				if(elementos_array[i][j] != '.' && elementos_array[i][j] != '-'){ //se for diferente de ponto -> spota o erro
					printf("Erro ao ler arquivo, contem elemento(s) invalidos no arquivo.\n");
    				exit(EXIT_FAILURE);
				}
			}
		}				
	}
	int elementos_sem_peso[200];
	j = 0;
	// Passa para int os elementos estejam validos e insere no array
	for(i = 0; i < n_elementos * LinhasQtd; ++i){
		elementos_int[i] = atoi(elementos_array[i]);
	}

	for(i = 0; i < n_elementos * LinhasQtd; ++i){
		if(i % 3 == 0) {
			++i;
		}
		elementos_sem_peso[i] = elementos_array[i];
	}
	int valor = 0;
	bool comeca0 = false;

	for(i=0; i < n_elementos * LinhasQtd; i++){
		if (elementos_sem_peso[i] == 0) comeca0 = true;
		if(valor < elementos_sem_peso[i]){
			valor = elementos_sem_peso[i];
		}
	}
	if (comeca0 == true) valor++;

	int vertice = valor;
	int aresta = LinhasQtd;

	if(grafoTipo == KRUSKAL){
		struct arestaK* arvore[MAX];	
		struct arestaK* tmp1;
		int z = 0;
		
		//Manda para o Grafo
		for(j = 0; j < n_elementos * LinhasQtd; j += 3){	
			tmp1 = insere_aresta_peso(elementos_int[j], elementos_int[j+1], elementos_int[j+2]); vertices = vertice; //Kruskal
			arvore[z] = tmp1;
			z++;
		}
		
		cria_arvore(arvore);
		imprime(arvore);
	}
	else if(grafoTipo == BELLMANFORD){
		struct grafo* grafo = criaGrafo(vertice, aresta); //isso aqui deveria estar no Ler();
 
 		for(j = 0, i = 0; j < n_elementos * LinhasQtd; j += 3, i++){
			//tendo o grafo feito, se faz os apontamentos, dentro do ler da seguinte forma:
			grafo->aresta[i].origem   = elementos_int[j];
			grafo->aresta[i].destino  = elementos_int[j+1] ;
			grafo->aresta[i].peso  	  = elementos_int[j+2];		
		}		
 
    	BellmanFord(grafo, 0); // 0 eh a raiz, o ponto de partida*/
	}	
}
