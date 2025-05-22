#pragma once

#define TAM_NOME_STRUCT 30
//---------------------------------------
// Struct of player
typedef struct 
{
    int pontuacao;
    char nome[TAM_NOME_STRUCT];
    char letras_testadas[27]; // 27 posições, cada uma pode armazenar 1 letra + '\0'
    int erros;                // Contador de erros
    int acertos;              // Contador de acertos
} SinglePlayer;

//---------------------------------------
void singlePlayerJogo();
int letraTestada(char *letra, char *letras_testadas);
void dificuldadeDaPalavra(int tamanho, char **dificuldade);
int quantidadeLetrasRepetidasPalavra(int tamanho, char *palavra);
void adicionaLetraTestada(char *letras_testadas, char letra[]);
//---------------------------------------