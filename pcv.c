#include<stdio.h>

// Definições das constantes utilizadas para auxiliar as funções
#define MAX_NUM_VERTICES  100
#define MAX_NUM_ARESTAS   4500
#define VAZIO             0
#define TRUE              1
#define FALSE             0
#define BRANCO            0
#define CINZA             1
#define PRETO             2
#define NIL_VALUE         -1

// Definições dos tipos para o Grafo
typedef int TipoValorVertice;
typedef int TipoValorAresta;
typedef int TipoValorTempo;
typedef int TipoCor;
typedef int TipoPeso;
typedef short bool;

typedef struct TipoGrafo {
  TipoPeso MatAdj[MAX_NUM_VERTICES + 1][MAX_NUM_VERTICES + 1];
  int NumVertices;
  int NumArestas;
} TipoGrafo;

typedef struct Caminho {
  TipoValorVertice passos[MAX_NUM_VERTICES + 1];
  int NumVertices;
  int TotalPassos;
} Caminho;

typedef TipoValorVertice Apontador;

// Definições das funções para manipular o Grafo
void FGVazio(TipoGrafo *grafo);
void InsereAresta(TipoValorVertice *v1, TipoValorVertice *v2, TipoPeso *peso, TipoGrafo *grafo);
bool ExisteAresta(TipoValorVertice v1, TipoValorVertice v2, TipoGrafo *grafo);
bool ListaAdjVazia(TipoValorVertice *vertice, TipoGrafo *grafo);
Apontador PrimeiroListaAdj(TipoValorVertice *vertice, TipoGrafo *grafo);
void ProxAdj(TipoValorVertice *vertice, TipoGrafo *grafo, TipoValorVertice *adj, TipoPeso *peso, Apontador *prox, bool *fimListaAdj);
void RetiraAresta(TipoValorVertice *v1, TipoValorVertice *v2, TipoPeso *peso, TipoGrafo *grafo);
void VisitaDsf(TipoValorVertice vertice, TipoGrafo *grafo, TipoValorTempo *tempo, TipoValorTempo *d, TipoValorTempo *t, TipoCor *cor, int *antecessor, Caminho *caminho);
void BuscaEmProfundidade(TipoGrafo *grafo);
void LiberaGrafo(TipoGrafo *grafo);
void ImprimeGrafo(TipoGrafo *grafo);
void TestaGrafo();

void RegistraPasso(Caminho *caminho, TipoValorVertice v);

int main() {
  TestaGrafo();
  printf("%s :)\n", "PCV");
  return 0;
}

