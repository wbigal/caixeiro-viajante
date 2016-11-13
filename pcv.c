#include<stdio.h>

#define MAX_NUM_VERTICES  100
#define MAX_NUM_ARESTAS   4500
#define VAZIO             0
#define TRUE              1
#define FALSE             0

// Definições dos tipos para o Grafo
typedef int TipoValorVertice;
typedef int TipoPeso;
typedef short bool;

typedef struct TipoGrafo {
  TipoPeso MatAdj[MAX_NUM_VERTICES + 1][MAX_NUM_VERTICES + 1];
  int NumVertices;
  int NumArestas;
} TipoGrafo;

typedef TipoValorVertice Apontador;

// Definições das funções para manipular o Grafo
void FGVazio(TipoGrafo *grafo);
void InsereAresta(TipoValorVertice *v1, TipoValorVertice *v2, TipoPeso *peso, TipoGrafo *grafo);
bool ExisteAresta(TipoValorVertice v1, TipoValorVertice v2, TipoGrafo *grafo);
bool ListaAdjVazia(TipoValorVertice *vertice, TipoGrafo *grafo);
Apontador PrimeiroListaAdj(TipoValorVertice *vertice, TipoGrafo *grafo);
void ProxAdj(TipoValorVertice *vertice, TipoGrafo *grafo, TipoValorVertice *adj, TipoPeso *peso, Apontador *prox, bool *fimListaAdj);
void RetiraAresta(TipoValorVertice *v1, TipoValorVertice *v2, TipoPeso *peso, TipoGrafo *grafo);
void LiberaGrafo(TipoGrafo *grafo);
void ImprimeGrafo(TipoGrafo *grafo);

int main() {
  Apontador aux;
  int i;
  TipoValorVertice v1, v2 adj;
  TipoPeso peso;
  TipoGrafo grafo, grafot;
  TipoValorVertice nVertices;
  int nArestas;
  bool fimListaAdj;



  printf("%s :)\n", "PCV");
  return 0;
}

// Inicializa todas as posições da matriz de adjacencias com VAZIO.
// Complexidade: O(n^2)
void FGVazio(TipoGrafo *grafo) {
  int i, j;
  for (i=0; i <= grafo->NumVertices; i++) {
    for (j=0; j <= grafo->NumVertices; j++) {
      grafo->MatAdj[i][j] = VAZIO;
    }
  }
}

// Insere um valor na matriz de adjancencias.
// Complexidade: Constante
void InsereAresta(TipoValorVertice *v1, TipoValorVertice *v2, TipoPeso *peso, TipoGrafo *grafo) {
  grafo->MatAdj[*v1][*v2] = *peso;
}

// Verifica se a aresta existe.
// Complexidade: Constante
bool ExisteAresta(TipoValorVertice v1, TipoValorVertice v2, TipoGrafo *grafo) {
  return (grafo->MatAdj[v1][v2] > VAZIO ? TRUE : FALSE);
}

// Verifica se uma lista de vertices esta vazia
// Complexidade: O(n)
bool ListaAdjVazia(TipoValorVertice *vertice, TipoGrafo *grafo) {
  Apontador aux = VAZIO;
  bool listaVazia = TRUE;

  while (aux < grafo->NumVertices && listaVazia) {
    if (grafo->MatAdj[*vertice][aux] > VAZIO) {
      listaVazia = FALSE;
    } else {
      aux++;
    }
  }

  return listaVazia;
}

// Procura pelo primeiro vertice em uma lista adjacente
// Complexidade: O(n)
Apontador PrimeiroListaAdj(TipoValorVertice *vertice, TipoGrafo *grafo) {
  TipoValorVertice primeiro;
  Apontador aux = VAZIO;
  bool listaVazia = TRUE;

  while (aux < grafo->NumVertices && listaVazia) {
    if (grafo->MatAdj[*vertice][aux] > 0) {
      primeiro = aux;
      listaVazia = FALSE;
    } else {
      aux++;
    }
  }

  if (aux == grafo->NumVertices) {
    printf("Erro: Lista de adjacencias vazia (PrimeiroListaAdj)\n");
  }

  return primeiro;
}

// Descobre a próxima posição adjacente
// Complexidade: O(n)
void ProxAdj(TipoValorVertice *vertice, TipoGrafo *grafo, TipoValorVertice *adj, TipoPeso *peso, Apontador *prox, bool *fimListaAdj) {
  *adj = *prox;
  *peso = grafo->MatAdj[*vertice][*prox];
  (*prox)++;

  while (*prox < grafo->NumVertices && grafo->MatAdj[*vertice][*prox] == VAZIO) {
    (*prox)++;
  }

  if (*prox == grafo->NumVertices) {
    *fimListaAdj = TRUE;
  }
}

// Retira um aresta do grafo
// Complexidade: Constante
void RetiraAresta(TipoValorVertice *v1, TipoValorVertice *v2, TipoPeso *peso, TipoGrafo *grafo) {
  if (grafo->MatAdj[*v1][*v2] == VAZIO) {
    printf("Aresta não existe\n");
  } else {
    *peso = grafo->MatAdj[*v1][*v2];
    grafo->MatAdj[*v1][*v2] = VAZIO;
  }
}

void LiberaGrafo(TipoGrafo *grafo) {
  // Não faz nada quando usamos matrizes de adjacencias
}

void ImprimeGrafo(TipoGrafo *grafo) {
  int i, j;

  printf(" ");

  for (i=0; i < grafo->NumVertices; i++) {
    printf(" %3d", i);
  }

  printf("\n");

  for (i=0; i < grafo->NumVertices; i++) {
    printf(" %3d", i);
    for (j=0; j <= grafo->NumVertices; j++) {
      printf(" %3d", grafo->MatAdj[i][j]);
    }
    printf("\n");
  }
}
