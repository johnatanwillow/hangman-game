#include <stdio.h>
#include <string.h> // Para strlen() e strchr()
#include <locale.h> // Para setlocale()
#include <time.h> // Para time()
#include <stdlib.h> // Para system()
#include <ctype.h> // Para isalpha() e strchr()
#include <windows.h>  // Para Sleep() no Windows

// Número máximo de erros permitidos
#define MAX_ERROS 6

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
    printf("                             ::MM::::::::::::::++mmMMMMMM@@################@@MMmm++::::::::::::++mm..                                 \n");
    printf("                             ..MM++::::::::::++MM@@@@##@@@@@@@@######@@@@######@@MMmm::::::::::++mm..                                 \n");
    printf("                               MMmm++++::::++MM@@####@@MMMMmmmmMM@@MMmmMMMM@@####@@MM++::::++++::::..                                 \n");
    printf("                               MMMMmmmm++++MM@@######@@mmMMmmmmMMMMMMMMMM@@@@######@@mm::++mm++++::                                   \n");
    printf("                               mmMMMMMMmmmm@@@@####@@MMMM++++++++++++++++mmMM@@####@@mm++mmmmmmmm++                                   \n");
}

int main() 
{
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    setlocale(LC_ALL, "Portuguese"); // Define a localidade para o idioma português
    setlocale(LC_CTYPE, "Portuguese");

    // Matriz 3x3 de strings: cada linha = um "registro", cada coluna = ID, nome e dica
    char *palavras[3][3] = {
        {"1", "VICTOR", "Começa com V"},
        {"2", "MARCIANO", "Começa com M"},
        {"3", "GUSTAVO", "Termina com O"}
    };

    int tamanho_matriz, id_randomico;
    char palavra[20];
    char dica[100];

    tamanho_matriz = sizeof(palavras[0]) / sizeof(palavras[0][0]); // Tamanho da matriz (número de palavras)

    id_randomico = rand() % tamanho_matriz; // Gera um índice aleatório entre 0 e e o tamanho da matriz - 1

    strncpy(palavra, palavras[id_randomico][1], sizeof(palavra));
    strncpy(dica, palavras[id_randomico][2], sizeof(dica));
    palavra[sizeof(palavra) - 1] = '\0'; // Garante terminação nula
    palavra[sizeof(dica) - 1] = '\0'; // Garante terminação nula

    char letra, letra_digitada;
	char letras_testadas[27][2];  // 27 posições, cada uma pode armazenar 1 letra + '\0'
	int tamanho = strlen(palavra);
	int erros = 0; // Contador de erros
	int acertos = 0; // Contador de acertos
	int esperar = 2; // Tempo de espera em segundos (para Sleep)
	int i, pos; // Operar sobre o vetor de letras testadas

	/* Inicializa letras_testadas com strings vazias e adicona o caractere nulo 
    (operador nulo) no final. Isso garante que cada posição do 
    vetor seja inicializada corretamente */
    for(i = 0; i < 27; i++){
        letras_testadas[i][0] = '\0';
    }

	char descoberta[tamanho + 1];
    
    // Inicializa o vetor descoberta com '_' e adiciona o caractere nulo no final
	for(i = 0; i < tamanho; i++){
	    descoberta[i]= '_';
	}
	descoberta[tamanho] = '\0';

	while(erros < MAX_ERROS && acertos < tamanho)
    {
		system("cls || clear");
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
        printf("                                                       JOGO DA FORCA                                                       \n");
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
		printf("Erros -> %d.\n", erros);
		printf("Acertos -> %d.\n", acertos);
		printf("Letras testadas ->");
		for (i = 0; i < 26; i++)
		{
			// Se o primeiro caractere do elemento não for o terminador nulo, exibe a letra
            if (letras_testadas[i][0] != '\0')
                printf(" | %c", letras_testadas[i][0]);
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
		printf("Tente uma letra: \n"); scanf(" %c", &letra_digitada);
        letra = toupper(letra_digitada); // Converte a letra digitada para maiúscula
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
        
        // Verifica se é um letra do alfabeto
        if(!isalpha(letra)){
        	system("cls || clear");
            printf("---------------------------------------------------------------------------------------------------------------------------\n");
            printf("                                                       JOGO DA FORCA                                                       \n");
            printf("---------------------------------------------------------------------------------------------------------------------------\n");
			printf("A entrada deve ser uma letra. Caractere \"%c\" \n", letra);
			printf("\nAguarde...\n", letra);
			printf("---------------------------------------------------------------------------------------------------------------------------\n");

			Sleep(esperar * 1000); // Espera 3 segundos (3000 milissegundos)
			
			continue;
		}

		// Verifica se a letra já foi testada (se está em letras_testadas); se não, adiciona na próxima posição livre
        pos = -1;
        for (i = 0; i < 26; i++) 
        {
            // if (letras_testadas[i][0] == letra) {
            //     pos = i;
            //     break;
            // }
            if (letras_testadas[i][0] == '\0') {
                pos = i;
                break;
            }
        }
        if (pos != -1 && letras_testadas[pos][0] == '\0') {
            letras_testadas[pos][0] = letra;
            letras_testadas[pos][1] = '\0';
        }

        // Compara cacharacteres da palavra com a letra digitada
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
        }
        // -------------------------------------------------------------------- TEST
        // else if (strlen(letra) != 1 || strlen(letra) != tamanho) {
        //     system("cls || clear");
        //     printf("---------------------------------------------------------------------------------------------------------------------------\n");
        //     printf("                                                       JOGO DA FORCA                                                       \n");
        //     printf("---------------------------------------------------------------------------------------------------------------------------\n");
		// 	printf("Tente testar uma letra ou a palavra inteira.\n");
		// 	printf("\nAguarde...\n");
		// 	printf("---------------------------------------------------------------------------------------------------------------------------\n");

		// 	Sleep(esperar * 1000); // Espera 3 segundos (3000 milissegundos)
        // }
        else {
			system("cls || clear");
            printf("---------------------------------------------------------------------------------------------------------------------------\n");
            printf("                                                       JOGO DA FORCA                                                       \n");
            printf("---------------------------------------------------------------------------------------------------------------------------\n");
			printf("A letra \"%c\" não está na palavra!\n", letra);
			printf("\nAguarde...\n");
			printf("---------------------------------------------------------------------------------------------------------------------------\n");
			erros++;

			Sleep(esperar * 1000); // Espera 3 segundos (3000 milissegundos)
		}

		system("cls || clear");
	}
	if(acertos == tamanho)
    {
		printf("---------------------------------------------------------------------------------------------------------------------------\n");
		printf("============================================== JOGO DA FORCA COMPLETO COM SUCESSO =========================================\n");
		printf("---------------------------------------------------------------------------------------------------------------------------\n");
        printf("Parabéns! Você acertou a palavra!\n");
        printf("\nA palavra era: %s\n\n", palavra);
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
		printf("\nNumero de errros: %d", erros);
		printf("\nNumero de acertos: %d\n", acertos);
		printf("Letras testadas ->");
		for (i = 0; i < 26; i++) 
		{
			// Se o primeiro caractere do elemento não for o terminador nulo, exibe a letra
            if (letras_testadas[i][0] != '\0')
                printf(" | %c", letras_testadas[i][0]);
		}
		printf(" |");
		printf("\n---------------------------------------------------------------------------------------------------------------------------\n");
        marciano(); // Chama a função para imprimir a cara do marciano
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
		Sleep(esperar * 1000);

	} else {
		printf("---------------------------------------------------------------------------------------------------------------------------\n");
		printf("============================================== JOGO DA FORCA COMPLETO COM FRACASSO =========================================\n");
		printf("---------------------------------------------------------------------------------------------------------------------------\n");
        printf("Se deu mal! Você não conseguiu!\n");
        printf("\nA palavra era: %s\n\n", palavra);
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
		printf("\nNumero de errros: %d", erros);
		printf("\nNumero de acertos: %d\n", acertos);
		printf("Letras testadas ->");
		for (i = 0; i < 26; i++) 
		{
			// Se o primeiro caractere do elemento não for o terminador nulo, exibe a letra
            if (letras_testadas[i][0] != '\0')
                printf(" | %c", letras_testadas[i][0]);
		}
		printf(" |");
		printf("\n---------------------------------------------------------------------------------------------------------------------------\n");
        marciano(); // Chama a função para imprimir a cara do marciano
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
		Sleep(esperar * 1000);
	}

	return 0;
}