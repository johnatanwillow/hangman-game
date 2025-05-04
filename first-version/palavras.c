// As bibliotecas usadas
#include <stdio.h>
#include <string.h> // PARA A SEPARAÇÃO DOS COMPONENTES DA LINHA
#include <stdlib.h>
#include <ctype.h> // PARA TOUPPER
#include <time.h>
#include <conio.h> // PARA RECEBER AS PALVRAS DO USUÁRIO
#include <windows.h>
//---------------------------------------
#include "palavras.h"
#include "interface.h"
//---------------------------------------

// Váriáveis globais
#define MAX_N_CHAR 255 // MAXIMO NUMERO DE CARACTERES POR LINHA
#define TAM_PALAVRA 20
#define TAM_DICA 100
#define ESPERAR 4000

char buffer[MAX_N_CHAR]; // Como será usado pelas as duas funções,ele é instanciado fora delas

void palavraAleatoria(char **palavra, char **dica)
{
    FILE *arquivo;
    arquivo = fopen("arquivo.txt", "r"); // Abertura do arquivo em modo de apenas leitura 'r'

    srand(time(NULL));
    int linhaAleatoria = rand() % contaLinhas() + 1; // Aleatoriza qual linha será lida,o +1 é pq 0 até (qLinha-1) ir pra 1 até qLinhas

    int i = 0;                                                               // Um contador para chegar até a linha aleatorizada
    while (i < linhaAleatoria && fgets(buffer, MAX_N_CHAR, arquivo) != NULL) // Um contador para chegar até a linha aleatorizada
        i++;

    strtok(buffer, "|");          // Pular a parte do Id.
    *palavra = strtok(NULL, "|"); // O USO DO NULL É PARA LIMPAR O ENDEREÇO ANTERIOR (O ID)E IR PARA O PROXIMO ITEM DA LISTA QUE É O NOME
    *dica = strtok(NULL, "|");    // O USO DO NULL É PARA LIMPAR O ENDEREÇO ANTERIOR (O NOME) E VAI PARA O PROXIMO ITEM DA LISTA QUE É A DICA

    fclose(arquivo); // Fecha o arquivo
}

int contaLinhas()
{
    FILE *arquivo;
    arquivo = fopen("arquivo.txt", "r");

    int qLinhas = 0;

    // O fgets é o que faz o buffer receber cada linha do arquivo,Enqunto a linha não possuir o fim de texto o contador aumentará
    while (fgets(buffer, MAX_N_CHAR, arquivo))
    {
        qLinhas++;
    }

    fclose(arquivo);
    return qLinhas;
}

void adicionarPalavra()
{
    FILE *arquivo;
    arquivo = fopen("arquivo.txt", "a"); // Abertura do arquivo em mode de adicão recente sem apagar os dados anteirores 'a'

    int linhas = contaLinhas() + 1; // Para o próximo id
    char id[2];                     // Para guardar o numero no i = 0,e o fim deles em i =1
    sprintf(id, "%d", linhas);      // Transformar de int para str;

    char palavra[TAM_PALAVRA];
    char dica[TAM_DICA];
    char *formato[3];

    telaAdiconarPalavra("Por favor, escreva uma palavra:                                              |");
    fflush(stdin); // Para limpar o 'buffer do teclado' que armazenava dados perdidos,impedindo que o proximo gets fosse lido
    gets(palavra);
    telaAdiconarPalavra("Por favor, escreva uma dica:                                                 |");
    fflush(stdin); // Para limpar o 'buffer do teclado' que armazenava dados perdidos,impedindo que o proximo gets fosse lido
    gets(dica);

    // Para transformar a string digitada em maiúscula
    for (int i = 0; i < strlen(palavra); i++)
    {
        palavra[i] = toupper(palavra[i]);
    }

    for (int i = 0; i < strlen(dica); i++)
    {
        if (i == 0)
            dica[i] = toupper(dica[i]);
        else
            dica[i] = tolower(dica[i]);
    }

    formato[0] = id;
    formato[1] = palavra;
    formato[2] = dica;

    fputs("\n", arquivo); // Para pular a linha dentro do arquivo
    for (int i = 0; i < 3; i++)
    {
        fputs(("%s ", formato[i]), arquivo); // Colocar o id , a palavar e a dica
        fputs("|", arquivo);                 // Para colocar a vírgula,se juntar os dois a virgula não a aparece
    }

    telaAdiconarPalavra("Por favor escreva uma dica:                                                    |");
    telaAdiconarPalavra("Palavra adicionada com sucesso! Aperte uma tecla para continuar...");
    getchar(); // Para esperar o usuário apertar uma tecla antes de continuar

    fclose(arquivo);
}
// Serve para verficar se possui arquivo
int temArquivo()
{
    FILE *arquivo;
    arquivo = fopen("arquivo.txt", "r");

    if (arquivo == NULL)
    { // SE CASO ARQUIVO NÃO FOR LIDO,DÁ MENSAGEM DE ERRO
        fprintf(stderr, "ERRO NA TENTATIVA DE LER O ARQUIVO.\n");
        return 1;
    }
    fclose(arquivo);
    return 0;
}

int verificarParaExclusaoOuAdicao()
{
    // nada ainda
    return 0;
}