#pragma once

#define TAM_NOME_STRUCT 30
#define TAM_PLAYERS_STRUCT 2

//---------------------------------------
// Struct of player
typedef struct 
{
    int pontuacao;
    char nomes[TAM_PLAYERS_STRUCT][TAM_NOME_STRUCT];
    char letras_testadas[27]; // 27 posições, cada uma pode armazenar 1 letra + '\0'
    int erros;                // Contador de erros
    int acertos;              // Contador de acertos
    int atual;
} MultiPlayer;

//---------------------------------------
void multiPlayerJogo();
int letraTestada(char *letra, char *letras_testadas);
void dificuldadeDaPalavra(int tamanho, char **dificuldade);
int quantidadeLetrasRepetidasPalavra(int tamanho, char *palavra);
void adicionaLetraTestada(char *letras_testadas, char letra[]);
void defineData(char *data_hora);
//---------------------------------------