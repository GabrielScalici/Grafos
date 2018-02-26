#include <stdio.h>
#include "graph.h"


int main(void) {
    
	int i, j, op, aux_parent =-1, aux_id, cont_cam = 0;
	int n_cidades, m_rotas, n_amigos, cid_cliente;
	double x_amigo, y_diaria;
	int caminho[50], flag = 0, amigo_perto = 1;

	Graph * g = createGraph(); 

	scanf("%d", &n_cidades);

	scanf("%lf %lf", &x_amigo, &y_diaria);

	scanf("%d", &m_rotas);

	//Adicionando os vertices
	for(i=0; i<n_cidades; i++){
		insertVertex(g, i+1);
	}

	//Criando arestas
	for(i=0; i<m_rotas; i++){
		int a, b;
		float val;
		//Lendo os valores
		scanf("%d %d %f", &a, &b, &val);
		//Criando os vertices]
		insertEdge(g, a, b, val);

	}

	scanf("%d", &n_amigos);

	//CRiando vetor com a distancia dos amigos
	int cid_amigos[n_amigos];

	//Armazenando a distancia dos amigos
	for(i=0; i<n_amigos; i++){
		int a;
		scanf("%d", &a);
		//Armaenando no vetor
		cid_amigos[i] = a;
	}

	//PEgando a opcao escolhida pelo usuario
	scanf("%d %d", &op, &cid_cliente);

	switch(op){
		case 1:
			//Calculando a distancia para Joaozinho
			dijkstra(g, 1);
			//Atribuindo o aux_id para o id do cliente
			aux_id = cid_cliente;
			//Analisando os parent, condicao de parada, parent == 0
			while(aux_parent != 0){
				//Roda a funcao que pega um id e busca o parent
				aux_parent = retorna_parent(g, aux_id);
				//Atualiza o valor do aux_id para o parent dele, para continuar a busca

				caminho[cont_cam] = aux_id;
				cont_cam++;

				//Atualizar o aux_id
				aux_id = aux_parent;
			}


			//Comparar dois vetores para saber se algum amigo tem mais perto
			for(i=0; i<n_amigos; i++){
				for(j=0; j<cont_cam; j++){
					if(cid_amigos[i]==caminho[j]){
						//Entao tem um amigo que esta mais perto que joaozinho
						//Imprime o valor da terceirização
						printf("%.3lf\n", x_amigo);
						flag = 1;
						amigo_perto = j;
					}
				}
			}

			//Analisando se ja foi encontrado algum amigo que more mais perto
			if(flag == 0){
				//Entao o joaozinho que ira fazer a entrega
			}

			printGraph(g);



			for(i=0; i<cont_cam; i++){
				printf("%d\n", caminho[i] );
			}

			break;
		case 2:

			//Calculando a distancia para Joaozinho
			dijkstra(g, 1);
			//Atribuindo o aux_id para o id do cliente
			aux_id = cid_cliente;
			//Analisando os parent, condicao de parada, parent == 0
			while(aux_parent != 0){
				//Roda a funcao que pega um id e busca o parent
				aux_parent = retorna_parent(g, aux_id);
				//Atualiza o valor do aux_id para o parent dele, para continuar a busca

				caminho[cont_cam] = aux_id;
				cont_cam++;

				//Atualizar o aux_id
				aux_id = aux_parent;
			}


			//Comparar dois vetores para saber se algum amigo tem mais perto
			for(i=0; i<n_amigos; i++){
				for(j=0; j<cont_cam; j++){
					if(cid_amigos[i]==caminho[j]){
						//Entao tem um amigo que esta mais perto que joaozinho
						flag = 1;
						amigo_perto = j;
					}
				}
			}

			//Analisando se ja foi encontrado algum amigo que more mais perto
			if(flag == 0){
				//Entao o joaozinho que ira fazer a entrega
			}

			//Mostrar os caminhos de quem vai fazer a entrega ate a cidade certa
			//Analisando o vetor caminho até encontrar o amigo que esta mais perto ou joazinho
			for(i = 0; i <= amigo_perto; i++){
				printf("%d ", caminho[i]);
			}
			//Usando a quebra de linha
			printf("\n");
			
			break;
		case 3:

			//Calculando a distancia para Joaozinho
			dijkstra(g, 1);
			//Atribuindo o aux_id para o id do cliente
			aux_id = cid_cliente;
			//Analisando os parent, condicao de parada, parent == 0
			while(aux_parent != 0){
				//Roda a funcao que pega um id e busca o parent
				aux_parent = retorna_parent(g, aux_id);
				//Atualiza o valor do aux_id para o parent dele, para continuar a busca

				caminho[cont_cam] = aux_id;
				cont_cam++;

				//Atualizar o aux_id
				aux_id = aux_parent;
			}


			//Comparar dois vetores para saber se algum amigo tem mais perto
			for(i=0; i<n_amigos; i++){
				for(j=0; j<cont_cam; j++){
					if(cid_amigos[i]==caminho[j]){
						//Entao tem um amigo que esta mais perto que joaozinho
						//Imprime o valor da terceirização
						printf("Repassa %.3lf\n", x_amigo);
						flag = 1;
						amigo_perto = j;
					}
				}
			}

			//Analisando se ja foi encontrado algum amigo que more mais perto
			if(flag == 0){
				//Entao o joaozinho que ira fazer a entrega
			}

			break;
	}

    return 0;
}
