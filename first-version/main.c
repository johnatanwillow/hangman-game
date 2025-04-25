#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <conio.h> //PARA RECEBER AS PALVRAS DO USUÁRIO
#include <windows.h>
//-----------------------------------------------------
#include "interface.h"
#include "single-player.h"
//-----------------------------------------------------


// Váriavies globais
#define ESPERAR 3000 // Tempo de espera em segundos (para Sleep)

int main() {
    setlocale(LC_ALL, "Portuguese");

    char opcao;

    do {
        system("cls || clear");
        exibirMenuPrincipal();
        scanf(" %c", &opcao);
        limparBuffer();

        switch (opcao) {
            case '1':
                singleplayerJogo();
                break;
            case '2':
                // telaMultiplayer();
                break;
            case '3':
                telaMenuGerenciarPalavras();
                break;
            case '4':
                telaRanking();
                break;
            case '5':
                telaHistorico();
                break;
            case '0':
                printf("Saindo do jogo...\n");
                Sleep(ESPERAR);
                system("cls || clear");
                marciano();
                break;
            default:
            system("cls || clear");
                inputErroUsuario("Opcao invalida! Tente novamente.");
                Sleep(ESPERAR);
        }
    } while (opcao != '0');

    return 0;
}