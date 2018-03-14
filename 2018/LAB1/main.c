#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo_matriz.c"

int main(void){
  char tipo_grafo, tipo_armazenamento;
  int vertices, arestas;
  int contador_arestas = 0;
  int v1, v2, peso;
  char op[2];
  GRAFO_M *g;

  //Armazenando se é Digrafo ou Grafo e numero de vertices e arestas
  scanf("%c %c", &tipo_grafo, &tipo_armazenamento);
  scanf("%d %d", &vertices, &arestas);

  //Verificando qual o tipo de grafo
  if(tipo_grafo == 'D'){
		if(tipo_armazenamento == 'M'){
			//Digrafo - Matriz
      g = criar_grafo_matriz(vertices, arestas);
      //Adicionando os valores no grafo

      while(contador_arestas < arestas){
        //Pegando os valores
        scanf("%d %d %d", &v1, &v2, &peso);
        //Inserindo
        g = inserir_valores_digrafo(g, v1-1, v2-1, peso);
        contador_arestas++;
      }

    //OPERACOES D M
    while(scanf("%s ", op) != EOF){
  		if(strcmp(op, "IG") == 0){
  			imprimir_matriz(g);
  		}else if(strcmp(op, "VA") == 0){


  		}else if(strcmp(op, "AA") == 0){
        scanf("%d %d %d", &v1, &v2, &peso);
        g = inserir_valores_digrafo(g, v1-1, v2-1, peso);

  		}else if(strcmp(op, "RA") == 0){


  		}else if(strcmp(op, "IT") == 0){

  		}else if(strcmp(op, "MP") == 0){

  		}
  	}


		}if(tipo_armazenamento == 'L'){
      //Digrafo - Lista

      //OPERACOES D L
    }

	}if(tipo_grafo == 'G'){
		if(tipo_armazenamento == 'M'){
			//Grafo - Matriz
      g = criar_grafo_matriz(vertices, arestas);
      //Adicionando os valores no grafo
      while(contador_arestas < arestas){
        //Pegando os valores
        scanf("%d %d %d", &v1, &v2, &peso);
        //Inserindo
        g = inserir_valores_grafo(g, v1, v2, peso);
        contador_arestas++;
      }

      //OPERACOES G M
      while(scanf("%s ", op) != EOF){
        if(strcmp(op, "IG") == 0){
          imprimir_matriz(g);
        }else if(strcmp(op, "VA") == 0){

        }else if(strcmp(op, "AA") == 0){
          scanf("%d %d %d", &v1, &v2, &peso);
          g = inserir_valores_grafo(g, v1, v2, peso);

        }else if(strcmp(op, "RA") == 0){

        }else if(strcmp(op, "IT") == 0){

        }else if(strcmp(op, "MP") == 0){

        }
      }

		}if(tipo_armazenamento == 'L'){
      //Grafo - Lista

      //OPERACOES G L
    }

	}




  return 0;
}
