# Documentação: `interface.c`

Este arquivo é responsável por toda a lógica de exibição do jogo da forca, incluindo menus, mensagens de erro, feedback ao jogador, e telas para os modos singleplayer e multiplayer.

## Funções

### Utilitárias

- `void limparBuffer()`
  > Limpa o buffer de entrada para evitar comportamentos indesejados com `fgets()`.

- `void scanfFgets(char *text, int size)`
  > Lê entrada do usuário com `fgets()` e remove o caractere de nova linha ao final.

### Menus e Interfaces Gerais

- `void exibirMenuPrincipal()`
  > Exibe o menu inicial com opções como jogar, gerenciar palavras, ver ranking ou sair.

- `void inputErroEntrada(char *texto_do_erro)`
  > Exibe uma tela de erro genérica com uma mensagem personalizada.

- `void semHistorico(char *texto_do_erro)`
  > Exibe uma tela de erro específica para falhas ao acessar o histórico.

### Telas Singleplayer

- `int telaSingleplayer(char nome[], int TAM_NOME)`
  > Solicita o nome do jogador para o modo singleplayer. Retorna `1` para voltar ao menu e `0` para continuar.

- `void telaSingleplayerJogo(...)`
  > Exibe o estado atual do jogo singleplayer, com boneco, palavra parcialmente descoberta, letras tentadas, etc.

- `void telaResultadoJogo(...)`
  > Mostra a tela final do modo singleplayer (vitória ou derrota).

### Telas Multiplayer

- `int telaMultiplayer(char nomeA[], char nomeB[], int TAM_NOME)`
  > Solicita os nomes dos dois jogadores para o modo multiplayer. Retorna `1` para voltar ao menu e `0` para continuar.

- `void telaMultiplayerJogo(...)`
  > Exibe o estado atual do jogo multiplayer para o jogador da vez.

- `void telaResultadoJogoMultiplayer(...)`
  > Mostra a tela final do modo multiplayer (vitória ou derrota).

### Gerenciamento de Palavras

- `int confirmarAdicaoDePalavra()`
  > Confirma se o usuário deseja adicionar uma nova palavra.

- `void telaMenuGerenciarPalavras()`
  > Exibe o menu para gerenciamento de palavras (adicionar, listar, etc).

## Observações

- A maioria das funções neste arquivo foca em output formatado com arte ASCII.
- O layout do terminal é controlado com `system("cls || clear")` para compatibilidade entre Windows e Linux.
- Usa `Sleep()` para pausas temporais após mensagens.
- Utiliza várias variáveis globais para textos intermediários e formatação.

---

**Dependências:**
- `interface.h`
- `palavras.h`
- `historico.h`
- `ranking.h`
- `single-player.h`
- `multiplayer.h`

**Autor:** Projeto colaborativo - Jogo da Forca

**Localização do arquivo:** `src/interface.c`