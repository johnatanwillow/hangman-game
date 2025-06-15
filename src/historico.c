// historico.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#include "../include/historico.h"
#include "../include/interface.h"

void carregarHistorico(Historico **historicos, int *total) {
    FILE *arquivo = fopen("data/historico.txt", "r");
    if (!arquivo) {
        perror("Erro ao abrir o historico.txt.\n");
        *historicos = NULL;
        *total = 0;
        return;
    }

    char buffer[MAX_LINHA];
    // int linhas = contaLinhasHistorico();

    int linhas = 0; //contar as linhas, inicializando com zero
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
        sscanf(buffer, "%d|%[^|]|%[^|]|%d",
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

void pesquisarPorData(char data[]) {
    Historico *historicos;
    int total;
    char texto_data[150] = "";

    carregarHistorico(&historicos, &total); //caso nao exista nenhum dado historico carregado
    if (!historicos || total == 0) {
        semHistorico("Nenhum dado historico carregado.");
        return;
    }

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
        semHistorico("Formato de data invalido! Use DDMMAAAA ou DD/MM/AAAA");
        liberarHistorico(historicos);
        return;
    }

    int i = -1;
    int palavra_maior;
    int max_linhas = contaLinhasHistorico();
    char *nome_extraido;
    int pontuacao_extraida_int;
    char *data_extraida;
    char *pontuacao_extraida;
    int encontrados = 0;

    FILE *meta_dados_historico = fopen("data/meta_historico.txt", "r");

    fscanf(meta_dados_historico,"%d", &palavra_maior);

    do { 
        if(i == -1){
            nome_extraido = "NOME";
            pontuacao_extraida = "PONTOS";
            data_extraida = "DATA";
            printf("|   ID | %s ", nome_extraido);

            for(int j = 0 ; j < palavra_maior-strlen(nome_extraido);j++)//Comparo os tamnhos e coloco os espaços devidos
                printf(" ");
            printf("| %s ", pontuacao_extraida);
            printf("| %s", data_extraida);
            for(int j = 0 ; j < 63 - palavra_maior - strlen(pontuacao_extraida) - strlen(data_extraida);j++)
                printf(" ");//É so para n ter um textão de 51 espaços
            printf(" |\n");
            printf("+");
            for(int j = 0 ; j < palavra_maior+8;j++)
                printf("-");
            printf("-+");
            for(int j = 0;j < 68-palavra_maior;j++)
                printf("-");
            printf("+\n");
        } else if (strcmp(historicos[i].data, dataFormatada) == 0 && i > -1) {
            nome_extraido = historicos[i].nome;
            pontuacao_extraida_int = historicos[i].pontuacao;
            data_extraida = historicos[i].data;
            printf("| %4d | %s ", i+1, nome_extraido);

            for(int j = 0 ; j < palavra_maior-strlen(nome_extraido);j++)//Comparo os tamnhos e coloco os espaços devidos
                printf(" ");
            printf("| %6d ", pontuacao_extraida_int);
            printf("| %s", data_extraida);
            for(int j = 0 ; j < 63 - palavra_maior - 6 - strlen(data_extraida);j++)
                printf(" ");//É so para n ter um textão de 51 espaços
            printf(" |\n");
            printf("+");
            for(int j = 0 ; j < palavra_maior+8;j++)
                printf("-");
            printf("-+");
            for(int j = 0;j < 68-palavra_maior;j++)
                printf("-");
            printf("+\n");
            encontrados++;
        }

        i++;
    } while (i < max_linhas);

    if (!encontrados) {
        sprintf(texto_data, "Nenhum registro encontrado para a data %s", dataFormatada);
        semHistorico(texto_data);
    }

    liberarHistorico(historicos);
}

void pesquisarPorNome(char nome[]) {
    Historico *historicos;
    int total;
    char nomeComparado[MAX_NOME];

    carregarHistorico(&historicos, &total);
    if (!historicos || total == 0) {
        semHistorico("Nenhum dado historico carregado.");
        return;
    }

    int i = -1;
    int palavra_maior;
    int max_linhas = contaLinhasHistorico();
    char *nome_extraido;
    int pontuacao_extraida_int;
    char *data_extraida;
    char *pontuacao_extraida;
    int encontrados = 0;

    FILE *meta_dados_historico = fopen("data/meta_historico.txt", "r");

    fscanf(meta_dados_historico,"%d", &palavra_maior);

    do { 
        if (i > -1) {
            strcpy(nomeComparado, historicos[i].nome);
        }
        if(i == -1){
            nome_extraido = "NOME";
            pontuacao_extraida = "PONTOS";
            data_extraida = "DATA";
            printf("|   ID | %s ", nome_extraido);

            for(int j = 0 ; j < palavra_maior-strlen(nome_extraido);j++)//Comparo os tamnhos e coloco os espaços devidos
                printf(" ");
            printf("| %s ", pontuacao_extraida);
            printf("| %s", data_extraida);
            for(int j = 0 ; j < 63 - palavra_maior - strlen(pontuacao_extraida) - strlen(data_extraida);j++)
                printf(" ");//É so para n ter um textão de 51 espaços
            printf(" |\n");
            printf("+");
            for(int j = 0 ; j < palavra_maior+8;j++)
                printf("-");
            printf("-+");
            for(int j = 0;j < 68-palavra_maior;j++)
                printf("-");
            printf("+\n");
        } else if (strstr(nomeComparado, nome) != NULL && i > -1) {
            nome_extraido = historicos[i].nome;
            pontuacao_extraida_int = historicos[i].pontuacao;
            data_extraida = historicos[i].data;
            printf("| %4d | %s ", i+1, nome_extraido);

            for(int j = 0 ; j < palavra_maior-strlen(nome_extraido);j++)//Comparo os tamnhos e coloco os espaços devidos
                printf(" ");
            printf("| %6d ", pontuacao_extraida_int);
            printf("| %s", data_extraida);
            for(int j = 0 ; j < 63 - palavra_maior - 6 - strlen(data_extraida);j++)
                printf(" ");//É so para n ter um textão de 51 espaços
            printf(" |\n");
            printf("+");
            for(int j = 0 ; j < palavra_maior+8;j++)
                printf("-");
            printf("-+");
            for(int j = 0;j < 68-palavra_maior;j++)
                printf("-");
            printf("+\n");
            encontrados++;
        }

        i++;
    } while (i < max_linhas);

    if (!encontrados) {
        semHistorico("Nenhum registro encontrado para este nome");
    }

    liberarHistorico(historicos);
}

void pesquisarPorID(int id) {
    Historico *historicos;
    int total;

    carregarHistorico(&historicos, &total);
    if (!historicos) return;

    int i = -1;
    int palavra_maior;
    int max_linhas = contaLinhasHistorico();
    char *nome_extraido;
    int pontuacao_extraida_int;
    char *data_extraida;
    char *pontuacao_extraida;
    int encontrado = 0;

    FILE *meta_dados_historico = fopen("data/meta_historico.txt", "r");

    fscanf(meta_dados_historico,"%d", &palavra_maior);

    do { 
        if(i == -1){
            nome_extraido = "NOME";
            pontuacao_extraida = "PONTOS";
            data_extraida = "DATA";
            printf("|   ID | %s ", nome_extraido);

            for(int j = 0 ; j < palavra_maior-strlen(nome_extraido);j++)//Comparo os tamnhos e coloco os espaços devidos
                printf(" ");
            printf("| %s ", pontuacao_extraida);
            printf("| %s", data_extraida);
            for(int j = 0 ; j < 63 - palavra_maior - strlen(pontuacao_extraida) - strlen(data_extraida);j++)
                printf(" ");//É so para n ter um textão de 51 espaços
            printf(" |\n");
            printf("+");
            for(int j = 0 ; j < palavra_maior+8;j++)
                printf("-");
            printf("-+");
            for(int j = 0;j < 68-palavra_maior;j++)
                printf("-");
            printf("+\n");
        } else if (historicos[i].id == id && i > -1) {
            nome_extraido = historicos[i].nome;
            pontuacao_extraida_int = historicos[i].pontuacao;
            data_extraida = historicos[i].data;
            printf("| %4d | %s ", i+1, nome_extraido);

            for(int j = 0 ; j < palavra_maior-strlen(nome_extraido);j++)//Comparo os tamnhos e coloco os espaços devidos
                printf(" ");
            printf("| %6d ", pontuacao_extraida_int);
            printf("| %s", data_extraida);
            for(int j = 0 ; j < 63 - palavra_maior - 6 - strlen(data_extraida);j++)
                printf(" ");//É so para n ter um textão de 51 espaços
            printf(" |\n");
            printf("+");
            for(int j = 0 ; j < palavra_maior+8;j++)
                printf("-");
            printf("-+");
            for(int j = 0;j < 68-palavra_maior;j++)
                printf("-");
            printf("+\n");
            encontrado = 1;
            break;
        }

        i++;
    } while (i < max_linhas);

    if (!encontrado) {
        semHistorico("Nenhum registro encontrado com este ID");
        return;
    }

    liberarHistorico(historicos);
}

void listarHistorico() {
    Historico *historicos;
    int total;
    int max_linhas = contaLinhasHistorico();
    char *nome_extraido;
    int pontuacao_extraida_int;
    char *data_extraida;
    char *pontuacao_extraida;

    carregarHistorico(&historicos, &total); //caso nao exista nenhum dado historico carregado
    if (!historicos || total == 0) {
        semHistorico("Nenhum dado historico carregado.");
        return;
    }

    int i = max_linhas;
    int palavra_maior;

    FILE *meta_dados_historico = fopen("data/meta_historico.txt", "r");

    fscanf(meta_dados_historico,"%d", &palavra_maior);

    do { 
        if(i ==  max_linhas){
            nome_extraido = "NOME";
            pontuacao_extraida = "PONTOS";
            data_extraida = "DATA";
            printf("|   ID | %s ", nome_extraido);

            for(int j = 0 ; j < palavra_maior-strlen(nome_extraido);j++)//Comparo os tamnhos e coloco os espaços devidos
                printf(" ");
            printf("| %s ", pontuacao_extraida);
            printf("| %s", data_extraida);
            for(int j = 0 ; j < 63 - palavra_maior - strlen(pontuacao_extraida) - strlen(data_extraida);j++)
                printf(" ");//É so para n ter um textão de 51 espaços
            printf(" |\n");
            printf("+");
            for(int j = 0 ; j < palavra_maior+8;j++)
                printf("-");
            printf("-+");
            for(int j = 0;j < 68-palavra_maior;j++)
                printf("-");
            printf("+\n");
        } else {
            nome_extraido = historicos[i].nome;
            pontuacao_extraida_int = historicos[i].pontuacao;
            data_extraida = historicos[i].data;
            printf("| %4d | %s ", i+1, nome_extraido);

            for(int j = 0 ; j < palavra_maior-strlen(nome_extraido);j++)//Comparo os tamnhos e coloco os espaços devidos
                printf(" ");
            printf("| %6d ", pontuacao_extraida_int);
            printf("| %s", data_extraida);
            for(int j = 0 ; j < 63 - palavra_maior - 6 - strlen(data_extraida);j++)
                printf(" ");//É so para n ter um textão de 51 espaços
            printf(" |\n");
            printf("+");
            for(int j = 0 ; j < palavra_maior+8;j++)
                printf("-");
            printf("-+");
            for(int j = 0;j < 68-palavra_maior;j++)
                printf("-");
            printf("+\n");
        }

        i--;
    } while (i >= 0);

    liberarHistorico(historicos);
}

void escreveHistorico(char *nome, int pontuacao, char *data)
{
    Historico *historicos;
    int total;
    int tamanho = contaLinhasHistorico();
    int palavra_maior, maior = 0;

    FILE *historico_file = fopen("data/historico.txt", "a");
    FILE *meta_dados_historico = fopen("data/meta_historico.txt", "w+");

    if (fscanf(meta_dados_historico, "%d", &palavra_maior) < 0) {
        palavra_maior = 0;
    }

    carregarHistorico(&historicos, &total);

    fscanf(meta_dados_historico,"%d", &palavra_maior);

    for (int i = 0; i < tamanho; i++) {
        if (strlen(historicos[i].nome) > maior)
            maior = strlen(historicos[i].nome);
    }
    if (strlen(nome) > maior) 
        maior = strlen(nome);

    fprintf(meta_dados_historico, "%d\n", maior);

    fprintf(historico_file,"%d|%s|%s|%d\n", tamanho+1, nome, data, pontuacao);

    fclose(historico_file);
    fclose(meta_dados_historico);
}

int contaLinhasHistorico() {
    FILE *arquivo = fopen("data/historico.txt", "r");

    int linhas = 0; //contar as linhas, inicializando com zero
    char buffer[MAX_LINHA];
    while (fgets(buffer, MAX_LINHA, arquivo)) {
        if (strlen(buffer) > 1) {
        linhas++;
        }
    }
    fclose(arquivo);
    return linhas;
}