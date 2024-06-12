 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

// Funções de Cidades
Estrada *getEstrada(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return NULL;
    }
    printf("Arquivo %s aberto com sucesso.\n", nomeArquivo);

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (!estrada) {
        printf("Erro ao alocar memória para estrada\n");
        fclose(file);
        return NULL;
    }

    int result;
    
    // Depuração: Tentativa de ler o comprimento da estrada
    result = fscanf(file, "%d", &(estrada->T));
    printf("Resultado da leitura do comprimento da estrada: %d, Valor lido: %d\n", result, estrada->T);
    if (result != 1) {
        printf("Erro ao ler o comprimento da estrada\n");
        free(estrada);
        fclose(file);
        return NULL;
    }

    // Depuração: Tentativa de ler o número de cidades
    result = fscanf(file, "%d", &(estrada->N));
    printf("Resultado da leitura do número de cidades: %d, Valor lido: %d\n", result, estrada->N);
    if (result != 1) {
        printf("Erro ao ler o número de cidades\n");
        free(estrada);
        fclose(file);
        return NULL;
    }

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C) {
        printf("Erro ao alocar memória para cidades\n");
        free(estrada);
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        // Depuração: Tentativa de ler os dados da cidade
        result = fscanf(file, "%d %255s", &(estrada->C[i].Posicao), estrada->C[i].Nome);
        printf("Resultado da leitura da cidade %d: %d, Valores lidos: %d, %s\n", i + 1, result, estrada->C[i].Posicao, estrada->C[i].Nome);
        if (result != 2) {
            printf("Erro ao ler os dados da cidade %d\n", i + 1);
            free(estrada->C);
            free(estrada);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);
    return estrada;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) {
        return -1;
    }

    double menorVizinhanca = estrada->T;
    for (int i = 0; i < estrada->N - 1; i++) {
        double vizinhanca = (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
        printf("Vizinhança entre %s e %s: %.2f\n", estrada->C[i].Nome, estrada->C[i + 1].Nome, vizinhanca);
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) {
        return NULL;
    }

    double menorVizinhanca = estrada->T;
    int cidadeIndex = -1;
    for (int i = 0; i < estrada->N - 1; i++) {
        double vizinhanca = (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
        printf("Vizinhança entre %s e %s: %.2f\n", estrada->C[i].Nome, estrada->C[i + 1].Nome, vizinhanca);
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            cidadeIndex = i;
        }
    }

    char *nomeCidade = (char *)malloc(256 * sizeof(char));
    if (cidadeIndex != -1) {
        strcpy(nomeCidade, estrada->C[cidadeIndex].Nome);
    } else {
        strcpy(nomeCidade, "");
    }

    free(estrada->C);
    free(estrada);
    return nomeCidade;
}

// Função principal para testes
int main() {
    // Nome do arquivo de teste
    const char *nomeArquivo = "teste01.txt";

    // Inicializar estrada e imprimir dados
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada) {
        printf("Estrada: Comprimento = %d, Número de cidades = %d\n", estrada->T, estrada->N);
        for (int i = 0; i < estrada->N; i++) {
            printf("Cidade %d: %s na posição %d\n", i + 1, estrada->C[i].Nome, estrada->C[i].Posicao);
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
