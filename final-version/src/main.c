#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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
                telaSingleplayer();
                break;
            case '2':
                telaMultiplayer();
                break;
            case '3':
                menuGerenciarPalavras();
                break;
            case '4':
                telaRanking();
                break;
            case '5':
                telaHistorico();
                break;
            case '0':
                printf("Saindo do jogo...\n");
                system("cls || clear");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                getchar();
        }
    } while (opcao != '0');

    return 0;
}