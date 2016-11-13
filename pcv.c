#include<stdio.h>

#define MAX_NUM_VERTICES  100
#define MAX_NUM_ARESTAS   4500

typedef int TipoValorVertice;
typedef int TipoPeso;

typedef struct TipoGrafo {
  TipoPeso MatrizAdjacencias[MAX_NUM_VERTICES + 1][MAX_NUM_VERTICES + 1];
  int NumVertices;
  int NumArestas;
} TipoGrafo;

typedef TipoValorVertice Apontador;

int main() {
  printf("%s :)\n", "PCV");
  return 0;
}
