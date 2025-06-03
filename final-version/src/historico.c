// historico.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/historico.h"

void telaGerenciarHistorico () {
    int opcao;
    do {
        system("cls || clear");
        printf("+==============================================================================+\n");
        printf("|                               -= HISTORICO =-                                |\n");
        printf("+==============================================================================+\n");
        printf("| 1. Pesquisar por Data                                                        |\n");
        printf("| 2. Pesquisar por Nome do Jogador                                             |\n");
        printf("| 3. Pesquisar por ID da Partida                                               |\n");
        printf("| 0. Voltar ao menu anterior                                                   |\n");
        printf("+------------------------------------------------------------------------------+\n");
        printf("| Escolha uma opcao:                                                           |\n");
        printf("+==============================================================================+\n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                pesquisarPorData();
                break;
            case 2:
                pesquisarPorNome();
                break;
            case 3:
                pesquisarPorID();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida. Tente novamente. \n");
        }

        printf("\nPressione Enter para continuar...");
        getchar();
        // while ((opcao = getchar()) != '\n' && opcao != EOF);

    } while (opcao != 0);
}

void strToLower(char *str) { // funcao para converter maiusculas e minusculas na pesquisa do nome. agora aceita tanto Gustavo, gustavo ou GUSTavO por exemplo
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void carregarHistorico(Historico **historicos, int *total) {
    FILE *arquivo = fopen("historico.txt", "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo.txt.\n");
        *historicos = NULL;
        *total = 0;
        return;
    }

    int linhas = 0; //contar as linhas, inicializando com zero
    char buffer[MAX_LINHA];
    while (fgets(buffer, MAX_LINHA, arquivo)) {
        if (strlen(buffer) > 1) {
        linhas++;
        }
    }
    rewind(arquivo);

    *historicos = (Historico*) malloc(linhas * sizeof(Historico));
    if(!(*historicos)) {
        printf("Erro ao alocar memoria.\n");
        fclose(arquivo);
        return;
    }
    *total = 0;

    while (fgets(buffer, MAX_LINHA, arquivo)) {
        sscanf(buffer, "%d;%[^;];%[^;];%d",
               &(*historicos)[*total].id,
               (*historicos)[*total].nome,
               (*historicos)[*total].data,
               &(*historicos)[*total].pontuacao);

        (*historicos)[*total].data[strcspn((*historicos)[*total].data, "\n\r")] = '\0';
        (*total)++;
    }

    fclose(arquivo);
}

void liberarHistorico(Historico *historicos) {
    free(historicos);
}

void pesquisarPorData() {
    Historico *historicos;
    int total;
    char data[MAX_DATA];

    carregarHistorico(&historicos, &total); //caso nao exista nenhum dado historico carregado
    if (!historicos || total == 0) {
        printf("Nenhum dado historico carregado.\n");
        return;
    }

    printf("\nDigite a data (DDMMAAAA ou DD/MM/AAAA): ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n\r")] = '\0';  // remove o \n

    // padroniza a entrada (adiciona zeros se necessario)
    char dataFormatada[MAX_DATA];
    if (strlen(data) == 8) {
        // adiciona as barras(DD/MM/AAAA)
        sprintf(dataFormatada, "%c%c/%c%c/%c%c%c%c",
                data[0], data[1], data[2], data[3],
                data[4], data[5], data[6], data[7]);
    } else if (strlen(data) == 10 && data[2] == '/' && data[5] == '/') {
        strcpy(dataFormatada, data);
        dataFormatada[strcspn(dataFormatada, "\n\r")] = '\0';
    } else {
        printf("Formato de data invalido! Use DDMMAAAA\n");
        liberarHistorico(historicos);
        return;
    }

    printf("\n=== RESULTADOS PARA %s ===\n", dataFormatada);
    int encontrados = 0;

    for (int i = 0; i < total; i++) {
        // compara apenas a parte da data
        if (strcmp(historicos[i].data, dataFormatada) == 0) {
            printf("ID: %d | Nome: %s | Pontuacao: %d\n",
                   historicos[i].id, historicos[i].nome, 
                   historicos[i].pontuacao);
            encontrados++;
        }
    }

    if (!encontrados) {
        printf("-= Nenhum registro encontrado para %s =-\n", dataFormatada);
        printf("Dica: Verifique se usou o formato DDMMAAAA\n");
    }

    liberarHistorico(historicos);
}

void pesquisarPorNome() {
    Historico *historicos;
    int total;
    char nome[MAX_NOME], nomeBusca[MAX_NOME]; //a partir de agora a logica segue o mesmo principio da pesquisaPorData

    carregarHistorico(&historicos, &total);
    if (!historicos || total == 0) {
        printf("Nenhum dado historico carregado.\n");
        return;
        }

    printf("\nDigite o nome do jogador: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("\n=== RESULTADOS PARA %s ===\n", nome);
    int encontrados = 0;

    strcpy(nomeBusca, nome);
    strToLower(nomeBusca);

    for (int j = 0; j < total; j++) {
        char nomeComparado[MAX_NOME];
        strcpy(nomeComparado, historicos[j].nome);
        strToLower(nomeComparado);
        
        if (strstr(nomeComparado, nomeBusca) != NULL) {
            printf("ID: %d | Data: %s | Pontuacao: %d\n",
                   historicos[j].id, historicos[j].data, historicos[j].pontuacao);
            encontrados++;
        }
    }

    if (!encontrados) {
        printf("-= Nenhum registro encontrado para este nome =-\n");
    }

    liberarHistorico(historicos);
}

void pesquisarPorID() {
    Historico *historicos;
    int total, id;

    carregarHistorico(&historicos, &total);
    if (!historicos) return;

    printf("\nDigite o ID da partida: ");
    scanf("%d", &id);
    getchar();

    printf("\n=== RESULTADOS PARA ID %d ===\n", id);
    int encontrado = 0;

    for (int k = 0; k < total; k++) {
        if (historicos[k].id == id) {
            printf("Nome: %s | Data: %s | Pontuacao: %d\n",
                   historicos[k].nome, historicos[k].data, historicos[k].pontuacao);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("-= Nenhum registro encontrado com este ID =-\n");
    }

    liberarHistorico(historicos);
}
