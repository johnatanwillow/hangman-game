
#pragma once

//---------------------------------------
void limparBuffer();
void scanfFgets(char *text, int size);
//---------------------------------------
void exibirMenuPrincipal();
void inputErroEntrada(char *texto_do_erro);
void inputErroLogicaUsuario(char *texto_do_erro, char *partes_do_corpo);
void telaResultadoJogo(char *partes_do_corpo, char *palavra, int acertos, int erros, char *letras_testadas, char *title, char *messenge, char *nome, int pontuacao);
void telaSingleplayerJogo(char *letra, char *dica, char *letras_testadas, char *descoberta, int acertos, int erros, int MAX_ERROS, int tamanho_palavra, char *partes_do_corpo, int TAM_PALAVRA);
int telaSingleplayer(char nome[], int TAM_NOME);
void telaMultiplayerJogo(char *jogador1, char *jogador2, char *letra);
void telaMultiplayer(char *jogador1, char *jogador2, char *letra);
void telaMenuGerenciarPalavras();
void telaAdiconarPalavra(char *text);
void telaRanking();
void telaHistorico();
void marciano();
//---------------------------------------