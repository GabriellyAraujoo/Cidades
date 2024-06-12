#include "cidades.h"
#include <stdio.h>

int main() {
  // Nome do arquivo de teste
  const char *nomeArquivo = "teste01.txt";

  // Inicializar estrada e imprimir dados
  Estrada *estrada = getEstrada(nomeArquivo);
  if (estrada) {
    printf("Estrada: Comprimento = %d, Número de cidades = %d\n", estrada->T,
           estrada->N);
    for (int i = 0; i < estrada->N; i++) {
      printf("Cidade %d: %s na posição %d\n", i + 1, estrada->C[i].Nome,
             estrada->C[i].Posicao);
    }

    // Calcular e imprimir a menor vizinhança
    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
    printf("Menor Vizinhança: %.2f\n", menorVizinhanca);

    // Encontrar e imprimir a cidade com a menor vizinhança
    char *cidade = cidadeMenorVizinhanca(nomeArquivo);
    printf("Cidade com Menor Vizinhança: %s\n", cidade);

    free(cidade);
    free(estrada->C);
    free(estrada);
  } else {
    printf("Erro ao inicializar a estrada.\n");
  }

  return 0;
}
