#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <ctype.h> // Para isalpha() e strchr()
#include <conio.h> // Para getchar()
//---------------------------------------
#include "palavras.h"
#include "interface.h"
//---------------------------------------

#define MAX_TENTATIVAS 6
#define ESPERAR 3000 // Tempo de espera em segundos (para Sleep)

//-------------------------------------------------------------------------------------
// Função que limpa o buffer de entrada (usada para evitar problemas com o fgets())
void limparBuffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Função que lê a entrada padrão até o tamanho máximo ou até encontrar um '\n'
void scanfFgets(char *text, int size)
{
    // Lê a entrada padrão até o tamanho máximo ou até encontrar um '\n'
    // Deve-se limpar a entrada padrão, pois o fgets() lê até o \n, apenas se houver uma quebra de linha antes, então o fgets() não vai ler nada.
    fgets(text, size, stdin);
    strtok(text, "\n"); // Remove the newline character from the string
    // text[strcspn(text, "\n")] = '\0';
}

// Exibe o menu principal do jogo
void exibirMenuPrincipal()
{

    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                             -= JOGO DA FORCA =-                              |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|      +----+                                                                  |\n");
    printf("|      |/   |                                                                  |\n");
    printf("|      |    0                                                                  |\n");
    printf("|      |   /|\\                  M E N U   P R I N C I P A L                    |\n");
    printf("|      |   / \\                                                                 |\n");
    printf("|      |                                                                       |\n");
    printf("|   ==============                                                             |\n");
    printf("|   \"            \"                                                             |\n");
    printf("|                                                                              |\n");
    printf("|------------------------------------------------------------------------------|\n");
    printf("| 1. Jogar (Singleplayer)                                                      |\n");
    printf("| 2. Jogar (Multiplayer)                                                       |\n");
    printf("| 3. Gerenciar Palavras                                                        |\n");
    printf("| 4. Ver Ranking                                                               |\n");
    printf("| 5. Ver Historico                                                             |\n");
    printf("| 0. Sair                                                                      |\n");
    printf("+==============================================================================+\n");
    printf("| Escolha uma opcao:                                                           |\n");
    printf("+==============================================================================+\n");
}

// Função que imprime alguma mensagem de erro de input para o usuário
void inputErroEntrada(char *texto_do_erro)
{

    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                                  -= ERROR =-                                 |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    0                                        |\n");
    printf("|                                |   /|\\                                       |\n");
    printf("|                                |   / \\                                       |\n");
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("| %s                                                                           \n", texto_do_erro);
    printf("|------------------------------------------------------------------------------|\n");
    printf("| Aguarde...                                                                   |\n");
    printf("+==============================================================================+\n");
    Sleep(ESPERAR);
}

// Função que imprime alguma mensagem de erro para o usuário (para logica do jogo SinglePlayer)
void inputErroLogicaUsuario(char *texto_do_erro, char *partes_do_corpo)
{
    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                                   -= ERROR =-                                |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    %c                                        |\n", partes_do_corpo[0]);
    printf("|                                |   %c%c%c                                       |\n", partes_do_corpo[2], partes_do_corpo[1], partes_do_corpo[3]);
    printf("|                                |   %c %c                                       |\n", partes_do_corpo[4], partes_do_corpo[5]);
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("| %s                                                                            \n", texto_do_erro);
    printf("|------------------------------------------------------------------------------|\n");
    printf("| Aguarde...                                                                   |\n");
    printf("+==============================================================================+\n");
    Sleep(ESPERAR);
}

