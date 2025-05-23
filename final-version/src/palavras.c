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
    arquivo = fopen("data/arquivo.txt", "r"); // Abertura do arquivo em modo de apenas leitura 'r'

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
    arquivo = fopen("data/arquivo.txt", "r");

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
    FILE *arquivo, *arquivo_leitrua;
    temArquivo();
    arquivo_leitrua = fopen("data/arquivo.txt", "r+"); // Abertura do arquivo em modo de leitura 'r'
    arquivo = fopen("data/arquivo.txt", "r+"); // Abertura do arquivo em mode de adicão recente sem apagar os dados anteirores 'a'

    int linhas = contaLinhasPalavras() + 1; // Para o próximo id
    char id[12];                     // Para guardar o numero no i = 0,e o fim deles em i =1
    sprintf(id, "%d", linhas);      // Transformar de int para str;

    char palavra[TAM_PALAVRA];
    char dica[TAM_DICA];
    char *formato[3];
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
    
    // Para transformar a string digitada em maiúscula
    for (int i = 0; i < strlen(palavra); i++)
    {
        palavra[i] = toupper(palavra[i]);
    }

    } else {
        int i = 0;                                                               
        while (i < contaLinhasPalavras()) { // Um contador para passar por todos as palavras
            fgets(buffer, MAX_N_CHAR, arquivo); // Lê a linha do arquivo
            strtok(buffer, "|");          // Pular a parte do Id.
            palavra_extraida = strtok(NULL, "|"); // O USO DO NULL É PARA LIMPAR O ENDEREÇO ANTERIOR (O ID)E IR PARA O PROXIMO ITEM DA LISTA QUE É O NOME
            palavra_extraida[strcspn(palavra_extraida, "\n")] = 0; // Remove o '\n' do final da string
            strcpy(palavra_arquivo, palavra_extraida); // Copia o nome da palavra do arquivo
            if (strcmp(palavra, palavra_extraida) == 0)
            {
                palavraExistente = 1; // Se a palavra já existe, não adiciona
                break;
            }
            i++;  
        }
    
        if (palavraExistente == 1)
        {
            // Se a palavra não existe, adiciona
            telaAdiconarPalavra("Essa palavra ja existe! Aperte uma tecla para continuar...                   |");
            getchar(); // Para esperar o usuário apertar uma tecla antes de continuar
    
            formato[0] = NULL;
            formato[1] = NULL;
            formato[2] = NULL;
    
            fclose(arquivo);
        } else {
            telaAdiconarPalavra("Por favor, escreva uma dica:                                                 |");
            fflush(stdin); // Para limpar o 'buffer do teclado' que armazenava dados perdidos,impedindo que o proximo gets fosse lido
            gets(dica);
    
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
                formato[0] = id;
                formato[1] = palavra;
                formato[2] = dica;
    
                fputs("\n", arquivo); // Para pular a linha dentro do arquivo
                for (int i = 0; i < 3; i++)
                {
                    fputs(("%s ", formato[i]), arquivo); // Colocar o id , a palavar e a dica
                    fputs("|", arquivo);                 // Para colocar o "|",se juntar os dois o "|" não a aparece
                }
    
                telaAdiconarPalavra("Palavra adicionada com sucesso! Aperte uma tecla para continuar...           |");
                getchar(); // Para esperar o usuário apertar uma tecla antes de continuar
    
                fclose(arquivo);
                fclose(arquivo_leitrua);
            }
        }
    }
}

// Serve para verficar se possui arquivo
int temArquivo()
{
    FILE *arquivo;
    arquivo = fopen("data/arquivo.txt", "r");

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