// Inicializa todas as posições da matriz de adjacencias com VAZIO.
// Complexidade: O(n^2)
void FGVazio(TipoGrafo *grafo) {
  int i, j;
  for (i=0; i < grafo->NumVertices; i++) {
    for (j=0; j < grafo->NumVertices; j++) {
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

// Insere o indice do vertice no caminho a ser percorrido
// Complexidade: Constante
void RegistraPasso(Caminho *caminho, TipoValorVertice v) {
  caminho->passos[caminho->NumVertices - caminho->TotalPassos - 1] = v;
  caminho->TotalPassos++;
}

// Percorre os itens BRANCO do grafo, auxiliando a Busca em Profundidade
// Complexidade: O(n^2)
void VisitaDsf(TipoValorVertice u, TipoGrafo *grafo, TipoValorTempo *tempo, TipoValorTempo *d, TipoValorTempo *t, TipoCor *cor, int *antecessor, Caminho *caminho) {
  bool fimListaAdj;
  TipoValorAresta peso;
  Apontador aux;
  TipoValorVertice v;

  cor[u] = CINZA;
  (*tempo)++;
  d[u] = (*tempo);

  printf("Visita %2d Tempo descoberta: %2d cinza\n", u, d[u]);

  if (!ListaAdjVazia(&u, grafo)) {
    aux = PrimeiroListaAdj(&u, grafo);
    fimListaAdj = FALSE;
    while (!fimListaAdj) {
      ProxAdj(&u, grafo, &v, &peso, &aux, &fimListaAdj);

      if (cor[v] == BRANCO) {
        antecessor[v] = u;
        VisitaDsf(v, grafo, tempo, d, t, cor, antecessor, caminho);
      }
    }
  }

  RegistraPasso(caminho, u);

  cor[u] = PRETO;
  (*tempo)++;
  t[u] = (*tempo);
  printf("Visita %2d Tempo Termino: %2d preto\n", u, t[u]);
}

// Percorre o grafo usando o algoritmo de busca em profundidade.
// Complexidade: O(2n)
void BuscaEmProfundidade(TipoGrafo *grafo) {
  TipoValorVertice x;
  TipoValorTempo tempo;
  TipoValorTempo d[MAX_NUM_VERTICES + 1];
  TipoValorTempo t[MAX_NUM_VERTICES + 1];
  TipoCor cor[MAX_NUM_VERTICES + 1];
  int antecessor[MAX_NUM_VERTICES + 1];
  Caminho caminho;

  tempo = 0;
  caminho.NumVertices = grafo->NumVertices;
  caminho.TotalPassos = 0;

  for (x=0; x < grafo->NumVertices; x++) {
    cor[x] = BRANCO;
    antecessor[x] = NIL_VALUE;
  }

  for (x=0; x < grafo->NumVertices; x++) {
    if (cor[x] == BRANCO) {
      VisitaDsf(x, grafo, &tempo, d, t, cor, antecessor, &caminho);
    }
  }

  for (x=0; x < grafo->NumVertices; x++) {
    if (x > 0) printf(" -> ");
    printf("%d", caminho.passos[x]);
  }

  printf("\n");
}

void LiberaGrafo(TipoGrafo *grafo) {
  // Não faz nada quando usamos matrizes de adjacencias
}

void ImprimeGrafo(TipoGrafo *grafo) {
  int i, j;

  printf("    ");

  for (i=0; i < grafo->NumVertices; i++) {
    printf(" %3d", i);
  }

  printf("\n");

  for (i=0; i < grafo->NumVertices; i++) {
    printf(" %3d", i);
    for (j=0; j < grafo->NumVertices; j++) {
      printf(" %3d", grafo->MatAdj[i][j]);
    }
    printf("\n");
  }
}

void TestaGrafo() {
  Apontador aux;
  int i;
  TipoValorVertice v1, v2, adj;
  TipoPeso peso;
  TipoGrafo grafo, grafot;
  TipoValorVertice nVertices;
  int nArestas;
  bool fimListaAdj;
/*
  printf("No. vertices: "); scanf("%d", &nVertices);
  printf("No. arestas: "); scanf("%d", &nArestas);

  grafo.NumVertices = nVertices;
  grafo.NumArestas = VAZIO;
  FGVazio(&grafo);

  i = 0;
  while(i < nArestas) {
    printf("Insere V1--V2--Peso:");
    scanf("%d %d %d", &v1, &v2, &peso);

    if (ExisteAresta(v1, v2, &grafo)) {
      printf("Aresta já existe\n");
    } else {
    grafo.NumArestas++;
      // Insere nas duas direções por não se tratar de um grafo direcionado
      InsereAresta(&v1, &v2, &peso, &grafo);
      InsereAresta(&v2, &v1, &peso, &grafo);
      i++;
    }
  }
  */

  nVertices = 8;
  grafo.NumVertices = nVertices;
  grafo.NumArestas = VAZIO;
  FGVazio(&grafo);

  v1 = 0; v2 = 2; peso = 1;
  InsereAresta(&v1, &v2, &peso, &grafo);
  InsereAresta(&v2, &v1, &peso, &grafo);
  grafo.NumArestas++;

  v1 = 0; v2 = 6;
  InsereAresta(&v1, &v2, &peso, &grafo);
  InsereAresta(&v2, &v1, &peso, &grafo);
  grafo.NumArestas++;

  v1 = 0; v2 = 7;
  InsereAresta(&v1, &v2, &peso, &grafo);
  InsereAresta(&v2, &v1, &peso, &grafo);
  grafo.NumArestas++;

  v1 = 2; v2 = 1;
  InsereAresta(&v1, &v2, &peso, &grafo);
  InsereAresta(&v2, &v1, &peso, &grafo);
  grafo.NumArestas++;

  v1 = 2; v2 = 4;
  InsereAresta(&v1, &v2, &peso, &grafo);
  InsereAresta(&v2, &v1, &peso, &grafo);
  grafo.NumArestas++;

  v1 = 2; v2 = 6;
  InsereAresta(&v1, &v2, &peso, &grafo);
  InsereAresta(&v2, &v1, &peso, &grafo);
  grafo.NumArestas++;

  v1 = 1; v2 = 3;
  InsereAresta(&v1, &v2, &peso, &grafo);
  InsereAresta(&v2, &v1, &peso, &grafo);
  grafo.NumArestas++;

  v1 = 1; v2 = 4;
  InsereAresta(&v1, &v2, &peso, &grafo);
  InsereAresta(&v2, &v1, &peso, &grafo);
  grafo.NumArestas++;

  v1 = 1; v2 = 3;
  InsereAresta(&v1, &v2, &peso, &grafo);
  InsereAresta(&v2, &v1, &peso, &grafo);
  grafo.NumArestas++;

  v1 = 3; v2 = 4;
  InsereAresta(&v1, &v2, &peso, &grafo);
  InsereAresta(&v2, &v1, &peso, &grafo);
  grafo.NumArestas++;

  v1 = 3; v2 = 5;
  InsereAresta(&v1, &v2, &peso, &grafo);
  InsereAresta(&v2, &v1, &peso, &grafo);
  grafo.NumArestas++;

  v1 = 4; v2 = 5;
  InsereAresta(&v1, &v2, &peso, &grafo);
  InsereAresta(&v2, &v1, &peso, &grafo);
  grafo.NumArestas++;

  v1 = 5; v2 = 6;
  InsereAresta(&v1, &v2, &peso, &grafo);
  InsereAresta(&v2, &v1, &peso, &grafo);
  grafo.NumArestas++;

  v1 = 5; v2 = 7;
  InsereAresta(&v1, &v2, &peso, &grafo);
  InsereAresta(&v2, &v1, &peso, &grafo);
  grafo.NumArestas++;

  v1 = 6; v2 = 7;
  InsereAresta(&v1, &v2, &peso, &grafo);
  InsereAresta(&v2, &v1, &peso, &grafo);
  grafo.NumArestas++;

  ImprimeGrafo(&grafo);

  BuscaEmProfundidade(&grafo);

/*
  printf("Lista adjacentes de: "); scanf("%d", &v1);

  if (ListaAdjVazia(&v1, &grafo)) {
    printf("Lista adjacente vazia");
  } else {
    aux = PrimeiroListaAdj(&v1, &grafo);
    fimListaAdj = FALSE;

    while (!fimListaAdj) {
      ProxAdj(&v1, &grafo, &adj, &peso, &aux, &fimListaAdj);
      printf(" %2d (%d)", adj, peso);
    }

    printf("\n");
  }
  */
}
