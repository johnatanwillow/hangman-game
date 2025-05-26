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

void telaHistorico();
void strToLower();
void carregarHistorico(Historico **historicos, int *total);
void liberarHistorico(Historico *historicos);
void pesquisarPorData();
void pesquisarPorNome();
void pesquisarPorID();

#endif // HISTORICO_H
