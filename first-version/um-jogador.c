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


int main() {
	setlocale(LC_CTYPE, "Portuguese");
	
	char palavra[] = "victor";
	char letra;
	char letras_testadas[27][2];  // 27 posições, cada uma pode armazenar 1 letra + '\0'
	int tamanho = strlen(palavra);
	int erros = 0;
	int esperar = 2;
	int acertos = 0;
	int i, pos;

	// Inicializa letras_testadas com strings vazias
    for(i = 0; i < 27; i++){
        letras_testadas[i][0] = '\0';
    }
    	
    // Inicializa o vetor descoberta com '_'e adiciona o caractere nulo no final
	char descoberta[tamanho + 1];

	for(i = 0; i < tamanho; i++){
	    descoberta[i]= '_';
	}
	descoberta[tamanho] = '\0';
	
	while(erros < MAX_ERROS && acertos < tamanho)
    {
		system("cls || clear");
        printf("---------------------------------------------------------------------------------------------------------------------------\n");
        printf("                                                       HANGMAN-GAME                                                       \n");
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
		printf("Tente uma letra: \n"); scanf(" %c", &letra);
        printf("---------------------------------------------------------------------------------------------------------------------------\n");

		// -------------------------------------------------------- //
		// Verifica se a letra já foi testada; se não, adiciona na próxima posição livre
        pos = -1;
        for (i = 0; i < 26; i++) 
        {
            if (letras_testadas[i][0] == letra) {
                pos = i;
                break;
            }
            if (letras_testadas[i][0] == '\0') {
                pos = i;
                break;
            }
        }
        if (pos != -1 && letras_testadas[pos][0] == '\0') {
            letras_testadas[pos][0] = letra;
            letras_testadas[pos][1] = '\0';
        }
		// -------------------------------------------------------- //
		
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
			printf("---------------------------------------------------------------------------------------------------------------------------\n");
			printf("A letra %c não está na palavra\n", letra);
			printf("\nAguarde...\n", letra);
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
		printf("\nNumero de erros: %d", erros);
		printf("\nNumero de acertos: %d\n", acertos);
		printf("Letras testadas ->");
		for (i = 0; i < 26; i++) 
		{
			// Se o primeiro caractere do elemento não for o terminador nulo, exibe a letra
            if (letras_testadas[i][0] != '\0')
                printf(" | %c", letras_testadas[i][0]);
		}
		printf(" |");
		printf("\nA palavra era: %s\n\n", palavra);
		printf("---------------------------------------------------------------------------------------------------------------------------\n");
		Sleep(esperar * 1000);
		
	} else {
		printf("---------------------------------------------------------------------------------------------------------------------------\n");
		printf("============================================== JOGO DA FORCA COMPLETO COM FRACASSO ========================================\n");
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
		printf("\nA palavra era: %s\n", palavra);
		printf("\n---------------------------------------------------------------------------------------------------------------------------\n");
		marciano();
		printf("\n---------------------------------------------------------------------------------------------------------------------------\n");
		Sleep(esperar * 1000);
	}
	
	return 0;
}