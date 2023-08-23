#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metro.h"



////////////FUNÇOES DE PARAGEM/////////////

void adicionarParagem(Paragem *paragens, int *numParagens) 
{
    if (*numParagens >= MAX_PARAGENS) {
        printf("Limite de paragens atingido. Impossível adicionar mais paragens.\n");
        return;
    }
    printf("\n--Dados da nova Paragem--\n");
    Paragem novaParagem;
    printf("Nome da paragem: ");
    scanf("%s", novaParagem.nome);
    printf("Código da paragem: ");
    scanf("%s", novaParagem.codigo);

    paragens[*numParagens] = novaParagem;
    (*numParagens)++;

    printf("\nParagem registada com sucesso!\n");
}

void removerParagem(Paragem *paragens, int *numParagens) 
{
    char codigo[5];
    printf("Insira o código da paragem a ser removida: ");
    scanf("%s", codigo);

    int indice = -1;
    for (int i = 0; i < *numParagens; i++) {
        if (strcmp(paragens[i].codigo, codigo) == 0) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        for (int i = indice; i < *numParagens - 1; i++) {
            paragens[i] = paragens[i + 1];
        }
        (*numParagens)--;
        printf("Paragem removida com sucesso!\n");
    } else {
        printf("Paragem não encontrada.\n");
    }
}

void visualizarParagens(Paragem *paragens, int numParagens) 
{
    if (numParagens == 0) {
        printf("\n--Nenhuma paragem cadastrada--\n");
        return;
    }

    printf("--- Paragens Cadastradas ---\n");
    for (int i = 0; i < numParagens; i++) {
        printf("-----//-----\n");
        printf("Nome: %s\n", paragens[i].nome);
        printf("Código: %s\n", paragens[i].codigo);
        printf("\n");
    }
    printf("-----//-----\n");
}

///////////////funções de linha/////////////////////

void adicionarParagemLinha(Linha *linha, Paragem *paragens, int numParagens)
{
    // Exibir paragens disponíveis para seleção
    printf("--- Paragens Disponíveis ---\n");
    for (int i = 0; i < numParagens; i++)
    {
        printf("%d. %s\n", i + 1, paragens[i].nome);
    }

    // Solicitar a paragem a ser adicionada
    int paragemSelecionada;
    printf("Selecione o número da paragem a ser adicionada: ");
    scanf("%d", &paragemSelecionada);

    // Verificar se o número da paragem selecionada é válido
    if (paragemSelecionada < 1 || paragemSelecionada > numParagens)
    {
        printf("Número de paragem inválido.\n");
        return;
    }

    // Índice da paragem selecionada no array de paragens
    int indiceParagem = paragemSelecionada - 1;

    // Verificar se a paragem já existe na linha
    No *atual = linha->paragens;
    while (atual != NULL)
    {
        if (strcmp(atual->paragem.nome, paragens[indiceParagem].nome) == 0)
        {
            printf("A paragem já existe na linha.\n");
            return;
        }
        atual = atual->proximo;
    }

    // Criar um novo nó para a paragem selecionada
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->paragem = paragens[indiceParagem];
    novoNo->proximo = NULL;

    // Verificar se a linha está vazia
    if (linha->paragens == NULL)
    {
        linha->paragens = novoNo;
    }
    else
    {
        // Encontrar o último nó da linha
        atual = linha->paragens;
        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }
        // Adicionar o novo nó ao final da linha
        atual->proximo = novoNo;
    }

    printf("Paragem adicionada com sucesso à linha %s.\n", linha->nome);
}

