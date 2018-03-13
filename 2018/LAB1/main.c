#include <stdio.h>


int main(void){
  char tipo_grafo, tipo_armazenamento;
  double vertices, arestas;
  int contador_arestas = 0;

  //Armazenando se é Digrafo ou Grafo e numero de vertices e arestas
  scanf("%s %s", &tipo_grafo, &tipo_armazenamento);
  scanf("%lf %lf", &vertices, &arestas);

  //Lendo os vertices
  while(contador_arestas < arestas){
    printf("ola\n" );
    contador_arestas++;
  }




  return 0;
}
