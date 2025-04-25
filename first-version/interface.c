#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

#define TAM_NOME 50
#define MAX_TENTATIVAS 6
#define ESPERAR 3000

 //first version
 //introduzi funcoes e constantes e variaveis para deixar mais intuitivo o funcionamento das telas

void limparBuffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void scanfFgets(char *text, int size) 
{
    // Lê a entrada padrão até o tamanho máximo ou até encontrar um '\n'
    // Deve-se limpar a entrada padrão, pois o fgets() lê até o \n, apenas se houver uma quebra de linha antes, então o fgets() não vai ler nada.
    fgets(text, size, stdin);
    strtok(text, "\n"); // Remove the newline character from the string
}

void exibirMenuPrincipal() {
    //FUNCAO INICIAL QUE EXIBE MENU PRINCIPAL
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

void inputErroUsuario(char *texto_do_erro) {
    printf("+==============================================================================+\n");
    printf("|                                -= ERROR: 404 =-                              |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|      +----+                                                                  |\n");
    printf("|      |/   |                                                                  |\n");
    printf("|      |    0                                                                  |\n");
    printf("|      |   /|\\                       HOUVE ALGUM ERRO!                         |\n");
    printf("|      |   / \\                                                                 |\n");
    printf("|      |                                                                       |\n");
    printf("|   ==============                                                             |\n");
    printf("|   \"            \"                                                             |\n");
    printf("|                                                                              |\n");
    printf("|------------------------------------------------------------------------------|\n");
    printf("| %s                                                                            \n", texto_do_erro);
    printf("+==============================================================================+\n");
}

void telaSingleplayerJogo() {
    int erros = 3; // exemplo
    char palavra_oculta[] = "_ _ _ _ _";
    char letras_tentadas[] = "A, E, I";
    char letra;
    // parts do corpo para poder alterar a imagem do boneco
    char cabeca = '0';
    char tronco = '|';
    char partes_do_corpo[6] = {'0', '|', '/', '\\', '/', '\\'};
    char errou_palavra = ' ';

    //FUNCAO QUE MOSTRA A TELA DE JOGO SINGLEPLAYER (PALAVRAS, TENTATIVAS RESTANTES E LETRAS TENTADAS SAO MERAMENTE ILUSTRATIVAS)

    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                             -= MODO SINGLEPLAYER =-                          |\n");
    printf("+==============================================================================+\n");
    printf("|                                                                              |\n");
    printf("|                                +----+                                        |\n");
    printf("|                                |/   |                                        |\n");
    printf("|                                |    %c                                        |\n", partes_do_corpo[0]);
    printf("|                                |   %c%c%c                                       |\n", partes_do_corpo[1],partes_do_corpo[2],partes_do_corpo[3]);
    printf("|                                |   %c %c                                       |\n", partes_do_corpo[4],partes_do_corpo[5]);
    printf("|                                |                                             |\n");
    printf("|                             ==============                                   |\n");
    printf("|                             \"            \"                                   |\n");
    printf("|                                                                              |\n");
    printf("|------------------------------------------------------------------------------|\n");
    printf("|                                                                              |\n");
    printf("| Palavra: %s                                                           |\n", palavra_oculta);
    printf("| Letras tentadas: %s                                                     |\n", letras_tentadas);
    printf("| Tentativas restantes: %d                                                      |\n", MAX_TENTATIVAS - erros);
    printf("|------------------------------------------------------------------------------|\n");
    printf("| Digite uma letra: ");
    scanf(" %c", &letra);
    limparBuffer();
    printf("| Voce digitou: %c\n", letra);
    printf("+==============================================================================+\n");
    getchar();
}

void telaSingleplayer() {
    char nome[TAM_NOME];
    //TELA QUE PEDE PRA INSIRIR O NOME DO JOGADOR NO MODO SOLO
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
    printf("|------------------------------------------------------------------------------|\n");
    printf("| Digite seu nome:                                                             |\n");
    printf("|------------------------------------------------------------------------------|\n");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    printf("|------------------------------------------------------------------------------|\n");
    printf("| Bem-vindo, %s! Preparando o jogo...                                          |\n", nome);
    printf("+==============================================================================+\n");
    Sleep(ESPERAR); // Espera 3 segundos (3000 milissegundos)
    telaSingleplayerJogo();
}

void telaMultiplayerJogo(char jogador1[], char jogador2[]) {
    int erros = 2; //EXEMPLO
    char palavra_oculta[] = "_ _ _ _ _";
    char letras_tentadas[] = "A, E";
    char letra;
    //MESMA COISA DA TELA DE JOGO DO MODO SINGLEPLAYER, POREM AGORA ADAPTADA PARA O MODO MULTIPLAYER (IMAGEM ILUSTRATIVA)

    for (int rodada = 1; rodada <= 2; rodada++) {
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
        printf("|------------------------------------------------------------------------------|\n");
        printf("|                                                                              |\n");
        printf("| Palavra: %s                                                           |\n", palavra_oculta);
        printf("| Letras tentadas: %s                                                        |\n", letras_tentadas);
        printf("| Tentativas restantes: %d                                                      |\n", MAX_TENTATIVAS - erros);
        printf("|------------------------------------------------------------------------------|\n");
        printf("| Jogador %d (%s), digite uma letra: ", rodada, rodada == 1 ? jogador1 : jogador2);
        scanf(" %c", &letra);
        limparBuffer();
        printf("| Voce digitou: %c\n", letra);
        printf("+==============================================================================+\n");
        getchar();
    }
}

void telaMultiplayer() {
    char jogador1[TAM_NOME], jogador2[TAM_NOME];
    //ALGORITMO SEMELHANTE AO DO MODO SINGLEPLAYER, TODAVIA AGORA ADAPTADO PARA O MODO MULTIPLAYER
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
    printf("|------------------------------------------------------------------------------|\n");
    printf("| Jogador 1, digite seu nome: ");
    printf("|------------------------------------------------------------------------------|\n");
    fgets(jogador1, TAM_NOME, stdin);
    jogador1[strcspn(jogador1, "\n")] = '\0';
    printf("|------------------------------------------------------------------------------|\n");
    printf("| Jogador 2, digite seu nome: ");
    printf("|------------------------------------------------------------------------------|\n");
    fgets(jogador2, TAM_NOME, stdin);
    jogador2[strcspn(jogador2, "\n")] = '\0';
    printf("|------------------------------------------------------------------------------|\n");
    printf("| Jogadores %s e %s, sejam vem-vindos(as). Preparando o jogo...\n", jogador1, jogador2);
    printf("+==============================================================================+\n");
    getchar();
    telaMultiplayerJogo(jogador1, jogador2);
}

void menuGerenciarPalavras() {
    char opcao;
    //FUNCAO QUE ABRE O MENU DE GERENCIAMENTO DE PALAVRAS (DEFNITIVAMENTE NAO ESTA PRONTO)
    do {
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
        printf("|------------------------------------------------------------------------------|\n");
        printf("| 1. Adicionar nova palavra                                                    |\n");
        printf("| 2. Excluir palavra existente                                                 |\n");
        printf("| 0. Voltar ao menu anterior                                                   |\n");
        printf("+==============================================================================+\n");
        printf("| Escolha uma opcao:                                                           |\n");
        printf("+==============================================================================+\n");
        scanf(" %c", &opcao);
        limparBuffer();
    } while (opcao != '0');
}

void telaRanking() {
    char opcao;
    //FUNCAO QUE ABRE O MENU DE RANKING, PRESSIONANDO '0' VOCE E LEVADO DE VOLTA AO MENU PRINCIPAL (NOMES E MODO DE CONTAGEM DE PONTOS SAO UM EXEMPLO)
    //NOS MENUS DE RANKING E HISTORICO PREFERI NAO INSERIR O "LOGO DO JOGO"(O DESENHO DA FORCA)
    do {
        system("cls || clear");
        printf("+==============================================================================+\n");
        printf("|                                 -= RANKING =-                                |\n");
        printf("+==============================================================================+\n");
        printf("| Pos | Nome              | Pontos | Partidas | Vitorias                       |\n");
        printf("|-----|-------------------|--------|----------|--------------------------------|\n");
        printf("| 1   | Fulano            |  1500  |    10    |     8                          |\n");
        printf("| 2   | Beltrano          |  1350  |     9    |     7                          |\n");
        printf("| 3   | Ciclano           |  1200  |    11    |     6                          |\n");
        printf("+==============================================================================+\n");
        printf("| Escolha uma opcao:                                                           |\n");
        printf("+==============================================================================+\n");
        scanf(" %c", &opcao);
        limparBuffer();
    } while (opcao != '0');
}

void telaHistorico() {
    char opcao;
    //FUNCAO QUE ABRE O MENU DE PESQUISA DO HISTORICO (ESTAGIO INICIAL), COM AS OPCOES DE PESQUISA POR DATA, POR NOME DO PLAYER E POR ID DA PARTIDA, PRESSIONANDO '0' VOCE E LEVADO DE VOLTA AO MENU INICIAL/PRINCIPAL
    do {
        system("cls || clear");
        printf("+==============================================================================+\n");
        printf("|                               -= HISTORICO =-                                |\n");
        printf("+==============================================================================+\n");
        printf("| 1. Pesquisar por Data                                                        |\n");
        printf("| 2. Pesquisar por Nome do Jogador                                             |\n");
        printf("| 3. Pesquisar por ID da Partida                                               |\n");
        printf("| 0. Voltar ao menu anterior                                                   |\n");
        printf("+==============================================================================+\n");
        printf("| Escolha uma opcao:                                                           |\n");
        printf("+==============================================================================+\n");
        scanf(" %c", &opcao);
        limparBuffer();
    } while (opcao != '0');
}

// Função que imprime a cara do marciano
void marciano() 

{
    printf("+=================================================================================================================+\n");
    printf("|                                            -= OBRIGADO, MARCIANO! =-                                            |\n");
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
    printf("+=================================================================================================================+\n");
}