void removerParagemLinha(Linha *linha)
{
    // Verificar se a linha está vazia
    if (linha->paragens == NULL)
    {
        printf("A linha está vazia.\n");
        return;
    }

    // Exibir as paragens da linha para seleção
    printf("--- Paragens da Linha %s ---\n", linha->nome);
    No *atual = linha->paragens;
    int contador = 1;
    while (atual != NULL)
    {
        printf("%d. %s\n", contador, atual->paragem.nome);
        atual = atual->proximo;
        contador++;
    }

    // Solicitar a paragem a ser removida
    int paragemSelecionada;
    printf("Selecione o número da paragem a ser removida: ");
    scanf("%d", &paragemSelecionada);

    // Verificar se o número da paragem selecionada é válido
    if (paragemSelecionada < 1 || paragemSelecionada >= contador)
    {
        printf("Número de paragem inválido.\n");
        return;
    }

    // Remover a paragem da linha
    if (paragemSelecionada == 1)
    {
        // Remover a primeira paragem
        No *temp = linha->paragens;
        linha->paragens = linha->paragens->proximo;
        free(temp);
    }
    else
    {
        // Encontrar o nó anterior à paragem a ser removida
        atual = linha->paragens;
        No *anterior;
        int indice = 1;
        while (indice < paragemSelecionada && atual != NULL)
        {
            anterior = atual;
            atual = atual->proximo;
            indice++;
        }

        // Verificar se a paragem foi encontrada
        if (atual == NULL)
        {
            printf("Paragem não encontrada.\n");
            return;
        }

        // Remover o nó da paragem
        anterior->proximo = atual->proximo;
        free(atual);
    }

    printf("Paragem removida com sucesso da linha %s.\n", linha->nome);
}

void adicionarLinha(Linha* linhas, int* numLinhas, Paragem* paragens, int numParagens) 
{
    if (*numLinhas >= MAX_LINHAS) {
        printf("Limite máximo de linhas atingido.\n");
        return;
    }

    Linha novaLinha;
    printf("Nome da linha: ");
    scanf("%s", novaLinha.nome);

    int numParagensLinha;
    printf("Número de paragens da linha: ");
    scanf("%d", &numParagensLinha);

    if (numParagensLinha <= 0 || numParagensLinha > MAX_PARAGENS_LINHA) {
        printf("Número inválido de paragens.\n");
        return;
    }

    novaLinha.paragens = NULL;  // Inicializa a lista encadeada com NULL

    for (int i = 0; i < numParagensLinha; i++) {
        char codigo[5];
        printf("Código da paragem %d: ", i + 1);
        scanf("%s", codigo);

        int indiceParagem = -1;
        for (int j = 0; j < numParagens; j++) {
            if (strcmp(paragens[j].codigo, codigo) == 0) {
                indiceParagem = j;
                break;
            }
        }

        if (indiceParagem == -1) {
            printf("Paragem com código %s não encontrada.\n", codigo);
            // Liberar a memória alocada para as paragens da linha
            No* atual = novaLinha.paragens;
            while (atual != NULL) {
                No* proximo = atual->proximo;
                free(atual);
                atual = proximo;
            }
            return;
        }

        // Criar um novo nó para a paragem e adicioná-lo à lista encadeada
        No* novoNo = (No*)malloc(sizeof(No));
        novoNo->paragem = paragens[indiceParagem];
        novoNo->proximo = NULL;

        if (novaLinha.paragens == NULL) {
            novaLinha.paragens = novoNo;
        } else {
            // Encontrar o último nó da lista encadeada e adicionar o novo nó a ele
            No* ultimo = novaLinha.paragens;
            while (ultimo->proximo != NULL) {
                ultimo = ultimo->proximo;
            }
            ultimo->proximo = novoNo;
        }
    }

    linhas[*numLinhas] = novaLinha;
    (*numLinhas)++;
    printf("\nLinha adicionada com sucesso!\n");
}

