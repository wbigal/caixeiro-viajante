#include<stdio.h>

#define MAX_NUM_VERTICES  100
#define MAX_NUM_ARESTAS   4500
#define VAZIO             0
#define TRUE              1
#define FALSE             0
#define BRANCO            0
#define CINZA             1
#define PRETO             2
#define NIL_VALUE         -1

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
  // +2 porque deve existir um passo entre a última aresta encontrada e a primeira.
  TipoValorVertice Passos[MAX_NUM_VERTICES + 2];
  int NumVertices;
  int TotalPassos;
} Caminho;

typedef TipoValorVertice Apontador;

void FGVazio(TipoGrafo *grafo);
void InsereAresta(TipoValorVertice *v1, TipoValorVertice *v2, TipoPeso *peso, TipoGrafo *grafo);
bool ExisteAresta(TipoValorVertice v1, TipoValorVertice v2, TipoGrafo *grafo);
bool ListaAdjVazia(TipoValorVertice *vertice, TipoGrafo *grafo);
Apontador PrimeiroListaAdj(TipoValorVertice *vertice, TipoGrafo *grafo);
void ProxAdj(TipoValorVertice *vertice, TipoGrafo *grafo, TipoValorVertice *adj, TipoPeso *peso, Apontador *prox, bool *fimListaAdj);
void VisitaDsf(TipoValorVertice vertice, TipoGrafo *grafo, TipoValorTempo *tempo, TipoValorTempo *d, TipoValorTempo *t, TipoCor *cor, Caminho *caminho);
Caminho BuscaEmProfundidade(TipoGrafo *grafo);
void RegistraPasso(Caminho *caminho, TipoValorVertice v);
void RegistraUltimoPasso(Caminho *caminho, TipoGrafo *grafo);
void ExibeCaminho(Caminho *caminho, TipoGrafo *grafo);
void ImprimeGrafo(TipoGrafo *grafo);
TipoGrafo CriaGrafo(int exemplo);

int main() {
  int i = 0;

  for (i=0; i < 2; i++) {
    printf("\n\n-----------------------------------------------------------------\n");
    printf("Exemplo %d\n", i + 1);
    printf("-----------------------------------------------------------------\n");
    TipoGrafo grafo = CriaGrafo(i + 1);
    Caminho caminho = BuscaEmProfundidade(&grafo);

    printf("\nMatriz representando o Grafo: \n");
    ImprimeGrafo(&grafo);

    printf("\n\nCaminho sugerido ao Caixeiro Viajante: \n");
    ExibeCaminho(&caminho, &grafo);

    printf("\n\nPressione qualquer tecla para continuar...");
    getchar();
  }

  printf("\n\nPCV :)\n");
  return 0;
}

// Inicializa todas as posições da matriz de adjacencias com VAZIO.
// Complexidade: para o grafo G(V,A), o algoritmo tem complexidade O(V^2)
void FGVazio(TipoGrafo *grafo) {
  int i, j;
  for (i=0; i < grafo->NumVertices; i++) {
    for (j=0; j < grafo->NumVertices; j++) {
      grafo->MatAdj[i][j] = VAZIO;
    }
  }
}

// Insere o peso na matriz de adjancencias.
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
// Complexidade: para o grafo G(V,A), o algoritmo tem complexidade O(|V|)
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

