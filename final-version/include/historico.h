// historico.h
#ifndef HISTORICO_H
#define HISTORICO_H

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
void telaHistorico();
void strToLower(char *str);
void carregarHistorico(Historico **historicos, int *total);
void liberarHistorico(Historico *historicos);
void pesquisarPorData();
void pesquisarPorNome();
void pesquisarPorID();
void escreveHistorico(char *nome, int pontuacao, char *data);
int contaLinhasHistorico();

#endif // HISTORICO_H
