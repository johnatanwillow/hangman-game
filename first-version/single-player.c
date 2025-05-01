#include <stdio.h> // Para printf() e scanf()
#include <string.h> // Para strlen() e strchr()
#include <locale.h> // Para setlocale()
#include <time.h> // Para time()
#include <stdlib.h> // Para system()
#include <ctype.h> // Para isalpha() e strchr()
#include <windows.h>  // Para Sleep() no Windows
//----------------------------------------------------
#include "interface.h" 
//----------------------------------------------------

// Váriavies globais
#define TAM_NOME 50
#define MAX_ERROS 6
#define TAM_PALAVRA 20
#define TAM_DICA 100
#define ESPERAR 3000 // Tempo de espera em segundos (para Sleep)

void singlePlayerJogo() 
{
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    setlocale(LC_ALL, "Portuguese_Brazil");

    // Matriz 3x3 de strings: cada linha = um "registro", cada coluna = ID, nome e dica
    char *palavras[3][3] = {
        {"8", "MACA", "Eh uma fruta vermelha!"},
        {"9", "ELISANGELA", "Eh mulher e dá aula de matematica!"},
        {"10", "MAMAO", "Eh uma fruta laranja!"}
    };

    int tamanho_matriz, id_randomico;
    char palavra[TAM_PALAVRA];
    char dica[TAM_DICA];

    tamanho_matriz = sizeof(palavras) / sizeof(palavras[0]); // Tamanho da matriz (número de palavras)

    id_randomico = rand() % tamanho_matriz; // Gera um índice aleatório entre 0 e e o tamanho da matriz - 1

    strncpy(palavra, palavras[id_randomico][1], sizeof(palavra));
    strncpy(dica, palavras[id_randomico][2], sizeof(dica));
    palavra[sizeof(palavra) - 1] = '\0'; // Garante terminação nula
    dica[sizeof(dica) - 1] = '\0'; // Garante terminação nula

    int pontuacao_player = 0; // Variável para armazenar a pontuação do jogador
    char letra[TAM_PALAVRA]; // Variável para armazenar a letra digitada pelo usuário
    char nome_player[TAM_NOME];
    char jogador1[TAM_NOME], jogador2[TAM_NOME];
	char letras_testadas[27];  // 27 posições, cada uma pode armazenar 1 letra + '\0'
	int tamanho = strlen(palavra);
    int acertou = 0; // Variável para verificar se o usuário acertou a palavra completa
	int erros = 0; // Contador de erros
	int acertos = 0; // Contador de acertos
	int i, pos; // Operar sobre o vetor de letras testadas
    // Partes do corpo para poder alterar a imagem do boneco
    char partes_do_corpo[6] = {'0', '|', '/', '\\', '/', '\\'};
    char errou_palavra = ' ';

	// Inicializa letras_testadas com strings vazias e adicona o caractere nulo 
    // (operador nulo) em cada elemento. Isso garante que cada posição do 
    // vetor seja inicializada corretamente e não contenha lixo de memória.
    for(i = 0; i < 27; i++){
        letras_testadas[i] = '\0';
    }

	char descoberta[tamanho + 1]; // Vetor para armazenar e mostrar as letras descobertas (corretas)
    
    // Inicializa o vetor descoberta com '_' e adiciona o caractere nulo no final
	for(i = 0; i < tamanho; i++){
        descoberta[i]= '_';
	}
	descoberta[tamanho] = '\0';

    if (telaSingleplayer(nome_player, TAM_NOME) == 1) {
        return; // Se o usuário quiser voltar, sai da função
    }

	while(erros < MAX_ERROS && acertos < tamanho && acertou == 0)
    {
        telaSingleplayerJogo(letra, dica, letras_testadas, descoberta, acertos, erros, MAX_ERROS, tamanho, partes_do_corpo, TAM_PALAVRA);
        
        if (strlen(letra) == 1)
        {
            if(!isalpha(letra[0])){
                inputErroLogicaUsuario("❌ A entrada deve ser uma letra. Caractere invalido! ❌", partes_do_corpo);
            }
    
            // Compara cacharacteres da palavra com a letra digitada
            if(strchr(palavra, letra[0]) != 0) 
            {
                for (i = 0; i <= tamanho; i++) 
                {
                    if (palavra[i] == letra[0] && descoberta[i] == '_') 
                    {
                        descoberta[i] = letra[0]; 
                        acertos++;
                    }
                } 
            } else {
                int verificador_testado = 0; // Variável para verificar se a letra já foi testada
                for (i = 0; i < strlen(letras_testadas); i++) 
                {
                    if (toupper(letras_testadas[i]) == letra[0]) {
                        verificador_testado = 1;
                        break;
                    }
                }
                if (verificador_testado != 0) {
                    inputErroLogicaUsuario("❌ Essa letra ja foi testada. Tente uma diferente! ❌", partes_do_corpo);
                } else {
                    inputErroLogicaUsuario("❌ Errou! Essa letra nao esta na palavra! ❌", partes_do_corpo);
                    erros++;
                    for (i = MAX_ERROS - 1; i >= MAX_ERROS - erros; i--) 
                    {
                        partes_do_corpo[i] = errou_palavra; // Atualiza a parte do corpo do boneco
                    }
                }
            }
        
            // Verifica se a letra já foi testada (se está em letras_testadas); se não, adiciona na próxima posição livre de letras_testadas
            pos = -1;
            for (i = 0; i < 26; i++) 
            {
                if (letras_testadas[i] == letra[0]) {
                    pos = i;
                    break;
                }
                if (letras_testadas[i] == '\0') {
                    pos = i;
                    break;
                }
            }
            if (pos != -1 && letras_testadas[pos] == '\0') {
                letras_testadas[pos] = letra[0];
            }
        } else if (strlen(letra) == tamanho) {
            if (strcmp(letra, palavra) == 0) {
                acertou = 1; // O usuário acertou a palavra
                acertos = tamanho; // Define o número de acertos como o tamanho da palavra
            } else {
                inputErroLogicaUsuario("❌ Errou! Essa palavra nao eh a correta! ❌", partes_do_corpo);
                erros++;
                for (i = MAX_ERROS - 1; i >= MAX_ERROS - erros; i--) 
                {
                    partes_do_corpo[i] = errou_palavra; // Atualiza a parte do corpo do boneco
                }
            }
        } else if (strlen(letra) != 1 || strlen(letra) != tamanho) {
            inputErroLogicaUsuario("❌ Tente uma letra ou a palavra inteira! ❌", partes_do_corpo);
        }
	}
	if ((acertou) || (acertos == tamanho))
    {
		telaResultadoJogo(partes_do_corpo, palavra, acertos, erros, letras_testadas, "✅ CONGRATULATIONS ✅", "✅ Parabens! Voce acertou a palavra e ganhou o jogo! ✅",nome_player);

	} else {
		telaResultadoJogo(partes_do_corpo, palavra, acertos, erros, letras_testadas, "❌ GAME OVER ❌", "❌ Sadness! Voce perdeu o jogo! ❌", nome_player);
	}
}
