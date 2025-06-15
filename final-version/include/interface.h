#pragma once

//---------------------------------------
#include "single-player.h"
#include "multiplayer.h"
//---------------------------------------
void limparBuffer();
void scanfFgets(char *text, int size);
//---------------------------------------
void exibirMenuPrincipal();
void inputErroEntrada(char *texto_do_erro);
void inputErroLogicaUsuario(char *texto_do_erro, char *partes_do_corpo);
void telaResultadoJogo(SinglePlayer player, char *partes_do_corpo, char *palavra, char *title, char *messenge);
void telaSingleplayerJogo(SinglePlayer player, char *letra, char *dica, char *descoberta, int MAX_ERROS, int tamanho_palavra, char *partes_do_corpo, int TAM_PALAVRA, char *dificuldade);
int telaSingleplayer(char nome[], int TAM_NOME);
void telaMultiplayerJogo(MultiPlayer player, char *letra, char *dica, char *descoberta, int MAX_ERROS, int tamanho_palavra, char *partes_do_corpo, int TAM_PALAVRA, char *dificuldade, int playerAtivo);
int telaMultiplayer(char nomeA[], char nomeB[], int TAM_NOME);
void telaResultadoJogoMultiplayer(MultiPlayer player, char *partes_do_corpo, char *palavra, char *title, char *messenge);
void telaMenuGerenciarPalavras();
int confirmarAdicaoDePalavra();
void telaAdiconarPalavra(char *text);
void telaRanking();
void telaListarHistorico();
void telaHistoricoData();
void telaHistoricoID();
void telaHistoricoNome();
void formatacaoBonita();
void semHistorico(char *texto_do_erro);
void telaPesquisaHistorico(char *text);
void marciano();
//---------------------------------------