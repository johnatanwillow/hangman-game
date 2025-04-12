#include <stdio.h> // Para printf() e scanf()
#include <string.h> // Para strlen() e strchr()
#include <locale.h> // Para setlocale()
#include <time.h> // Para time()
#include <stdlib.h> // Para system()
#include <ctype.h> // Para isalpha() e strchr()
#include <windows.h>  // Para Sleep() no Windows

int main() 
{
    int opcao = 0; // Variável para armazenar a opção escolhida pelo usuário

    do
    {
        system("cls || clear");
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
        printf("                                                       JOGO DA FORCA                                                       \n");
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
        menu();
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
        printf("Escolha uma opção: \n"); scanf("%d", &opcao);
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
    } while (opcao != 0);
    
    return 0;
}