void atualizarLinha(Linha *linhas, int numLinhas, Paragem *paragens, int numParagens)
{
    // Verificar se existem linhas disponíveis
    if (numLinhas == 0)
    {
        printf("Nenhuma linha cadastrada.\n");
        return;
    }

    // Exibir linhas disponíveis
    printf("--- Linhas Disponíveis ---\n");
    for (int i = 0; i < numLinhas; i++)
    {
        printf("%d. %s\n", i + 1, linhas[i].nome);
    }

    // Solicitar o número da linha a ser atualizada
    int linhaSelecionada;
    printf("Selecione o número da linha a ser atualizada: ");
    scanf("%d", &linhaSelecionada);

    // Verificar se o número da linha selecionada é válido
    if (linhaSelecionada < 1 || linhaSelecionada > numLinhas)
    {
        printf("Número de linha inválido.\n");
        return;
    }

    // Índice da linha selecionada no array de linhas
    int indiceLinha = linhaSelecionada - 1;

    // Exibir as paragens da linha selecionada
    printf("--- Paragens da Linha %s ---\n\n", linhas[indiceLinha].nome);
    No *atual = linhas[indiceLinha].paragens;
    int contador = 1;
    while (atual != NULL)
    {
        printf("%d. %s\n", contador, atual->paragem.nome);
        atual = atual->proximo;
        contador++;
    }

    // Solicitar ação ao usuário (adicionar ou remover paragens)
    int opcao;
    printf("Selecione uma opção:\n");
    printf("1. Adicionar paragem\n");
    printf("2. Remover paragem\n");
    printf("0. Cancelar\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        // Adicionar paragem à linha selecionada
        adicionarParagemLinha(&linhas[indiceLinha], paragens, numParagens);
        break;
    case 2:
        // Remover paragem da linha selecionada
        removerParagemLinha(&linhas[indiceLinha]);
        break;
    case 0:
        // Cancelar ação
        printf("Ação cancelada.\n");
        break;
    default:
        printf("Opção inválida.\n");
        break;
    }
}

void visualizarLinhas(Linha* linhas, int numLinhas) 
{
    printf("\n--- Linhas ---\n\n");

    for (int i = 0; i < numLinhas; i++) {
        printf("Linha %d:\n", i + 1);
        printf("Nome: %s\n", linhas[i].nome);
        
        printf("Paragens:\n");
        No* atual = linhas[i].paragens;
        
        while (atual != NULL) {
            printf("- %s\n", atual->paragem.nome);
            atual = atual->proximo;
        }
        
        printf("\n");
    }
}

void eliminarLinha(Linha *linhas, int *numLinhas)
{
    // Verificar se existem linhas
    if (*numLinhas == 0)
    {
        printf("Não há linhas para eliminar.\n");
        return;
    }

    printf("--- Linhas Disponíveis ---\n");

    // Exibir o menu das linhas
    for (int i = 0; i < *numLinhas; i++)
    {
        printf("%d. %s\n", i + 1, linhas[i].nome);
    }

    int opcao;
    printf("Escolha o número da linha que deseja eliminar (0 para cancelar): ");
    scanf("%d", &opcao);

    // Verificar a opção escolhida
    if (opcao == 0)
    {
        printf("Operação cancelada.\n");
        return;
    }
    else if (opcao < 1 || opcao > *numLinhas)
    {
        printf("Opção inválida.\n");
        return;
    }

    // Índice da linha a ser eliminada
    int indice = opcao - 1;

    // Guardar o nome da linha a ser eliminada antes de removê-la
    char nomeLinhaRemovida[50];
    strcpy(nomeLinhaRemovida, linhas[indice].nome);

    // Deslocar as linhas restantes para preencher o espaço vazio
    for (int i = indice; i < *numLinhas - 1; i++)
    {
        linhas[i] = linhas[i + 1];
    }

    // Reduzir o número de linhas
    (*numLinhas)--;

    printf("A linha %s foi eliminada com sucesso.\n", nomeLinhaRemovida);
}


