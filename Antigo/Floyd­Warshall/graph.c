#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define FALSE 0
#define TRUE 1


/*
	COMEÇANDO AS IMPLEMENTAÇÕES
*/


Grafo* criarGrafo(){
	
	Grafo* g = malloc(sizeof(Grafo));

	g->vertice = NULL;
	g->aresta = NULL;
	g->q_ver = 0;
	g->q_are = 0;

	return g;
}

void insertVertex(Grafo* g, int o){

	Vertice* novo = malloc(sizeof(Vertice));
	Vertice* aux;
	Vertice* p;

	novo->used = TRUE;
	novo->value = g->q_ver + 1;
	novo->prox = NULL;
	novo->ant = NULL;
	novo->lista = NULL;
	novo->cont = 1;
	novo->custo = o;

	g->q_ver = g->q_ver + 1;

	//ATUALIZANDO NA LISTA DE ADJ DO GRAFO	
	if(g->vertice == NULL){

		g->vertice = novo;

	}else{

		p = g->vertice;

		while(p != NULL){
			
			aux = p;

			p = p->prox;
		}

		novo->ant = aux;

		aux->prox = novo;
	}

}

void insertEdge(Grafo* g, double o, int a, int b){
	Aresta* novo = malloc(sizeof(Aresta));
	Aresta* aux;
	Aresta* p;
	Vertice* v;
	Vertice* v_aux;
	int c;

	novo->used = TRUE;
	novo->custo = o;
	novo->ant = NULL;
	novo->prox = NULL;

	if(a > b){
		c = a;
		a = b;
		b = c;
	}

	//PROCURANDO OS VERTICES DESEJADOS 
	//V1
	v = g->vertice;

	while(v->value != a){
		v = v->prox;
	}

	if(v->value == a){
		

		novo->v1 = v;

		v_aux = v;

	}

	//V2
	v = g->vertice;

	while(v->value != b){
		v = v->prox;
	}

	if(v->value == b){
		
		//ADICIONANDO OS PONTEIRO NAS LISTAS DE ADJ DE CADA VERTICE

		v->lista = (Vertice**)realloc(v->lista, sizeof(Vertice*)*v->cont);	
		
		v->lista[v->cont-1] = v_aux; 	

		v->cont = v->cont + 1;

		v_aux->lista = (Vertice**)realloc(v_aux->lista, sizeof(Vertice*)*v_aux->cont);

		v_aux->lista[v_aux->cont-1] = v;

		v_aux->cont = v_aux->cont + 1;

		novo->v2 = v;

	}

	g->q_are = g->q_are + 1;

	novo->value = g->q_are;

	//ATUALIZANDO A LISTA DE ARESTAS NO GRAFO
	if(g->aresta == NULL){

		g->aresta = novo;

	}else{

		p = g->aresta;

		while(p != NULL){
			
			aux = p;

			p = p->prox;
		}

		novo->ant = aux;

		aux->prox = novo;
	}

}

int vertexValue(Grafo* g, int v){
	Vertice* p;

	p = g->vertice;

	while(p->value != v){
		
		p = p->prox;
	
	}

	if(p->value == v){

		return p->custo; 
	}

}

double edgeValue(Grafo* g, int e){
	Aresta* p;

	p = g->aresta;

	//ENCONTRANDO A ARESTA PEDIDA PELO USUARIO
	while(p->value != e){
		
		p = p->prox;
	
	}

	if(p->value == e){

		return p->custo; 
	}

}

int numVertex(Grafo* g){
	return g->q_ver;
}

int numEdge(Grafo* g){
	return g->q_are;
}

int areAdjacent(Grafo* g, int v, int w){
	Vertice* p;
	int i;

	//PESQUISANDO A LSITA DE ADJACENTES EM UM DOS VERTICES

	p = g->vertice;

	while(p != NULL){
		
		if(p->value == v){
			break;
		}else{
			p = p->prox;
		}
	}

	//PESQUISANDO NA LISTA
	for(i=0 ; i < p->cont-1; i++){
		if(p->lista[i]->value == w){
			return TRUE;
		}
	}

	return FALSE;

}

void endVertices(Grafo* g, int e, Vertice** v, Vertice** w){
	Aresta* p;

	p = g->aresta;
	//NÃO PREECISA RETORNARM, SOMEWNTE ATRIBUIR VERTICES NOS PONTEIROS
	//BUSCANDO A ARESTA CORRETA
	while(p != NULL){
		if(p->value == e){
			break;
		}else{
			p = p->prox;
		} 
	}

	//ATUALIZANDO OS PONTEIROS DE PARAMETROS
	*v = p->v1;
	*w = p->v2;
	
}

Vertice* opposite(Grafo* g, int v, int e){
	Aresta* p;

	p = g->aresta;
	//NÃO PREECISA RETORNARM, SOMEWNTE ATRIBUIR VERTICES NOS PONTEIROS
	//BUSCANDO A ARESTA CORRETA
	while(p != NULL){
		if(p->value == e){
			break;
		}else{
			p = p->prox;
		} 
	}

	//VERICAR QUAL O VALOR PARA SER RETORNADO
	if(p->v1->value == v){
		//RETORNA A OUTRA PONTA
		return p->v2;
	}else{
		return p->v1;
	}

}

void replaceVertex(Grafo* g, int v, int o){
	Vertice* p;

	p = g->vertice;

	//PESQUISANDO O VERTICECORRETO
	while(p->value != v){
		
		p = p->prox;
	
	}

	if(p->value == v){

		p->custo = o;
	}
}

