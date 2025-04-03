#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <windows.h>  // Para Sleep() no Windows
#else
    #include <unistd.h>   // Para sleep() no Linux/macOS
#endif

#define MAX_ERROS 6

int main() {
	setlocale(LC_CTYPE, "Portuguese_Brazil.1252");
	
	char palavra[] = "opa";
	char letra;
	int tamanho = strlen(palavra);
	int erros = 0;
	int esperar = 2;
	int acertos = 0;
	int i;
	
    // Inicializa o vetor descoberta com '_'
    // e adiciona o caractere nulo no final
	char descoberta[tamanho + 1];

	for(i = 0; i < tamanho; i++){
	    descoberta[i]= '_';
	}
	descoberta[tamanho] = '\0';
	
	while(erros < MAX_ERROS && acertos < tamanho)
    {
        printf("-----------------------------------------\n");
        printf("               HANGMAN-GAME              \n");
        printf("-----------------------------------------\n");
		printf("Erros -> %d.\n", erros);
		printf("Acertos -> %d.\n", acertos);
		printf("Restam %d chances.\n", (MAX_ERROS - erros));
        printf("-----------------------------------------\n");

        for (i = 0; i < tamanho; i++) 
        {
            if (descoberta[i] == '_') 
            {
                printf("_ ");
            } else {
                printf("%c ", descoberta[i]);
            }
        }

		printf("\n\n-----------------------------------------\n");
		printf("Tente uma letra: \n"); scanf(" %c", &letra);
        printf("-----------------------------------------\n");
		
		if(strchr(palavra, letra) != 0)
        {
			for (i = 0; i <= tamanho; i++) 
            {
                if (palavra[i] == letra && descoberta[i] == '_') 
                {
                    descoberta[i] = letra; 
                    acertos++;
                }
		    } 
        } else {
			system("cls || clear");
			printf("-----------------------------------------\n");
			printf("A letra %c não está na palavra\n", letra);
			printf("\nAguarde...\n", letra);
			printf("-----------------------------------------\n");
			erros++;

			Sleep(esperar * 1000); // Espera 3 segundos (3000 milissegundos)
		}

		system("cls || clear");
	}
	if(acertos == tamanho)
    {
		printf("-----------------------------------------\n");
        printf("Parabéns você conseguiu!", palavra);

		printf("-----------------------------------------\n");
		Sleep(esperar * 1000);
		
	} else {
		printf("-----------------------------------------\n");
        printf("Que pena, você não conseguiu! A palavra era: %s \a\n", palavra);

		printf("-----------------------------------------\n");
		Sleep(esperar * 1000);
	}
	
	return 0;
}