// Função que imprime o resultado do jagador em jogo SinglePlayer
void telaResultadoJogo(char *partes_do_corpo, char *palavra, int acertos, int erros, char *letras_testadas, char *title, char *messenge, char *nome, int pontuacao)
{
    int i;

    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                          -= %s =-                       |\n", title);
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    %c                                        |\n", partes_do_corpo[0]);
    printf("|                                |   %c%c%c                                       |\n", partes_do_corpo[2], partes_do_corpo[1], partes_do_corpo[3]);
    printf("|                                |   %c %c                                       |\n", partes_do_corpo[4], partes_do_corpo[5]);
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("| %s! %s                          \n", nome, messenge);
    printf("+------------------------------------------------------------------------------+\n");
    printf("| A palavra era: %s                                                           \n", palavra);
    printf("| Sua pontuacao foi: %d                                                       \n", pontuacao);
    printf("| Acertos: %d                                                                   |\n", acertos);
    printf("| Erros: %d                                                                     |\n", erros);
    printf("| Letras tentadas :");
    for (i = 0; i < 26; i++)
    {
        // Se o primeiro caractere do elemento não for o terminador nulo, exibe a letra
        if (letras_testadas[i] != '\0')
            printf(" %c ", letras_testadas[i]);
    }
    printf("\n+------------------------------------------------------------------------------+\n");
    printf("| Pressione uma tecla para continuar...\n");
    printf("+------------------------------------------------------------------------------+\n");
    getchar(); // Aguarda o usuário pressionar uma tecla
}

