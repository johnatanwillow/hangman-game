#pragma once

#define MAX_LINHA 200
#define MAX_NOME 50
#define MAX_DATA 11

typedef struct {
    int id;
    char nome[MAX_NOME];
    char data[MAX_DATA];
    int pontuacao;
} Historico;

void telaGerenciarHistorico();
void listarHistorico();
void carregarHistorico(Historico **historicos, int *total);
void liberarHistorico(Historico *historicos);
void pesquisarPorData(char data[]);
void pesquisarPorNome(char nome[]);
void pesquisarPorID(int id);
void escreveHistorico(char *nome, int pontuacao, char *data);
int contaLinhasHistorico();
void listarHistorico();