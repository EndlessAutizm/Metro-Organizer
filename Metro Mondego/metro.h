#ifndef METRO_H
#define METRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_PARAGENS 100
#define MAX_LINHAS 50
#define MAX_PARAGENS_LINHA 50

typedef struct {
    char nome[50];
    char codigo[5];
} Paragem;

typedef struct No {
    Paragem paragem;
    struct No *proximo;
} No;

typedef struct {
    char nome[50];
    No *paragens;
} Linha;



// Função para adicionar uma nova paragem ao array de paragens
void adicionarParagem(Paragem *paragens, int *numParagens);


// Função para remover uma paragem do array de paragens
void removerParagem(Paragem *paragens, int *numParagens);


// Função para visualizar todas as paragens do array de paragens
void visualizarParagens(Paragem *paragens, int numParagens);


// Função para adicionar uma nova linha ao array de linhas
void adicionarLinha(Linha *linhas, int *numLinhas, Paragem *paragens, int numParagens);


// Função para atualizar uma linha existente no array de linhas
void atualizarLinha(Linha *linhas, int numLinhas, Paragem *paragens, int numParagens);


// Função para visualizar todas as linhas do array de linhas
void visualizarLinhas(Linha *linhas, int numLinhas);


// Função para eliminar uma linha do array de linhas
void eliminarLinha(Linha *linhas, int *numLinhas);


// Função para calcular os percursos com base nas linhas e paragens fornecidas
void calcularPercursos(Linha *linhas, int numLinhas, Paragem *paragens, int numParagens);


// Função para guardar todas as informações presentes nos arrays de linhas e paragens em um arquivo binário
void guardarInformacao(Linha *linhas, int numLinhas, Paragem *paragens, int numParagens);


// Função para carregar as informações de um arquivo binário para os arrays de linhas e paragens
void carregarInformacao(Linha *linhas, int *numLinhas, Paragem *paragens, int *numParagens);



#endif