// Procura pelo primeiro vertice adjacente em uma lista adjacente
// Complexidade: para o grafo G(V,A), o algoritmo tem complexidade O(|V|)
Apontador PrimeiroListaAdj(TipoValorVertice *vertice, TipoGrafo *grafo) {
  TipoValorVertice primeiro;
  Apontador aux = 0;
  bool listaVazia = TRUE;

  while (aux < grafo->NumVertices && listaVazia) {
    if (grafo->MatAdj[*vertice][aux] > VAZIO) {
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
// Complexidade: para o grafo G(V,A), o algoritmo tem complexidade O(|V|)
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

// Percorre os itens BRANCO do grafo, auxiliando a Busca em Profundidade
// Complexidade: para o grafo G(V,A), o algoritmo tem complexidade O(|V|+|A|)
void VisitaDsf(TipoValorVertice u, TipoGrafo *grafo, TipoValorTempo *tempo, TipoValorTempo *d, TipoValorTempo *t, TipoCor *cor, Caminho *caminho) {
  bool fimListaAdj;
  TipoValorAresta peso;
  Apontador aux;
  TipoValorVertice v;

  cor[u] = CINZA;
  (*tempo)++;
  d[u] = (*tempo);

  //printf("Visita %2d Tempo descoberta: %2d cinza\n", u, d[u]);

  if (!ListaAdjVazia(&u, grafo)) {
    aux = PrimeiroListaAdj(&u, grafo);
    fimListaAdj = FALSE;
    while (!fimListaAdj) {
      ProxAdj(&u, grafo, &v, &peso, &aux, &fimListaAdj);

      if (cor[v] == BRANCO) {
        VisitaDsf(v, grafo, tempo, d, t, cor, caminho);
      }
    }
  }

  RegistraPasso(caminho, u);

  cor[u] = PRETO;
  (*tempo)++;
  t[u] = (*tempo);
  //printf("Visita %2d Tempo Termino: %2d preto\n", u, t[u]);
}

// Percorre o grafo usando o algoritmo de busca em profundidade.
// Complexidade: para o grafo G(V,A), o algoritmo tem complexidade O(|V|*2)
Caminho BuscaEmProfundidade(TipoGrafo *grafo) {
  TipoValorVertice x;
  TipoValorTempo tempo;
  TipoValorTempo d[MAX_NUM_VERTICES + 1];
  TipoValorTempo t[MAX_NUM_VERTICES + 1];
  TipoCor cor[MAX_NUM_VERTICES + 1];
  Caminho caminho;

  tempo = 0;
  caminho.NumVertices = grafo->NumVertices + 1;
  caminho.TotalPassos = 0;

  // Inicia vetores com valores NIL_VALUE
  for (x=0; x < grafo->NumVertices; x++) {
    cor[x] = BRANCO;
    caminho.Passos[x] = NIL_VALUE;
  }

  // Percorre os vértices, e para os vértices de cor branca é chamada
  // a função VisitaDsf recursivamente.
  for (x=0; x < grafo->NumVertices; x++) {
    if (cor[x] == BRANCO) {
      VisitaDsf(x, grafo, &tempo, d, t, cor, &caminho);
    }
  }

  RegistraUltimoPasso(&caminho, grafo);

  return caminho;
}

// Insere o indice do vertice no caminho a ser percorrido
// Complexidade: Constante
void RegistraPasso(Caminho *caminho, TipoValorVertice v) {
  caminho->Passos[caminho->NumVertices - caminho->TotalPassos - 2] = v;
  caminho->TotalPassos++;
}

// Tenta ligar a última aresta encontrada com a PrimeiroListaAdj
// Complexidade: Constante
void RegistraUltimoPasso(Caminho *caminho, TipoGrafo *grafo) {
  if (ExisteAresta(caminho->Passos[0], caminho->Passos[caminho->NumVertices - 2], grafo)) {
    caminho->Passos[caminho->NumVertices - 1] = caminho->Passos[0];
  } else {
    caminho->Passos[caminho->NumVertices - 1] = NIL_VALUE;
    printf("\n**** Nao existe aresta entre o primeiro e último vertices ****\n\n");
  }
  caminho->TotalPassos++;
}

// Exibe na tela o caminho que o Caixeiro Viajante deverá percorrer entre os vértices
// Complexidade: para o grafo G(V,A), o algoritmo tem complexidade O(|V|)
void ExibeCaminho(Caminho *caminho, TipoGrafo *grafo) {
  int i;
  bool erro = FALSE;
  // Exibe a saída do caminho que o Caixeiro Viajante deve percorrer
  for (i=0; i < caminho->NumVertices && erro == FALSE; i++) {
    if (i > 0) {
      printf(" -> ");

      if (!ExisteAresta(caminho->Passos[i - 1], caminho->Passos[i], grafo)) {
        printf("Erro!\nNao existe aresta entre os vertices %d e %d", caminho->Passos[i - 1], caminho->Passos[i]);
        erro = TRUE;
      }
    }
    if (erro == FALSE) printf("%d", caminho->Passos[i]);
  }
}

// Imprime a matriz de adjancencias
// Complexidade: para o grafo G(V,A), o algoritmo tem complexidade O(|V|^2+|V|)
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

// Gera um grafo para ser trabalhado pelo algoritmo do Caixeiro Viajante
// Complexidade: Constante para exemplo == 1 / O(|V|^2) para o segundo exemplo
TipoGrafo CriaGrafo(int exemplo) {
  TipoValorVertice v1, v2;
  TipoPeso peso;
  TipoGrafo grafo;
  TipoValorVertice nVertices;

  if (exemplo == 1) {
    printf("\nEste será o grafo:\n\n");
    printf("0 ----- 2 ----- 1\n");
    printf("| \\    /  \\    /|\n");
    printf("|  \\ /     \\  / |\n");
    printf("|   6       4   |\n");
    printf("|  / \\     /  \\ |\n");
    printf("| /   \\  /     \\|\n");
    printf("7 ----- 5 ----- 3\n\n");

    nVertices = 8;
    grafo.NumVertices = nVertices;
    grafo.NumArestas = VAZIO;
    FGVazio(&grafo);

    v1 = 0; v2 = 2; peso = 2;
    InsereAresta(&v1, &v2, &peso, &grafo); InsereAresta(&v2, &v1, &peso, &grafo);
    grafo.NumArestas++;

    v1 = 0; v2 = 6; peso = 6;
    InsereAresta(&v1, &v2, &peso, &grafo); InsereAresta(&v2, &v1, &peso, &grafo);
    grafo.NumArestas++;

    v1 = 0; v2 = 7; peso = 7;
    InsereAresta(&v1, &v2, &peso, &grafo); InsereAresta(&v2, &v1, &peso, &grafo);
    grafo.NumArestas++;

    v1 = 2; v2 = 1; peso = 3;
    InsereAresta(&v1, &v2, &peso, &grafo); InsereAresta(&v2, &v1, &peso, &grafo);
    grafo.NumArestas++;

    v1 = 2; v2 = 4; peso = 6;
    InsereAresta(&v1, &v2, &peso, &grafo); InsereAresta(&v2, &v1, &peso, &grafo);
    grafo.NumArestas++;

    v1 = 2; v2 = 6; peso = 8;
    InsereAresta(&v1, &v2, &peso, &grafo); InsereAresta(&v2, &v1, &peso, &grafo);
    grafo.NumArestas++;

    v1 = 1; v2 = 3; peso = 4;
    InsereAresta(&v1, &v2, &peso, &grafo); InsereAresta(&v2, &v1, &peso, &grafo);
    grafo.NumArestas++;

    v1 = 1; v2 = 4; peso = 5;
    InsereAresta(&v1, &v2, &peso, &grafo); InsereAresta(&v2, &v1, &peso, &grafo);
    grafo.NumArestas++;

    v1 = 1; v2 = 3; peso = 4;
    InsereAresta(&v1, &v2, &peso, &grafo); InsereAresta(&v2, &v1, &peso, &grafo);
    grafo.NumArestas++;

    v1 = 3; v2 = 4; peso = 7;
    InsereAresta(&v1, &v2, &peso, &grafo); InsereAresta(&v2, &v1, &peso, &grafo);
    grafo.NumArestas++;

    v1 = 3; v2 = 5; peso = 8;
    InsereAresta(&v1, &v2, &peso, &grafo); InsereAresta(&v2, &v1, &peso, &grafo);
    grafo.NumArestas++;

    v1 = 4; v2 = 5; peso = 9;
    InsereAresta(&v1, &v2, &peso, &grafo); InsereAresta(&v2, &v1, &peso, &grafo);
    grafo.NumArestas++;

    v1 = 5; v2 = 6; peso = 11;
    InsereAresta(&v1, &v2, &peso, &grafo); InsereAresta(&v2, &v1, &peso, &grafo);
    grafo.NumArestas++;

    v1 = 5; v2 = 7; peso = 12;
    InsereAresta(&v1, &v2, &peso, &grafo); InsereAresta(&v2, &v1, &peso, &grafo);
    grafo.NumArestas++;

    v1 = 6; v2 = 7; peso = 13;
    InsereAresta(&v1, &v2, &peso, &grafo); InsereAresta(&v2, &v1, &peso, &grafo);
    grafo.NumArestas++;
  } else {
    printf("\nEste grafo terá 30 vertices e todos estarão conectados por arestas\n\n");

    nVertices = 30;
    grafo.NumVertices = nVertices;
    grafo.NumArestas = VAZIO;
    FGVazio(&grafo);

    int i, j;

    for (i=0; i < nVertices - 1;i++) {
      for (j=i+1; j< nVertices; j++) {
        v1 = i; v2 = j; peso = 1;
        InsereAresta(&v1, &v2, &peso, &grafo); InsereAresta(&v2, &v1, &peso, &grafo);
        grafo.NumArestas++;
      }
    }
  }

  return grafo;
}