// Função que imprime a interface da tela de jogo SinglePlayer
void telaSingleplayerJogo(char *letra, char *dica, char *letras_testadas, char *descoberta, int acertos, int erros, int MAX_ERROS, int tamanho_palavra, char *partes_do_corpo, int TAM_PALAVRA, char *dificuldade)
{
    int i;

    // FUNCAO QUE MOSTRA A TELA DE JOGO SINGLEPLAYER (PALAVRAS, TENTATIVAS RESTANTES E LETRAS TENTADAS SAO MERAMENTE ILUSTRATIVAS)
    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                             -= MODO SINGLEPLAYER =-                          |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    %c                                        |\n", partes_do_corpo[0]);
    printf("|                                |   %c%c%c                                       |\n", partes_do_corpo[2], partes_do_corpo[1], partes_do_corpo[3]);
    printf("|                                |   %c %c                                       |\n", partes_do_corpo[4], partes_do_corpo[5]);
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("| Acertos: %d                                                                   |\n", acertos);
    printf("| Erros: %d                                                                     |\n", erros);
    printf("| Tentativas restantes: %d                                                      |\n", MAX_ERROS - erros);
    printf("| Dificuldade: %s (%d letras)                                                   \n", dificuldade, tamanho_palavra);
    printf("| Letras tentadas :");
    for (i = 0; i < 26; i++)
    {
        // Se o primeiro caractere do elemento não for o terminador nulo, exibe a letra
        if (letras_testadas[i] != '\0')
            printf(" %c ", letras_testadas[i]);
    }
    printf("\n| DICA: \"%s\"                                                             \n", dica);
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                             ");
    for (i = 0; i < tamanho_palavra; i++)
    {
        if (descoberta[i] == '_')
        {
            printf("_ ");
        }
        else
        {
            printf("%c ", descoberta[i]);
        }
    }
    printf("\n|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("| Digite uma letra: ");
    printf("\n+------------------------------------------------------------------------------+\n");
    scanfFgets(letra, TAM_PALAVRA); // Lê a letra digitada pelo usuário
    for (i = 0; i < strlen(letra); i++)
    {
        letra[i] = toupper(letra[i]); // Converte a string digitada para maiúscula
    }
    printf("+==============================================================================+\n");
}

// Função que imprime a interface da tela de escolha do nome do SinglePlayer ou retornar ao menu principal (foto de ser int)
int telaSingleplayer(char nome[], int TAM_NOME)
{
    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                            -= MODO SINGLEPLAYER =-                           |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    0                                        |\n");
    printf("|                                |   /|\\                                       |\n");
    printf("|                                |   / \\                                       |\n");
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("| Digite seu nome / \"0\" para voltar:                                           |\n");
    printf("+------------------------------------------------------------------------------+\n");
    scanfFgets(nome, TAM_NOME); // Lê o nome do jogador
    if (nome[0] == '0')
    {
        return 1; // Retorna 1 se o usuário quiser voltar
    }
    else
    {
        printf("+------------------------------------------------------------------------------+\n");
        printf("| Bem-vindo(a), %s! Preparando o jogo . . .                                     \n", nome);
        printf("+==============================================================================+\n");
        Sleep(ESPERAR);
        return 0; // Retorna 0 se o usuário quiser continuar
    }
}

// Função que imprime a interface da tela de jogo Multiplayer
// (ainda não implementada, mas já está com o esqueleto pronto)
void telaMultiplayerJogo(char *jogador1, char *jogador2, char *letra)
{
    int erros = 2; // EXEMPLO
    char palavra_oculta[] = "_ _ _ _ _";
    char letras_tentadas[] = "A, E";
    // MESMA COISA DA TELA DE JOGO DO MODO SINGLEPLAYER, POREM AGORA ADAPTADA PARA O MODO MULTIPLAYER (IMAGEM ILUSTRATIVA)

    for (int rodada = 1; rodada <= 2; rodada++)
    {
        system("cls || clear");
        printf("+==============================================================================+\n");
        printf("|                              -= MODO MULTIPLAYER =-                          |\n");
        printf("+==============================================================================+\n");
        printf("|                                                                              |\n");
        printf("|                                +----+                                        |\n");
        printf("|                                |/   |                                        |\n");
        printf("|                                |    0                                        |\n");
        printf("|                                |   /|\\                                       |\n");
        printf("|                                |   / \\                                       |\n");
        printf("|                                |                                             |\n");
        printf("|                             ==============                                   |\n");
        printf("|                             \"            \"                                   |\n");
        printf("|                                                                              |\n");
        printf("+------------------------------------------------------------------------------+\n");
        printf("|                                                                              |\n");
        printf("| Palavra: %s                                                           |\n", palavra_oculta);
        printf("| Letras tentadas: %s                                                        |\n", letras_tentadas);
        printf("| Tentativas restantes: %d                                                      |\n", MAX_TENTATIVAS - erros);
        printf("+------------------------------------------------------------------------------+\n");
        printf("| Jogador %d (%s), digite uma letra: ", rodada, rodada == 1 ? jogador1 : jogador2);
        limparBuffer();
        scanfFgets(letra, sizeof(letra));
        for (int i = 0; i < strlen(letra); i++)
        {
            letra[i] = toupper(letra[i]); // Converte a string digitada para maiúscula
        }
        printf("| Voce digitou: %c\n", letra);
        printf("+==============================================================================+\n");
        getchar();
    }
}

// Função que imprime a interface da tela de escolha dos nomes do Multiplayer
// (ainda não implementada, mas já está com o esqueleto pronto)
void telaMultiplayer(char *jogador1, char *jogador2, char *letra)
{
    // ALGORITMO SEMELHANTE AO DO MODO SINGLEPLAYER, TODAVIA AGORA ADAPTADO PARA O MODO MULTIPLAYER
    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                             -= MODO MULTIPLAYER =-                           |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    0                                        |\n");
    printf("|                                |   /|\\                                       |\n");
    printf("|                                |   / \\                                       |\n");
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("| Jogador 1, digite seu nome: ");
    printf("+------------------------------------------------------------------------------+\n");
    limparBuffer();
    scanfFgets(jogador1, sizeof(jogador1));
    printf("+------------------------------------------------------------------------------+\n");
    printf("| Jogador 2, digite seu nome: ");
    printf("+------------------------------------------------------------------------------+\n");
    limparBuffer();
    scanfFgets(jogador2, sizeof(jogador2));
    printf("+------------------------------------------------------------------------------+\n");
    printf("| Jogadores %s e %s, sejam vem-vindos(as). Preparando o jogo...\n", jogador1, jogador2);
    printf("+==============================================================================+\n");
    getchar();
    telaMultiplayerJogo(jogador1, jogador2, letra);
}

// Função que imprime a interface da tela gerenciamento de palavras do arquivo
void telaMenuGerenciarPalavras()
{
    char opcao;

    do
    {
        system("cls || clear");
        printf("+==============================================================================+\n");
        printf("|                       -= GERENCIAMENTO DE PALAVRAS =-                        |\n");
        printf("+==============================================================================+\n");
        printf("|                                                                              |\n");
        printf("|                                +----+                                        |\n");
        printf("|                                |/   |                                        |\n");
        printf("|                                |    0                                        |\n");
        printf("|                                |   /|\\                                       |\n");
        printf("|                                |   / \\                                       |\n");
        printf("|                                |                                             |\n");
        printf("|                             ==============                                   |\n");
        printf("|                             \"            \"                                   |\n");
        printf("|                                                                              |\n");
        printf("+------------------------------------------------------------------------------+\n");
        printf("| 1. Adicionar nova palavra                                                    |\n");
        printf("| 2. Excluir palavra existente                                                 |\n");
        printf("| 0. Voltar ao menu anterior                                                   |\n");
        printf("+------------------------------------------------------------------------------+\n");
        printf("| Escolha uma opcao:                                                           |\n");
        printf("+==============================================================================+\n");
        scanf(" %c", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case '1':
            adicionarPalavra();
            break;
        case '2':
            // excluirPalavra();
            break;
        case '0':
            break;
        default:
            inputErroEntrada("Opcao invalida! Tente 1, 2 ou 0.");
            Sleep(ESPERAR);
        }
    } while (opcao != '0');
}

// Função e tela que que auxilia na lógica de adicionar palavras
void telaAdiconarPalavra(char *text)
{
    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                           -= ADICIONAR PALAVRA =-                            |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    0                                        |\n");
    printf("|                                |   /|\\                                       |\n");
    printf("|                                |   / \\                                       |\n");
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("|                                                                              |\n");
    printf("| %s\n", text);
    printf("+==============================================================================+\n");
}

// Função que imprime a interface da tela de ranking
// (ainda não implementada, mas já está com o esqueleto pronto)
void telaRanking()
{
    char opcao;
    // FUNCAO QUE ABRE O MENU DE RANKING, PRESSIONANDO '0' VOCE E LEVADO DE VOLTA AO MENU PRINCIPAL (NOMES E MODO DE CONTAGEM DE PONTOS SAO UM EXEMPLO)
    // NOS MENUS DE RANKING E HISTORICO PREFERI NAO INSERIR O "LOGO DO JOGO"(O DESENHO DA FORCA)
    do
    {
        system("cls || clear");
        printf("+==============================================================================+\n");
        printf("|                                 -= RANKING =-                                |\n");
        printf("+==============================================================================+\n");
        printf("| Pos | Nome              | Pontos | Partidas | Vitorias                       |\n");
        printf("|-----|-------------------|--------|----------|--------------------------------|\n");
        printf("| 1   | Fulano            |  1500  |    10    |     8                          |\n");
        printf("| 2   | Beltrano          |  1350  |     9    |     7                          |\n");
        printf("| 3   | Ciclano           |  1200  |    11    |     6                          |\n");
        printf("+------------------------------------------------------------------------------+\n");
        printf("| Escolha uma opcao:                                                           |\n");
        printf("+==============================================================================+\n");
        scanf(" %c", &opcao);
        limparBuffer();
    } while (opcao != '0');
}

// Função que imprime a interface da tela de histórico
// (ainda não implementada, mas já está com o esqueleto pronto)
void telaHistorico()
{
    char opcao;
    // FUNCAO QUE ABRE O MENU DE PESQUISA DO HISTORICO (ESTAGIO INICIAL), COM AS OPCOES DE PESQUISA POR DATA, POR NOME DO PLAYER E POR ID DA PARTIDA, PRESSIONANDO '0' VOCE E LEVADO DE VOLTA AO MENU INICIAL/PRINCIPAL
    do
    {
        system("cls || clear");
        printf("+==============================================================================+\n");
        printf("|                               -= HISTORICO =-                                |\n");
        printf("+==============================================================================+\n");
        printf("| 1. Pesquisar por Data                                                        |\n");
        printf("| 2. Pesquisar por Nome do Jogador                                             |\n");
        printf("| 3. Pesquisar por ID da Partida                                               |\n");
        printf("| 0. Voltar ao menu anterior                                                   |\n");
        printf("+------------------------------------------------------------------------------+\n");
        printf("| Escolha uma opcao:                                                           |\n");
        printf("+==============================================================================+\n");
        scanf(" %c", &opcao);
        limparBuffer();
    } while (opcao != '0');
}

// Função que imprime o rosto do Professor Marciano
void marciano()
{
    printf("+=================================================================================================================+\n");
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
    printf("\n+============================================================================================================================+\n");
    printf("|                                                    -= OBRIGADO, MARCIANO! =-                                               |\n");
    printf("+============================================================================================================================+\n");
}
//-------------------------------------------------------------------------------------