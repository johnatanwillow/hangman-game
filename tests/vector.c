#include <stdio.h>
#include <string.h> // Para strlen() e strchr()
#include <locale.h> // Para setlocale()
#include <time.h> // Para time()
#include <stdlib.h> // Para system()
#include <ctype.h> // Para isalpha() e strchr()
#include <windows.h>  // Para Sleep() no Windows

// Alternativa ao scanf, mas aqui podemos ler até o tamanho máximo da string
void scanf_completo(char *text, int size) 
{
    // Lê a entrada padrão até o tamanho máximo ou até encontrar um '\n'
    // Deve-se limpar a entrada padrão, pois o fgets() lê até o \n, apenas se houver uma quebra de linha antes, então o fgets() não vai ler nada.
    fgets(text, size, stdin);
    strtok(text, "\n"); // Remove the newline character from the string
}

// Define o limpador de entrada padrão
void input_clear() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() 
{
    char *palavras[6][3] = {
        {"1", "VICTOR", "É aluno de SI"},
        {"2", "MARCIANO", "É um professor"},
        {"3", "GUSTAVO CARDOSO", "Termina com O"},
        {"4", "MURILO", "Termina com O"},
        {"5", "GUSTAVO", "Fez o frontend do projeto"},
        {"6", "ARTHUR", "É das arabia"}
    };
    // Matriz 3x3 de strings: cada linha = um "registro", cada coluna = código, nome, descrição
    char palavra[20];
    char teste[] = "victor";
    int tamanho_matriz = sizeof(palavras) / sizeof(palavras[0]); // Tamanho da matriz (número de palavras)

    scanf_completo(palavra, sizeof(palavra)); // Lê a string digitada pelo usuário

    for (int i = 0; i < strlen(palavra); i++) {
        palavra[i] = toupper(palavra[i]); // Converte a string digitada para maiúscula
    }

    // palavra[sizeof(palavra) - 1] = '\0'; // Garante terminação nula

    // strcpy(atribue, toupper(palavra[0])); // Copia a letra digitada para a variável letra

    printf("A string digitada é: %c\n", palavra[0]);
    printf("Len: %d\n", strlen(palavra));
    if (strcmp(palavra, teste) == 0) {
        printf("As strings são iguais.\n");
    } else {
        printf("As strings são diferentes.\n");
    }
    for (int i = 0; i < tamanho_matriz; i++) {
        printf("A letra %d é: %s\n", i, palavras[i][1]);
    }

    return 0;
}