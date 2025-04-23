#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define TAM_NOME 50
#define MAX_TENTATIVAS 6

 //first version
 //introduzi funcoes e constantes e variaveis para deixar mais intuitivo o funcionamento das telas

void limparBuffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirMenuPrincipal() {
    //FUNCAO INICIAL QUE EXIBE MENU PRINCIPAL
    printf("+==============================================================================+\n");
    printf("|                          -= JOGO DA FORCA =-                                 |\n");
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
    printf("| Escolha uma opcao: ");
}

void telaSingleplayerJogo() {
    int erros = 3; // exemplo
    char palavra_oculta[] = "_ _ _ _ _";
    char letras_tentadas[] = "A, E, I";
    char letra;
    //FUNCAO QUE MOSTRA A TELA DE JOGO SINGLEPLAYER (PALAVRAS, TENTATIVAS RESTANTES E LETRAS TENTADAS SAO MERAMENTE ILUSTRATIVAS)

    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                          -= MODO SINGLEPLAYER =-                             |\n");
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
    printf("| Letras tentadas: %s                                                     |\n", letras_tentadas);
    printf("| Tentativas restantes: %d                                                      |\n", MAX_TENTATIVAS - erros);
    printf("|------------------------------------------------------------------------------|\n");
    printf("| Digite uma letra: ");
    scanf(" %c", &letra);
    limparBuffer();
    printf("| Voce digitou: %c\n", letra);
    getchar();
}

void telaSingleplayer() {
    char nome[TAM_NOME];
    //TELA QUE PEDE PRA INSIRIR O NOME DO JOGADOR NO MODO SOLO
    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                          -= MODO SINGLEPLAYER =-                             |\n");
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
    printf("| Digite seu nome: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    printf("| Bem-vindo, %s! Preparando o jogo...\n", nome);
    printf("+==============================================================================+\n");
    getchar();
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
        printf("|                            -= MODO MULTIPLAYER =-                            |\n");
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
        getchar();
    }
}

void telaMultiplayer() {
    char jogador1[TAM_NOME], jogador2[TAM_NOME];
    //ALGORITMO SEMELHANTE AO DO MODO SINGLEPLAYER, TODAVIA AGORA ADAPTADO PARA O MODO MULTIPLAYER
    system("cls || clear");
    printf("+==============================================================================+\n");
    printf("|                           -= MODO MULTIPLAYER =-                             |\n");
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
    fgets(jogador1, TAM_NOME, stdin);
    jogador1[strcspn(jogador1, "\n")] = '\0';
    printf("| Jogador 2, digite seu nome: ");
    fgets(jogador2, TAM_NOME, stdin);
    jogador2[strcspn(jogador2, "\n")] = '\0';
    printf("| Jogadores %s e %s, preparando o jogo...\n", jogador1, jogador2);
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
        printf("|                     -= GERENCIAMENTO DE PALAVRAS =-                          |\n");
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
        printf("| Escolha uma opcao: ");
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
        printf("| Digite 0 para sair: ");
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
        printf("|                             -= HISTORICO =-                                  |\n");
        printf("+==============================================================================+\n");
        printf("| 1. Pesquisar por Data                                                        |\n");
        printf("| 2. Pesquisar por Nome do Jogador                                             |\n");
        printf("| 3. Pesquisar por ID da Partida                                               |\n");
        printf("| 0. Voltar ao menu anterior                                                   |\n");
        printf("+==============================================================================+\n");
        printf("| Escolha uma opcao: ");
        scanf(" %c", &opcao);
        limparBuffer();
    } while (opcao != '0');
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    char opcao;

    do {
        system("cls || clear");
        exibirMenuPrincipal();
        scanf(" %c", &opcao);
        limparBuffer();

        switch (opcao) {
            case '1':
                telaSingleplayer();
                break;
            case '2':
                telaMultiplayer();
                break;
            case '3':
                menuGerenciarPalavras();
                break;
            case '4':
                telaRanking();
                break;
            case '5':
                telaHistorico();
                break;
            case '0':
                printf("Saindo do jogo...\n");
                system("cls || clear");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                getchar();
        }
    } while (opcao != '0');

    return 0;
}
