#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
//#include "fila.h"

#define MAX_VERTICES 50
#define MAX_EDGES 200
#define TAM 50

#define FALSE 0
#define TRUE 1

/* Vertex */
struct vertex {
    /* marcador que indica se o vértice está sendo usado (used == TRUE) ou não
    ** (used==FALSE) */
    int used;
    
    /* objeto armazenado pelo vértice */
	int value;

    //Dstancia para o algoritmo de caminho minimo
    double dist;

    //vertice predecessor
    int parent;
};

/* Edge */
struct edge {
    /* marcador que indica se a aresta está sendo usada (used == TRUE) ou não
    ** (used == FALSE) */
    int used;
    
    /* primeiro vértice da aresta */
    int v1;
    
    /* segundo vértice da aresta */
    int v2;
    
    /* objeto armazenado pela aresta */
    double value;
};

/* Graph
** implementado utilizando-se a estrutura: LISTA DE ARESTAS */
struct graph {
    /* vetor estático que armazena os vértices */
    Vertex vertices[MAX_VERTICES];
    
    /* vetor estático que armazena as arestas */
    Edge edges[MAX_EDGES];
    
    /* armazena o número de vértices e o número de arestas do grafo*/
    int n_vertices, n_edges;
};

typedef struct elemento{
    int valor;
    double dist;
}ELEMENTO;

//struct definindo os atributos de um fila
typedef struct fila_estatica{
    ELEMENTO vector[TAM];
    int inicio;
    int fim;
    int total;

}FILA_ESTATICA;


//Criar a fila estatica circular
FILA_ESTATICA * criar_fila(){
    FILA_ESTATICA * fila = (FILA_ESTATICA*)malloc(sizeof(FILA_ESTATICA));

    if(fila != NULL){
        fila->fim = 0;
        fila->inicio = 0;
        fila->total = 0;
    } 

    return(fila);
}

//Verifica se a fila esta cheia
int cheia(FILA_ESTATICA * fila){
    return(fila->total == TAM);
}

//Verifica se a fila esta vazia
int vazia(FILA_ESTATICA * fila){
    return(fila->total == 0);
}

int tamanho(FILA_ESTATICA * fila){
    return(fila->total);
}

//Adiciona item na fila
int entra(FILA_ESTATICA * fila, int item, double dist){
    if(!cheia(fila)){
        fila->vector[fila->fim].valor = item;
        fila->vector[fila->fim].dist = dist;
        fila->fim = (fila->fim + 1) % TAM;
        fila->total++;
        return(1);
    }
    return(0);
}

//Remove um elemento da fila
int sai(FILA_ESTATICA * fila){
    if(!vazia(fila)){
        int ret = fila->vector[fila->inicio].valor;
        fila->inicio = (fila->inicio + 1) % TAM;
        fila->total--;
        return(ret);
    }
    return -1;
}

//Ordenar a fila com base na prioridade
void ordenar(FILA_ESTATICA * fila){
    int i, j;
    ELEMENTO  aux;


    //printf("FILA ANTES %d %d %d %d\n", fila->vector[0].valor, fila->vector[1].valor, fila->vector[2].valor, fila->vector[3].valor );
    if(!vazia(fila)){
        //bubble sort
        for(i=fila->total; i >= 1; i--) 
        {  
            for(j=fila->inicio; j < i ; j++) 
            {
                if(fila->vector[j].dist > fila->vector[j+1].dist) 
                {
                    aux = fila->vector[j];
                    fila->vector[j] = fila->vector[j+1];
                    fila->vector[j+1] = aux;
                 }
             }
        }
    }
    //printf("FILA DEPOIS %d %d %d %d\n", fila->vector[0].valor, fila->vector[1].valor, fila->vector[2].valor, fila->vector[3].valor );
}

