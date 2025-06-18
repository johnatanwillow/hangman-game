# Documentação: `multiplayer.c`

Este arquivo implementa a lógica do modo Multiplayer do jogo da forca, incluindo o fluxo de jogo, controle de turno entre jogadores, avaliação de letras e palavras, pontuação e armazenamento no histórico/ranking.

## Funções

### `void multiPlayerJogo()`
Executa o loop principal do modo multiplayer:
- Inicializa dados dos jogadores
- Sorteia palavra e dica
- Alterna entre os jogadores a cada erro
- Exibe a interface gráfica a cada rodada
- Verifica acertos, erros, fim de jogo e calcula pontuação
- Salva resultado no histórico e ranking

## Variáveis e Recursos

- `MultiPlayer player`
  > Estrutura com dados dos dois jogadores, letras testadas, pontuação, erros e jogador atual.

- `char partes_do_corpo[6]`
  > Armazena partes do boneco enforcado para exibir graficamente os erros.

- `char errou_palavra[6] = {'0', '|', '/', '\\', '/', '\\'}`
  > Modelo usado para desenhar o boneco conforme os erros ocorrem.

- `char descoberta[]`
  > Vetor que guarda a palavra com os espaços preenchidos conforme o jogador acerta.

- `char letra[]`
  > Entrada do jogador: uma letra ou tentativa da palavra inteira.

## Fluxo do jogo

1. Chama `telaMultiplayer()` para capturar os nomes dos jogadores.
2. Inicia o jogo com palavra sorteada e dificuldade definida.
3. Em loop:
   - Mostra tela do jogo (`telaMultiplayerJogo`)
   - Processa entrada (`letra`)
   - Avalia:
     - Se letra está correta e não foi testada → atualiza acertos
     - Se letra errada e não testada → incrementa erros e troca de jogador
     - Se palavra inteira correta → vitoria
     - Se errada → erro
   - Atualiza boneco conforme `errou_palavra`
4. Ao fim:
   - Exibe tela de resultado (`telaResultadoJogoMultiplayer`)
   - Salva dados com `ranqueamento()` e `escreveHistorico()`

## Observações

- Usa `strchr`, `isalpha`, `strcmp` e outras funções de `string.h` e `ctype.h` para validação de entrada.
- Usa `Sleep()` para pausas entre eventos.
- Troca de jogador é feita com `player.atual = 1 - player.atual`.

---

**Dependências:**
- `palavras.h` (para sortear palavras)
- `interface.h` (telas)
- `ranking.h` (salvar pontuação)
- `historico.h` (registro de partida)
- `multiplayer.h`

**Autor:** Projeto colaborativo - Jogo da Forca

**Localização do arquivo:** `src/multiplayer.c`

