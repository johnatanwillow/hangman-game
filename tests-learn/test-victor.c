#include <stdio.h>
#include <string.h>
#include <locale.h>

#define MAX_ERROS 6

int main() {
	setlocale(LC_ALL,"Portuguese");
	
	char palavra[] = "babaca";
	char letra;
	int tamanho = strlen(palavra);
	int erros = 0;
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
		printf("Número de erros: %d\n", erros);
		printf("Número de acertos: %d\n", acertos);
		printf("%s\n", descoberta);
		
		printf("\nTente uma letra: \n"); scanf(" %c", &letra);
		
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
			printf("A letra %c não está na palavra\n", letra);
			erros++;
		}
	}
	if(acertos == tamanho)
    {
		printf("\a Parabéns vc conseguiu, a palavra era: %s", palavra);
		
	} else {
		printf("Não conseguiu, q pena. A palavra era: %s", palavra);
	}
	
	return 0;
}