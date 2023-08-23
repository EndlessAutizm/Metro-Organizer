#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metro.h"





int main() {
    Paragem *paragens = (Paragem *)malloc(MAX_PARAGENS * sizeof(Paragem));
    int numParagens = 0;

    Linha *linhas = (Linha *)malloc(MAX_LINHAS * sizeof(Linha));
    int numLinhas = 0;

    char codigo[5];
    int opcao, opcaoP, opcaoL;


///////////////////MENUS////////////////  
    do {
        printf("\n--- Menu Principal ---\n\n");
        printf("1. Gerir Paragens\n");
        printf("2. Gerir Linhas\n");
        printf("3. Calcular Percursos\n");
        printf("4. Guardar Informação\n");
        printf("5. Carregar Informação\n");
        printf("0. Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                do {
                    printf("\n--- Menu Paragens ---\n\n");
                    printf("1. Adicionar Paragem\n");
                    printf("2. Remover Paragem\n");
                    printf("3. Visualizar Paragens\n");
                    printf("0. Voltar\n");
                    printf("\nEscolha uma opção: ");
                    scanf("%d", &opcaoP);

                    switch (opcaoP) {
                        case 1:
                            adicionarParagem(paragens, &numParagens);
                            break;
                        case 2:
                            removerParagem(paragens, &numParagens);
                            break;
                        case 3:
                            visualizarParagens(paragens, numParagens);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opção inválida. Tente novamente.\n");
                    }
                } while (opcaoP != 0);
                break;
            case 2:
                do {
                    printf("\n--- Menu Linhas ---\n\n");
                    printf("1. Adicionar Linha\n");
                    printf("2. Atualizar Linha\n");
                    printf("3. Visualizar Linhas\n");
                    printf("4. Eliminar Linha\n");
                    printf("0. Voltar\n");
                    printf("\nEscolha uma opção: ");
                    scanf("%d", &opcaoL);

                    switch (opcaoL) {
                        case 1:
                            adicionarLinha(linhas, &numLinhas, paragens, numParagens);
                            break;
                        case 2:
                            atualizarLinha(linhas, numLinhas, paragens, numParagens);
                            break;
                        case 3:
                            visualizarLinhas(linhas, numLinhas);
                            break;
                        case 4:
                            eliminarLinha(linhas, &numLinhas);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opção inválida. Tente novamente.\n");
                    }
                } while (opcaoL != 0);
                break;
            case 3:
                calcularPercursos(linhas, numLinhas, paragens, numParagens);
                break;
            case 4:
                guardarInformacao(linhas, numLinhas, paragens, numParagens);
                break;
            case 5:
                carregarInformacao(linhas, &numLinhas, paragens, &numParagens);
                break;
            case 0:
                printf("\n###--Saindo--###\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

  
/////////////////CODIGOS FINAIS////////////    
  free(paragens);
  free(linhas);
return 0;
}
