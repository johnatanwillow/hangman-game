//-----------------------------------------------------
// EXECUTE NO TERMINAL:
// gcc main.c ./src/single-player.c ./src/interface.c ./src/palavras.c ./src/ranking.c ./src/historico.c ./src/multiplayer.c -o forca.exe
// gcc src/*.c -o forca.exe
//-----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <conio.h> //PARA RECEBER AS PALVRAS DO USUÁRIO
#include <windows.h>
//-----------------------------------------------------
#include "./include/interface.h"
#include "./include/palavras.h"
#include "./include/historico.h"
#include "./include/single-player.h"
#include "./include/multiplayer.h"
//-----------------------------------------------------

// Váriavies globais
#define ESPERAR 3000 // Tempo de espera em segundos (para Sleep)
#define ESPERAR_FIM 4000

int main()
{
    setlocale(LC_ALL, "Portuguese");

    char opcao;

    do
    {
        exibirMenuPrincipal();
        scanf(" %c", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case '1':
            singlePlayerJogo();
            break;
        case '2':
            multiPlayerJogo();
            break;
        case '3':
            telaMenuGerenciarPalavras();
            break;
        case '4':
            telaRanking();
            break;
        case '5':
            telaGerenciarHistorico();
            break;
        case '0':
            finalizandoJogo();
            Sleep(ESPERAR_FIM);
            marciano();
            break;
        default:
            inputErroEntrada("Opcao invalida! Tente novamente.");
            Sleep(ESPERAR);
        }
    } while (opcao != '0');

    return 0;
}