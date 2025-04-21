#include <stdio.h> // Para printf() e scanf()
#include <string.h> // Para strlen() e strchr()
#include <locale.h> // Para setlocale()
#include <time.h> // Para time()
#include <stdlib.h> // Para system()
#include <ctype.h> // Para isalpha() e strchr()
#include <windows.h>  // Para Sleep() no Windows

// Declarando protótipos de funções
void scanf_completo(char *text, int size);
void input_clear(); 
void marciano(); 

// Número máximo de erros permitidos
#define MAX_ERROS 6

int main(void) 
{
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    setlocale(LC_ALL, "Portuguese_Brazil");

    // Matriz 3x3 de strings: cada linha = um "registro", cada coluna = ID, nome e dica
    char *palavras[3][3] = {
        {"8", "MAÇÃ", "É uma fruta vermelha!"},
        {"9", "ELISANGELA", "É mulher e dá aula de matemática!"},
        {"10", "MAMAO", "É uma fruta laranja!"}
    };

    int tamanho_matriz, id_randomico;
    char palavra[20];
    char dica[100];

    tamanho_matriz = sizeof(palavras) / sizeof(palavras[0]); // Tamanho da matriz (número de palavras)

    id_randomico = rand() % tamanho_matriz; // Gera um índice aleatório entre 0 e e o tamanho da matriz - 1

    strncpy(palavra, palavras[id_randomico][1], sizeof(palavra));
    strncpy(dica, palavras[id_randomico][2], sizeof(dica));
    palavra[sizeof(palavra) - 1] = '\0'; // Garante terminação nula
    palavra[sizeof(dica) - 1] = '\0'; // Garante terminação nula

    char letra[20]; // Variável para armazenar a letra digitada pelo usuário
	char letras_testadas[27];  // 27 posições, cada uma pode armazenar 1 letra + '\0'
	int tamanho = strlen(palavra);
    int acertou = 0; // Variável para verificar se o usuário acertou a palavra completa
	int erros = 0; // Contador de erros
	int acertos = 0; // Contador de acertos
	int esperar = 2; // Tempo de espera em segundos (para Sleep)
	int i, pos; // Operar sobre o vetor de letras testadas

	/* Inicializa letras_testadas com strings vazias e adicona o caractere nulo 
    (operador nulo) no final. Isso garante que cada posição do 
    vetor seja inicializada corretamente */
    for(i = 0; i < 27; i++){
        letras_testadas[i] = '\0';
    }

	char descoberta[tamanho + 1];
    
    // Inicializa o vetor descoberta com '_' e adiciona o caractere nulo no final
	for(i = 0; i < tamanho; i++){
	    descoberta[i]= '_';
	}
	descoberta[tamanho] = '\0';

	while(erros < MAX_ERROS && acertos < tamanho && acertou == 0)
    {
		system("cls || clear");
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
        printf("                                                       JOGO DA FORCA                                                       \n");
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
		printf("Erros -> %d.\n", erros);
		printf("Acertos -> %d.\n", acertos);
		printf("Letras testadas ->");
        printf(" |");
		for (i = 0; i < 26; i++)
		{
			// Se o primeiro caractere do elemento não for o terminador nulo, exibe a letra
            if (letras_testadas[i] != '\0')
                printf(" %c |", letras_testadas[i]);
		}
        printf("\nDica -> %s.\n", dica);
		printf("\nRestam %d chances.\n", (MAX_ERROS - erros));
        printf("---------------------------------------------------------------------------------------------------------------------------\n");

        for (i = 0; i < tamanho; i++) 
        {
            if (descoberta[i] == '_') 
            {
                printf("_ ");
            } else {
                printf("%c ", descoberta[i]);
            }
        }

		printf("\n\n---------------------------------------------------------------------------------------------------------------------------\n");
		printf("Tente uma letra: \n");
        // input_clear(); // Limpa o buffer de entrada
        scanf_completo(letra, sizeof(letra)); // Lê a letra digitada pelo usuário
        for (int i = 0; i < strlen(letra); i++) {
            letra[i] = toupper(letra[i]); // Converte a string digitada para maiúscula
        }("---------------------------------------------------------------------------------------------------------------------------\n");
        
        if (strlen(letra) == 1)
        {
            if(!isalpha(letra[0])){
                system("cls || clear");
                printf("---------------------------------------------------------------------------------------------------------------------------\n");
                printf("                                                       JOGO DA FORCA                                                       \n");
                printf("---------------------------------------------------------------------------------------------------------------------------\n");
                printf("A entrada deve ser uma letra. Caractere \"%c\" \n", letra);
                printf("\nAguarde...\n");
                printf("---------------------------------------------------------------------------------------------------------------------------\n");
    
                Sleep(esperar * 1000);
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
                    system("cls || clear");
                    printf("---------------------------------------------------------------------------------------------------------------------------\n");
                    printf("                                                       JOGO DA FORCA                                                       \n");
                    printf("---------------------------------------------------------------------------------------------------------------------------\n");
                    printf("A letra \"%c\" já foi testada!\n", letra[0]);
                    printf("\nAguarde...\n");
                    printf("---------------------------------------------------------------------------------------------------------------------------\n");

                    Sleep(esperar * 1000);
                } else {
                    system("cls || clear");
                    printf("---------------------------------------------------------------------------------------------------------------------------\n");
                    printf("                                                       JOGO DA FORCA                                                       \n");
                    printf("---------------------------------------------------------------------------------------------------------------------------\n");
                    printf("A letra \"%c\" não está na palavra!\n", letra[0]);
                    printf("\nAguarde...\n");
                    printf("---------------------------------------------------------------------------------------------------------------------------\n");
                    erros++;

                    Sleep(esperar * 1000);
                }
            }
        
            // Verifica se a letra já foi testada (se está em letras_testadas); se não, adiciona na próxima posição livre
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
                system("cls || clear");
                printf("---------------------------------------------------------------------------------------------------------------------------\n");
                printf("                                                       JOGO DA FORCA                                                       \n");
                printf("---------------------------------------------------------------------------------------------------------------------------\n");
                printf("A palavra \"%s\" não é a correta!\n", letra);
                printf("\nAguarde...\n");
                printf("---------------------------------------------------------------------------------------------------------------------------\n");
                erros++;
                Sleep(esperar * 1000); // Espera 3 segundos (3000 milissegundos)
            }
        } else if (strlen(letra) != 1 || strlen(letra) != tamanho) {
            system("cls || clear");
            printf("---------------------------------------------------------------------------------------------------------------------------\n");
            printf("                                                       JOGO DA FORCA                                                       \n");
            printf("---------------------------------------------------------------------------------------------------------------------------\n");
			printf("Tente uma letra ou a palavra inteira.\n");
			printf("\nAguarde...\n");
			printf("---------------------------------------------------------------------------------------------------------------------------\n");

			Sleep(esperar * 1000); // Espera 3 segundos (3000 milissegundos)
        }

		system("cls || clear");
	}
	if ((acertou) || (acertos == tamanho))
    {
		printf("---------------------------------------------------------------------------------------------------------------------------\n");
		printf("============================================== JOGO DA FORCA COMPLETO COM SUCESSO =========================================\n");
		printf("---------------------------------------------------------------------------------------------------------------------------\n");
        printf("Parabéns! Você acertou a palavra!\n");
        printf("\nA palavra é: %s\n\n", palavra);
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
		printf("\nNumero de errros: %d", erros);
		printf("\nNumero de acertos: %d\n", acertos);
		printf("Letras testadas ->");
		printf(" |");
		for (i = 0; i < 26; i++)
		{
			// Se o primeiro caractere do elemento não for o terminador nulo, exibe a letra
            if (letras_testadas[i] != '\0')
                printf(" %c |", letras_testadas[i]);
		}
		printf("\n---------------------------------------------------------------------------------------------------------------------------\n");
        marciano(); // Chama a função para imprimir a cara do marciano
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
		Sleep(esperar * 1000);

	} else {
		printf("---------------------------------------------------------------------------------------------------------------------------\n");
		printf("============================================== JOGO DA FORCA COMPLETO COM FRACASSO =========================================\n");
		printf("---------------------------------------------------------------------------------------------------------------------------\n");
        printf("Se deu mal! Você não conseguiu!\n");
        printf("\nA palavra é: %s\n\n", palavra);
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
		printf("\nNumero de errros: %d", erros);
		printf("\nNumero de acertos: %d\n", acertos);
		printf("Letras testadas ->");
		printf(" |");
		for (i = 0; i < 26; i++)
		{
			// Se o primeiro caractere do elemento não for o terminador nulo, exibe a letra
            if (letras_testadas[i] != '\0')
                printf(" %c |", letras_testadas[i]);
		}
		printf("\n---------------------------------------------------------------------------------------------------------------------------\n");
        marciano(); // Chama a função para imprimir a cara do marciano
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
		Sleep(esperar * 1000);
	}

	return 0;
}

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

