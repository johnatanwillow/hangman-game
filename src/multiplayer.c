#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h> // Para isalpha() e strchr()
#include <windows.h>
//----------------------------------------------------
#include "../include/palavras.h"
#include "../include/interface.h"
#include "../include/multiplayer.h"
#include "../include/ranking.h"
#include "../include/historico.h"
//----------------------------------------------------

// Váriavies globais
#define MAX_ERROS 6
#define TAM_NOME 30
#define TAM_PALAVRA 30
#define TAM_DICA 150
#define ESPERAR 2000 // Tempo de espera em segundos (para Sleep)
//----------------------------------------------------

// Função que executa o jogo
void multiPlayerJogo()
{
    setlocale(LC_ALL, "American_English");

    // Definição de variáveis
    //----------------------------------------------------
    MultiPlayer player;
    player.pontuacao = 0;
    player.erros = 0;
    player.acertos = 0;
    player.atual = 0;
    char *palavra;           // Variável para armazenar a palavra escolhida
    char *dica;              // Variável para armazenar a dica da palavra escolhida
    char *dificuldade;       // Variável para armazenar a dificuldade da palavra escolhida
    char letra[TAM_PALAVRA]; // Variável para armazenar a letra digitada pelo usuário
    int i;                   // Operar sobre o vetor de letras testadas
    char data_hora[20];      // Armazenar data e hora
    //                        {'0', '|', '/', '\\', '/', '\\'};
    char partes_do_corpo[6] = {' ', ' ', ' ', ' ', ' ', ' '}; // Partes do corpo para poder alterar a imagem do boneco
    char errou_palavra[6] = {'0', '|', '/', '\\', '/', '\\'};

    temArquivo();                      // Verfica se existe o arquivo.txt
    palavraAleatoria(&palavra, &dica); // Inicia qual será a palavra e a dica
    int tamanho = strlen(palavra);
    //----------------------------------------------------

    // Instancias importantes
    //----------------------------------------------------
    // Inicializa letras_testadas com strings vazias e adicona o caractere nulo (operador nulo) em cada elemento.
    for (i = 0; i < 27; i++)
    {
        player.letras_testadas[i] = '\0';
    }

    char descoberta[tamanho + 1]; // Vetor para armazenar e mostrar as letras descobertas (corretas)

    // Inicializa o vetor descoberta com '_' e adiciona o caractere nulo no final
    for (i = 0; i < tamanho; i++)
    {
        if (palavra[i] == ' ')
            descoberta[i] = '-';
        else
            descoberta[i] = '_';
    }
    descoberta[tamanho] = '\0';
    //----------------------------------------------------

    //----------------------------------------------------
    dificuldadeDaPalavra(tamanho, &dificuldade); // Define a dificuldade da palavra
    //----------------------------------------------------

    // Início do jogo, obtençao do nome do jogador ou retornar ao menu principal
    //----------------------------------------------------
    if (telaMultiplayer(player.nomes[0], player.nomes[1], TAM_NOME) == 1)
    {
        return; // Se o usuário quiser voltar, sai da função MultiPlayerJogo
    }

    // Loop do jogo
    //----------------------------------------------------
    while (player.erros < MAX_ERROS && player.acertos < tamanho)
    {
        telaMultiplayerJogo(player, letra, dica, descoberta, MAX_ERROS, tamanho, partes_do_corpo, TAM_PALAVRA, dificuldade, player.atual);

        if (strlen(letra) == 1)
        {
            if (!isalpha(letra[0]))
            {
                inputErroLogicaUsuario("A entrada deve ser uma letra. Caractere invalido! ", partes_do_corpo);
            }
            else if (strchr(palavra, letra[0]) != 0)
            { // Compara cacharacteres da palavra com a letra digitada
                if (letraTestada(letra, player.letras_testadas) != 0)
                {
                    inputErroLogicaUsuario("Essa letra ja foi testada. Tente uma diferente! ", partes_do_corpo);
                }
                else
                {
                    for (i = 0; i <= tamanho; i++)
                    {
                        if (palavra[i] == letra[0] && descoberta[i] == '_')
                        {
                            descoberta[i] = letra[0];
                            player.acertos++;
                        }
                    }
                }
                adicionaLetraTestada(player.letras_testadas, letra);
            }
            else
            {
                if (letraTestada(letra, player.letras_testadas) != 0)
                {
                    inputErroLogicaUsuario("Essa letra ja foi testada. Tente uma diferente! ", partes_do_corpo);
                }
                else
                {
                    inputErroLogicaUsuario("Errou! Essa letra nao esta na palavra! ", partes_do_corpo);
                    // for (i = MAX_ERROS - 1; i >= MAX_ERROS - erros; i--) Lógica linda!!!
                    partes_do_corpo[player.erros] = errou_palavra[player.erros]; // Atualiza a parte do corpo do boneco
                    player.erros++;
                    player.atual = 1 - player.atual;
                }
                adicionaLetraTestada(player.letras_testadas, letra);
            }
        }
        else if (strlen(letra) == tamanho)
        {
            if (strcmp(letra, palavra) == 0)
            {
                player.acertos = tamanho; // Define o número de acertos como o tamanho da palavra
            }
            else
            {
                inputErroLogicaUsuario("Errou! Essa palavra nao eh a correta! ", partes_do_corpo);
                partes_do_corpo[player.erros] = errou_palavra[player.erros]; // Atualiza a parte do corpo do boneco
                player.erros++;
            }
        }
        else if (strlen(letra) != 1 || strlen(letra) != tamanho)
        {
            inputErroLogicaUsuario("Tente uma letra ou a palavra inteira! ", partes_do_corpo);
        }
    }
    if (player.acertos == tamanho)
    {
        // Pontuação: tamanho da palavra * (tentativas - quantidade de erros) * 100 - (quantidade de letras repetidas na palavra * 100)
        player.pontuacao = tamanho * (MAX_ERROS - player.erros) * 100 - (quantidadeLetrasRepetidasPalavra(tamanho, palavra) * 100); // Cálculo da pontuação
        telaResultadoJogoMultiplayer(player, partes_do_corpo, palavra, "    CONGRATULATIONS    ", "Congratulations! YOU WON THE GAME!!!");
        ranqueamento(player.nomes[player.atual], player.pontuacao);

        defineData(data_hora);
        escreveHistorico(player.nomes[player.atual], player.pontuacao, data_hora);
    }
    else
    {
        player.pontuacao = 0;
        // telaResultadoJogo(player, partes_do_corpo, palavra, "      GAME OVER      ", "Sadness! Voce perdeu o jogo! ");

        defineData(data_hora);
        escreveHistorico(player.nomes[player.atual], player.pontuacao, data_hora);
    }
}
