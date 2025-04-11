#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strncpy()
#include <time.h>
#include <math.h>
#include <locale.h> // Para setlocale()

int main() 
{
    // Matriz 3x3 de strings: cada linha = um "registro", cada coluna = código, nome, descrição
    char palavras[] = "victor";
    char teste[] = "victor";

    if (strcmp(palavras, teste) == 0) {
        printf("As strings são iguais.\n");
    } else {
        printf("As strings são diferentes.\n");
    }

    return 0;
}