void calcularPercursos(Linha *linhas, int numLinhas, Paragem *paragens, int numParagens)
{
    char partida[50];
    char chegada[50];
    char linhaPartida[50], linhaChegada[50];
    int encontrouPartida = 0;

    printf("Ponto de partida: ");
    scanf("%s", partida);

    printf("Ponto de chegada: ");
    scanf("%s", chegada);

    // Encontrar a linha da partida
    for (int i = 0; i < numLinhas; i++) {
        No *atual = linhas[i].paragens;

        while (atual != NULL) {
            if (strcmp(atual->paragem.nome, partida) == 0) {
                strcpy(linhaPartida, linhas[i].nome);
                break;
            }
            atual = atual->proximo;
        }
        if (atual != NULL) {
            break;
        }
    }

    // Encontrar a linha da chegada
    for (int i = 0; i < numLinhas; i++) {
        No *atual = linhas[i].paragens;

        while (atual != NULL) {
            if (strcmp(atual->paragem.nome, chegada) == 0) {
                strcpy(linhaChegada, linhas[i].nome);
                break;
            }
            atual = atual->proximo;
        }
        if (atual != NULL) {
            break;
        }
    }

    // Verificar se há uma mudança de linha possível
    int conexaoEncontrada = 0;
    char linhaConexao[50];
    for (int i = 0; i < numLinhas; i++) {
        No *atual = linhas[i].paragens;

        while (atual != NULL) {
            if (strcmp(atual->paragem.nome, partida) == 0 && strcmp(atual->proximo->paragem.nome, chegada) != 0) {
                strcpy(linhaConexao, linhas[i].nome);
                conexaoEncontrada = 1;
                break;
            }
            atual = atual->proximo;
        }

        if (conexaoEncontrada) {
            break;
        }
    }

    // Percurso se as paragens forem da mesma linha
    if (strcmp(linhaPartida, linhaChegada) == 0) {
        printf("\nPercurso (Linha %s):\n", linhaPartida);

        for (int i = 0; i < numLinhas; i++) {
            if (strcmp(linhas[i].nome, linhaPartida) == 0) {
                No *atual = linhas[i].paragens;

                while (atual != NULL && strcmp(atual->paragem.nome, partida) != 0) {
                    atual = atual->proximo;
                }

                printf("%s", atual->paragem.nome);

                while (atual != NULL && strcmp(atual->paragem.nome, chegada) != 0) {
                    atual = atual->proximo;
                    printf(" --> %s", atual->paragem.nome);
                }

                break;
            }
        }
    }
    else if (conexaoEncontrada) { // Percurso com uma mudança de linha
        printf("\nPercurso com uma mudanca de linha:\n");

        for (int i = 0; i < numLinhas; i++) {
            if (strcmp(linhas[i].nome, linhaPartida) == 0) {
                No *atual = linhas[i].paragens;

                printf("\nLinha %s:\n", linhaPartida);
                while (atual != NULL && strcmp(atual->paragem.nome, partida) != 0) {
                    printf("%s --> ", atual->paragem.nome);
                    atual = atual->proximo;
                }
                printf("%s", atual->paragem.nome);

                break;
            }
        }

        printf("\n\nMudanca de linha na paragem %s\n\n", partida);

        for (int i = 0; i < numLinhas; i++) {
            if (strcmp(linhas[i].nome, linhaConexao) == 0) {
                No *atual = linhas[i].paragens;

                printf("Linha %s:\n", linhaConexao);
                while (atual != NULL && strcmp(atual->paragem.nome, chegada) != 0) {
                    printf("%s --> ", atual->paragem.nome);
                    atual = atual->proximo;
                }
                printf("%s", atual->paragem.nome);

                break;
            }
        }
    }
    else {
        printf("\nNao existe conexao direta entre as linhas.\n");
    }

    printf("\n\n");
}


void guardarInformacao(Linha *linhas, int numLinhas, Paragem *paragens, int numParagens) {
    FILE* arquivo = fopen("informacao.txt", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Escreve o número de linhas e o número de paragens no arquivo
    fwrite(&numLinhas, sizeof(int), 1, arquivo);
    fwrite(&numParagens, sizeof(int), 1, arquivo);

    // Escreve os dados das linhas no arquivo
    fwrite(linhas, sizeof(Linha), numLinhas, arquivo);

    // Escreve os dados das paragens no arquivo
    fwrite(paragens, sizeof(Paragem), numParagens, arquivo);

    fclose(arquivo);
}

void carregarInformacao(Linha *linhas, int *numLinhas, Paragem *paragens, int *numParagens) {
    FILE* arquivo = fopen("informacao.txt", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Lê o número de linhas e o número de paragens do arquivo
    fread(numLinhas, sizeof(int), 1, arquivo);
    fread(numParagens, sizeof(int), 1, arquivo);

    // Lê os dados das linhas do arquivo
    fread(linhas, sizeof(Linha), *numLinhas, arquivo);

    // Lê os dados das paragens do arquivo
    fread(paragens, sizeof(Paragem), *numParagens, arquivo);

    fclose(arquivo);
}