// As bibliotecas usadas
#include <stdio.h>
#include <string.h> // PARA A SEPARAÇÃO DOS COMPONENTES DA LINHA
#include <stdlib.h>
#include <ctype.h> // PARA TOUPPER
#include <time.h>
#include <conio.h> // PARA RECEBER AS PALVRAS DO USUÁRIO
#include <windows.h>
//---------------------------------------
#include "../include/palavras.h"
#include "../include/interface.h"
//---------------------------------------

// Váriáveis globais
#define MAX_N_CHAR 255 // MAXIMO NUMERO DE CARACTERES POR LINHA
#define TAM_PALAVRA 30
#define TAM_DICA 150
#define ESPERAR 2000

char buffer[MAX_N_CHAR]; // Como será usado pelas as duas funções,ele é instanciado fora delas

void palavraAleatoria(char **palavra, char **dica)
{
    FILE *arquivo;
    arquivo = fopen("data/palavras.txt", "r"); // Abertura do arquivo em modo de apenas leitura 'r'

    srand(time(NULL));
    int linhaAleatoria = rand() % contaLinhasPalavras() + 1; // Aleatoriza qual linha será lida,o +1 é pq 0 até (qLinha-1) ir pra 1 até qLinhas

    int i = 0;                                                               // Um contador para chegar até a linha aleatorizada
    while (i < linhaAleatoria && fgets(buffer, MAX_N_CHAR, arquivo) != NULL) // Um contador para chegar até a linha aleatorizada
        i++;

    strtok(buffer, "|");          // Pular a parte do Id.
    *palavra = strtok(NULL, "|"); // O USO DO NULL É PARA LIMPAR O ENDEREÇO ANTERIOR (O ID)E IR PARA O PROXIMO ITEM DA LISTA QUE É O NOME
    *dica = strtok(NULL, "|");    // O USO DO NULL É PARA LIMPAR O ENDEREÇO ANTERIOR (O NOME) E VAI PARA O PROXIMO ITEM DA LISTA QUE É A DICA

    fclose(arquivo); // Fecha o arquivo
}

int contaLinhasPalavras()
{
    FILE *arquivo;
    arquivo = fopen("data/palavras.txt", "r");

    int qLinhas = 0;
    if(arquivo != NULL){
    // O fgets é o que faz o buffer receber cada linha do arquivo,Enqunto a linha não possuir o fim de texto o contador aumentará
    while (fgets(buffer, MAX_N_CHAR, arquivo))
    {
        qLinhas++;
    }
    }
    fclose(arquivo);
    return qLinhas;
}


void adicionarPalavra()
{
    
    FILE *arquivo;
    temArquivo();   
    arquivo = fopen("data/palavras.txt", "r+"); // Abertura do arquivo em mode de adicão recente sem apagar os dados anteirores 'a'
    
    int id = contaLinhasPalavras() + 1; // Para o próximo id
    char palavra[TAM_PALAVRA];
    char dica[TAM_DICA];
    char *palavra_extraida;
    char palavra_arquivo[TAM_PALAVRA];
    int palavraExistente = 0;

    telaAdiconarPalavra("Escreva uma palavra (sem acento e sem espaco) ou \"Enter\" para voltar:        |");
    fflush(stdin); // Para limpar o 'buffer do teclado' que armazenava dados perdidos,impedindo que o proximo gets fosse lido
    fgets(palavra, sizeof(palavra), stdin); // mais seguro que gets
    palavra[strcspn(palavra, "\n")] = '\0';
    
    for (int i = 0; i < strlen(palavra); i++) {
        if (!isalpha(palavra[i])) {
            inputErroEntrada("Palavra invalida! Não digite espaço ou acentuação.");
            return; // Retorna 1 se o usuário quiser voltar
        }
    }

    if (palavra[0] == '\0' || strlen(palavra) == 0) {
        return;
    }
    else {
        //Para transformar a string digitada em maiúscula
         for (int i = 0; i < strlen(palavra); i++)    {
            palavra[i] = toupper(palavra[i]);
    }

        while (fgets(buffer, MAX_N_CHAR, arquivo)) { //Pega todos as palavras na verificação

            strtok(buffer, "|");          // Pular a parte do Id.

            palavra_extraida = strtok(NULL, "|"); // O USO DO NULL É PARA LIMPAR O ENDEREÇO ANTERIOR (O ID)E IR PARA O PROXIMO ITEM DA LISTA QUE É O NOME
            palavra_extraida[strcspn(palavra_extraida, "\n")] = 0; // Remove o '\n' do final da string

            strcpy(palavra_arquivo, palavra_extraida); // Copia o nome da palavra do arquivo
            if (strcmp(palavra, palavra_extraida) == 0) 
            {
                palavraExistente = 1; // Se a palavra já existe, não adiciona
                break;
            }
          
        }
    
        if (palavraExistente == 1)
        {
            // Se a palavra não existe, adiciona
            telaAdiconarPalavra("Essa palavra ja existe! Aperte uma tecla para continuar...                   |");
            getchar(); // Para esperar o usuário apertar uma tecla antes de continuar
            
            fclose(arquivo);
        } else {

            telaAdiconarPalavra("Por favor, escreva uma dica:                                                 |");
            fflush(stdin); // Para limpar o 'buffer do teclado' que armazenava dados perdidos,impedindo que o proximo gets fosse lido
            gets(dica);

            for(int i = 0; i < strlen(dica); i++){
                if(i == 0 && isspace(dica[i])){
                    inputErroEntrada("Dica invalida! Nao inicie com espaco.");
                    return; // Retorna 1 se o usuário quiser voltar
                }
    
                if(dica[i] < 0){ //Como está no local americano , todas as palavras acentuadas são negativas
                    
                    inputErroEntrada("Dica invalida! Nao digite acentuacao.");
                    return; // Retorna 1 se o usuário quiser voltar
                }
            }
            for (int i = 0; i < strlen(dica); i++)
            {
                if (i == 0)
                    dica[i] = toupper(dica[i]);
                else
                    dica[i] = tolower(dica[i]);
            }
    
            if (confirmarAdicaoDePalavra() == 0)
            {
                fclose(arquivo);

            }
            else
            {
                if(id > 1)
                fprintf(arquivo,"\n%d|%s|%s|",id,palavra,dica);
                else
                fprintf(arquivo,"%d|%s|%s|",id,palavra,dica);
                telaAdiconarPalavra("Palavra adicionada com sucesso! Aperte uma tecla para continuar...           |");
                getchar(); // Para esperar o usuário apertar uma tecla antes de continuar
    
                fclose(arquivo);
            }
        }
    }
}

// Serve para verficar se possui arquivo
int temArquivo()
{
    FILE *arquivo;
    arquivo = fopen("data/palavras.txt", "r");

    if (arquivo == NULL)
    { // SE CASO ARQUIVO NÃO FOR LIDO,DÁ MENSAGEM DE ERRO
        fprintf(stderr, "ERRO NA TENTATIVA DE LER O ARQUIVO.\n");
        return 1;
    }
    fclose(arquivo);
    return 0;
}