void replaceKey(FILA_ESTATICA * fila, int id, double dist_mudada){
    int i;
    //printf("entrou no replaceKEY ID = %d\n\n", id);
    //Percorrer a fila até achar o id correto
    for(i = 0 ; i < 4 ; i++){
        //Caso encontre o id
        //printf("\n\n\n entrou no for \n\n\n");
        //printf("\n\n\nencontrou o id na fila, %d \n\n\n", fila->vector[i].valor);
        if(fila->vector[i].valor == id){
            //printf("aleluuuuuuuuuuuuuuuuuuuia\n");
            //Atualizar o valor da distancia na fila
            fila->vector[i].dist = dist_mudada;
            
        }
    }
    //Ordenar a fila apos atualizar os valores
    //ordenar(fila);

}

//
//
// FINAL DE FILA DE PRIORIDADE
//
//


/* Cria um grafo */
Graph* createGraph(void) {
    int i, j;
    Graph* g;
    
    /* Aloca dinamicamente um grafo que é retornado para o usuário */
    g = (Graph*) malloc(sizeof(Graph));

    /* Marca todos os vértices como livres (i.e., não utilizadas) */
    for (i = 0; i < MAX_VERTICES; i++) { g->vertices[i].used = FALSE; }
    
    /* Marca todas as arestas como livres (i.e., não utilizadas) */
    for (j = 0; j < MAX_EDGES; j++) { g->edges[j].used = FALSE; }
    
    g->n_vertices = 0;
    g->n_edges = 0;
    
    return g;
}

/* Apaga um grafo */
void eraseGraph(Graph* g) {
    /* Libera o espaço em memória alocado pela função createGraph() */
    free(g);
}

/* Função para adicionar um vértice ao grafo */
int insertVertex(Graph* g, int o) {
    int i;
    
    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == FALSE) break;
    }
    
    if (i < MAX_VERTICES) {
        g->n_vertices++;
        g->vertices[i].value = o;
        g->vertices[i].used = TRUE;
    } else {
        printf("ERRO: Número máximo de vértices já foi atingido!\n");
    }
    return i;
}

/* Função para adicionar uma aresta não direcionada ao grafo */
int insertEdge(Graph* g, int v, int w, double o) {
    int j;
    
    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used == FALSE) break;
    }
    
    if (j < MAX_EDGES) {
        g->n_edges++;
        g->edges[j].v1 = v;
        g->edges[j].v2 = w;
        g->edges[j].value = o;
        g->edges[j].used = TRUE;
    } else {
        printf("ERRO: Número máximo de arestas já foi atingido!\n");
    }
    return j;
}

/* Função para substituir o elemento armazenado no vértice 'v' por 'o' */
void replaceVertex(Graph* g, int v, int o) {
    g->vertices[v].value = o;
}

/* Função para substituir o elemento armazenado na aresta 'e' por 'o' */
void replaceEdge(Graph* g, int e, int o) {
    g->edges[e].value = o;
}

/* Função para remover um vértice do grafo */
int removeVertex(Graph* g, int v) {
    int j;
    
    g->vertices[v].used = FALSE;
    g->n_vertices--;
    
    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used != FALSE && (g->edges[j].v1 == v || g->edges[j].v2 == v)) {
            g->edges[j].used = FALSE;
            g->n_edges--;
        }
    }
    return g->vertices[v].value;
}

/* Função para remover uma aresta do grafo */
int removeEdge(Graph* g, int e) {
    g->edges[e].used = FALSE;
    g->n_edges--;
    return g->edges[e].value;
}


/* MÉTODOS GERAIS */
/* Função para acessar o número de vértices de um grafo */
int numVertices(Graph* g) {
    return g->n_vertices;
}

/* Função para acessar o número de arestas de um grafo */
int numEdges(Graph* g) {
    return g->n_edges;
}

/* Função para acessar o grau de um vértice de um grafo */
int degree(Graph* g, int v) {
    int j, dg;
    
    dg = 0;
    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used == TRUE) {
             if (g->edges[j].v1 == v) dg++;
             if (g->edges[j].v2 == v) dg++;
        }
    }
    return dg;
}

