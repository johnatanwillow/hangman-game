#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <ctype.h> // Para isalpha() e strchr()
#include <conio.h> // Para getchar()
//---------------------------------------
#include "../include/palavras.h"
#include "../include/interface.h"
#include "../include/ranking.h"
#include "../include/historico.h"
#include "../include/single-player.h"
#include "../include/multiplayer.h"
//---------------------------------------

#define MAX_TENTATIVAS 6
#define ESPERAR 2000 // Tempo de espera em segundos (para Sleep)
char texto[150];
int tamanho_linha = 78;
int max_char;
char texto_letras_testadas[150] = "";
char texto_letra[4] = "";
char texto_palavra[50] = "";
char texto_p[4] = "";

//-----------------------------------------------------------------------------------
/**
 * Função que limpa o buffer de entrada (usada para evitar problemas com o fgets())
 */
void limparBuffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/**
 * Função que lê a entrada padrão até o tamanho máximo ou até encontrar um '\n'
 */
void scanfFgets(char *text, int size)
{
    // Lê a entrada padrão até o tamanho máximo ou até encontrar um '\n'
    // Deve-se limpar a entrada padrão, pois o fgets() lê até o \n, apenas se houver uma quebra de linha antes, então o fgets() não vai ler nada.
    fgets(text, size, stdin);
    strtok(text, "\n"); // Remove the newline character from the string
    // text[strcspn(text, "\n")] = '\0';
}

/**
 * Exibe o menu principal do jogo.
 */
