#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NUM_ESTADOS 26
#define NUM_RODOVIAS 43

typedef struct {
  char nome[2];
  int indice;
} Estado;

typedef struct {
  int estado_a;
  int estado_b;
  int indice;
} Rodovia;

void carregar_estados();
void carregar_rodovias();
Estado novo_estado(char nome[], int indice);
Rodovia nova_rodovia(int estado_a, int estado_b, int indice);

int main() {
  Estado estados[NUM_ESTADOS];
  Rodovia rodovias[NUM_RODOVIAS];
  carregar_estados(estados);
  carregar_rodovias(rodovias);

  // int i;
  //
  // for (i = 0; i < NUM_ESTADOS; i++) {
  //   printf("%s\n", estados[i].nome);
  // }
  //
  // for (i = 0; i < 44; i++) {
  //   printf("%s - %s - %d\n",
  //     estados[rodovias[i].estado_a].nome,
  //     estados[rodovias[i].estado_b].nome,
  //     rodovias[i].codigo
  //   );
  // }

  return 0;
}

Estado novo_estado(char nome[], int indice) {
  Estado novo;
  char *pointer = novo.nome;
  strcpy(pointer, nome);
  novo.indice = indice;
  return novo;
}

Rodovia nova_rodovia(int estado_a, int estado_b, int indice) {
  Rodovia nova;
  nova.estado_a = (estado_a > estado_b ? estado_b : estado_a);
  nova.estado_b = (estado_b > estado_a ? estado_a : estado_b);
  nova.indice = indice;
  return nova;
}

void carregar_estados(Estado estados[]) {
  int i = 0;
  estados[i++] = novo_estado("AC", 0);
  estados[i++] = novo_estado("AL", 1);
  estados[i++] = novo_estado("AM", 2);
  estados[i++] = novo_estado("AP", 3);
  estados[i++] = novo_estado("BA", 4);
  estados[i++] = novo_estado("CE", 5);
  estados[i++] = novo_estado("ES", 6);
  estados[i++] = novo_estado("GO", 7);
  estados[i++] = novo_estado("MA", 8);
  estados[i++] = novo_estado("MG", 9);
  estados[i++] = novo_estado("MS", 10);
  estados[i++] = novo_estado("MT", 11);
  estados[i++] = novo_estado("PA", 12);
  estados[i++] = novo_estado("PB", 13);
  estados[i++] = novo_estado("PE", 14);
  estados[i++] = novo_estado("PI", 15);
  estados[i++] = novo_estado("PR", 16);
  estados[i++] = novo_estado("RJ", 17);
  estados[i++] = novo_estado("RN", 18);
  estados[i++] = novo_estado("RO", 19);
  estados[i++] = novo_estado("RR", 20);
  estados[i++] = novo_estado("RS", 21);
  estados[i++] = novo_estado("SC", 22);
  estados[i++] = novo_estado("SE", 23);
  estados[i++] = novo_estado("SP", 24);
  estados[i++] = novo_estado("TO", 25);
}

void carregar_rodovias(Rodovia rodovias[]) {
  int i = 0;
  rodovias[i++] = nova_rodovia(21, 22, 0);
  rodovias[i++] = nova_rodovia(22, 16, 1);
  rodovias[i++] = nova_rodovia(16, 10, 2);
  rodovias[i++] = nova_rodovia(16, 24, 3);
  rodovias[i++] = nova_rodovia(24, 10, 4);
  rodovias[i++] = nova_rodovia(24, 9, 5);
  rodovias[i++] = nova_rodovia(24, 17, 6);
  rodovias[i++] = nova_rodovia(17, 9, 7);
  rodovias[i++] = nova_rodovia(17, 6, 8);
  rodovias[i++] = nova_rodovia(9, 10, 9);
  rodovias[i++] = nova_rodovia(9, 6, 10);
  rodovias[i++] = nova_rodovia(9, 4, 11);
  rodovias[i++] = nova_rodovia(9, 7, 12);
  rodovias[i++] = nova_rodovia(7, 10, 13);
  rodovias[i++] = nova_rodovia(7, 11, 14);
  rodovias[i++] = nova_rodovia(10, 11, 15);
  rodovias[i++] = nova_rodovia(7, 25, 16);
  rodovias[i++] = nova_rodovia(7, 4, 17);
  rodovias[i++] = nova_rodovia(11, 25, 18);
  rodovias[i++] = nova_rodovia(11, 12, 19);
  rodovias[i++] = nova_rodovia(11, 19, 20);
  rodovias[i++] = nova_rodovia(19, 0, 21);
  rodovias[i++] = nova_rodovia(19, 2, 22);
  rodovias[i++] = nova_rodovia(2, 20, 23);
  rodovias[i++] = nova_rodovia(2, 12, 24);
  rodovias[i++] = nova_rodovia(12, 3, 25);
  rodovias[i++] = nova_rodovia(12, 8, 26);
  rodovias[i++] = nova_rodovia(12, 25, 27);
  rodovias[i++] = nova_rodovia(8, 25, 28);
  rodovias[i++] = nova_rodovia(8, 15, 29);
  rodovias[i++] = nova_rodovia(25, 4, 30);
  rodovias[i++] = nova_rodovia(15, 4, 31);
  rodovias[i++] = nova_rodovia(15, 5, 32);
  rodovias[i++] = nova_rodovia(15, 14, 33);
  rodovias[i++] = nova_rodovia(5, 14, 34);
  rodovias[i++] = nova_rodovia(5, 13, 35);
  rodovias[i++] = nova_rodovia(5, 18, 36);
  rodovias[i++] = nova_rodovia(18, 13, 37);
  rodovias[i++] = nova_rodovia(13, 14, 38);
  rodovias[i++] = nova_rodovia(14, 1, 39);
  rodovias[i++] = nova_rodovia(14, 4, 40);
  rodovias[i++] = nova_rodovia(1, 23, 41);
  rodovias[i++] = nova_rodovia(23, 4, 42);
  rodovias[i++] = nova_rodovia(4, 6, 43);
}