/* Função para verificar se dois vértices são ou não adjacentes */
int areAdjacent(Graph* g, int v, int w) {
    int j;
    
    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used == TRUE) {
             if (g->edges[j].v1 == v && g->edges[j].v2 == w) return TRUE;
             if (g->edges[j].v1 == w && g->edges[j].v2 == v) return TRUE;
        }
    }
    return FALSE;
}


/* MÉTODOS DE IMPRESSÃO */

/* ATENÇÃO: Caso o grafo não seja direcionado, as funções de impressão das
   arestas ordenará de forma ascendente os identificadores dos vértices. */

/* Imprime a quantidade de vértices de um grafo seguido de uma lista ordenada
   de forma ascendente pelo identificador de cada vértice contendo os valores
   armazenados nestes, i.e., imprime os pares ordenados (identificador(v), valor(v))*/
void printVertices(Graph* g) {
    int i, num_vertices;
    
    num_vertices = numVertices(g);
    printf("%d\n", num_vertices);
    
    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == TRUE)
            printf("%d %d\n", i, g->vertices[i].value);
    }
}

/* Imprime a quantidade de arestas de um grafo seguido de uma lista ordenada
   de forma ascendente pelo identificador de cada aresta contendo as tuplas
   (identificador(e), identificador(v1), identificador(v2), valor(e)), onde os
   identificadores de v1 e v2 também são ordenados de forma ascendente caso o
   grafo não seja direcionado */
void printEdges(Graph* g) {
    int j, num_edges;
    
    num_edges = numEdges(g);
    printf("%d\n", num_edges);
    
    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used == TRUE) {
            if (g->edges[j].v1 > g->edges[j].v2) {
                printf("%d %d %d %lf\n", j, g->edges[j].v2, g->edges[j].v1, g->edges[j].value);
            } else {
                printf("%d %d %d %lf\n", j, g->edges[j].v1, g->edges[j].v2, g->edges[j].value);
            }
        }
    }
}

/* Imprime a quantidade de vértices, a quantidade de arestas, a lista de vértices
   e a lista de arestas de um grafo */
void printGraph(Graph* g) {
    int i, j, num_vertices, num_edges;
    
    num_edges = numEdges(g);
    num_vertices = numVertices(g);
    printf("%d\n%d\n", num_vertices, num_edges);
    
    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == TRUE)
            printf("Vertice: %d %d %d\n", i, g->vertices[i].value, g->vertices[i].parent);
    }
    
    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used == TRUE) {
            if (g->edges[j].v1 > g->edges[j].v2) {
                printf("Aresta: %d %d %d %lf\n", j, g->edges[j].v2, g->edges[j].v1, g->edges[j].value);
            } else {
                printf("Aresta:%d %d %d %lf\n", j, g->edges[j].v1, g->edges[j].v2, g->edges[j].value);
            }
        }
    }
}

/* Imprime a quantidade de vértices de um grafo seguido de uma lista ordenada de
   forma ascendente pelo identificador de cada vértice contendo o grau deste, i.e.,
   imprime os pares ordenados (identificador(v), grau(v))*/
void printDegree(Graph* g) {
    int i, dg, num_vertices;
    
    num_vertices = numVertices(g);
    printf("%d\n", num_vertices);
    
    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == TRUE) {
            dg = degree(g, i);
            printf("%d %d\n", i, dg);
        }
    }
}

/* Imprime TRUE se dois vértices são adjacentes ou FALSE caso contrário */
void printAdjacent(Graph* g, int v, int w) {
    if (areAdjacent(g, v, w)) printf("TRUE\n");
    else printf("FALSE\n");
}