void replaceEdge(Grafo* g, int e, double o){
	Aresta* p;

	p = g->aresta;

	//PESQUISANDO A ARESTA CORRETA
	while(p->value != e){
		
		p = p->prox;
	
	}

	if(p->value == e){

		p->custo = o;
	}
}

double removeEdge(Grafo* g, int e){
	Aresta* p;
	Aresta* aux;
	Vertice* v1;
	Vertice* v2;
	int i;
	double valor;
	
	//VARIAVEL AUXILIAR PARA ATUALIZAR A LISTA DE CADA VERTICE APOS ELIMINAR A ARESTA
	Vertice* change = malloc(sizeof(Vertice));;

	//ATRIBUINDO OS VALORES PARA O CHANGE, QUE IRA ATUALIZAR A LISTA NOS VERTICES
	change->used = FALSE;
	change->custo = -1;
	change->value = -1;
	change->cont = -1;
	change->prox = NULL;
	change->ant = NULL;
	change->lista = NULL;

	//INICIANDO A PESQUISA PELA ARESTA CORRETA
	p = g->aresta;

	//PESQUISANDO A ARESTA CORRETA
	while(p->value != e){
		
		aux = p;

		p = p->prox;
	
	}

	if(p->value == e){
		//ANOTANDO OS VERTICES QUE TAL ARESTA LIGAVA	
		v1 = p->v1;
		v2 = p->v2;

		//COMO NAO HA MAIS ARESTA ENTRE TAIS VERTICES, EH NECESSARIO TIRA-LOS DA LISTA DE ADJACENCIA DOS MESMOS
		//REMOVENDO V2 DA LISTA DE V1
		for(i=0 ; i < p->v1->cont-1; i++){
			if(p->v1->lista[i]->value == p->v2->value){
				//QUANDO ENCONTRAR O VALOR V2 NA LISTA DO V1
				//ATRABUIR NEGATIVO PARA NAO PARTICIPAR MAIS DAS PESQUISAS DE ADJACENCIA
				p->v1->lista[i] = change;
			}
		}

		//REMOVENDO V2 DA LISTA DE V1
		for(i=0 ; i < p->v2->cont-1; i++){
			if(p->v2->lista[i]->value == p->v1->value){
				//QUANDO ENCONTRAR O VALOR V2 NA LISTA DO V1
				p->v2->lista[i] = change;
			}
		}

		//ATRIBUINDO O VALOR PARA SER RETORNADO
		valor = p->custo;

		//CASO ENCONTRE, ALTERAR A LISTA DE ARESTAS E REMOVER A ARESTA
		//EXCETO PARA QUANDO FOR O PRIMEIRO VALOR, POIS O ANTERIOR EH IGUAL A NULL
		if(p->ant == NULL){
			g->aresta = p->prox;
			p->prox->ant = NULL;

		//CASO ESTEJA NO FINAL
		}else if(p->prox == NULL){
			p->ant->prox = NULL;
			//CASO ESTEJA NO MEIO
		}else{
			aux->prox = p->prox;
			p->prox->ant = aux;

		}

		//LIBERANDO A ARESTA APOS AS REFERENCIAS A ELA SEREM ELIMINADAS	
		free(p);
	}

	//DIMINUINDO A QUANTIDADE DE ARESTAS TOTAIS DO GRAFO
	g->q_are = g->q_are - 1;

	//RETORNANDO O ELEMENTO ARMAZENADO NA ARESTA
	return valor;
}

int removeVertex(Grafo* g, int v){
	Vertice* p;
	Vertice* aux;
	Aresta* a;
	int valor;

	p = g->vertice;

	//PESQUISANDO O VERTICECORRETO
	while(p->value != v){
		
		p = p->prox;
	
	}

	if(p->value == v){
		//ANALISANDO AS EXCECOES.
		//QUANDO O VERTICE FOR O PRIMEIRO DA LISTA
		if(p->ant == NULL){
			g->vertice = p->prox;
			p->prox->ant = NULL;

			//QUANDO FOR DO MEIO OU FINAL DA LISTA
		}else if(p->prox == NULL){
			p->ant->prox = NULL;

			//CASO ESTEJA NO MEIO DA LISTA
		}else{
			p->ant->prox = p->prox;
			p->prox->ant = p->ant;

		}


		//ELIMINANDO AS ARESTAS
		//ENCONTRANDO TODAS AS ARESTAS QUE TEM O VERTICE EM UM DOS VALORES
		a = g->aresta;

		while(a != NULL){
			
			if(a->v1->value == v){
				removeEdge(g, a->value);
			}else if(a->v2->value == v){
				removeEdge(g, a->value);
			}

			a = a->prox;
		
		}
		//LIBERANDO O VERTICE
		free(p);
		
	}
	return valor;
}

void printGraph(Grafo* g){
	Vertice* p;
	Aresta* a; 

	printf("%d\n", g->q_ver);

	p = g->vertice;

	while(p != NULL){
		
		printf("%d %d\n", p->value, p->custo);

		p = p->prox;
	
	}

	printf("%d\n", g->q_are);

	a = g->aresta;

	while(a != NULL){
		
		printf("%d %d %d %.3lf\n", a->value, a->v1->value, a->v2->value, a->custo);

		a = a->prox;
	
	}

}

//FUNCOES PARA O ALGORTIMO FW



//NAO ESQUECER DE DAR FREE