// Função que imprime a cara do marciano
void marciano() 
{
    printf("                                                     ..--::::::++++::::::..                                                             \n");
    printf("                                                 ..--::::::::::++::::++++::--..                                                         \n");
    printf("                                               --::++++::--              ..--::--..                                                     \n");
    printf("                                           --::++++::                          --::--                                                   \n");
    printf("                                       --::::::::..                                --::..                                               \n");
    printf("                                   ..::::++::--                                      ..----..                                           \n");
    printf("                               ..--::++++::                                              ::::--..                                       \n");
    printf("                             ..++++++++::                                                  ::::++--                                     \n");
    printf("                             ++mm++++--                                                      ::++mm::                                   \n");
    printf("                           ::mmmm++::                                                        ..++mmMM--                                 \n");
    printf("                         ..++mmmm--                                                            ..::mmMM..                               \n");
    printf("                         ::MMMM::....                                                            ..++MMmm                               \n");
    printf("                         ::MMMM::....                                                            ..::MMMM--                             \n");
    printf("                         ::MMMM::....                                                          ....::MMMM--                             \n");
    printf("                         ::MMMM--....            ....                                            ..::@@MM..                             \n");
    printf("                         --MMmm......  ....--------------......................------....        ..::MMMM..                             \n");
    printf("                         ::MM++......--::++mmmmmmmmmmmm::::----------------::::++mmmm++::----..  ..::@@mm                               \n");
    printf("                         --@@mm..--::++mmmmMMMM@@@@@@@@mmmm++::----::::::++mm@@@@@@@@MMMMmm++--....--@@++                               \n");
    printf("                         --MMmm----++++++++::::++++mmMMMMmmmm++::::::++mmmmMM@@MMmm++::::++++++::--::MM++                               \n");
    printf("                         ..++mm++::::::::::::::++++mmmmmm++mm++::--::++mmmmmmMMmmmmmm++++++++mm++++++mm::                               \n");
    printf("                         ..++mm::----::::::::++++++mmmmmmmmmmmm++++mmmmMMMMMMMMmmmm++++::::++++::::mmMM--                               \n");
    printf("                           ++mm++----::::++++mmMM@@MMMMMMmmmmMMMMMMMMMMmmMMMMMMMM@@MMmm++++++::::--mmmm                                 \n");
    printf("                           ++MM++..--::++MMMMMM@@@@MMMMMMmmmmMM::..mmMMmmMMMMMMMM@@@@@@MMmm++++::::mmmm                                 \n");
    printf("                           ++MM++..--::++++mmmmMM@@MMMMmmmmmm++    ..MMmmmmMMMMMM@@MMmmMMMMmm::::::mmMM                                 \n");
    printf("                           ++MM++..--::::::::++++++++++++++MM::      mmMM++++mm++mm++++++++++::--::mmMM                                 \n");
    printf("                           ++MM++..------::::::::::::::::++mm..      --MM++::::++::++++::::::----::mmMM                                 \n");
    printf("                           ++MM++....----------::::::----mm::        ..mm++::::::::::::::::------++mmMM                                 \n");
    printf("                           ::mm--++  ..----------------::mm..          ++mm::--------------------::mm::                                 \n");
    printf("                           ::mm----::--  ..----------++MM::            --mmmm------------------++::mm                                 \n");
    printf("                           --mm--..----::++++mmmmmm++++++......    ......::::++++++++::::++::--::::++                                 \n");
    printf("                           --++::------......------::::::------....------::++::--........--------::mm                                 \n");
    printf("                           --++++------......--------::::++mm++----::mm++++++::------......------++mm                                 \n");
    printf("                           ..++++--------....--------::++mm@@MM++++MM##@@++::::--------..--------++mm                                 \n");
    printf("                           ..::mm------------------::::++@@####@@MM@@####mm::::::::------------::mmmm                                 \n");
    printf("                             ++mm::--------------::::++mm@@##############@@mm++++::--------::--++mm::                                 \n");
}