void exibirMenuPrincipal()
{

    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                             -= JOGO DA FORCA =-                              |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|      +----+                                                                  |\n");
    printf("|      |/   |                                                                  |\n");
    printf("|      |    0                                                                  |\n");
    printf("|      |   /|\\                  M E N U   P R I N C I P A L                    |\n");
    printf("|      |   / \\                                                                 |\n");
    printf("|      |                                                                       |\n");
    printf("|   ==============                                                             |\n");
    printf("|   \"            \"                                                             |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|------------------------------------------------------------------------------|\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("| 1. Jogar (Singleplayer)                                                      |\n");
    printf("| 2. Jogar (Multiplayer)                                                       |\n");
    printf("| 3. Gerenciar Palavras                                                        |\n");
    printf("| 4. Ver Ranking                                                               |\n");
    printf("| 5. Ver Historico                                                             |\n");
    printf("| 0. Sair                                                                      |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("+==============================================================================+\n");
    printf("| Escolha uma opcao:                                                           |\n");
    printf("+==============================================================================+\n");
}

/** Função que exibe algum erro de input para o usuário.
 * @param {char *} texto_do_erro - texto fornecido de acordo com o tipo de erro.
 */
void inputErroEntrada(char *texto_do_erro)
{

    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                                  -= ERROR =-                                 |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    0                                        |\n");
    printf("|                                |   /|\\                                       |\n");
    printf("|                                |   / \\                                       |\n");
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    sprintf(texto, "%s", texto_do_erro);
    formatacaoBonita();
    printf("|------------------------------------------------------------------------------|\n");
    printf("| Aguarde...                                                                   |\n");
    printf("+==============================================================================+\n");
    Sleep(ESPERAR);
}

void semHistorico(char *texto_do_erro)
{

    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                             -= ERROR HISTORICO =-                            |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    0                                        |\n");
    printf("|                                |   /|\\                                       |\n");
    printf("|                                |   / \\                                       |\n");
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    sprintf(texto, "%s", texto_do_erro);
    formatacaoBonita();
    printf("+------------------------------------------------------------------------------+\n");
    printf("| Aperte uma tecla . . .                                                       |\n");
    printf("+==============================================================================+\n");
    Sleep(ESPERAR);
}

// ------------------------------------------------------------------------------------------------------
/** Função que imprime alguma mensagem de erro para o usuário (para logica do jogo SinglePlayer)
 * @param {char *} texto_do_erro - texto fornecido de acordo com o tipo de erro.
 * @param {char *} partes_do_corpo - partes do corpo do personagem que representa o erro.
 */
void inputErroLogicaUsuario(char *texto_do_erro, char *partes_do_corpo)
{
    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                                   -= ERROR =-                                |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    %c                                        |\n", partes_do_corpo[0]);
    printf("|                                |   %c%c%c                                       |\n", partes_do_corpo[2], partes_do_corpo[1], partes_do_corpo[3]);
    printf("|                                |   %c %c                                       |\n", partes_do_corpo[4], partes_do_corpo[5]);
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    sprintf(texto, "%s", texto_do_erro);
    formatacaoBonita();
    printf("|------------------------------------------------------------------------------|\n");
    printf("| Aguarde...                                                                   |\n");
    printf("+==============================================================================+\n");
    Sleep(ESPERAR);
}

/** Função que imprime o resultado do jogo do jagador em jogo SinglePlayer (para logica do jogo SinglePlayer)
 * @param {SinglePlayer} player - jogador que jogou o jogo.
 * @param {char *} palavra - indicando a palavra da vez do jogo.
 * @param {char *} partes_do_corpo - partes do corpo do personagem que representa o erro.
 * @param {char *} title - titulo da tela de resultado do jogo.
 * @param {char *} messenge - mensagem de resultado do jogo, baseado no acerto ou erro do jogador.
 */
void telaResultadoJogo(SinglePlayer player, char *partes_do_corpo, char *palavra, char *title, char *messenge)
{
    int i;
    sprintf(texto_letras_testadas, "");
    sprintf(texto_letra, "");

    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                          -= %s =-                       |\n", title);
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    %c                                        |\n", partes_do_corpo[0]);
    printf("|                                |   %c%c%c                                       |\n", partes_do_corpo[2], partes_do_corpo[1], partes_do_corpo[3]);
    printf("|                                |   %c %c                                       |\n", partes_do_corpo[4], partes_do_corpo[5]);
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    sprintf(texto, "%s! %s", player.nome, messenge);
    formatacaoBonita();
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    sprintf(texto, "A palavra era: %s", palavra);
    formatacaoBonita();
    sprintf(texto, "Sua pontuacao foi: %d", player.pontuacao);
    formatacaoBonita();
    sprintf(texto, "Acertos: %d", player.acertos);
    formatacaoBonita();
    printf("| Erros: %d                                                                     |\n", player.erros);
    for (i = 0; i < 26; i++)
    {
        // Se o primeiro caractere do elemento não for o terminador nulo, exibe a letra
        if (player.letras_testadas[i] != '\0') {
            sprintf(texto_letra, " %c ", player.letras_testadas[i]);
            strncat(texto_letras_testadas, texto_letra, 4);
        }
    }
    sprintf(texto, "Letras tentadas:%s", texto_letras_testadas);
    formatacaoBonita();
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("| Pressione uma tecla para continuar . . .                                     |\n");
    printf("+------------------------------------------------------------------------------+\n");
    getchar(); // Aguarda o usuário pressionar uma tecla
}

// Função que imprime a interface da tela de jogo SinglePlayer
void telaSingleplayerJogo(SinglePlayer player, char *letra, char *dica, char *descoberta, int MAX_ERROS, int tamanho_palavra, char *partes_do_corpo, int TAM_PALAVRA, char *dificuldade)
{
    int i;
    sprintf(texto_letras_testadas, "");
    sprintf(texto_letra, "");

    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                             -= MODO SINGLEPLAYER =-                          |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    %c                                        |\n", partes_do_corpo[0]);
    printf("|                                |   %c%c%c                                       |\n", partes_do_corpo[2], partes_do_corpo[1], partes_do_corpo[3]);
    printf("|                                |   %c %c                                       |\n", partes_do_corpo[4], partes_do_corpo[5]);
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    sprintf(texto, "Acertos: %d", player.acertos);
    formatacaoBonita();
    printf("| Erros: %d                                                                     |\n", player.erros);
    printf("| Tentativas restantes: %d                                                      |\n", MAX_ERROS - player.erros);
    sprintf(texto, "Dificuldade: %s (%d letras)", dificuldade, tamanho_palavra);
    formatacaoBonita();
    for (i = 0; i < 26; i++)
    {
        // Se o primeiro caractere do elemento não for o terminador nulo, exibe a letra
        if (player.letras_testadas[i] != '\0') {
            sprintf(texto_letra, " %c ", player.letras_testadas[i]);
            strncat(texto_letras_testadas, texto_letra, 4);
        }
    }
    sprintf(texto, "Letras tentadas:%s", texto_letras_testadas);
    formatacaoBonita();
    sprintf(texto_letras_testadas, "");
    if (player.erros >=2) {
        sprintf(texto, "DICA: \"%s\"", dica);
        formatacaoBonita();
    }
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    for (i = 0; i < tamanho_palavra; i++)
    {
        if (descoberta[i] == '_')
        {
            sprintf(texto_p, "_ ");
            strncat(texto_palavra, texto_p, 2);
        }
        else
        {
            sprintf(texto_p, "%c ", descoberta[i]);
            strncat(texto_palavra, texto_p, 2);
        }
    }
    sprintf(texto, "                             %s", texto_palavra);
    formatacaoBonita();
    sprintf(texto_palavra, "");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("| Digite uma letra ou a palavra:                                               |");
    printf("\n+------------------------------------------------------------------------------+\n");
    scanfFgets(letra, TAM_PALAVRA); // Lê a letra digitada pelo usuário
    for (i = 0; i < strlen(letra); i++)
    {
        letra[i] = toupper(letra[i]); // Converte a string digitada para maiúscula
    }
    printf("+==============================================================================+\n");
}

// Função que imprime a interface da tela de escolha do nome do SinglePlayer ou retornar ao menu principal (foto de ser int)
int telaSingleplayer(char nome[], int TAM_NOME)
{
    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                            -= MODO SINGLEPLAYER =-                           |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    0                                        |\n");
    printf("|                                |   /|\\                                       |\n");
    printf("|                                |   / \\                                       |\n");
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("| Digite o nome ou \"0\" / \"Enter\" p/ voltar (nao digite espaco ou acento):      |\n");
    printf("+------------------------------------------------------------------------------+\n");
    scanfFgets(nome, TAM_NOME); // Lê o nome do jogador
    for (int i = 0; i < strlen(nome); i++)
    {
        if (!isalpha(nome[i]))
        {
            inputErroEntrada("Nome invalido! Tente novamente.");
            return 1; // Retorna 1 se o usuário quiser voltar
        }
    }
    if (nome[0] == '0')
    {
        return 1; // Retorna 1 se o usuário quiser voltar
    }
    else if (nome[0] == '\n')
    {
        return 1; // Retorna 1 se o usuário quiser voltar
    }
    else
    {
        system("cls || clear");
        printf("+==============================================================================+\n");
        printf("|                            -= MODO SINGLEPLAYER =-                           |\n");
        printf("+==============================================================================+\n");
        printf("|                                                                              |\n");
        printf("|                                +----+                                        |\n");
        printf("|                                |/   |                                        |\n");
        printf("|                                |    0                                        |\n");
        printf("|                                |   /|\\                                       |\n");
        printf("|                                |   / \\                                       |\n");
        printf("|                                |                                             |\n");
        printf("|                             ==============                                   |\n");
        printf("|                             \"            \"                                   |\n");
        printf("|                                                                              |\n");
        printf("+------------------------------------------------------------------------------+\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        sprintf(texto, "Bem-vindo(a), %s! Preparando o jogo . . .", nome);
        formatacaoBonita();
        printf("+==============================================================================+\n");
        Sleep(ESPERAR);
        return 0; // Retorna 0 se o usuário quiser continuar
    }
}

/** Função que imprime o resultado do jogo do jagador em jogo MultiPlayer (para logica do jogo MultiPlayer)
 * @param {MultiPlayer} player - jogador que jogou o jogo.
 * @param {char *} palavra - indicando a palavra da vez do jogo.
 * @param {char *} partes_do_corpo - partes do corpo do personagem que representa o erro.
 * @param {char *} title - titulo da tela de resultado do jogo.
 * @param {char *} messenge - mensagem de resultado do jogo, baseado no acerto ou erro do jogador.
 */
void telaResultadoJogoMultiplayer(MultiPlayer player, char *partes_do_corpo, char *palavra, char *title, char *messenge)
{
    int i;

    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                          -= %s =-                       |\n", title);
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    %c                                        |\n", partes_do_corpo[0]);
    printf("|                                |   %c%c%c                                       |\n", partes_do_corpo[2], partes_do_corpo[1], partes_do_corpo[3]);
    printf("|                                |   %c %c                                       |\n", partes_do_corpo[4], partes_do_corpo[5]);
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    sprintf(texto, "%s! %s", player.nomes[0], messenge);
    formatacaoBonita();
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    sprintf(texto, "A palavra era: %s", palavra);
    formatacaoBonita();
    sprintf(texto, "Sua pontuacao foi: %d", player.pontuacao);
    formatacaoBonita();
    sprintf(texto, "Acertos: %d", player.acertos);
    formatacaoBonita();
    printf("| Erros: %d                                                                     |\n", player.erros);
    for (i = 0; i < 26; i++)
    {
        // Se o primeiro caractere do elemento não for o terminador nulo, exibe a letra
        if (player.letras_testadas[i] != '\0') {
            sprintf(texto_letra, " %c ", player.letras_testadas[i]);
            strncat(texto_letras_testadas, texto_letra, 4);
        }
    }
    sprintf(texto, "Letras tentadas:%s", texto_letras_testadas);
    formatacaoBonita();
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("\n+------------------------------------------------------------------------------+\n");
    printf("| Pressione uma tecla para continuar...\n");
    printf("+------------------------------------------------------------------------------+\n");
    getchar(); // Aguarda o usuário pressionar uma tecla
}

// Função que imprime a interface da tela de jogo MultiPlayer
void telaMultiplayerJogo(MultiPlayer player, char *letra, char *dica, char *descoberta, int MAX_ERROS, int tamanho_palavra, char *partes_do_corpo, int TAM_PALAVRA, char *dificuldade, int playerAtivo)
{
    int i;
    sprintf(texto_letras_testadas, "");
    sprintf(texto_letra, "");

    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                             -= MODO MULTIPLAYER =-                          |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    %c                                        |\n", partes_do_corpo[0]);
    printf("|                                |   %c%c%c                                       |\n", partes_do_corpo[2], partes_do_corpo[1], partes_do_corpo[3]);
    printf("|                                |   %c %c                                       |\n", partes_do_corpo[4], partes_do_corpo[5]);
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    sprintf(texto, "Vez de: %s", player.nomes[playerAtivo]);
    formatacaoBonita();
    printf("+------------------------------------------------------------------------------+\n");
    sprintf(texto, "Acertos: %d", player.acertos);
    formatacaoBonita();
    printf("| Erros: %d                                                                     |\n", player.erros);
    printf("| Tentativas restantes: %d                                                      |\n", MAX_ERROS - player.erros);
    sprintf(texto, "Dificuldade: %s (%d letras)", dificuldade, tamanho_palavra);
    formatacaoBonita();
    for (i = 0; i < 26; i++)
    {
        // Se o primeiro caractere do elemento não for o terminador nulo, exibe a letra
        if (player.letras_testadas[i] != '\0') {
            sprintf(texto_letra, " %c ", player.letras_testadas[i]);
            strncat(texto_letras_testadas, texto_letra, 4);
        }
    }
    sprintf(texto, "Letras tentadas:%s", texto_letras_testadas);
    formatacaoBonita();
    sprintf(texto_letras_testadas, "");
    if (player.erros >=2) {
        sprintf(texto, "DICA: \"%s\"", dica);
        formatacaoBonita();
    }
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    for (i = 0; i < tamanho_palavra; i++)
    {
        if (descoberta[i] == '_')
        {
            // printf("_ ");
            sprintf(texto_p, "_ ");
            strncat(texto_palavra, texto_p, 2);
        }
        else
        {
            // printf("%c ", descoberta[i]);
            sprintf(texto_p, "%c ", descoberta[i]);
            strncat(texto_palavra, texto_p, 2);
        }
    }
    sprintf(texto, "                             %s", texto_palavra);
    formatacaoBonita();
    sprintf(texto_palavra, "");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("| Digite uma letra:                                                            |");
    printf("\n+------------------------------------------------------------------------------+\n");
    scanfFgets(letra, TAM_PALAVRA); // Lê a letra digitada pelo usuário
    for (i = 0; i < strlen(letra); i++)
    {
        letra[i] = toupper(letra[i]); // Converte a string digitada para maiúscula
    }
    printf("+==============================================================================+\n");
}

// Função que imprime a interface da tela de escolha do nome do MultiPlayer ou retornar ao menu principal (foto de ser int)
int telaMultiplayer(char nomeA[], char nomeB[], int TAM_NOME)
{
    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                            -= MODO MULTIPLAYER =-                           |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    0                                        |\n");
    printf("|                                |   /|\\                                       |\n");
    printf("|                                |   / \\                                       |\n");
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("| Digite nome do jogador 1 ou \"0\" / \"Enter\" p/ voltar:                         |\n");
    printf("+------------------------------------------------------------------------------+\n");
    scanfFgets(nomeA, TAM_NOME); // Lê o nome do jogador
    for (int i = 0; i < strlen(nomeA); i++)
    {
        if (!isalpha(nomeA[i]))
        {
            inputErroEntrada("Nome invalido! Tente novamente.");
            return 1; // Retorna 1 se o usuário quiser voltar
        }
    }
    if (nomeA[0] == '0')
    {
        return 1; // Retorna 1 se o usuário quiser voltar
    }
    else if (nomeA[0] == '\n')
    {
        return 1; // Retorna 1 se o usuário quiser voltar
    }
    else
    {
        system("cls || clear");
        printf("+==============================================================================+\n");
        printf("|                            -= MODO MULTIPLAYER =-                           |\n");
        printf("+==============================================================================+\n");
        printf("|                                                                              |\n");
        printf("|                                +----+                                        |\n");
        printf("|                                |/   |                                        |\n");
        printf("|                                |    0                                        |\n");
        printf("|                                |   /|\\                                       |\n");
        printf("|                                |   / \\                                       |\n");
        printf("|                                |                                             |\n");
        printf("|                             ==============                                   |\n");
        printf("|                             \"            \"                                   |\n");
        printf("|                                                                              |\n");
        printf("+------------------------------------------------------------------------------+\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("| Digite nome do jogador 2 ou \"0\" / \"Enter\" p/ voltar:                         |\n");
        printf("+------------------------------------------------------------------------------+\n");
        scanfFgets(nomeB, TAM_NOME); // Lê o nome do jogador
        for (int i = 0; i < strlen(nomeB); i++)
        {
            if (!isalpha(nomeB[i]))
            {
                inputErroEntrada("Nome invalido! Tente novamente.");
                return 1; // Retorna 1 se o usuário quiser voltar
            }
        }
        if (nomeB[0] == '0')
        {
            return 1; // Retorna 1 se o usuário quiser voltar
        }
        else if (nomeB[0] == '\n')
        {
            return 1; // Retorna 1 se o usuário quiser voltar
        }
        else
        {

            system("cls || clear");
            printf("+==============================================================================+\n");
            printf("|                            -= MODO MULTIPLAYER =-                           |\n");
            printf("+==============================================================================+\n");
            printf("|                                                                              |\n");
            printf("|                                +----+                                        |\n");
            printf("|                                |/   |                                        |\n");
            printf("|                                |    0                                        |\n");
            printf("|                                |   /|\\                                       |\n");
            printf("|                                |   / \\                                       |\n");
            printf("|                                |                                             |\n");
            printf("|                             ==============                                   |\n");
            printf("|                             \"            \"                                   |\n");
            printf("|                                                                              |\n");
            printf("+------------------------------------------------------------------------------+\n");
            printf("|                                                                              |\n");
            printf("|                                                                              |\n");
            printf("|                                                                              |\n");
            printf("|                                                                              |\n");
            printf("|                                                                              |\n");
            printf("|                                                                              |\n");
            printf("|                                                                              |\n");
            printf("|                                                                              |\n");
            printf("|                                                                              |\n");
            printf("|                                                                              |\n");
            printf("|                                                                              |\n");
            sprintf(texto, "Bem-vindos(as), %s e %s! Preparando o jogo . . .", nomeA, nomeB);
            formatacaoBonita();
            printf("+==============================================================================+\n");
            Sleep(ESPERAR);
            return 0; // Retorna 0 se o usuário quiser continuar
        }
    }
}

// Função que confirma a adição de uma nova palavra
int confirmarAdicaoDePalavra()
{
    char opcao;

    do
    {
        system("cls || clear");
        printf("+==============================================================================+\n");
        printf("|                      -= CONFIRMAR ADICAO DE PALAVRA =-                       |\n");
        printf("+==============================================================================+\n");
        printf("|                                                                              |\n");
        printf("|                                +----+                                        |\n");
        printf("|                                |/   |                                        |\n");
        printf("|                                |    0                                        |\n");
        printf("|                                |   /|\\                                       |\n");
        printf("|                                |   / \\                                       |\n");
        printf("|                                |                                             |\n");
        printf("|                             ==============                                   |\n");
        printf("|                             \"            \"                                   |\n");
        printf("|                                                                              |\n");
        printf("+------------------------------------------------------------------------------+\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("+------------------------------------------------------------------------------+\n");
        printf("| Deseja realmente adicionar? (1 - SIM, 0 - NAO)                               |\n");
        printf("+==============================================================================+\n");
        scanf(" %c", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case '1':
            return 1; // Retorna 1 se o usuário confirmar a adição
        case '0':
            return 0; // Retorna 0 se o usuário não confirmar a adição
        default:
            inputErroEntrada("Opcao invalida! Tente 1 ou 0.");
            Sleep(ESPERAR);
        }
    } while (opcao != '0');
}

// Função que imprime a interface da tela gerenciamento de palavras do arquivo
void telaMenuGerenciarPalavras()
{
    char opcao;

    do
    {
        system("cls || clear");
        printf("+==============================================================================+\n");
        printf("|                       -= GERENCIAMENTO DE PALAVRAS =-                        |\n");
        printf("+==============================================================================+\n");
        printf("|                                                                              |\n");
        printf("|                                +----+                                        |\n");
        printf("|                                |/   |                                        |\n");
        printf("|                                |    0                                        |\n");
        printf("|                                |   /|\\                                       |\n");
        printf("|                                |   / \\                                       |\n");
        printf("|                                |                                             |\n");
        printf("|                             ==============                                   |\n");
        printf("|                             \"            \"                                   |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("+------------------------------------------------------------------------------+\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("| 1. Adicionar nova palavra                                                    |\n");
        printf("| 0. Voltar ao menu anterior                                                   |\n");
        printf("+------------------------------------------------------------------------------+\n");
        printf("| Escolha uma opcao:                                                           |\n");
        printf("+==============================================================================+\n");
        scanf(" %c", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case '1':
            adicionarPalavra();
            break;
        case '0':
            break;
        default:
            inputErroEntrada("Opcao invalida! Tente 1, 2 ou 0.");
            Sleep(ESPERAR);
        }
    } while (opcao != '0');
}

// Função que imprime a interface da tela pesquisa de historicos no arquivo
void telaGerenciarHistorico()
{
    int opcao;
    do
    {
        system("cls || clear");
        printf("+==============================================================================+\n");
        printf("|                               -= HISTORICO =-                                |\n");
        printf("+==============================================================================+\n");
        printf("|                                                                              |\n");
        printf("|                                +----+                                        |\n");
        printf("|                                |/   |                                        |\n");
        printf("|                                |    0                                        |\n");
        printf("|                                |   /|\\                                       |\n");
        printf("|                                |   / \\                                       |\n");
        printf("|                                |                                             |\n");
        printf("|                             ==============                                   |\n");
        printf("|                             \"            \"                                   |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("+------------------------------------------------------------------------------+\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("|                                                                              |\n");
        printf("| 1. Pesquisar por Data                                                        |\n");
        printf("| 2. Pesquisar por Nome do Jogador                                             |\n");
        printf("| 3. Pesquisar por ID da Partida                                               |\n");
        printf("| 4. Listar todos os historicos                                                |\n");
        printf("| 0. Voltar ao menu anterior                                                   |\n");
        printf("+------------------------------------------------------------------------------+\n");
        printf("| Escolha uma opcao:                                                           |\n");
        printf("+==============================================================================+\n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            telaHistoricoData();
            break;
        case 2:
            telaHistoricoNome();
            break;
        case 3:
            telaHistoricoID();
            break;
        case 4:
            telaListarHistorico();
            break;
        case 0:
            break;
        default:
            printf("Opcao invalida. Tente novamente. \n");
        }

    } while (opcao != 0);
}

// Função e tela que que auxilia na lógica de adicionar palavras
void telaAdiconarPalavra(char *text)
{
    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                           -= ADICIONAR PALAVRA =-                            |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    0                                        |\n");
    printf("|                                |   /|\\                                       |\n");
    printf("|                                |   / \\                                       |\n");
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("| %s\n", text);
    printf("+==============================================================================+\n");
}

void telaPesquisaHistorico(char *text)
{
    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                          -= PESQUISA HISTORICO  =-                           |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    0                                        |\n");
    printf("|                                |   /|\\                                       |\n");
    printf("|                                |   / \\                                       |\n");
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("| %s\n", text);
    printf("+==============================================================================+\n");
}

// Função que imprime a interface da tela de ranking
void telaRanking()
{
    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                                 -= RANKING =-                                |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("| Aperte qualquer tecla para voltar...                                         |\n");
    printf("|                                                                              |\n");
    printf("+==============================================================================+\n");
    lerArquivoRanking();
    getchar();
}

void telaHistoricoID() {
    int id = 0;
    telaPesquisaHistorico("Digite o ID da partida ou \"Enter\" para voltar:                               |");
    scanf("%d", &id);
    getchar();

    // if (!isdigit(id)) {
    //     inputErroEntrada("ID invalido! Nao digite espaco ou acentuacao.");
    //     return; // Retorna se o usuário quiser voltar
    // }

    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                              -= HISTORICO ID =-                              |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("| Aperte qualquer tecla para voltar...                                         |\n");
    printf("|                                                                              |\n");
    printf("+==============================================================================+\n");
    pesquisarPorID(id);
    getchar();
}

void telaHistoricoNome() {
    char nome[MAX_NOME];
    telaPesquisaHistorico("Digite o nome do jogador ou \"Enter\" para voltar:                             |");

    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < strlen(nome); i++) {
        if (!isalpha(nome[i])) {
            inputErroEntrada("Nome invalido! Nao digite espaco ou acentuacao.");
            return; // Retorna se o usuário quiser voltar
        }
    }
    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                             -= HISTORICO NOME =-                             |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("| Aperte qualquer tecla para voltar...                                         |\n");
    printf("|                                                                              |\n");
    printf("+==============================================================================+\n");
    pesquisarPorNome(nome);
    getchar();
}

void telaHistoricoData() {
    char data[MAX_DATA];
    telaPesquisaHistorico("Digite a data (DDMMAAAA ou DD/MM/AAAA) ou \"Enter\" para voltar:               |");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n\r")] = '\0';  // remove o \n

    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                             -= HISTORICO DATA =-                             |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("| Aperte qualquer tecla para voltar...                                         |\n");
    printf("|                                                                              |\n");
    printf("+==============================================================================+\n");
    pesquisarPorData(data);
    getchar();
}

void telaListarHistorico() {
    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                             -= LISTA HISTORICO =-                            |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("| Aperte qualquer tecla para voltar...                                         |\n");
    printf("|                                                                              |\n");
    printf("+==============================================================================+\n");
    listarHistorico();
    getchar();
}

void formatacaoBonita() {
    printf("| %s", texto); 
    for (int i = 0; i < tamanho_linha - strlen(texto); i++) {
        if (i != tamanho_linha - strlen(texto) - 1)
            printf(" ");
        else 
            printf("|\n");}
}

void formatacaoBonitaFim() { 
    for (int i = 0; i < tamanho_linha - strlen(texto); i++) {
        if (i != tamanho_linha - strlen(texto) - 1)
            printf(" ");
        else 
            printf("|\n");}
}

void finalizandoJogo() {
    char text[50] = "Saindo do jogo . . .";

    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                               -=  CARREGANDO =-                              |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    0                                        |\n");
    printf("|                                |   /|\\                                       |\n");
    printf("|                                |   / \\                                       |\n");
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                             "); 
    for (int i = 0; i < strlen(text); i++) { 
        printf("%c", text[i]);
        Sleep(200);}
    sprintf(texto, "                            %s", text);
    formatacaoBonitaFim();
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("| Obrigado por jogar!!                                                         |\n");      
    printf("+==============================================================================+\n");
}

// Função que imprime o rosto do Professor Marciano
void marciano()
{
    system("cls || clear");
    printf("+============================================================================================================================+\n");
    printf("|                                                                                                                            |\n");
    printf("                                                     ..--::::::++++::::::..                                                             \n");
    printf("                                                 ..--::::::::::++::::++++::--..                                                         \n");
    printf("                                               --::++++::--              ..--::--..                                                     \n");
    printf("                                           --::++++::                          --::--                                                   \n");
    printf("                                       --::::::::..                                --::..                                               \n");
    printf("                                   ..::::++::--                                      ..----..                                           \n");
    printf("                               ..--::++++::                                              ::::--..                                       \n");
    printf("                             ..++++++++::                                                  ::::++--                                     \n");
    printf("                             ++mm++++--                                                      ::++mm::                                   \n");
    printf("                           ::mmmm++::                                                        ..++mmMM--                                 \n");
    printf("                         ..++mmmm--                                                            ..::mmMM..                               \n");
    printf("                         ::MMMM::....                                                            ..++MMmm                               \n");
    printf("                         ::MMMM::....                                                            ..::MMMM--                             \n");
    printf("                         ::MMMM::....                                                          ....::MMMM--                             \n");
    printf("                         ::MMMM--....            ....                                            ..::@@MM..                             \n");
    printf("                         --MMmm......  ....--------------......................------....        ..::MMMM..                             \n");
    printf("                         ::MM++......--::++mmmmmmmmmmmm::::----------------::::++mmmm++::----..  ..::@@mm                               \n");
    printf("                         --@@mm..--::++mmmmMMMM@@@@@@@@mmmm++::----::::::++mm@@@@@@@@MMMMmm++--....--@@++                               \n");
    printf("                         --MMmm----++++++++::::++++mmMMMMmmmm++::::::++mmmmMM@@MMmm++::::++++++::--::MM++                               \n");
    printf("                         ..++mm++::::::::::::::++++mmmmmm++mm++::--::++mmmmmmMMmmmmmm++++++++mm++++++mm::                               \n");
    printf("                         ..++mm::----::::::::++++++mmmmmmmmmmmm++++mmmmMMMMMMMMmmmm++++::::++++::::mmMM--                               \n");
    printf("                           ++mm++----::::++++mmMM@@MMMMMMmmmmMMMMMMMMMMmmMMMMMMMM@@MMmm++++++::::--mmmm                                 \n");
    printf("                           ++MM++..--::++MMMMMM@@@@MMMMMMmmmmMM::..mmMMmmMMMMMMMM@@@@@@MMmm++++::::mmmm                                 \n");
    printf("                           ++MM++..--::++++mmmmMM@@MMMMmmmmmm++    ..MMmmmmMMMMMM@@MMmmMMMMmm::::::mmMM                                 \n");
    printf("                           ++MM++..--::::::::++++++++++++++MM::      mmMM++++mm++mm++++++++++::--::mmMM                                 \n");
    printf("                           ++MM++..------::::::::::::::::++mm..      --MM++::::++::++++::::::----::mmMM                                 \n");
    printf("                           ++MM++....----------::::::----mm::        ..mm++::::::::::::::::------++mmMM                                 \n");
    printf("                           ::mm--++  ..----------------::mm..          ++mm::--------------------::mm::                                 \n");
    printf("                           ::mm----::--  ..----------++MM::            --mmmm------------------++::mm                                 \n");
    printf("                           --mm--..----::++++mmmmmm++++++......    ......::::++++++++::::++::--::::++                                 \n");
    printf("                           --++::------......------::::::------....------::++::--........--------::mm                                 \n");
    printf("                           --++++------......--------::::++mm++----::mm++++++::------......------++mm                                 \n");
    printf("                           ..++++--------....--------::++mm@@MM++++MM##@@++::::--------..--------++mm                                 \n");
    printf("                           ..::mm------------------::::++@@####@@MM@@####mm::::::::------------::mmmm                                 \n");
    printf("                             ++mm::--------------::::++mm@@##############@@mm++++::--------::--++mm::                                 \n");
    printf("|                                                                                                                            |\n");
    printf("+============================================================================================================================+\n");
    printf("|                                                    -= OBRIGADO, MARCIANO! =-                                               |\n");
    printf("+============================================================================================================================+\n");
}
//-----------------------------------------------------------------------------------
