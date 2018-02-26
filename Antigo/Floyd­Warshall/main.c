#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

double** criaDist(Grafo* g){
	int i, j;
	int v1, v2;
	Aresta* a;
	double** mat_dist;

	//CRIANDO A MATRIZ DE DISTANCIA
	mat_dist = malloc(sizeof(double*)*g->q_ver);
	
	for(i = 0; i < g->q_ver; i++){
		mat_dist[i] = malloc(sizeof(double)*g->q_ver);
	}

	//SETANDO OS VALORES INFINITOS = 1.000.000
	for(i = 0; i < g->q_ver; i++){
		for(j = 0; j < g->q_ver; j++){
			mat_dist[i][j] =  1000000;
		}
	}

	//Anotando os valores da matriz de distancia de acordo com a aresta
	a = g->aresta;

	while(a != NULL){
		
		//PEGANDO A LOCALIZACAO NA MATRIZ		
		v1 = a->v1->value;
		v2 = a->v2->value;

		//USANDO A LOCALIZACAO PARA SETAR A DISTANCIA
		mat_dist[v1-1][v2-1] = a->custo;
		mat_dist[v2-1][v1-1] = a->custo;

		a = a->prox;
	
	}

	return mat_dist;
}

//FUNCAO PARA CRIAR A MATRIZ DE ANTECESSORES

int** criaParent(Grafo* g, double** mat_dist){
	int i, j;
	int** mat_par;

	//CRIANDO A MATRIZ DE PARENTES
	mat_par = malloc(sizeof(double*)*g->q_ver);
	
	for(i = 0; i < g->q_ver; i++){
		mat_par[i] = malloc(sizeof(double)*g->q_ver);
	}

	//COLOCANDO OS VALORES NA MATRIZ DE PARENTES
	for(i = 0; i < g->q_ver; i++){
		for(j = 0; j < g->q_ver; j++){
			if(mat_dist[i][j] != 1000000)
				mat_par[i][j] = i;
			else
				mat_par[i][j] = -1;
		}
	}

	//RETORNAR A MATRIZ DE PARENTES PARA SER USADA PELO ALGORITMO
	return mat_par;
}

//FAZENDO O ALGORITMO FW
int** algFW(Grafo* g, double** mat_dist, int** mat_par){
	int i, j, k;

	//FAZENDO A LOGICA DO ALGORITMO
	for(k = 0; k < g->q_ver; k++){
		for(i = 0; i < g->q_ver; i++){
			for(j = 0; j < g->q_ver; j++){
				//FAZENDO NEGAR
				if(mat_dist[i][k] != 1000000 || mat_dist[k][j] != 1000000){
					if(mat_dist[i][j] > mat_dist[i][k] + mat_dist[k][j]){
						mat_dist[i][j] = mat_dist[i][k] + mat_dist[k][j];
						mat_par[i][j] = mat_par[k][j];
					}
				}

			}
		}
	}

	return mat_par;
}

//FUNCAO PARA IMPRIMIR O CAMINHO MINIMO
void i_min(int** mat_par, int i, int j){
	
	if(i == j){
		printf("%d ", i+1);
	}else if(mat_par[i][j] == -1){
		printf("0 ");
	}else{
		i_min(mat_par, i, mat_par[i][j]);
		printf("%d ", j+1);
	}
}

                                                              
int main(void){

	Grafo* g = malloc(sizeof(Grafo));
	
	char op[3];

	int o;

	//VARIAVEL MATRIZES
	double**mat_dist;
	int**mat_par;

	//VARIAVEIS PARA AUXILIAR NAS OP
	int par, par2;
	double par3;

	//VARIAVIES TESTE
	Vertice* p;
	int i;


	g = criarGrafo();

	while(o != 11){

		scanf("%s", op);

		//PEGANDO AS OPCOES DIGITADAS PELO USUARIO
		if (strcmp (op, "CV") == 0){
			o = 1;
		}else if(strcmp (op, "DV") == 0){
			o = 2;
		}else if(strcmp (op, "CA") == 0){
			o = 3;
		}else if(strcmp (op, "DA") == 0){
			o = 4;
		}else if(strcmp (op, "TV") == 0){
			o = 5;
		}else if(strcmp (op, "TA") == 0){
			o = 6;
		}else if(strcmp (op, "FW") == 0){
			o = 7;
		}else if(strcmp (op, "IG") == 0){
			o = 8;
		}else if(strcmp (op, "ID") == 0){
			o = 9;
		}else if(strcmp (op, "IC") == 0){
			o = 10;
		}else if(strcmp (op, "FM") == 0){
			o = 11;
		}


		//TRANSFORMANDO OPCOES PARA 
		switch(o){
			//CRIA VERTICE
			case 1:
				scanf("%d", &par);

				insertVertex(g, par);
				
				break;
			//DELETA VERTICE
			case 2:
				scanf("%d", &par);

				removeVertex(g, par);
				
				break;
			//CRIA ARESTA
			case 3:
				scanf("%d %d %lf", &par, &par2, &par3);

				insertEdge(g, par3, par, par2);
				
				break;
			//DELETA ARESTA
			case 4:
				scanf("%d", &par);

				removeEdge(g, 1);
				
				break;
			//TROCA VERTICE
			case 5:
				scanf("%d %d", &par, &par2);

				replaceVertex(g, par, par2);
				
				break;
			//TROCA ARESTA
			case 6:
				scanf("%d %lf", &par, &par3);

				replaceEdge(g, par, par3);
				
				break;
			//EXECUTA O ALGORTIMO FW
			case 7:
				//INICIALIZANDO AS MATRIZES PARA SLTAR O ALGORTIMO
				mat_dist = criaDist(g);
				mat_par = criaParent(g, mat_dist);

				mat_par =  algFW(g, mat_dist, mat_par);
				
				break;
			//IMPRIME GRAFO
			case 8:
				printGraph(g);
				
				break;
			//IMPRIMI DISTANCIA FW
			case 9:
				scanf("%d %d", &par, &par2);

				printf("%.3lf\n", mat_dist[par-1][par2-1]);
				
				break;
			//IMPRIMI CAMINHO MINIMO
			case 10:
				scanf("%d %d", &par, &par2);

				//DIMINUINDO 1 PARA SEGUIR OS INDICES CORRETOR NA MATRIZ
				par--;
				par2--;

				//CHAMANDO O ALGORITMO DE IMPRIMIR O MENOR CAMINHO
				i_min(mat_par, par, par2);

				//PULANDO A LINHA PARA MANTER A ESTRUTURA DO PROGRAMA
				printf("\n");
				
				break;
			//TERMINA O PROGRAMA
			case 11:
				//NAO FAZ NADA POIS O WHILE IRA INTERROMPER O PROGRAMA
	
				break;
		}
	}

	//LIBERANDO A MEMORIA UTILIZADA DA MÁQUINA
	free(g);


	return 0;
}


