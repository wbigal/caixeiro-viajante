# Problema do Caixeiro Viajante

Este programa tenta resolver o *Problema do Caixeiro Viajante (PCV)* utilizando as técnicas da programação dinâmica. O algoritmo utilizado é bem simples e não atende a todos os requisitos para uma real solução para o PCV (não encontra o melhor caminho, por exemplo). O programa consegue resolver alguns grafos simples *Hamiltonianos*.

## Solução
O programa consegue resolver grafos simples utilizando um algoritmo de Busca em Profundidade.

Os passos para traçar o caminho para o caixeiro viajante são:

1) Representar o grafo em uma matriz bidimensional *VxV*;

2) Fazer uma busca em profundidade, onde cada vértice percorrido recebe uma cor:
 - Vértices nunca percorridos recebem a cor branca;
 - Vértices descobertos pela primeira vez recebem a cor cinza;
 - Quando o vértice esta mapeado, recebe a cor preta.

3) Definir o caminho que o Caixeiro Viajante deve percorrer.

O algoritmo resolve cada vértice, utilizando matrizes e vetores para auxiliar no cálculo do resultado final. No final da execução do algoritmo, temos um vetor Caminho já ordenado com a sequência correta de vértices que o Caixeiro Viajante deve visitar.

## Complexidade

A complexidade do algoritmo de busca em profundidade é de **O(|A| + |V|)**, para o grafo **G(V, A)**. Então, dado um grafo G(V, A) representado em uma matriz *VxV*, o algoritmo é capaz de definir uma rota com complexidade **O(|A| + |V|)**.

Para encontrar o melhor caminho (o que este programa não tenta fazer), seria necessário percorrer todos os vértices do grafo partindo de todos os vértices do grafo. Isso teria complexidade *O(|V|!)*.