//Algoritmo para verificar o menor caminho
void dijkstra(Graph * g, int s){

    FILA_ESTATICA * fila = criar_fila();
    int i, saiu_fila, aux;

    //printf("COemcoe\n");
    //Percorrendo todos os vertices
    for(i=0; i<g->n_vertices; i++){
        if(g->vertices[i].value == s){
            //Atrribuindo zero ṕois eh o proprio vertice
            g->vertices[i].dist = 0;
            //printf("DEu zero para dist\n");
        }else{
            //VAlor infinito simbolico
            g->vertices[i].dist = 1000000;
            //printf("alto para dist\n");
        }
        //printf("enbtrou na fila\n");
        //COlocando o vertice na fila
        entra(fila, g->vertices[i].value, g->vertices[i].dist);
    }

    //Enquanto a fila não for vazia
    while(!vazia(fila)){
        //Remover um elemento da Fila
        saiu_fila = sai(fila);
        //printf("tirou da fila o %d \n", saiu_fila);

        //Percorrer arestas para ver os vértices opostos ao vertice removido
        for(i = 0; i < MAX_EDGES; i++){
            //Verifica se é uma aresta válida 
            
            if (g->edges[i].used == TRUE) {
                //printf("ENtrou nas arestas validas\n");
                //Verificar se tem o vertice aux que saiu da fila
                if(g->edges[i].v1 == saiu_fila){
                    //printf("Achou no v1\n");
                    //Ver a outra ponta da aresta para ver o vertice oposto
                    aux = g->edges[i].v2;
                    //printf("VALOR DE V1 = %d VALOR DE DIST = %lf \n", saiu_fila , g->vertices[saiu_fila-1].dist);
                    //printf("Aresta %lf = \n", g->edges[i].value);
                    //printf(" VALOR DE V2 = %d VALOR DE DIST = %lf \n", aux, g->vertices[aux-1].dist);
                    //Verificando as distancias dos vertices opostos
                    if(g->vertices[aux-1].dist > (g->vertices[saiu_fila-1].dist + g->edges[i].value)){
                        g->vertices[aux-1].dist = (g->vertices[saiu_fila-1].dist + g->edges[i].value);
                        g->vertices[aux-1].parent = g->vertices[saiu_fila-1].value;
                        //Atualizando a fila tambem 
                        //printf("ANOTOU COMO PARENT\n");

                        //printf("%d %lf\n %d %lf \n%d %lf \n%d %lf\n", fila->vector[0].valor, fila->vector[0].dist, fila->vector[1].valor, fila->vector[1].dist, fila->vector[2].valor, fila->vector[2].dist, fila->vector[3].valor, fila->vector[3].dist);

                        //Envia a fila, o id para localizar e o valor para trocar
                        replaceKey(fila, aux, g->vertices[aux-1].dist);

                        //printf("%d %lf\n %d %lf \n%d %lf \n%d %lf\n", fila->vector[0].valor, fila->vector[0].dist, fila->vector[1].valor, fila->vector[1].dist, fila->vector[2].valor, fila->vector[2].dist, fila->vector[3].valor, fila->vector[3].dist);

                        ordenar(fila);

                       // printf("%d %lf\n %d %lf \n%d %lf \n%d %lf\n", fila->vector[0].valor, fila->vector[0].dist, fila->vector[1].valor, fila->vector[1].dist, fila->vector[2].valor, fila->vector[2].dist, fila->vector[3].valor, fila->vector[3].dist);
                    }

                }else if(g->edges[i].v2 == saiu_fila){
                    //printf("Achou no v2\n");
                    //Ver a outra ponta
                    aux = g->edges[i].v1;
                    //Verificando a distancia dos vertices opostos
                    if(g->vertices[aux-1].dist > (g->vertices[saiu_fila-1].dist + g->edges[i].value)){
                        g->vertices[aux-1].dist = g->vertices[saiu_fila-1].dist + g->edges[i].value;
                        g->vertices[aux-1].parent = g->vertices[saiu_fila-1].value;
                        //Atualizando a fila tambem
                        replaceKey(fila, aux, g->vertices[aux-1].dist);
                        ordenar(fila);
                    }
                }
            }
        }
    }
}

int retorna_parent(Graph * g, int id){
    int i;
    //pesquisando nos vertices
    for(i=0; i< MAX_VERTICES; i++){
        if(g->vertices[i].value == id){
            //Pegando o valor do parent
            return g->vertices[i].parent;
        }
    }
}